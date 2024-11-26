#ifndef __ALL_H
#define __ALL_H

//#define OPEN_AT_CMD_DEBUG
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

#define IncludeDelayMs FL_DelayMs
#define WIFI_BUFF_MAXLEN 1024   // 接收缓存空间
#define ONCE_PACKAGE_LEN 1000   // http分块发送的单块size
#define IMSI_liantong
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


#define ATCMD_MAXNUMBER 19
#define AT24CXX_Manager_NET (*_AT24CXX_Manager_NET)

#endif

