#!/bin/bash
cd 
. ~/esp/esp-idf/export.sh
cd ~/sensor-dev
#idf.py set-target esp32c6
idf.py build
idf.py -p /dev/ttyACM0 flash monitor
#use ctrl+] to exit monitoring
