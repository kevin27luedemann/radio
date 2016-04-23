#follow instructions on 
#http://rpihome.blogspot.de/2015/02/installing-pico-tts.html
#firts put
#deb http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi
#and
#deb-src http://mirror.ox.ac.uk/sites/archive.raspbian.org/archive/raspbian/ wheezy main contrib non-free rpi
#into the /etc/apt/sources.lits

if [ "$1" -eq "ok" ]; then
	apt-get update;
	apt-get install fakeroot debhelper automake autoconf libtool help2man libpopt-dev hardening-wrapper;
	mkdir pico_build;
	cd pico_build;
	apt-get source libttspico-utils;
	cd svox*;
	dpkg-buildpackage -rfakeroot -us -uc;
	cd ..;
	dpkg -i libttspico-data*;
	dpkg -i libttspico0_*;
	dpkg -i libttspico-utils;
	cd ..;
	rm -rf pico_build;
else
	cat /etc/apt/source.list
	cat /etc/apt/sources.list
fi
