# vectorp — Root Access Control Analysis

**Binary:** `firmware/apps_decrypted/vectorp` (3.2 MB, MIPS32 LE, dynamically linked, symbols present)  
**Role:** Main UI daemon (LVGL-based touchscreen), MQTT client, root agreement handler

---

## Root Access Mechanism — Complete Picture

### What vectorp does (UI layer only)

1. Shows multi-language root disclaimer (6 languages in string table)
2. `page_guide_privacypolicy_create_agree` → renders the disclaimer page
3. `chk_agree_event_handler` @ `0x004ae0bc` — checkbox handler: stores agree state at `odin+5504`, calls `save_systemconfig`
4. `btn_continue_agree_cb` @ `0x004c2b94` — "Agree" button: unconditionally writes `odin+5504 = 1`, saves config, closes dialog

**Config persistence:** Config written to `/creality/gui/config/system_config.json` via `save_systemconfig` @ `0x0057859c`

### What vectorp does NOT do

- Does NOT call `/dev/sc` for root enabling (ioctl calls are all networking/framebuffer — codes 0x8913/0x8927/0x8915/0x891b)
- Does NOT have the permission file download URL as a plaintext string
- Does NOT write `/usr/data/permission` — no such path reference found

### Conclusion: Root grant is externally mediated

The disclaimer UI is a **stub** — it saves a flag to JSON config and nothing else. The actual root unlock happens via `seed.sh` at boot:
- `check_login_permission()` reads `/usr/data/permission`
- Verifies with `cmd_sc -v` (RSA+eFuse)
- If MAC matches and "root" present: `sed 's/^!root/root/'` on `/tmp/shadow`

The permission file for K1C 2025 would have come from Creality's cloud (likely via MQTT or an API endpoint not present in the binary). **Creality removed this endpoint**, making the UI non-functional for root grant.

---

## Key Internals

### Global singleton: `getodin()` → Odin struct

The `getodin()` function returns a global state/config struct used throughout vectorp.

| Offset | Field | Notes |
|--------|-------|-------|
| +4792 | system config section base | used as `addiu a0,v0,4792` in save calls |
| +5504 | `agree_root` flag | 1 = user accepted disclaimer |
| +9988 | extruder PID state | 1/2/3 values in `extruder_pid_state_update_observer_cb` |
| +0x2714 | access state | 0=idle, 3=printing, 4=other |
| +44 | UI element ptr | used in `btn_continue_agree_cb` |

### Shell command execution: `popencmd` / `popencmd.part.0`

`popencmd(cmd, buf, size)` → `popen(cmd, "r")`, reads one line, strips newline.  
Shell commands confirmed in vectorp:
- `mkdir -p /usr/data/creality/debug` — debug dir creation
- `rm -f /usr/data/printer_data/logs/*.7z` — log cleanup  
- `md5sum /usr/apps/usr/bin/vectorp > /tmp/vectorp.md5` — self-integrity check
- `cat /etc/version` — firmware version read
- `compress_all_system_logs` — system log archival

No root-enable shell commands found.

### MQTT endpoints (vectorp is MQTT client)

- **Brokers:** `mqtt.crealitycloud.cn:1883`, `mqtt.crealitycloud.com:1883`, `pre-tb-iot.crealitycloud.com:1883`
- **Topics (publish):** `cx_machine.system_info`, `cx_machine.proc_stats`
- **Topics (subscribe):** `cx_printer.objects.subscribe`, `printer/objects/subscribe`
- **REST API endpoints:**
  - `/api/cxy/v2/device/registerDevice`
  - `/api/cxy/v2/firmware/list`
  - `%s/api/cxy/v2/device/user/getAliyunSts` — Alibaba OSS credentials
  - `%s/api/cxy/v2/device/user/onwerInfo` — device owner binding
  - `%s/api/cxy/v2/device/user/submitLogFile`

No root permission API endpoint present as plaintext.

### Expert mode page

`page_settings_system_expertmode_create` @ `0x004c6240` — creates UI widget container only.  
Constructor at `0x004c5c2c` renders settings for PID tuning, zoffset, etc. **No root toggle switch found in expert mode.**

### Access token (nexusp API)

`cbGetAccessOneShotToken` @ `0x00499254` — retrieves a 36-byte oneshot token (UUID-style).  
`cgi_GetAccessOneShotToken` @ `0x0049f424` — HTTP handler for `/api/cxy/v2/device/user/onwerInfo`.

---

## Attack Surface

| Surface | Finding |
|---------|---------|
| Root UI bypass | Editing `system_config.json` to set `agree_root=1` does nothing actionable without the cloud permission file |
| Permission file forge | Place SCBT-format file at `/usr/data/permission` with MAC addr + "root" in plaintext; requires patched soc_security.ko to pass `cmd_sc -v` |
| SSH key auth | **Current approach already works** — S999persistence installs authorized_keys; SSH key auth bypasses locked shadow password entirely |
| MQTT intercept | Potential: intercept MQTT traffic to inject a permission-file-download message; requires MITM on mqtt.crealitycloud.cn |

---

## Ghidra Analysis Artifacts

- `notes/binary-analysis/vectorp/ghidra-functions.txt` — 5412 functions
- `notes/binary-analysis/vectorp/ghidra-decompiled.c` — 323 security-relevant functions decompiled
