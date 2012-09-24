TOSCA_DOWNLOADS = http://...

all:
	# type "make fresh" to set up from a fresh RPi image

fresh: adjust-hostname tosca-disk-mount create-users install-packages \
       install-tosca autorun-tosca set-passwords 
	# installation complete, rebooting now ...
	shutdown -r now

adjust-hostname:
	hostname toscapi
	sed -i s/raspberrypi/toscapi/ /etc/hostname
	sed -i s/raspberrypi/toscapi/ /etc/hosts

tosca-disk-mount:
	mkdir -p /media/TOSCAUSB
	echo "/dev/disk/by-label/TOSCAUSB /media/TOSCAUSB vfat defaults,noatime 0 0" >>/etc/fstab
	echo "/media/TOSCAUSB/tosca-build.img /home/build ext4 defaults,noatime 0 0" >>/etc/fstab

create-users:
	useradd -m -G dialout,plugdev tosca
	useradd -m -G adm,staff,users build
	echo "build ALL=(ALL) NOPASSWD: ALL" >>/etc/sudoers

install-packages:
	apt-get update
	apt-get install -y bison flex gperf texinfo gawk libtool automake m4 \
	                   libncurses5-dev cvs git rsync mtools tmux screen \
	                   nodejs nginx libzmq-dev libuuid1 luajit luarocks

install-tosca:
	#wget $(TOSCA_DOWNLOADS)/tosca-home.tgz
	#tar xfz tosca-home.tgz -C /home
	#wget $(TOSCA_DOWNLOADS)/tosca-tools.tgz
	#tar xfz tosca-tools.tgz -C /usr/local

autorun-tosca:
	echo '@reboot if [ -x bin/onboot ]; then bin/onboot; fi' | crontab -u tosca -

set-passwords:
	passwd tosca
	passwd build
