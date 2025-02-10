#include "ColorShowTask.h"
#include "JsonDataDoneLib.h"
#include "NumberBaseLib.h"
#ifdef _COLORSHOW_H

#define HourTaskOfColorShowTime MinToSec(60)
#define MinTaskOfColorShowTime MinToSec(5)

// #define HourTaskOfColorShowTime (60)
// #define MinTaskOfColorShowTime (5)

ColorDisPlayOfMainDev ColorShowData = {
    .IsStartHeat = false,
    .HourData = {
        .InWaterTemp = 71.0,    // ℃
        .OutWaterTemp = 72.0,   // ℃
        .SumEnergy = 1234,      // GJ
        .SumFlow = 1235,        // m³
    },
    .MinData = {
        .FlowSpeed = 13.1       // m³/h
    }
};

void sendDataByRS4852(char * SendCmd, int SendCmdLen) {
    LPUart0Send((unsigned char *)SendCmd, SendCmdLen);
}

void initTaskOfColorShowTask(void) {
    RTC_TASK.InitSetTimeTask(HourTaskOfColorShow, HourTaskOfColorShowTime, hourTaskOfColorShowTask);
    RTC_TASK.InitSetTimeTask(MinTaskOfColorShow, MinTaskOfColorShowTime, minTaskOfColorShowTask);
    return;
}
void saveMeterDataMainDev(char InputData[], int InputDataLen) {
    char * TempP = strchr((char *)InputData, 0x68);
    InputDataLen -= TempP - InputData;
    int64_t TempNum = 0;
    newstrobj(IN_Str, 1);
    newString(TempString, 30);
    if ((TempP[1] == 0x20) && (TempP[58] == 0x16)) {
        if ((TempP[9] != 0x81) || (TempP[10] != 0x2E) || (TempP[11] != 0x90) || (TempP[12] != 0x1F)) { // 81 2E 90 1F
            return;
        }

        //****************进水温度*******************/
        swapStr((char *)&TempP[39], 3);
        memset(TempString.Name._char, 0, TempString.MaxLen); // 清空
        IN_Str.Name._char = (char *)&TempP[39];
        IN_Str.MaxLen = 3;
        TempNum = shortChStrToDoubleChStr(IN_Str, TempString);
        TempNum = anyBaseArrayToAnyBaseNumber(TempString.Name._char, TempNum, 10, 16);
        ColorShowData.HourData.InWaterTemp = TempNum;
        TempNum = 0; // 清零

        //****************回水温度*******************/
        swapStr((char *)&TempP[42], 3);
        memset(TempString.Name._char, 0, TempString.MaxLen); // 清空
        IN_Str.Name._char = (char *)&TempP[42];
        IN_Str.MaxLen = 3;
        TempNum = shortChStrToDoubleChStr(IN_Str, TempString);
        TempNum = anyBaseArrayToAnyBaseNumber(TempString.Name._char, TempNum, 10, 16);
        ColorShowData.HourData.OutWaterTemp = TempNum;
        TempNum = 0; // 清零

        //****************累计耗能*******************/
        TempNum = 0; // 清零
        swapStr((char *)&TempP[19], 4);
        memset(TempString.Name._char, 0, TempString.MaxLen); // 清空
        IN_Str.Name._char = (char *)&TempP[19];
        IN_Str.MaxLen = 4;
        TempNum = shortChStrToDoubleChStr(IN_Str, TempString);
        TempNum = anyBaseArrayToAnyBaseNumber(TempString.Name._char, TempNum, 10, 16);

        switch (TempP[23]) {          // 识别单位并同时处理 TempNum 的转换
            case 0x05: // 1 KW*h
                TempNum = (double)TempNum / 277.78;
                break;
            case 0x0E: // 1 MJ
                TempNum = (double)TempNum / 1000.0;
                break;
            case 0x0F: // 10 MJ
                TempNum = (double)TempNum / 100.0;
                break;
            case 0x10: // 100 MJ
                TempNum = (double)TempNum / 10.0;
                break;
        }
        ColorShowData.HourData.SumEnergy = TempNum; // 累计耗能 GJ

        //****************累计耗流*******************/
        swapStr((char *)&TempP[34], 4);
        memset(TempString.Name._char, 0, TempString.MaxLen); // 清空
        IN_Str.Name._char = (char *)&TempP[34];
        IN_Str.MaxLen = 4;
        TempNum = shortChStrToDoubleChStr(IN_Str, TempString);
        TempNum = anyBaseArrayToAnyBaseNumber(TempString.Name._char, TempNum, 10, 16);

        switch (TempP[38]) {          // 识别单位并同时处理 TempNum 的转换
            case 0x2A: // 10 L
                TempNum = (double)TempNum / 100.0;
                break;
            case 0x2B: // 100 L
                TempNum = (double)TempNum / 10.0;
                break;
            case 0x2C: // 1000 L
                TempNum = (double)TempNum;
                break;
        }
        ColorShowData.HourData.SumFlow = TempNum; // 累计耗流 m3

        //****************  流速  *******************/
        TempNum = 0; // 清零
        swapStr((char *)&TempP[29], 4);
        memset(TempString.Name._char, 0, TempString.MaxLen); // 清空
        IN_Str.Name._char = (char *)&TempP[29];
        IN_Str.MaxLen = 4;
        TempNum = shortChStrToDoubleChStr(IN_Str, TempString);
        if ((TempString.Name._char[0] & 0x80) == 0x80) {
            TempString.Name._char[0] -= 0x80;
            TempNum = anyBaseArrayToAnyBaseNumber(TempString.Name._char, TempNum, 10, 16);
            TempNum = 0 - TempNum;
        } else {
            TempNum = anyBaseArrayToAnyBaseNumber(TempString.Name._char, TempNum, 10, 16);
        }
        switch (TempP[33]) {          // 识别单位并同时处理 TempNum 的转换
            case 0x32: // 1 L／h
                TempNum = TempNum * 1000.0;
                break;
            case 0x33: // 10 L／h
                TempNum = TempNum * 100.0;
                break;
            case 0x34: // 100 L／h
                TempNum = TempNum * 10.0;
                break;
            case 0x35: // 1 m³/h
                break;
        }
        ColorShowData.MinData.FlowSpeed = TempNum; // 瞬时流速 m³/h
    }
    return;
}
void hourTaskOfColorShowTask(void) {
    RTC_TASK.InitSetTimeTask(HourTaskOfColorShow, HourTaskOfColorShowTime, hourTaskOfColorShowTask);
    if (DOWN_Mode_RS4852_ON != true) {
        return;
    }
    struct _JsonHourData {
        JsonItem IsStartHeat;  // 进水温度
        JsonItem InWaterTemp;  // 进水温度
        JsonItem OutWaterTemp; // 回水温度
        JsonItem SumEnergy;    // 累计耗能
        JsonItem SumFlow;      // 累计耗流
    } HourDataJson;
    newString(OutputJsonStr, 300);
    newJsonList ColorShowJsonData = NEW_JSON_LIST(&ColorShowJsonData);
    // 1小时：进回水温度, 累计耗能，累计耗流
    if (ColorShowData.IsStartHeat) {
        ColorShowJsonData.setJsonItemData(&ColorShowJsonData, &HourDataJson.IsStartHeat, "IsStartHeat:%ls;%d", "true", 0);
    } else {
        ColorShowJsonData.setJsonItemData(&ColorShowJsonData, &HourDataJson.IsStartHeat, "IsStartHeat:%ls;%d", "false", 0);
    }
    ColorShowJsonData.setJsonItemData(&ColorShowJsonData, &HourDataJson.InWaterTemp, "InWater:%lf;%d", ColorShowData.HourData.InWaterTemp, 0);
    ColorShowJsonData.setJsonItemData(&ColorShowJsonData, &HourDataJson.OutWaterTemp, "OutWater:%lf;%d", ColorShowData.HourData.OutWaterTemp, 0);
    ColorShowJsonData.setJsonItemData(&ColorShowJsonData, &HourDataJson.SumEnergy, "SumEnergy:%lf;%d", ColorShowData.HourData.SumEnergy, 0);
    ColorShowJsonData.setJsonItemData(&ColorShowJsonData, &HourDataJson.SumFlow, "SumFlow:%lf;%d", ColorShowData.HourData.SumFlow, 0);
    ColorShowJsonData.OutPushJsonString(OutputJsonStr, &ColorShowJsonData);
    sendDataByRS4852(OutputJsonStr.Name._char, OutputJsonStr.getStrlen(&OutputJsonStr));
    return;
}
void minTaskOfColorShowTask(void) {
    RTC_TASK.InitSetTimeTask(MinTaskOfColorShow, MinTaskOfColorShowTime, minTaskOfColorShowTask);
    if (DOWN_Mode_RS4852_ON != true) {
        return;
    }
    struct _JsonMinData {
        JsonItem IsStartHeat; // 进水温度
        JsonItem FlowSpeed;   // 流速
    } MinDataJson;
    newString(OutputJsonStr, 100);
    newJsonList ColorShowJsonData = NEW_JSON_LIST(&ColorShowJsonData);
    // 5分钟：流速
    if (ColorShowData.IsStartHeat) {
        ColorShowJsonData.setJsonItemData(&ColorShowJsonData, &MinDataJson.IsStartHeat, "IsStartHeat:%ls;%d", "true", 0);
    } else {
        ColorShowJsonData.setJsonItemData(&ColorShowJsonData, &MinDataJson.IsStartHeat, "IsStartHeat:%ls;%d", "false", 0);
    }
    ColorShowJsonData.setJsonItemData(&ColorShowJsonData, &MinDataJson.FlowSpeed, "FlowSpeed:%lf;%d", ColorShowData.MinData.FlowSpeed, 0);
    ColorShowJsonData.OutPushJsonString(OutputJsonStr, &ColorShowJsonData);
    sendDataByRS4852(OutputJsonStr.Name._char, OutputJsonStr.getStrlen(&OutputJsonStr));
    return;
}
#endif
