#!/bin/sh
make;
mv main radio;
mkdir -p /usr/bin/piradio/;
cp -p *.jpg /usr/bin/piradio/;
cp -p *.png /usr/bin/piradio/;
cp radio /usr/bin/;
mkdir -p /tmp/piradio/
chmod 777 /tmp/piradio/
echo "test radio" > /tmp/piradio/stat.txt;
chmod 777 /tmp/piradio/stat.txt;
#radio
