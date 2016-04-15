#! /bin/bash
stunde=`date +"%H"`
minute=`date +"%M"`

if [ "$1" == "radio" ]; then
	mpc stop
fi

if [ $stunde -gt 4 ]; then
	if [ $stunde -le 9 ] ; then
		wget --directory-prefix=/home/$USER/ -q http://www.wetter.com/deutschland/stemmen/DE0010191.html
		text1="`cat /home/$USER/DE0010191.html | awk '/In Stemmen/ {print $0}' | head -1`"
		text=`echo ${text1:0:-6}`
		./sprich.sh "Guten Morgen. $text"
		rm -f /home/$USER/DE0010191.html
	fi
fi

if [ "$1" == "radio" ]; then
	mpc play
fi
