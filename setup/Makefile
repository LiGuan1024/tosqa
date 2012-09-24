TOSCA_DOWNLOADS = http://...

all:
	# type "make fresh" to set up from a fresh RPi image

fresh: adjust-hostname tosca-disk-mount create-users install-packages \
       install-tosca set-passwords 
	# installation complete, rebooting now ...
	#shutdown -r now

adjust-hostname:
	hostname toscapi
	sed -i s/raspberrypi/toscapi/ /etc/hostname
	sed -i s/raspberrypi/toscapi/ /etc/hosts

tosca-disk-mount:
	mkdir -p /toscadev
	echo "/dev/sda /toscadev ext4 defaults,noatime 0 0" >>/etc/fstab

create-users:
	useradd -m -G dialout,plugdev tosca
	useradd -m -G adm,staff,users -b /toscadev build
	echo "pi ALL=(ALL) NOPASSWD: ALL" >>/etc/sudoers

install-packages:
	apt-get install -y bison flex gperf texinfo gawk libtool automake m4 \
	                   libncurses5-dev cvs git

install-tosca:
	#wget $(TOSCA_DOWNLOADS)/tosca-home.tgz
	#tar -C /home tosca-home.tgz
	#wget $(TOSCA_DOWNLOADS)/tosca-tools.tgz
	#tar -C /usr/local tosca-tools.tgz

set-passwords:
	passwd tosca
	passwd build
