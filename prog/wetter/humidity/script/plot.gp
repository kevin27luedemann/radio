reset

set terminal pdf


set xdata time
set timefmt "%d.%m.%y %H:%M"
#set xrange ["28.05.16 00:00":"29.05.16 00:00"]
set format x "%d.%m\n%H:%M"
set timefmt "%d.%m.%y %H:%M:%S:"

set xlabel "Zeit"

#set yrange [10.0:70.0]

set output DATUM
set multiplot layout 2,1
p ".wetter.log" u 1:3 w l t "Temperatur [°C]"
p ".wetter.log" u 1:4 w l t "rel. Luftfeuchte [%]"
unset multiplot
set output
#pause -1
