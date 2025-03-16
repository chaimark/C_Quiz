## 单步构建 linux
###1、构建 rootfs.ext4
	cd T507/longan
	./build.sh coreB ubuntu

###2、构建 u-boot
	cd T507/longan/brany/brany2.0/u-boot-2018/configs
	cp xxxx_defconfig ../.config
	make ARCH=arm64 CROSSCOMPILE=aarch64-linux-gnu- menuconfig
	make

###3、构建 linux
	sudo apt install python3
	cd /usr/bin/
	ln ./python3 python
	./build.sh coreB Image
