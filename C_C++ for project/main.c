#include "./MyCmdDos/CsvSplit.h"
#include "./array_quiz/ArrayQuiz.h"
#include "./C_MyLib/NumberBaseLib.h"
#include "./MyCmdDos/CsvSplit.h"
#include "./array_quiz/ArrayQuiz.h"
#include "./C_MyLib/NumberBaseLib.h"
#include "./C_MyLib/StrLib.h"
#include "./C_MyLib/WinExcel.h"
#include "./C_MyLib/JsonDataDoneLib.h"
#include "./C_MyLib/WinExcel.h"
#include "./C_MyLib/JsonDataDoneLib.h"
#include "./C_MyLib/JsonDataAnalyzeLib.h"
#include "./C_MyLib/JsonCheckFun.h"
#include <stdio.h>

// char NetDataBuff[1024] = {
//     "\r\n{\"dev\": {\"msg_id\": 81,\"id\": \"12345678\"},\"data\": {\"IP\": \"192.168.1.1\",\"Prot\": \"5683\"}}",
// };

// // 处理 WT的JSON 指令
// bool WT_MQTT_JSON_Analysis(void) {
//     char ArrayID[8] = {"12345678"};
//     strnew JsonStr = NEW_NAME(NetDataBuff);
//     JsonObject JsonObjOfUserCmd = newJsonObjectByString(JsonStr);
//     newString(TempStr, 100);
//     newString(IDStr, 100);
//     JsonObject DevStrObj = JsonObjOfUserCmd.getObject(&JsonObjOfUserCmd, "dev", TempStr);
//     if (DevStrObj.getInt(&DevStrObj, "msg_id") == 81) {
//         DevStrObj.getString(&DevStrObj, "id", IDStr);
//         if (memcmp(IDStr.Name._char, ArrayID, ARR_SIZE(ArrayID)) != 0) {
//             return false;
//         }
//     }
//     memset(TempStr.Name._char, 0, TempStr.MaxLen);
//     JsonObject dataStrObj = JsonObjOfUserCmd.getObject(&JsonObjOfUserCmd, "data", TempStr);
//     strnew TempIP = NEW_NAME("192.168.1.1");
//     newString(TempProt, 100);
//     dataStrObj.getString(&dataStrObj, "IP", TempIP);
//     dataStrObj.getString(&dataStrObj, "Prot", TempProt);
//     printf("%d", atoi(TempProt.Name._char));
//     return true;
// }
// int main() {
//     WT_MQTT_JSON_Analysis();
// }

char Data[] = {0x68,0x55,0x33,0x22,0x16,0x68,0x55,0x33,0x22,0x16};
// 组织透传数据上报
void WT_JSON_Send_Immediately_Main_Copy_Meter_Data(char * JSON_TTL_Buff, unsigned char * data, unsigned char lentgh) {
    //WT_MQTT_FLAG = 0; // WT 的指令

    char MetterId[10] = {0};
    char * Start68chr = strchr((char *)data, 0x68);
    char * TempP = Start68chr;
    TempP = Start68chr + 2; // 跳转转到表号
    // 组织 WT 1.2 回复
    HEX2ToASCII((char *)TempP, 4, MetterId, (4 * 2));
    int tempT10 = (*(Start68chr + 12) == 0x2F ? 2 : (*(Start68chr + 12) == 0x1F ? 1 : -1)); // 获取指令执行结果
    char NowTime[20] = {0};

    // 副表控制数据
    struct _CtrlCopyMeter_Manager {
        struct _List {
            JsonItem ListP;
            struct _Class {
                JsonItem ClassP;
                JsonItem CmdCode;   // 控制指令编码
                JsonItem CmdStatus; // 控制指令状态1:执行中,-1:失败,2:成功
                JsonItem MetterId;  // 阀门设备编码
                JsonItem SendTime;  // 控制指令下发时间 (yyyy-MM-dd HH:mm:ss)
            } Class;
        } List;
        JsonItem DevCode; // 控制指令编码
        JsonItem ResDoneData;
        JsonItem ResError;
        JsonItem Total;
        JsonItem AutoNumberIDs;
    } CtrlCopyMeter_Manager;
    newString(OutputJsonStr, 300);
    newJsonList WTMqttJsonData = NEW_JSON_LIST(&WTMqttJsonData);
    WTMqttJsonData.Head_WTjsonDataNote = NULL;

    setJsonItemData(&CtrlCopyMeter_Manager.List.ListP, "list:%p;%d", NULL, 0);          // List 数组
    setJsonItemData(&CtrlCopyMeter_Manager.List.Class.ClassP, ":%lp;%d", NULL, 1); // List 中的对象
    setJsonItemData(&CtrlCopyMeter_Manager.List.Class.CmdCode, "T8:%d;%d", 0, 2);
    setJsonItemData(&CtrlCopyMeter_Manager.List.Class.CmdStatus, "T10:%d;%d", tempT10, 2);
    setJsonItemData(&CtrlCopyMeter_Manager.List.Class.MetterId, "R53:%s;%d", MetterId, 2);
    setJsonItemData(&CtrlCopyMeter_Manager.List.Class.SendTime, "J79:%s;%d", NowTime, 2);

    setJsonItemData(&CtrlCopyMeter_Manager.DevCode, "code:%d;%d", 1, 0);
    if (tempT10 == 2) {
        setJsonItemData(&CtrlCopyMeter_Manager.ResDoneData, "data:%s;%d", "执行成功", 0);
        setJsonItemData(&CtrlCopyMeter_Manager.ResError, "error:%ls;%d", "null", 0);
    } else if (tempT10 == 1) {
        setJsonItemData(&CtrlCopyMeter_Manager.ResDoneData, "data:%s;%d", "正在执行", 0);
        setJsonItemData(&CtrlCopyMeter_Manager.ResError, "error:%ls;%d", "null", 0);
    } else {
        setJsonItemData(&CtrlCopyMeter_Manager.ResDoneData, "data:%s;%d", "执行异常", 0);
        setJsonItemData(&CtrlCopyMeter_Manager.ResError, "error:%s;%d", "未知", 0);
    }
    setJsonItemData(&CtrlCopyMeter_Manager.Total, "Total:%d;%d", 1, 0);
    setJsonItemData(&CtrlCopyMeter_Manager.AutoNumberIDs, "AutoNumberIDs:%ls;%d", "null", 0);

    AddCsToJsonAndPushJsonStr(&WTMqttJsonData, OutputJsonStr);
    WTMqttJsonData.OutPushJsonString(OutputJsonStr, &WTMqttJsonData);
    memcpy(JSON_TTL_Buff, OutputJsonStr.Name._char, strlen(OutputJsonStr.Name._char));
    return;
}
int main() {
    char JSONOUT[1000] = {0};
    WT_JSON_Send_Immediately_Main_Copy_Meter_Data(JSONOUT, Data, 10);
    printf("%s", JSONOUT);
    // if(){

    // }
}
