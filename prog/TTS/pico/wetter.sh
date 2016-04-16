#! /bin/bash
stunde=`date +"%H"`
minute=`date +"%M"`

if [ "$1" == "radio" ]; then
	mpc stop
fi

if [ $stunde -ge 5 ]; then
	if [ $stunde -le 9 ] ; then
		wget --directory-prefix=/tmp/ -q http://www.wetter.com/deutschland/stemmen/DE0010191.html
		text1="`cat /tmp/DE0010191.html | awk '/In Stemmen/ {print $0}' | head -1`"
		text=`echo ${text1:0:-6}`
		/usr/scripte/sprich.sh "Guten Morgen. $text"
		rm -f /tmp/DE0010191.html
	fi
fi

if [ "$1" == "radio" ]; then
	mpc play
fi
