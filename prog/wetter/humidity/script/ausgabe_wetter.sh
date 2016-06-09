#!/bin/bash
# grundlegende Zeitvariablen
datum=`date +"%d.%m.%y"`

mv ~/.wetter.log ./

gnuplot -e "DATUM='/home/pi/Bilder/wetter/$datum.pdf'" /home/pi/projekt/radio/prog/wetter/humidity/script/plot.gp
mv .wetter.log /home/pi/Bilder/wetter/.$datum.log
