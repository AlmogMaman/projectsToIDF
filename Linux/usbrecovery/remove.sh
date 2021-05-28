#!/bin/sh
cd /
date=`date +%d-%m-%Y`
umount -l /media/$date
umount -f /media/$date
rmdir /media/$date
echo "" > currentUsb


