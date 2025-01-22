#ifndef __PUBLICLIB_NO_ONE_H
#define __PUBLICLIB_NO_ONE_H

// #define OPEN_AT_CMD_DEBUG
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
// #include "fm33le0xx_fl.h"
// #include "../Src/Define.h"
#include "WT_MQTT_JSON.h"

#define IncludeDelayMs FL_DelayMs
#define WIFI_BUFF_MAXLEN 1024   // 接收缓存空间
#define ONCE_PACKAGE_LEN 1000   // http分块发送的单块size

// #define IMSI_liantong
// #define IMSI_dianxing

#ifdef IMSI_liantong
// 联通
#define IMSI_BAND 3
#elif defined IMSI_dianxing
// 电信
#define IMSI_BAND 5
#else
// 移动
#define IMSI_BAND 8
#endif

#define ATCMD_MAXNUMBER 29
#define AT24CXX_Manager_NET (*_AT24CXX_Manager_NET)

#define _Module_UserSend 60   // 最大不能超过 255
#define _Module_AutoSend 61   // 最大不能超过 255

extern void IPstrToHexArray(strnew IpHex, const char * Ipstr);
extern unsigned char get_CheckSum(unsigned char data[], int length);
// #define TimeSpeedNum 37 // 设置 1 秒等价与 TimeSpeetNum 秒
#ifdef TimeSpeedNum
extern void TimeSpeed(void);
#endif
#endif

