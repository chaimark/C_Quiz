// #include "./MyCmdDos/CsvSplit.h"
// #include "./array_quiz/ArrayQuiz.h"
// #include "./C_MyLib/NumberBaseLib.h"
#include "./C_MyLib/StrLib.h"
// #include "./C_MyLib/WinExcel.h"
// #include "./C_MyLib/JsonDataDoneLib.h"
#include "./C_MyLib/JsonDataAnalyzeLib.h"
#include <stdio.h>
char JsonStrDown[1000] = {"{\"string\": \"Hello!\",\"number\": 42a,\"boolean\": true,\"nullValue\": null,\"array\": [1, 2, 3, \"four\", true, null],\"object\": {\"key1\": \"value1\",\"key2\": 100,\"key3\": {\"nestedKey1\": \"nestedValue1\",\"nestedKey2\": [10, 20, 30]},\"key4\": [\"a\", \"b\", \"c\"]},\"nestedArray\": [{\"id\": 1, \"name\": \"Item 1\"},{\"id\": 2, \"name\": \"Item 2\"}]}"};

// 处理 WT的JSON 指令
bool WT_MQTT_JSON_Analysis(void) {
    return true;
}

int main() {
    JsonObject JsonObj = newJsonObjectByString(NEW_NAME(JsonStrDown));
    newString(TempStr, 100);
    JsonObj.getString(&JsonObj, "string", TempStr);
    printf("%s\n", TempStr.Name._char);
    int number = JsonObj.getInt(&JsonObj, "number");
    printf("%d\n", number);
    bool boolean = JsonObj.getBool(&JsonObj, "boolean");
    printf("%s\n", (boolean ? "true" : "false"));
    bool IsNull = JsonObj.isJsonNull(&JsonObj, "nullValue");
    printf("%s\n", (IsNull ? "true" : "false"));
    JsonArray jsonArr = JsonObj.getArray(&JsonObj, "array", TempStr);
    printf("%s\n", jsonArr.JsonString.Name._char);
    // JsonObject jsonObj = JsonObj.getObject(&JsonObj, "object");
    // JsonArray jsonArr = JsonObj.getArray(&JsonObj, "nestedArray");

    // JsonArray JsonArr = newJsonArrayByString(NEW_NAME(JsonStrDown));
    //  JsonArr.getArray();
    //  JsonArr.getObject();
    //  JsonArr.get();
    //  JsonArr.isJsonNull();
    //  JsonArr.JsonString;
}

// char Data[] = {0x68,0x55,0x33,0x22,0x16,0x68,0x55,0x33,0x22,0x16};
// // 组织透传数据上报
// void WT_JSON_Send_Immediately_Main_Copy_Meter_Data(char * JSON_TTL_Buff, unsigned char * data, unsigned char lentgh) {
//     //WT_MQTT_FLAG = 0; // WT 的指令

//     newString(OutputJsonStr, 300);
//     newJsonList WTMqttJsonData = NEW_JSON_LIST(&WTMqttJsonData);
//     WTMqttJsonData.Head_WTjsonDataNote = NULL;

//     char MetterId[10] = {0};
//     char * Start68chr = strchr((char *)data, 0x68);
//     char * TempP = Start68chr;
//     TempP = Start68chr + 2; // 跳转转到表号

//     if ((*(TempP - 1)) == 0x55) { // 二网阀请求下发示例： 控制6855 1.3
//         // 组织 WT 1.3 回复
//         HEX2ToASCII((char *)TempP, 4, MetterId, (4 * 2));
//         int tempT10 = (*(Start68chr + 12) == 0x2F ? 2 : (*(Start68chr + 12) == 0x1F ? 1 : -1)); // 获取指令执行结果
//         char NowTime[20] = {0};
//         //getStrNowDataAndTimeByRTC(NowTime);

//         // 主表控制数据
//         struct _CtrlMainMeter_Manager {
//             JsonItem DevCode; // 控制指令编码
//             struct _List {
//                 JsonItem ListP; // 控制指令编码
//                 struct _Class {
//                     JsonItem ClassP; // 控制指令编码
//                     JsonItem CmdCode;   // 控制指令编码
//                     JsonItem CmdStatus; // 控制指令状态1:执行中,-1:失败,2:成功
//                     JsonItem MetterId;  // 阀门设备编码
//                     JsonItem SendTime;  // 控制指令下发时间 (yyyy-MM-dd HH:mm:ss)
//                 } Class;
//             } List;
//             JsonItem ResDoneData;
//             JsonItem ResError;
//             JsonItem Total;
//             JsonItem AutoNumberIDs;
//         } CtrlMainMeter_Manager;
//         setJsonItemData(&CtrlMainMeter_Manager.DevCode, "code:%d;%d", 2, 0);
//         setJsonItemData(&CtrlMainMeter_Manager.List.ListP, "list:%p;%d", CtrlMainMeter_Manager.List.ListP, 0);          // List 数组
//         setJsonItemData(&CtrlMainMeter_Manager.List.Class.ClassP, ":%lp;%d", CtrlMainMeter_Manager.List.Class.ClassP, 1); // Class 对象
//         setJsonItemData(&CtrlMainMeter_Manager.List.Class.CmdCode, "T8:%d;%d", 0, 2);
//         setJsonItemData(&CtrlMainMeter_Manager.List.Class.CmdStatus, "T10:%d;%d", tempT10, 2);
//         setJsonItemData(&CtrlMainMeter_Manager.List.Class.MetterId, "P103:%s;%d", MetterId, 2);
//         setJsonItemData(&CtrlMainMeter_Manager.List.Class.SendTime, "J79:%s;%d", NowTime, 2);

