#! /bin/bash

sprache="de-DE"
tempfile="/tmp/sprich.wav"

text="$1"

pico2wave -l=${sprache} -w=${tempfile} "`echo ${text}`"
aplay ${tempfile} 2> /dev/null
rm -f ${tempfile}
