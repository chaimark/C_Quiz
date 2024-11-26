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
#include "./C_MyLib/SendDataBySerial.h"
#include <stdio.h>
#include <windows.h>




// void SendCmdMenu(strnew data) {
//     //{"Read":"AT24DataJSON","NowCheckNum":1765}
//     char * ConstData = "{\"Read\":\"AT24DataJSON\",\"NowCheckNum\":1765}"; // 需要发送的数据
//     memcpy(data.Name._char, ConstData, strlen(ConstData));
//     // printf("请选择需要发送的数据：\n");
//     // printf("1. 发送数据\n");
//     // printf("2. 退出\n");
// }
// char SwitchNeedSendData(strnew data) {
//     char EscFlag = 0;
//     SendCmdMenu(data);
//     //printf("输入 #, 结束该进程");
//     // 清理缓冲区
//     //fflush(stdin);
//     //scanf("%c", &EscFlag);
//     return EscFlag;
// }
// int main() {
//     char comPort[7] = {0};
//     list_serial_ports();  // 列出所有可用的串口4
//     printf("请输入您需要使用的串口：");
//     unsigned char comNum = 0;
//     scanf("%d", &comNum);
//     sprintf(comPort, "COM%d", comNum);
//     SendDataTask(comPort, SwitchNeedSendData);
//     return 0;
// }

// char NetDataBuff[1024] = {"{\"gw\":{\"msg_id\":60,\"msg_gw_pr\":0,\"gw_id\":\"02345678903\"},\"data\":{\"NowPackNum\":3,\"Code\":\"1146FFF7E9FF10F047F802F0FDFF03B4FFF7F2FF03BC0EF0E5FD000070B505460C46164602E00FCC0FC5103E102EFAD2082E02D303CC03C5083E042E07D301CC01C5361F03E021782970641C6D1C761EF9D270BD0748804707480047FEE7FEE7FEE7FEE7FEE7FEE704480549054A064B7047000029080100C140000098450020,\"CsCheckNum\":87}}"};

// // 处理 WT的JSON 指令
// bool WT_MQTT_JSON_Analysis(void) {
//     JsonObject JsonObjOfUserCmd = newJsonObjectByString(NEW_NAME(NetDataBuff));
//     int A = JsonObjOfUserCmd.getInt(&JsonObjOfUserCmd, "CsCheckNum");
//     printf("校验码：%d\n", A);
//     return true;
// }
// int main() {
//     WT_MQTT_JSON_Analysis();
// }

// char Data[] = {0x68,0x55,0x33,0x22,0x16,0x68,0x55,0x33,0x22,0x16};
// // 组织透传数据上报
// void WT_JSON_Send_Immediately_Main_Copy_Meter_Data(char * JSON_TTL_Buff, unsigned char * data, unsigned char lentgh) {
//     //WT_MQTT_FLAG = 0; // WT 的指令

//     char MetterId[10] = {0};
//     char * Start68chr = strchr((char *)data, 0x68);
//     char * TempP = Start68chr;
//     TempP = Start68chr + 2; // 跳转转到表号
//     // 组织 WT 1.2 回复
//     HEX2ToASCII((char *)TempP, 4, MetterId, (4 * 2));
//     int tempT10 = (*(Start68chr + 12) == 0x2F ? 2 : (*(Start68chr + 12) == 0x1F ? 1 : -1)); // 获取指令执行结果
//     char NowTime[20] = {0};

//     // 副表控制数据
//     struct _CtrlCopyMeter_Manager {
//         struct _List {
//             JsonItem ListP;
//             struct _Class {
//                 JsonItem ClassP;
//                 JsonItem CmdCode;   // 控制指令编码
//                 JsonItem CmdStatus; // 控制指令状态1:执行中,-1:失败,2:成功
//                 JsonItem MetterId;  // 阀门设备编码
//                 JsonItem SendTime;  // 控制指令下发时间 (yyyy-MM-dd HH:mm:ss)
//             } Class;
//         } List;
//         JsonItem DevCode; // 控制指令编码
//         JsonItem ResDoneData;
//         JsonItem ResError;
//         JsonItem Total;
//         JsonItem AutoNumberIDs;
//     } CtrlCopyMeter_Manager;
//     newString(OutputJsonStr, 300);
//     newJsonList WTMqttJsonData = NEW_JSON_LIST(&WTMqttJsonData);
//     WTMqttJsonData.Head_JsonDataNote = NULL;

//     setJsonItemData(&CtrlCopyMeter_Manager.List.ListP, "list:%p;%d", NULL, 0);          // List 数组
//     setJsonItemData(&CtrlCopyMeter_Manager.List.Class.ClassP, ":%lp;%d", NULL, 1); // List 中的对象
//     setJsonItemData(&CtrlCopyMeter_Manager.List.Class.CmdCode, "T8:%d;%d", 0, 2);
//     setJsonItemData(&CtrlCopyMeter_Manager.List.Class.CmdStatus, "T10:%d;%d", tempT10, 2);
//     setJsonItemData(&CtrlCopyMeter_Manager.List.Class.MetterId, "R53:%s;%d", MetterId, 2);
//     setJsonItemData(&CtrlCopyMeter_Manager.List.Class.SendTime, "J79:%s;%d", NowTime, 2);

//     setJsonItemData(&CtrlCopyMeter_Manager.DevCode, "code:%d;%d", 1, 0);
//     if (tempT10 == 2) {
//         setJsonItemData(&CtrlCopyMeter_Manager.ResDoneData, "data:%s;%d", "执行成功", 0);
//         setJsonItemData(&CtrlCopyMeter_Manager.ResError, "error:%ls;%d", "null", 0);
//     } else if (tempT10 == 1) {
//         setJsonItemData(&CtrlCopyMeter_Manager.ResDoneData, "data:%s;%d", "正在执行", 0);
//         setJsonItemData(&CtrlCopyMeter_Manager.ResError, "error:%ls;%d", "null", 0);
//     } else {
//         setJsonItemData(&CtrlCopyMeter_Manager.ResDoneData, "data:%s;%d", "执行异常", 0);
//         setJsonItemData(&CtrlCopyMeter_Manager.ResError, "error:%s;%d", "未知", 0);
//     }
//     setJsonItemData(&CtrlCopyMeter_Manager.Total, "Total:%d;%d", 1, 0);
//     setJsonItemData(&CtrlCopyMeter_Manager.AutoNumberIDs, "AutoNumberIDs:%ls;%d", "null", 0);

//     AddCsToJsonAndPushJsonStr(&WTMqttJsonData, OutputJsonStr);
//     WTMqttJsonData.OutPushJsonString(OutputJsonStr, &WTMqttJsonData);
//     memcpy(JSON_TTL_Buff, OutputJsonStr.Name._char, strlen(OutputJsonStr.Name._char));
//     return;
// }
// int main() {
//     char JSONOUT1[1000] = {0};
//     WT_JSON_Send_Immediately_Main_Copy_Meter_Data(JSONOUT1, Data, 10);
//     printf("JSONOUT1:\n%s\n\n", JSONOUT1);
//     char JSONOUT2[1000] = {0};
//     if (checkOfCsJsonStrIsRight(NEW_NAME(JSONOUT1), NEW_NAME(JSONOUT1))) {
//         printf("JSONOUT2:\n%s\n\n", JSONOUT1);
//     }
// }
