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

// 组织透传数据上报
void WT_JSON_Send_Immediately_Main_Copy_Meter_Data(char * JSON_TTL_Buff, unsigned char * data, unsigned char lentgh) {

}
int main() {
    char MQTT_4G_SendBuf[1024] = {0};
    struct _data {
        JsonItem copy_meter_total;      // 复表数
        JsonItem copy_groups_num;       // 复表组数
        struct _copy_meter_id {
            JsonItem copy_meter_id_P;   // 复表仪表ID数组
            JsonItem idStr;             // 复表仪表ID数组
            JsonItem idStr2;             // 复表仪表ID数组
        }copy_meter_id;
    } HY_MQTT_JSON;

    memset(&HY_MQTT_JSON, 0, sizeof(HY_MQTT_JSON));
    newJsonList HYMqttJsonData = NEW_JSON_LIST(&HYMqttJsonData);

    HY_MQTT_JSON.copy_meter_total.var.Dataint = 10;
    HY_MQTT_JSON.copy_groups_num.var.Dataint = 2;

    setJsonItemData(&HY_MQTT_JSON.copy_meter_total, "copy_meter_total:%d;%d;", HY_MQTT_JSON.copy_meter_total.var.Dataint, 0);
    setJsonItemData(&HY_MQTT_JSON.copy_groups_num, "copy_groups_num:%d;%d;", HY_MQTT_JSON.copy_groups_num.var.Dataint, 0);
    setJsonItemData(&HY_MQTT_JSON.copy_meter_id.copy_meter_id_P, "copy_meter_id:%p;%d", &HY_MQTT_JSON.copy_meter_id, 0);
    setJsonItemData(&HY_MQTT_JSON.copy_meter_id.idStr, ":%s;%d", "123456", 1);
    setJsonItemData(&HY_MQTT_JSON.copy_meter_id.idStr2, ":%s;%d", "123456", 1);

    HYMqttJsonData.OutPushJsonString(NEW_NAME(MQTT_4G_SendBuf), &HYMqttJsonData);
    HYMqttJsonData.ResJsonDataNote(&HYMqttJsonData);
    printf("%s\n", MQTT_4G_SendBuf);
}
