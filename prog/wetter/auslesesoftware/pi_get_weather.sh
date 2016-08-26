stty 9600 -F /dev/ttyAMA0
echo "da" > /dev/ttyAMA0
while read -r line < /dev/ttyAMA0; do
   datum=`date +'%d.%m.%Y %H:%M:%S'`
	echo $datum "\t" $line >> "/home/pi/.wetterstation.log"
	echo $datum "\t" $line > "/home/pi/.wetterstation_current.log"
	sleep 60
	echo "da" > /dev/ttyAMA0
done
