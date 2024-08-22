#ifndef AT24XXXDATALOADER_H
#define AT24XXXDATALOADER_H

#include "All.h"
/*
电信 Band5
移动 Band8
联通 Band3
*/

// 需要引入外部 AT24CXX_MANAGER_S 定义
#include <stdbool.h>
#ifndef __AT24C0256_H
typedef struct AT24CXX_MANAGER_S {
    // 32字节
    char sign;		   // 初始化标志
    char gw_id[6];	   // 设备地址
    char username[10]; // 登录
    char password[15];

    // 32*6 = 192 字节
    char heating_start[15];
    char heating_end[15];
    char NET_Local_IMEI[15];
    char NET_Local_IP[30];
    char NET_Local_MASK[30];
    char NET_Local_GATEWAY[30];
    char NET_4G_Remote_Url[42];
    int NET_4G_Remote_Port;

    short int main_interval;
    short int copy_interval;
    short int copy_statistics;
    unsigned int not_intimer_interval;
    unsigned char Save_Working_Mode;

    char MQTTCheckENableFlag; // MQTT 使能标志
    char TCPCheckENableFlag;  // TCP 查询使能标志

    char porjectId[20];
    char productkey[20];
} AT24CXX_MANAGER_T;

#endif

// public
typedef struct _GetNBData {
    char NB_DEV_IMEI[20];
    char NB_DEV_SNR;
    char NB_DEV_CSQ;
    char NB_DEV_RSRP;
    char NB_DEV_RSRQ;
    char NB_SIM_BAND;
    char NB_SIM_ICCID[20];
    char NB_SIM_IMSI[20];
    char NB_Socket_Num;
} GetNBData_T;

extern AT24CXX_MANAGER_T * _AT24CXX_Manager_NET;
#define AT24CXX_Manager_NET (*_AT24CXX_Manager_NET)
extern GetNBData_T GetNBData;  // NB数据

extern void AT24CXXLoader_Init(void);

#endif
