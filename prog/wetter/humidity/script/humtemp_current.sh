#!/bin/bash
# grundlegende Zeitvariablen
datum=`date +"%d.%m.%y %H:%M:%S"`
 
GPIO=7
INPUT=$(sudo /home/pi/.lol_dht22/loldht $GPIO | grep "Temperature")
echo $INPUT
HUM=$(echo $INPUT|cut -d " " -f3)
TEMP=$(echo $INPUT|cut -d " " -f7)

echo ${HUM:0:4}
echo ${TEMP:0:4}


#echo -e "$datum\t$TEMP\t$HUM" >> /home/pi/.wetter.log ;
echo -e "$TEMP#$HUM#" > /home/pi/.wetter.status ;
echo -e "${datum}\t${TEMP:0:4}\t${TEMP:0:4}\t${HUM:0:4}\t${HUM:0:4}\t0000.0" > "/home/pi/.wetterstation_current.log"
