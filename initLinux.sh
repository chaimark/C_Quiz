#!/bin/bash
sudo apt update
sudo apt upgrade
sudo apt install git
sudo apt install gcc
mkdir /home/leige/git_room
mkdir /home/leige/myBin
mkdir /home/leige/work
mkdir /home/leige/outputClass
mkdir /home/leige/zipClass
cd /home/leige/git_room
git config --global user.name chai21sks
git config --global user.email 3046476712@qq.com
echo please open your youtbe.cmd and enter any key to continue
read -n 1 -s
git clone https://github.com/chaimark/C_Quiz.git
git clone https://github.com/chaimark/Linux_C_Project.git
cd /home/leige/git_room/Linux_C_Project
echo please open your youtbe.cmd again and enter any key to continue
read -n 1 -s
git config --global --unset http.proxy
git config --global --unset https.proxy
cd /home/leige/git_room/Linux_C_Project
gcc AddPath.c -o /home/leige/myBin/AddPath
cd /home/leige/myBin
sudo chmod 765 AddPath
mkdir /home/leige/work/rootfs
cd /home/leige/work/rootfs
mkdir bin dev etc opt home lib mnt proc sbin sys tmp usr var
mkdir usr/bin usr/lib usr/sbin lib/modules usr/src
cd ./dev
sudo mknod -m 666 console c 5 1
sudo mknod -m 666 null c 1 3
sudo apt-get install u-boot-tools
sudo apt-get install module-*
sudo apt-get install libncurses5-dev
sudo apt-get install ncurses-dev    
sudo apt-get install libpcap-dev 
apt-get install lib32stdc++6
sudo apt-get install build-essential
sudo apt-get install lib32z1
sudo apt-get install libc6-i386
sudo apt-get install qemu-user-static
sudo apt-get update
sudo apt-get upgrade
cd /home/leige/outputClass
dd if=/dev/zero of=/home/leige/outputClass/rootfs.img bs=1M count=512
mkfs.ext3 /home/leige/outputClass/rootfs.img
resize2fs -M /home/leige/outputClass/rootfs.img
sudo mkdir /mnt/tempPoint
sudo mount -o loop /home/leige/outputClass/rootfs.img /mnt/tempPoint
cd /home/leige/myBin
echo export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/opt/TuxamitoSoftToolchains/arm-arm1176jzfssf-linux-gnueabi/gcc-4.6.4/lib >> ~/.bashrc
./AddPath $(pwd)
./AddPath -show
echo please Add arm-linux-gcc path of lib and bin



