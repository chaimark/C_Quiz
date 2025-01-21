#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "WT_MQTT_JSON.h"
#include "StrLib.h"
#include "NetProt_Module.h"
#include "NumberBaseLib.h"
#include "JsonDataDoneLib.h"
#include "JsonDataAnalyzeLib.h"
#include "../Src/RTC.h"
#include "../Src/Define.h"
#include "../Src/AT24C0256.h"
#include "../Interflow/NetProt_Module.h"
#include "../Interflow/AT24CXXDataLoader.h"

WTData WT_DATA = {
    .Sing = 0xB2,
    .PATH_PUB = "weitai/yasite/02345678903/pub",
    .PATH_SUB = "weitai/yasite/02345678903/sub",
    .UserName = "ql",
    .PassWord = "admin",
};

static char SendJsonBuff[512] = {0};
// AT+QMTPUBEX=0,0,2,0,"hy/gw/set/02345678903",Len
bool WT_JSON_Send_Meter_Data(void) {
    memset(SendJsonBuff, 0, sizeof(SendJsonBuff));
    strnew JsonDataStr = NEW_NAME(SendJsonBuff);
    struct _Wifi_ArgumentData {
        JsonItem ClassP;
        JsonItem Name;                  // Name
        struct _List {                  // List
            JsonItem ListP;
            JsonItem MeterID;           // 设备编码
            JsonItem RoomTemperature;   // 室内温度
            JsonItem NowTime;           // 数据采集时间
        }List[24];
    } Wifi_ArgumentData;

    newJsonList JsonStrObj = NEW_JSON_LIST(&JsonStrObj);

    char ArrayID[9] = {0};
    HEX2ToASCII((char *)AT24CXX_Manager_NET.MeterID, 4, ArrayID, 8);

    JsonStrObj.setJsonItemData(&JsonStrObj, &Wifi_ArgumentData.Name, "Name:%s;%d", "rtc_hour", 0);
    JsonStrObj.setJsonItemData(&JsonStrObj, &Wifi_ArgumentData.ClassP, "list:%p;%d", &Wifi_ArgumentData.ClassP, 0);
    if (Meter_Manager.DataCount == 0) {
        SaveDevData();
    }
    #warning(需要考虑 DataCount == 24 时传输 buff 是否会溢出, 是否需要分包);
    double Clock_InsideT = 0;
    for (int i = 0; (i < 3 && i < Meter_Manager.DataCount); i++) {
        Clock_InsideT = Meter_Manager.MeterTemperature[(Meter_Manager.DataStartHour + i) % 24].RoomTemperature;
        JsonStrObj.setJsonItemData(&JsonStrObj, &Wifi_ArgumentData.List[i].ListP, ":%lp;%d", &Wifi_ArgumentData.List[i].ListP, 1);
        JsonStrObj.setJsonItemData(&JsonStrObj, &Wifi_ArgumentData.List[i].MeterID, "J91:%s;%d", ArrayID, 2); // J91  设备编码
        JsonStrObj.setJsonItemData(&JsonStrObj, &Wifi_ArgumentData.List[i].RoomTemperature, "S3:%f;%d", Clock_InsideT, 2); // S3   室内温度
        JsonStrObj.setJsonItemData(&JsonStrObj, &Wifi_ArgumentData.List[i].NowTime, "S66:%s;%d", Meter_Manager.MeterTemperature[i].CollectionTime, 2); // S66  数据采集时间
    }
    JsonStrObj.OutPushJsonString(JsonDataStr, &JsonStrObj);
    char SendCmd[60] = {0};
    memcpy(SendCmd, "AT+QMTPUBEX=0,0,2,0,\"", strlen("AT+QMTPUBEX=0,0,2,0,\""));
    catString(SendCmd, WT_DATA.PATH_PUB, ARR_SIZE(SendCmd), strlen(WT_DATA.PATH_PUB));
    int SendCmdLen = catString(SendCmd, "\",", ARR_SIZE(SendCmd), strlen("\","));
    sprintf(&SendCmd[SendCmdLen], "%d", strlen(JsonDataStr.Name._char));
    catString(SendCmd, "\r\n", ARR_SIZE(SendJsonBuff), strlen("\r\n"));
    sendDataByTTLProt(SendCmd, strlen(SendCmd));
    IncludeDelayMs(200);
    if (!copyDataForUART()) {
        return false;
    }
    if (strstr(Now_NetDevParameter.NetDataBuff, ">") == NULL) {
        return false;
    }
    sendDataByTTLProt(SendJsonBuff, strlen(SendJsonBuff));
    IncludeDelayMs(200);
    if (!copyDataForUART()) {
        return false;
    }
    for (int i = 0; i < 2; i++) {
        if (FindStr_WaitTime(NEW_NAME("+QMTPUBEX:"), 1000) == false) {   // 模组是否回复
            ClearNetDataBuff();
            continue;
        }
        for (int i = 0; (i < 3 && Meter_Manager.DataCount > 0); i++) {
            Meter_Manager.DeleteQueue(&Meter_Manager);  // delete queue
        }
        return true;
    }
    return false;
}
// 处理 WT的JSON 指令
bool WT_MQTT_JSON_Analysis(void) {
    char ArrayID[8] = {0};
    HEX2ToASCII((char *)AT24CXX_Manager_NET.MeterID, 4, ArrayID, 8);
    strnew JsonStr = NEW_NAME(Now_NetDevParameter.NetDataBuff);
    JsonObject JsonObjOfUserCmd = newJsonObjectByString(JsonStr);
    newString(TempStr, 100);
    newString(IDStr, 100);
    JsonObject DevStrObj = JsonObjOfUserCmd.getObject(&JsonObjOfUserCmd, "dev", TempStr);
    if (DevStrObj.getInt(&DevStrObj, "msg_id") == 81) {
        DevStrObj.getString(&DevStrObj, "id", IDStr);
        if (memcmp(IDStr.Name._char, ArrayID, ARR_SIZE(ArrayID)) != 0) {
            return false;
        }
    }
    memset(TempStr.Name._char, 0, TempStr.MaxLen);
    JsonObject dataStrObj = JsonObjOfUserCmd.getObject(&JsonObjOfUserCmd, "data", TempStr);
    strnew TempIP = NEW_NAME(AT24CXX_Manager_NET.NET_Remote_Url);
    newString(TempProt, 100);
    dataStrObj.getString(&dataStrObj, "ip", TempIP);
    dataStrObj.getString(&dataStrObj, "prot", TempProt);
    AT24CXX_Manager_NET.NET_Remote_Port = atoi(TempProt.Name._char);
    return true;
}

