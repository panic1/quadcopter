#!/bin/sh

rm -f /var/lib/connman/wifi.config
connmanctl tether wifi on
