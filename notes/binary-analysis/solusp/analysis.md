# solusp — Authorization Key & IPC Analysis

**Binary:** `firmware/apps_decrypted/solusp` (575 KB, MIPS32 LE, dynamically linked, C++ symbols present)  
**Role:** OTA orchestration, AI camera/lidar management, WebSocket server, Klipper bridge

---

## IPC Architecture (Shared Memory)

solusp uses **POSIX shared memory + semaphores** for inter-daemon IPC (not Unix domain sockets).

### `hs_ipcshm_get` @ `0x004123a4` — shared memory client
```c
hs_ipcshm_get(char *name, unsigned int size, void **ptr):
    fd = shm_open(name, O_RDWR, 0666)   // open shared mem object
    ptr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)
    return ptr
```

### Semaphore functions
- `hs_ipcsem_post` @ `0x00412200` — signal semaphore (V operation)
- `hs_ipcsem_wait` @ `0x00412224` — wait on semaphore (P operation) with timeout
- `hs_ipcsem_get` @ `0x0041239c` — get semaphore handle by name
- `hs_ipcsem_nowait` @ `0x00412358` — non-blocking semaphore check

### Socket path format
solusp CLI args: `--systemPath=/etc/app` (default).  
Observed socket pattern: `%s/comms/%s.sock` → `/etc/app/comms/<service>.sock`  
This may be for a separate socket-based IPC layer in addition to shared memory.

---

## Klipper Bridge: `wsKlipper` class

solusp maintains a WebSocket connection to Klipper via `/tmp/klippy_uds`.

| Symbol | Address | Notes |
|--------|---------|-------|
| `wsKlipper::init_connect` | `0x0043847c` | Connect to Klipper UDS |
| `wsKlipper::reconnect` | `0x00438540` | Reconnect on disconnect |
| `wsKlipper::sendCode` | `0x00439f48` | Send G-code command |
| `wsKlipper::moveCode` | `0x0043abf4` | XYZ move command |
| `wsKlipper::sendGcodeFile` | `0x0043b6f8` | Submit gcode file path |
| `wsKlipper::getInstance` | `0x0040b56c` | Singleton accessor |

**Attack surface**: solusp has direct access to Klipper for all printer motion commands. Any code injection into solusp = full printer control.

---

## Authorization Code Scheme

### Actors
- **`ObbrecLidar`** class — depth camera/lidar (serial-connected AI sensor hardware)
- `CMD_GET_AUTHORIZE_CODE` — command to request the auth key from the lidar
- `CMD_SET_AUTHORIZE_CODE` — command to push the auth key back to the system

### Key derivation: `ObbrecLidar::get_authorize_key` @ `0x0043db04` (2552 bytes)

```c
// 1. Check: internal data buffer must be ≥ 17 bytes
if (data_buf_end - data_buf_start < 17) {
    log(0xce, "get_authorize_key failed, receive data size is not 17.");
    return -8;
}

// 2. Copy buffer
dest = malloc(buf_len);
memmove(dest, data_buf, buf_len);

// 3. Negate bytes at offsets 7..14 (inclusive)
for (p = dest+7; p < dest+15; p++) {
    *p = -*p;
}

// 4. Construct std::string from dest+11 onward
str = std::string(dest + 11);

// 5. Compute MD5 of that string
MD5(str, strlen, md5_out_buf[16]);

// 6. Format as hex using ostringstream, store in output vector
// Output: MD5 hex string → output param_1 vector<uint8_t>
```

**The 17-byte serial frame from ObbrecLidar hardware:**
- bytes 0-6: header/metadata
- bytes 7-14: 8 bytes negated (likely checksum or key bytes)
- bytes 11-16: 6 bytes used as MD5 input string
- The authorization key is the MD5 (16 bytes) of specific sensor data bytes

**This authorization key is for the ObbrecLidar AI sensor only** — NOT related to root access.

### Error paths
- `"Failed to get authorize key."` — ObbrecLidar hardware not responding
- `"Failed to send CMD_SET_AUTHORIZE_CODE."` — IPC send failure

---

## OTA Command Surface

| Command | Description | Risk |
|---------|-------------|------|
| `CMD_ENTER_OTA_UPGRADE_MODE` | Begin OTA mode | Puts printer in upgrade state |
| `CMD_SET_OTA_FILE_INFO` | Set update package metadata | Must be followed by transfer |
| `CMD_TRANSFER_OTA_FILE` | Transfer update package bytes | Data write to upgrade dir |
| `CMD_ONE_KEY_RECOVERY` | Factory reset | **DESTRUCTIVE** — wipes /usr/data |
| `CMD_GET_AUTHORIZE_CODE` | Read ObbrecLidar auth key | Sensor auth, not root |
| `CMD_SET_AUTHORIZE_CODE` | Write auth key to system | Sensor auth, not root |

**`CMD_ONE_KEY_RECOVERY` attack surface:** If solusp's WebSocket command interface is accessible on LAN without auth, triggering factory reset could brick the printer's user data. Verify if the WebSocket server binds only to localhost or to all interfaces.

---

## WebSocket server (libwebsockets)

solusp links `libwebsockets.so.19` and serves a WebSocket endpoint. The `klipper_ip` arg (`/tmp/klippy_uds`) suggests the WS server bridges to Klipper. Commands arrive over this WS interface and get dispatched to the CMD_ handler table.

**Port/bind address:** Not identified from strings alone. Use `ss -tlnp` on rooted device to find solusp's listening ports.

---

## Ghidra Analysis Artifacts

- `notes/binary-analysis/solusp/ghidra-functions.txt` — 1428 functions
- `notes/binary-analysis/solusp/ghidra-decompiled.c` — 30 security-relevant functions decompiled
