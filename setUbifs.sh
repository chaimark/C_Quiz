#!/bin/bash
sudo apt-get install mtd-utils > /dev/null

#创建文件系统镜像
read -p "文件系统的大小(512M):" FLASH_SIZE_MB
read -p "页面大小(4k):" PageSize
read -p "可擦除块的大小(256k):" DeakSize 

/home/leige/myBin/imgtoubi ${FLASH_SIZE_MB} ${PageSize} ${DeakSize} $1 /home/leige/outputClass/rootfs.img

DEV_FLASH_IMG="rootfs.ubi"    # 模拟的闪存设备文件
UBI_CFG="dev_flash.cfg"          # UBI 配置文件

# 创建 UBI 配置文件
cat > ${UBI_CFG} <<EOF
[ubi]
mode=ubi
image=/home/leige/outputClass/rootfs.img
vol_id=0
vol_type=dynamic
vol_name=rootfs
vol_alignment=1MiB
vol_size=${FLASH_SIZE_MB}MiB
EOF

# 将 UBI 卷映像加载到设备
ubinize -o ${DEV_FLASH_IMG} -m $((PageSize * 1024)) -p ${DeakSize}KiB ${UBI_CFG}

rm -rf ${UBI_CFG}
rm -rf /home/leige/outputClass/rootfs.img

# 完成，退出
exit 0

