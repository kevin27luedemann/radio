#! /bin/bash

# pruefe ob das Radio die Anfrage geschickt hat
if [ "$1" == "radio" ]; then
	mpc stop
fi

# grundlegende Zeitvariablen
stunde=`date +"%H"`
minute=`date +"%M"`
heute=`date +"%e.%b.%Y"`
#stunde=5
#minute=16
uhrzeit="$stunde:$minute"

# viele Begruessungen und ansagen per Zufall
zufallszahl=$RANDOM
let "zufallszahl %= 100"
unkorreliertezufallszahl=$RANDOM
let "unkorreliertezufallszahl %= 100"

#Begrussungsvariable
if [ $stunde -le 11 ]; then
	if [ $zufallszahl -le 50 ]; then
		begruessung="Guten Morgen."
	elif [ $zufallszahl -le 75 ]; then
		begruessung="Moin Moin."
	else
		begruessung="Moin."
	fi
elif [ $stunde -le 17 ]; then
	if [ $zufallszahl -le 80 ]; then
		begruessung="Guten Tag."
	else 
		begruessung="Gudden Dach."
	fi
else
	if [ $zufallszahl -le 80 ]; then
		begruessung="Guten Abend."
	else
		begruessung="NAbend."
	fi
fi

# Ausgabe des Datums
if [ $stunde -le 12 ]; then
	datumstext="Wir haben heute den $heute ."
else
	datumstext=""
fi

# Ausgabe de Uhrzeit
if [ $stunde -le 4 ]; then
	uhrzeittext="Es ist noch viel zu früh zum Radio hören"
elif [ $stunde -le 22 ]; then
	if [ $stunde -eq 19 ]; then
		let "diff = 60 -$minute"
		uhrzeittext="Es ist jetzt $uhrzeit und es sind noch $diff Minuten bis zur Tagesschau."
	elif [ $stunde -eq 20 ] && [ $minute -le 15 ]; then	
		uhrzeittext="Es ist jetzt $uhrzeit und die Tagesschau läuft gerade."
	else
		uhrzeittext="Es ist jetzt $uhrzeit ."
	fi
else
	uhrzeittext="Es ist viel zu spät zum Radio hören"
fi

# Wetterdaten aus der URL holen und
if [ $stunde -ge 5 ] && [ $stunde -le 9 ] && [ $unkorreliertezufallszahl -lt 99 ] && [ $unkorreliertezufallszahl -ge 1 ]; then
	wget --directory-prefix=/tmp/ -q http://www.wetter.com/deutschland/goettingen/weende/DE0003197029.html
	wettertext="`cat /tmp/DE0003197029.html | awk '/In Weende/ {print $0}' | head -1`"
	rm -f /tmp/DE0010191.html
	wettertext=`echo Das Wetter: ${wettertext:1:-6}`
fi

# Sonderkommentar in seltenen Faellen
if [ $stunde -eq 6 ] && [ $minute -le 15 ] && [ $zufallszahl -le 20 ]; then
	sonderkommentar="Guten Appetit."
elif ([ $stunde -eq 18 ] || [ $stunde -eq 19 ]) && [ $zufallszahl -le 5 ]; then
	sonderkommentar="Guten Appetit."
elif [ $stunde -eq 5 ] && [ $zufallszahl -ge 90 ]; then
	sonderkommentar="Bitte wecke die Katzen nicht schon wieder"
fi

# Ausgabe des Textes
/usr/scripte/sprich.sh "$begruessung $datumstext $uhrzeittext $wettertext $sonderkommentar"

# pruefen ob die Anfrage vom Radio gesendet wurde
if [ "$1" == "radio" ]; then
	mpc play
fi

