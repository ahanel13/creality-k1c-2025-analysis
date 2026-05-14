#!/bin/sh

log() {
    printf "$(date): $1\n" >> /tmp/wifi_watchdog.log
}

while true; do
    sleep 30

    state=$(wpa_cli -i wlan0 status 2>/dev/null | grep "^wpa_state=" | cut -d= -f2)

    if [ "$state" != "COMPLETED" ]; then
        log "disconnected (state=$state), reassociating"
        wpa_cli -i wlan0 reassociate 2>/dev/null

        i=0
        while [ $i -lt 30 ]; do
            sleep 1
            state=$(wpa_cli -i wlan0 status 2>/dev/null | grep "^wpa_state=" | cut -d= -f2)
            [ "$state" = "COMPLETED" ] && break
            i=$((i + 1))
        done

        if [ "$state" = "COMPLETED" ]; then
            log "reconnected, renewing DHCP"
            kill -USR1 $(pidof udhcpc) 2>/dev/null
        else
            log "reconnect failed after 30s"
        fi
    fi
done
