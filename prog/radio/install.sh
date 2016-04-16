#!/bin/sh
# erstellen der fure das Radio wichtigen Programme und kopieren der Recourcen
make;
mv main radio;
mkdir -p /usr/bin/piradio/;
cp -p ./ress/*.jpg /usr/bin/piradio/;
cp -p ./ress/*.png /usr/bin/piradio/;
cp radio /usr/bin/;
mkdir -p /tmp/piradio/
chmod 777 /tmp/piradio/
echo "test radio" > /tmp/piradio/stat.txt;
chmod 777 /tmp/piradio/stat.txt;

# kopieren der notwendigen scripte
mkdir -p /usr/scripte/
cp -p ../TTS/pico/sprich.sh /usr/scripte/
chmod 555 /usr/scripte/sprich.sh
cp -P ../TTS/pico/wetter.sh /usr/scripte/
chmod 555 /usr/scripte/wetter.sh
#radio