//         if (tempT10 == 2) {
//             setJsonItemData(&CtrlMainMeter_Manager.ResDoneData, "data:%s;%d", "执行成功", 0);
//             setJsonItemData(&CtrlMainMeter_Manager.ResError, "error:%ls;%d", "null", 0);
//         } else if (tempT10 == 1) {
//             setJsonItemData(&CtrlMainMeter_Manager.ResDoneData, "data:%s;%d", "正在执行", 0);
//             setJsonItemData(&CtrlMainMeter_Manager.ResError, "error:%ls;%d", "null", 0);
//         } else {
//             setJsonItemData(&CtrlMainMeter_Manager.ResDoneData, "data:%s;%d", "执行异常", 0);
//             setJsonItemData(&CtrlMainMeter_Manager.ResError, "error:%s;%d", "未知", 0);
//         }
//         setJsonItemData(&CtrlMainMeter_Manager.Total, "Total:%d;%d", 1, 0);
//         setJsonItemData(&CtrlMainMeter_Manager.AutoNumberIDs, "AutoNumberIDs:%ls;%d", "null", 0);
//     } else { // 户阀（温控阀）请求示例： 控制6853 1.2
//         // 组织 WT 1.2 回复
//         HEX2ToASCII((char *)TempP, 4, MetterId, (4 * 2));
//         int tempT10 = (*(Start68chr + 12) == 0x2F ? 2 : (*(Start68chr + 12) == 0x1F ? 1 : -1)); // 获取指令执行结果
//         char NowTime[20] = {0};
//         //getStrNowDataAndTimeByRTC(NowTime);

//         // 副表控制数据
//         struct _CtrlCopyMeter_Manager {
//             struct _List {
//                 JsonItem ListP; // 控制指令编码
//                 struct _Class {
//                     JsonItem ClassP; // 控制指令编码
//                     JsonItem CmdCode;   // 控制指令编码
//                     JsonItem CmdStatus; // 控制指令状态1:执行中,-1:失败,2:成功
//                     JsonItem MetterId;  // 阀门设备编码
//                     JsonItem SendTime;  // 控制指令下发时间 (yyyy-MM-dd HH:mm:ss)
//                 } Class;
//             } List;
//             JsonItem DevCode; // 控制指令编码
//             JsonItem ResDoneData;
//             JsonItem ResError;
//             JsonItem Total;
//             JsonItem AutoNumberIDs;
//         } CtrlCopyMeter_Manager;

//         setJsonItemData(&CtrlCopyMeter_Manager.List.ListP, "list:%p;%d", CtrlCopyMeter_Manager.List, 0);          // List 数组
//         setJsonItemData(&CtrlCopyMeter_Manager.List.Class.ClassP, ":%lp;%d", CtrlCopyMeter_Manager.List.Class, 1); // List 中的对象
//         setJsonItemData(&CtrlCopyMeter_Manager.List.Class.CmdCode, "T8:%d;%d", 0, 2);
//         setJsonItemData(&CtrlCopyMeter_Manager.List.Class.CmdStatus, "T10:%d;%d", tempT10, 2);
//         setJsonItemData(&CtrlCopyMeter_Manager.List.Class.MetterId, "R53:%s;%d", MetterId, 2);
//         setJsonItemData(&CtrlCopyMeter_Manager.List.Class.SendTime, "J79:%s;%d", NowTime, 2);

//         setJsonItemData(&CtrlCopyMeter_Manager.DevCode, "code:%d;%d", 1, 0);
//         if (tempT10 == 2) {
//             setJsonItemData(&CtrlCopyMeter_Manager.ResDoneData, "data:%s;%d", "执行成功", 0);
//             setJsonItemData(&CtrlCopyMeter_Manager.ResError, "error:%ls;%d", "null", 0);
//         } else if (tempT10 == 1) {
//             setJsonItemData(&CtrlCopyMeter_Manager.ResDoneData, "data:%s;%d", "正在执行", 0);
//             setJsonItemData(&CtrlCopyMeter_Manager.ResError, "error:%ls;%d", "null", 0);
//         } else {
//             setJsonItemData(&CtrlCopyMeter_Manager.ResDoneData, "data:%s;%d", "执行异常", 0);
//             setJsonItemData(&CtrlCopyMeter_Manager.ResError, "error:%s;%d", "未知", 0);
//         }
//         setJsonItemData(&CtrlCopyMeter_Manager.Total, "Total:%d;%d", 1, 0);
//         setJsonItemData(&CtrlCopyMeter_Manager.AutoNumberIDs, "AutoNumberIDs:%ls;%d", "null", 0);
//     }
//     WTMqttJsonData.OutPushJsonString(OutputJsonStr, &WTMqttJsonData);
//     memcpy(JSON_TTL_Buff, OutputJsonStr.Name._char, strlen(OutputJsonStr.Name._char));
//     return;
// }
// int main() {
//     char JSONOUT[1000] = {0};
//     WT_JSON_Send_Immediately_Main_Copy_Meter_Data(JSONOUT, Data, 10);
//     printf("%s", JSONOUT);
// }
