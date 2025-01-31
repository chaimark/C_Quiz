# 该文件夹下是关于如何使用6410学习Linux的步骤

01、学习Linux常用的shell命令<br>
02、学习编写shell脚本<br>
03、学习编写简单的Makefile<br>
04、简单了解6410开发板的硬件设备<br>
05、在电脑上安装合适的传口驱动, 为烧录和与6410通信做准备<br>

# 学习log

## 2024.4-2024.5

    建议学习（数据结构、计算机组成原理、操作系统和计算机网络）
    下载 wsl_update_x64.msi 运行
    在 windows中 安装 Ubuntu, 学习使用 Linux 的安装命令
    注意: wsl --unregister ubuntu2204 可以重装 wsl
    注意: ubuntu2204 config --default-user leige (可以设置默认登录用户为 leige)
    使用: adduser 添加用户, passwd 添加密码
    使用: groups root 查看 root 用户的用户组
    使用: usermod -aG sudo leige 添加 sudo 权限
    cat /etc/passwd 查看 leige 用户是否创建
    cat /etc/group
    查看 leige 用户是否创建
    移出某用户组: deluser leige root
    新建某用户组 groupadd XXX
    删除某个用户组 groupdel XXX

## 2024.5-2024.8

    看视频教程了解 Linux 中的命令
    使用 Ubuntu 作为日常使用, 并记录用到的所有命令
    创建桌面快捷键 .desktop 文件, 并使用命令 ln -s 创建快捷链接
    学习了解常用命令{
        chown -R leige:leige /home/leige (修改文件所有者)
        ls      mkdir   chmod       passwd      adduser     deluser
        gcc     vim     touch       ifconfig    ping        dd
        tar     rm      su          grep        find        apt
        read    file    mknod       mount       mkfs        ubinze  
        ps      du      sed         crontab
    }
    学习编写shell脚本, 编写了简单的脚本, 并成功运行《自动打开梯子访问 github》
    在 MOOC 上找相关课程, 了解 Linux 的整体结构{
        了解 Liunx 的系统结构, 用户空间, 系统空间, 权限系统
        了解 ll 显示的权限属性
    }
    学习如何使用 gcc 编译程序{
        gcc AddPat.c -o AddPath
    }
    学习如何使用 gdb 调试程序
    学习如何使用 make 编译程序
    学习如何制作开发库, 学习如何使用 gcc 连接库文件 .a 和 .so
    简单学习 Makefile, 编写了简单的Makefile, 并成功运行编译 hello world

## 2024.8-2024.9

    开发 AddPath 命令并将其加入Linux 的 /bin 目录作为全局命令{
        实现使用 AddPath 可以将某路径快速加入全局变量中（实现: 添加 删除 查看）
    } 
    学习 git , 并使用 git 管理自己的项目{
        记忆: git add -A
        记忆: git commit -m "XXX"
        记忆: git status
        记忆: git push
        其他命令存档写入某文件, 方便查阅
    }
    了解正则表达式
    购买开发板, 了解如何烧录程序
    了解并安装开发板卖方提供的交叉编译器, 可能需要安装某些扩展库或其他支持
    在 windows 的 Linux 子系统上安装交叉编译链   
    安装 sudo tar -zxvf arm-linux-gcc -C /
    解压的arm-linux-gcc 目录下有 bin 和 lib 目录, 将 bin 目录添加到 PATH 中
    AddPath /opt/xxxx/bin & lib 加到 .bashrc 中
    export LD_LIBRARY_PATH=/opt....../lib 加到 .bashrc 中
    配置全局 PATH 修改:{ 
        etc/environment; 
        /home/username/.bashrc;
        /home/username/.bash_profile;
    }
    安装 32 位支持库:{
        apt-get install lib32stdc++6 暗转32 位支持库
        sudo apt-get install build-essential
        sudo apt-get install lib32z1
        sudo apt-get install libc6-i386
        sudo apt-get install qemu-user-static
        sudo apt-get update
        sudo apt-get upgrade
        wsl 可能需要增加 Liunx 原生头文件{
            将下面的命令用 root 用户编写shell脚本后放入 Init.d 文件夹
            sudo update-binfmts --install i386 /usr/bin/qemu-i386-static --magic '\x7fELF\x01\x01\x01\x03\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x03\x00\x01\x00\x00\x00' --mask '\xff\xff\xff\xff\xff\xff\xff\xfc\xff\xff\xff\xff\xff\xff\xff\xff\xf8\xff\xff\xff\xff\xff\xff\xff'
            sudo apt-get update
            sudo apt-get upgrade
        }
    }
    在上位机使用 ifconfig 查询IP, 并安装 tftp 服务器, 并配置 tftp 服务器 与 NFS 服务器{
        sudo apt-get install tftp-hpa  
        sudo apt-get install tftp
        sudo apt install nfs-kernel-server
        sudo apt-get install nfs
        sudo vim /etc/exports{             # 设置 nfs 共享目录
            /srv/nfs4/rootfs   192.168.10.0/24(rw,sync,no_root_squash,no_subtree_check)
        }
        sudo vim /etc/default/tftpd-hpa     # 设置 tftp 共享目录
    }

