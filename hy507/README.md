## 单步构建 linux sun50iw9p1
###1、构建 rootfs.ext4
	cd brandy/brandy-2.0/u-boot-2018/configs
	cp sun50iw9p1_longan_defconfig ../.config
	cd T507/longan
	./build.sh coreB ubuntu

###2、构建 u-boot	
	cd brandy/brandy-2.0/u-boot-2018/configs
	cp sun50iw9p1_nor_defconfig ../.config
	cd T507/longan
	./build.sh coreB bootloader

###3、构建 linux
	sudo apt install python3
	cd /usr/bin/
	ln ./python3 python
	./build.sh distclean
	cd kernel/linux-4.9/arch/arm64/configs
    	cp sun50iw9p1smp_longan_defconfig ../defconfig
    	vim ~/work/kernel/linux-4.9/scripts/dtc/dtc-lexer.lex.c
	extren xxxxx yylloc
	./build.sh clean
	./build.sh
