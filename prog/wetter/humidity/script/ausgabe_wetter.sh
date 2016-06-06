#!/bin/bash
# grundlegende Zeitvariablen
datum=`date +"%d.%m.%y"`

mv ~/.wetter.log ./

gnuplot -e "DATUM='/home/pi/Bilder/wetter/$datum.pdf'" plot.gp
mv .wetter.log /home/pi/Bilder/wetter/.$datum.log
