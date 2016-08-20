#!/bin/sh

rm -f /var/lib/connman/wifi.config

connmanctl tether wifi off
connmanctl scan wifi
service=$(connmanctl services | grep Panic1 | tr -s ' ' | cut -d ' ' -f 3)

cat << EOF > /var/lib/connman/wifi.config
[service_${service}]
Type = wifi
Security = wpa2
Name = <SSID>
Passphrase = <PASSWORD>
EOF