## 2024.9-2024.12

    使用chown
    编译官方 uboot.bin :{
        tar -vzxf 解压官方提供的 u—boot 压缩包
        进入目录, 使用 vim 打开 Makefile, 搜索目标 “*6140*” 并复制目标
        然后退出vim, 并在当前目录 配置 make 工具:{
            make ARCH=arm CROSS_COMPLE=arm-linux- mini6410_nand256_config
            然后使用 make ARCH=arm CROSS_COMPILE=arm-linux- 编译 uboot.bin 
        }
    }
    设置 bootloader 环境变量{
        help 查看uboot 的帮助信息
        printenv 查看uboot 的环境变量
        setenv ipaddr 192.168.3.219         // 开发板IP
        setenv serverip 192.168.3.170       // 主机IP
        setenv gatewayip 192.168.3.1        // 网关IP
        setenv netmask 255.255.255.0        // 子网掩码
        setenv ethaddr 00:0c:29:8f:6a:5b    // MAC 地址
        setenv loadaddr 0xc0008000          // 下载地址  
        setenv bootargs root=/dev/nfs nfsroot=192.168.3.170:/srv/nfs4/rootfs/,proto=tcp rw ip=192.168.3.219:192.168.3.170 console=ttySAC0,115200 init=/linuxrc lcd=S70
        setenv bootcmd{                    // boot 启动后的自动命令
            setenv bootcmd nand read 0xXXXXXX 0xXXXXXXX 0xXXXXXX; nand read 0xXXXXXX 0xXXXXXX 0xXXXXX; bootm 0xXXXX
            setenv bootcmd tftp 0xc0008000 zImage; tftp 0xXXXXXXX 文件系统; bootm 0xc0008000
        }
        saveenv 保存环境变量
    }
    制作根文件系统:{
        在 /home/leige 下创建 rootfs 目录 并 cd 到 rootfs
        mkdir bin dev etc opt home lib mnt proc sbin sys tmp usr var
        mkdir usr/bin usr/lib usr/sbin lib/modules usr/src
        cd ./dev
        mknod -m 666 console c 5 1
        mknod -m 666 null c 1 3
        mknod -m 666 tty2 c 1 3
        lib 库{
            为保证链接库能用直接用友善之臂的根文件系统 root_qtopia 中的链接库lib 目录 
            使用:
                sudo cp -r ........../lib/*so* ~/work/rootfs/lib/ -d
                sudo cp -r ........../lib/*.a ~/work/rootfs/lib/ -d
                特例: 找到 ld-linux-armhf.so.3 链接指向的源文件，并以 ld-linux-armhf.so.的名字 复制到 rootfs 中
            用同样的方法 复制编译器目录的所有 lib 文件
            /opt/TuxamitoSoftToolchains/arm-arm1176jzfssf-linux-gnueabi/gcc-4.6.4/arm-arm1176jzfssf-linux-gnueabi/lib32
            /opt/TuxamitoSoftToolchains/arm-arm1176jzfssf-linux-gnueabi/gcc-4.6.4/arm-arm1176jzfssf-linux-gnueabi/lib64
            /opt/TuxamitoSoftToolchains/arm-arm1176jzfssf-linux-gnueabi/gcc-4.6.4/arm-arm1176jzfssf-linux-gnueabi/lib
        }
        复制 busybox 的 etc 结构{
            sudo cp -rfa /home/leige/busybox-1.17.2/examples/bootfloppy/etc/* ~/rootfs/etc/
        }
        进入 busybox 目录, 编译 busybox{
            make menuconfig ARCH=arm CROSS_COMPILE=arm-linux-{
                选择 Build busybox as a static binary (静态链接库)
                选择 Don't use /usr (避免安装到 usr 目录) 
                选择 Busybox install.. /home/leige/work/rootfs
                选择 vi-style line editing commands
            }
            如果编译时提示 loginutils/passwd.o' failed: 则需要在 include/libbb.h 中添加 #include <sys/resource.h>
            make ARCH=arm CROSS_COMPILE=arm-linux- install
        }
        进入 linux 内核目录, 编译内核模块{
            sudo apt-get install module-init-tools
            make ARCH=arm CROSS_COMPILE=arm-linux- menuconfig
            make modules ARCH=arm CROSS_COMPILE=arm-linux-
            make modules_install ARCH=arm CROSS_COMPILE=arm-linux- INSTALL_MOD_PATH=/home/leige/work/rootfs
        }
        回到内核目录, make menuconfig ARCH=arm CROSS_COMPILE=arm-linux- 配置内核支持的文件系统{
            选择 Initial RAM filesystem and RAM disk support
        }
        cd ....rootfs/
        ln -s bin/busybox init
    }
    编译官方内核:{
        sudo apt-get install u-boot-tools 安装 uImage 生成工具
        tar -vzxf 解压官方提供的 linux 压缩包
        进入 arch/arm/configs 目录,  找到对应开发板的config文件, 复制到 linux 目录下
        make menuconfig ARCH=arm 配置 make 工具
        安装对应的支持库{
            sudo apt-get install libncurses5-dev
            sudo apt-get install ncurses-dev    
            sudo apt-get install libpcap-dev       
        }
        make menuconfig ARCH=arm CROSS_COMPILE=arm-linux- 配置内核
        make uImage ARCH=arm CROSS_COMPILE=arm-linux- 编译内核（）
    }
    准备 通用的 SD 卡启动盘:{
        通过分区工具将 SD 卡分为两个区, 一个无格式分区(前256M), 一个 FAT32 分区(其他正常空间)
        sudo fdisk -l 查询SD卡分区信息
        使用 sudo dd 命令将 uboot.bin 烧写到 SD 卡, 并避开前 512 字节（分区表信息） 
    }
    准备 友善之臂的 SD 卡启动盘:{
        6410 提供的 superboot 有两种启动方式, 一种是从 SD 卡启动, 一种是从 NAND 启动
        将 SD 卡中的 images/FriendlyoARM.ini 文件中的 USB-Mode = yes 改成 USB-Mode = no, 则与普通 uboot.bin SD卡启动一致, 否则开发板将处于 USB 下载模式, 需要配合友善之臂提供的下载工具烧写 uboot.bin 到nand flasH 中运行。
        制作 SD 卡启动只需要使用友善提供的软件直接将 superboot 制作成启动盘
    }

## 2024.12-2025.1

    从SD卡或NAND启动 uboot.bin{
        从 eMMC 启动内核{ 
            //eMMC 就是 NAND flash
            使用 uboot 的命令查看 NAND flash 或 SD 卡中的存放的 uImage 和 根文件系统
            使用 uboot 的命令将 (官方的 uImage 和 根文件系统) 下载到 DDR 中
            然后使用 bootz/bootm 命令启动内核
        }
        从 net 启动内核{
            ifconfig 获取主机IP
            在uboot 中 ping 主机IP, 确保网络畅通
            在uboot 中 使用 tftp 将主机中 (官方的 uImage 和 根文件系统) 下载到 DDR 中
            然后使用 bootz/bootm 命令启动内核
        }
    }
    使用 NFS 作为文件系统{
        重新配置 Linux 内核 make menuconfig ARCH=arm CROSS_COMPILE=arm-linux- 
        取消掉 Initial RAM filesystem and RAM disk support
        选择 Network File System
        选择 NFS client support
        选择 rootfs over NFS
        重新编译内核
        setenv serverip 192.168.3.170       # NFS 服务器的 IP 地址
        setenv ipaddr 192.168.3.219         # 设备的 IP 地址
        setenv gatewayip 192.168.3.1        # 网关
        setenv netmask 255.255.255.0        # 子网掩码
        setenv bootargs 'root=/dev/nfs nfsroot=192.168.3.170:/srv/nfs4/rootfs/,proto=tcp rw ip=192.168.3.219:192.168.3.170:192.168.3.1:255.255.255.0 console=ttySAC0,115200 init=/linuxrc lcd=S70'  # 内核启动参数
        在 uboot 中使用 bootm/bootz 命令启动内核
        如果 uboot 任然找不到 nfs 文件系统, 请关闭防火墙再试 
    }
    将 NFS 制作成ubi{
        setUbifs /srv/nfs4/rootfs
    }
    制作设备树文件{
        
    }
    使用tftp 下载内核和根文件系统{
        根据编译后的大小, 确定需要 copy 到 RAM内存中的地址
        然后使用 bootz/bootm 命令启动内核和文件系统, 进入 Linux
    }
    进入 Linux 后, 使用 XXXXXX 将开发版挂载到ubuntu上{
        在上位机上开发, 然后将程序copy到挂载的位置
    }

## 还未执行

    学习如何制作 uImage 配置内核
    学习如何制作 busybox 配置文件
    学习如何制作 uboot Makefile 的配置目标
    学习如何开发 Linux 环境下的设备驱动
    学习如何使用 insmod 加载驱动
    学习如何使用 rmmod 卸载驱动
    学习如何使用 lsmod 查看驱动
    学习如何开发 ARM Linux 环境下的应用程序

## 常用命令

    了解 tar, 打包文件夹成文件
    了解 gzip, 压缩文件
    了解 gunzip, 解压文件
    了解 zip, 压缩文件
    了解 unzip, 解压文件

## 需要安装的环境和工具

### wsl 第一个addLeige.sh

### ubuntu 中修改文件夹所有者 change_chownUser.sh

### ubuntn 初始化 linux 开发环境 initLinux.sh

### 制作 ubi 文件系统 setUbifs.sh
