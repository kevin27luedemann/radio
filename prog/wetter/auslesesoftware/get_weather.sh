stty 9600 -F /dev/ttyUSB0
echo "da" > /dev/ttyUSB0
while read -r line < /dev/ttyUSB0; do
   datum=`date +'%d.%m.%Y %H:%M:%S'`
	echo -e $datum "\t" $line >> "/home/luedemann/.wetterstation.log"
	echo $datum "\t" $line > "/home/luedemann/.wetterstation_current.log"
	sleep 20
	echo "da" > /dev/ttyUSB0
done
