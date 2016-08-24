stty 9600 -F /dev/ttyUSB0
echo "da" > /dev/ttyUSB0
while read -r line < /dev/ttyUSB0; do
   datum=`date +'%d.%m.%Y %H:%M:%S'`
	echo -e $datum "\t" $line >> "/home/pi/.wetterstation.log"
	echo -e $datum "\t" $line > "/home/pi/.wetterstation_current.log"
	sleep 20
	echo "da" > /dev/ttyUSB0
done
