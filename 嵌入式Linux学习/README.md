# 该文件夹下是关于如何使用6410学习Linux的步骤
01、学习Linux常用的shell命令<br>
02、学习编写shell脚本<br>
03、学习编写简单的Makefile<br>
04、简单了解6410开发板的硬件设备<br>
05、在电脑上安装合适的传口驱动，为烧录和与6410通信做准备<br>

# 学习log
## 2024.4-2024.8
    安装 Ubuntu20.04 LTS，学习使用 Linux 的安装命令
    看视频教程了解 Linux 中的命令
    使用 Ubuntu 作为日常使用，并记录用到的所有命令
    创建桌面快捷键 .desktop 文件，并使用命令 ln -s 创建快捷方式
    学习了解常用命令    
    学习编写shell脚本，编写了简单的脚本，并成功运行《自动打开梯子访问 github》
    记录自己常用的命令
    在 MOOC 上找相关课程，了解 Linux 的整体结构
    了解 Liunx 的系统结构，用户空间，系统空间，权限系统
    简单学习（数据结构、计算机组成原理、操作系统和计算机网络）
    学习如何使用 gcc 编译程序
    学习如何使用 gdb 调试程序
    学习如何使用 make 编译程序
    学习如何制作开发库，学习如何使用 gcc 连接库文件
    简单学习 Makefile，编写了简单的Makefile，并成功运行
## 2024.8-2024.9
    开发 AddPath 并将其加入Linux 的 /bin 目录作为全局命令 
    学习 git ，并使用 git 管理 自己的项目
    了解正则表达式
    购买开发板，了解如何烧录程序
    了解并安装开发板卖方提供的交叉编译器，可能需要安装某些扩展库或其他支持
    简单了解交叉编译工具集合 {
        readeif
        size
        nm
        strip
        strings
        objdump
        objcopy
        add2line
    }
    在 windows 的 Linux 子系统上重新安装交叉编译链
    安装 sudo tar -zxvf arm-linux-gcc -C /
    下载 wsl_update_x64.msi 运行
    sudo apt-get install build-essential
    gcc AddPat.c -o AddPath
    配置全局 PATH 修改:{ 
        etc/environment; 
        /home/username/.bashrc; 
        /home/username/.bash_profile;
    }
    安装 32 位支持库:{
        sudo apt-get install lib32z1
        sudo apt-get install libc6-i386
        sudo apt-get install qemu-user-static
        sudo apt-get update
        sudo apt-get upgrade
        增加 Liunx 原生头文件
        sudo update-binfmts --install i386 /usr/bin/qemu-i386-static --magic '\x7fELF\x01\x01\x01\x03\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x03\x00\x01\x00\x00\x00' --mask '\xff\xff\xff\xff\xff\xff\xff\xfc\xff\xff\xff\xff\xff\xff\xff\xff\xf8\xff\xff\xff\xff\xff\xff\xff'
        sudo apt-get update
        sudo apt-get upgrade
    }
## 2024.9-2024.
    配置内核:{
        sudo apt-get install libncurses5-dev
        sudo apt-get install ncurses-dev
        make menuconfig ARCH=arm
    }
    编译内核:{
        make uImage ARCH=arm CROSS_COMPILE=arm-linux-
    }
## 还未执行
    学习如何使用交叉编译器编译程序
    学习如何使用 menuconfig 配置内核,并使用 zImage 编译内核
    学习如何使用 busybox 配置根文件系统
    学习如何使用 mkfs 创建文件系统
    学习如何制作自己的 bootloader
    学习如何烧录bootloader, zImage, 根文件系统到开发板
    学习如何使用 mtools 挂载文件系统
    学习如何使用 mount 挂载文件系统
    学习如何使用 umount 卸载文件系统
    学习如何使用 chroot 
    学习如何开发 Linux 环境下的设备驱动
    学习如何使用 insmod 加载驱动
    学习如何使用 rmmod 卸载驱动
    学习如何使用 lsmod 查看驱动
    学习如何开发 ARM Linux 环境下的应用程序

#### 常用命令
    了解 cd 命令， 切换目录
    了解 ls 命令，查看文件和文件夹
    了解 pwd，查看当前目录
    了解 mkdir，创建文件夹
    了解 touch，创建文件
    了解 rm，删除文件
    了解 rmdir，删除文件夹
    了解 cp，复制文件
    了解 mv，移动文件，重名了文件
    了解 cat，查看文件内容
    简单了解 vim，编辑文本
    了解 grep ，搜索文件内容
    了解 find，搜索文件
    了解 tar，压缩文件
    了解 gzip，压缩文件
    了解 gunzip，解压文件
    了解 zip，压缩文件
    了解 unzip，解压文件
    了解 chmod，修改文件权限
    了解 ps ，查看进程