///*****************************************///
unsigned int getBaseAddr(void) {
    return EEPROM_OTHER_ADDRESS;
}
unsigned char EEprom_WT_Parameter_Init(bool isWriteFlag) {
    unsigned int EEPROM_BASE_ADDRESS = getBaseAddr();
    unsigned char ret = 0;
    int len = sizeof(WT_DATA);
    unsigned char * p = (unsigned char *)(&WT_DATA);
    if ((EEprom_Byte1Read(EEPROM_BASE_ADDRESS) != WT_DATA.Sing) || (isWriteFlag)) {
        for (int i = 1; i < len; i++) {
            ret = EEprom_Byte1Write(i + EEPROM_BASE_ADDRESS, p[i]);
            if (ret == 0) {
                return ret;
            }
        }
        ret = EEprom_Byte1Write(EEPROM_BASE_ADDRESS, p[0]);
        if (ret == 0) {
            return ret;
        }
    } else {
        for (int i = 1; i < len; i++) {
            p[i] = EEprom_Byte1Read(EEPROM_BASE_ADDRESS + i);
        }
    }
    return 0;
}
// 写参数
unsigned char WT_EEprom_Write(unsigned char * data, unsigned char len) {
    unsigned int EEPROM_BASE_ADDRESS = getBaseAddr();
    int addr = (int)data - (int)(&WT_DATA); // 数据地址
    return EEprom_Write_Start(data, EEPROM_BASE_ADDRESS + addr, len);
}



