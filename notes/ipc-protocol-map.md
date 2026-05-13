# Inter-Daemon IPC Protocol Map

## Architecture Overview

All 8 app daemons run as processes launched from `/usr/apps/etc/init.d/` init scripts.  
They communicate via two mechanisms:

1. **POSIX Shared Memory + Semaphores** — main high-bandwidth IPC
2. **Unix Domain Sockets** — possible secondary channel (socket path: `/etc/app/comms/<name>.sock`)
3. **Named Pipes** — alchemistp uses `/tmp/alchemistp_*pipe` (Go process)

---

## Daemon Map

| Binary | Role | Key External Connections |
|--------|------|-------------------------|
| `vectorp` | UI (LVGL), MQTT client | MQTT brokers at crealitycloud.cn:1883 |
| `alchemistp` | Camera, print file mgmt (Go, stripped) | Cloud IP 58.48.202.36, `/tmp/alchemistp_*pipe` |
| `nexusp` | File API, SQLite, API tokens | Local HTTP API |
| `solusp` | OTA, AI camera bridge, Klipper bridge | `/tmp/klippy_uds`, libwebsockets WS server |
| `quintusp` | OTA command dispatcher, camera ctrl | Talks to solusp via IPC |
| `onyxp` | WebRTC signaling + media | WebRTC cloud: `api.crealitycloud.cn`, `admin-pre.crealitycloud.cn` |
| `thirteenthp` | DTLS/SRTP RTP streams | WebRTC media transport |
| `mdns` | mDNS/Bonjour service advertisement | UDP broadcast |

---

## Shared Memory IPC (`hs_ipc*` functions in solusp)

**Implementation:** `shm_open()` + `mmap()` for data exchange, `sem_post/wait` for synchronization.

```c
hs_ipcshm_get(char *name, unsigned int size, void **ptr)
// Opens POSIX shared mem object by name, maps it, stores pointer in *ptr
// name is the shared memory key (e.g. "/solusp_cmd_shm" — not confirmed)
```

Confirmed functions:
- `hs_ipcsem_get(name)` → get semaphore handle
- `hs_ipcsem_post(sem_t*)` → signal (non-blocking)
- `hs_ipcsem_wait(sem_t*, timeout)` → wait (blocking with timeout)
- `hs_ipcsem_nowait(sem_t*)` → non-blocking check

The shared memory NAMES are not visible as plaintext strings in the binaries (likely assembled at runtime from the `systemPath` arg). On the device, `ls /dev/shm/` from root shell would reveal all active shared memory objects.

---

## Named Pipes / FIFOs

| Path | Owner | Purpose |
|------|-------|---------|
| `/tmp/alchemistp_*pipe` | alchemistp | Go runtime IPC for alchemistp sub-goroutines |
| `/tmp/uvc_fifo` | quintusp/solusp | UVC camera raw frame FIFO |

---

## Unix Domain Sockets

| Path | Owner | Purpose |
|------|-------|---------|
| `/tmp/klippy_uds` | Klipper (external) | wsKlipper in solusp connects here |
| `/tmp/h264_uds_chassis` | solusp/thirteenthp | H.264 video stream (chassis camera) |
| `/tmp/h264_uds_nozzle` | solusp/thirteenthp | H.264 video stream (nozzle camera) |
| `/etc/app/comms/*.sock` | solusp (inferred) | Service command sockets (pattern from strings) |
| `/tmp/wpa_ctrl_%d-%d` | wpa_supplicant | WiFi control socket |

---

## Command Dispatch Protocol (CMD_* identifiers)

Used between solusp ↔ quintusp ↔ other daemons via shared memory:

```
CMD_ENTER_OTA_UPGRADE_MODE    — begin OTA session
CMD_SET_OTA_FILE_INFO         — metadata for incoming OTA package
CMD_TRANSFER_OTA_FILE         — bulk OTA data transfer
CMD_ONE_KEY_RECOVERY          — factory reset (destructive)
CMD_GET_AUTHORIZE_CODE        — read ObbrecLidar hardware auth key
CMD_SET_AUTHORIZE_CODE        — write auth key to system
CMD_GET_CLOUD_FRAME           — request video frame for cloud
CMD_GET_CLOUD_MODE            — cloud streaming mode query
CMD_GET_MODULE_STATUS         — AI module health check
CMD_GET_SOFTWARE_VERSION      — firmware version report
CMD_OPEN_STREAM / CMD_CLOSE_STREAM  — video stream control
CMD_GET_IR_IMAGE / CMD_SNAP_IR_IMAGE — IR camera capture
CMD_LASER_SWITCH / CMD_LED_SWITCH   — hardware I/O
CMD_MODULE_SELF_TEST          — AI module self-test
CMD_ONE_KEY_RECOVERY          — factory reset
```

---

## Message Format (inferred)

The CMD_* identifiers suggest an enum-based command table. Based on the shared memory architecture, likely format:

```
struct ipc_message {
    uint32_t cmd_id;       // one of CMD_* values
    uint32_t session_id;   // or transaction ID
    uint32_t payload_len;
    uint8_t  payload[...]; // command-specific data
};
```

Exact format requires live debugging or kernel tracing (`strace -e trace=shm_open,mmap`) on the rooted device.

---

## Root Access via IPC

**None of the IPC commands are root-related.** The root access mechanism in `seed.sh` happens before any of these daemons are started. The daemons run as unprivileged processes.

Root shell access is controlled entirely by:
1. `/usr/data/permission` file + `cmd_sc -v` verification (handled by `seed.sh` at boot)
2. SSH authorized_keys (S999persistence writes to root's authorized_keys)
3. dropbear SSH daemon (S50dropbear init script)

---

## Device → Cloud Protocol Summary

```
[vectorp] ──MQTT publish──→ mqtt.crealitycloud.cn:1883  (system_info, proc_stats)
[vectorp] ──HTTPS──────────→ api.crealitycloud.cn       (device register, owner info)
[vectorp] ──HTTPS──────────→ api.crealitycloud.com      (firmware list, OTA info)
[onyxp]   ──WSS────────────→ admin-pre.crealitycloud.cn (WebRTC signaling)
[onyxp]   ──WSS────────────→ api.crealitycloud.cn       (WebRTC signal push)
[vectorp] ──HTTPS──────────→ aliyun OSS                 (log upload, timelapse upload)
[alchemistp]──HTTP─────────→ 58.48.202.36               (hardcoded IP — undocumented)
```
