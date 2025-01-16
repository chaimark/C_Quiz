sudo apt update
sudo apt upgrade
sudo apt install git -y
sudo apt install gcc -y
mkdir /home/leige/git_room
mkdir /home/leige/myBin
mkdir /home/leige/work
mkdir /home/leige/outputClass
mkdir /home/leige/zipClass
cd /home/leige/git_room
git config --global user.name chai21sks
git config --global user.email chai21sks@gmail.com
echo please open your youtbe.cmd and enter any key to continue
read -n 1 -s
git clone https://github.com/chaimark/C_Quiz.git
git clone https://github.com/chaimark/Linux_C_Project.git
cd /home/leige/git_room/Linux_C_Project
echo please open your youtbe.cmd again and enter any key to continue
read -n 1 -s
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
sudo apt-get install module-* -y
sudo apt-get install net-tools -y
sudo apt-get install tftp-hpa tftp-server tftp -y
sudo apt-get install nfs* -y
sudo apt-get install nfs -y
sudo apt-get install ncurses-dev -y
sudo apt-get install libpcap-dev -y
sudo apt-get install lib32z1 -y
sudo apt-get install libc6-i386 -y
sudo apt-get install qemu-user-static -y
sudo apt-get install zlib1g-dev unzip lib32stdc++6 lib32stdc++6-4.8-dbg build-essential libncurses5 libncurses5-dev u-boot-tools traceroute -y
sudo apt-get install mtd-utils -y
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


