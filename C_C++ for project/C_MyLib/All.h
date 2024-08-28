#ifndef __ALL_H
#define __ALL_H

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

