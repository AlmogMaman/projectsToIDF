#!/usr/bin/env bash

export XAUTHORITY=%s/.Xauthority
export DISPLAY=:0
export DBUS_SESSTION_BUS_ADDRESS="unix:path=/run/user/%d/bus"

{
notify-send -t 10000 -u normal 'USB Detected' 'starting to create snapshot\nPlease do not remove the device'
echo '1 ' >> debug
sleep 10s
} &