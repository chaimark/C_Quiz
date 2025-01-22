#ifndef _WT_MQTT_JSON_H
#define _WT_MQTT_JSON_H

#include "StrLib.h"

typedef struct _WTData {
    char Sing;              // 初始化标志
    char PATH_SUB[40];     // 订阅主题
    char PATH_PUB[40];     // 发布主题
    char UserName[20];     // 用户名
    char PassWord[20];     // 密码
}WTData;
extern WTData WT_DATA;

extern bool WT_JSON_Send_Meter_Data(void);             // 组织上报仪表数据
extern bool WT_MQTT_JSON_Analysis(void);

extern unsigned char EEprom_WT_Parameter_Init(bool isWriteFlag);   // 初始化参数
extern unsigned char WT_EEprom_Write(unsigned char * data, unsigned char len); // 写入参数
#endif



