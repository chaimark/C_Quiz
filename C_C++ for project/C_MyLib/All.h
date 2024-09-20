#ifndef __ALL_H
#define __ALL_H

//#define OPEN_AT_CMD_DEBUG 255

// #include "main.h"
// #include "AT24C0256.h"
// #include "Define.h"
// #include "Uart.h"
// #include "RTC.h"
// #include "AT24C0256.h"
// #include "MQTT_JSON.h"
// #include "Gpio.h"
// #include "WT_MQTT_JSON.h"

#define IncludeDelayMs FL_DelayMs
// #define WIFI_BUFF_MAXLEN 1024                                  // 接收缓存空间
// #define ONCE_PACKAGE_LEN 1000                                  // http分块发送的单块size
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

#endif

