#!/usr/bin/env bash

export XAUTHORITY=/home/magshimim/.Xauthority
export DISPLAY=:0
export DBUS_SESSTION_BUS_ADDRESS="unix:path=/run/user/1000/bus"

{
notify-send -t 10000 -u normal 'USB Detected' 'starting to create snapshot\nPlease do not remove the device'
echo $1 > debug
echo $ID_VENDOR_ID > currentUsb
SERVER=root@192.168.1.23:
date=`date +%d-%m-%Y`
mkdir /media/$date
mount -t auto -o rw,noauto,async,dirsync,noexec,nodev,noatime $1 /media/$date
rsync -ab /media/$date $SERVER/home/Backups/$ID_VENDOR_ID; notify-send 'snapshot' 'Backup uploaded to cloud'
sleep 10s
} &
