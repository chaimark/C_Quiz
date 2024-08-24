#include "./MyCmdDos/CsvSplit.h"
#include "./array_quiz/ArrayQuiz.h"
#include "./C_MyLib/NumberBaseLib.h"
#include "./C_MyLib/StrLib.h"
#include "./C_MyLib/WinExcel.h"
#include "./C_MyLib/JsonDataDoneLib.h"

int main() {
    strnew OutputStrC;
    char Str[1000] = {0};
    strnew OutputStrB = NEW_NAME(Str);
    strnew OutputStrB = NEW_NAME("Hello World!");
    newString(OutputStrA, 1000);
}


// char OutSting[1000] = {0};

// int main(int argc, char * argv[]) {
// // 主表数据
//     struct _InputMainMeter_Manager {
//         char MeterID[30];              // 采集表号
//         double InputWaterTemperature;  // 供水温度 ℃
//         double ReturnWaterTemperature; // 回水温度 ℃
//         double TemperatureDifference;  // 温差     ℃
//         double InstantaneousHeat;      // 瞬时热量 GJ/h
//         double AccumulatedHeat;        // 累计热量 GJ
//         double InstantaneousFlow;      // 瞬时流量 m³/h
//         double AccumulatedFlow;        // 累计流量 t
//         char CollectionTime[20];       // 采集时间 (yyyy-MM-dd HH:mm:ss)
//     } InputMainMeter_Manager = {0};
//     // 副表数据
//     struct _InputCopyMeter_Manager {
//         char MeterID[30];              // 温控阀编码
//         double SetRoomTemperature;     // 设定温度
//         double RoomTemperature;        // 室内温度
//         double InputWaterTemperature;  // 供水温度(无数据则为nult)
//         double OutputWaterTemperature; // 回水温度
//         double ValveOpenDeg;           // 阀门开度(92.5%传92.5)
//         double Power;                  // 电量(单位%如50%那么数值就是50)
//         char ControlStrategy[30];      // 控制策略(0:开度给定,1:室温控制,2:圆温控制)
//         char FaultInformation[100];    // 故障信息
//         char CollectionTime[20];       // 采集时间 (yyyy-MM-dd HH:mm:ss)
//         char Name[30];                 // 固定字段
//     } InputCopyMeter_Manager = {0};

//     newJsonList WTMqttJsonData = {0};
//     WTMqttJsonData = NEW_JSON_LIST(&WTMqttJsonData);
//     char ArrayID[14] = {"02345678903"};

//     JsonItem WTRequestData[4] = {0};
//     if (1) {
//         JsonItem MainlistItem[9] = {0};
//         memcpy(InputMainMeter_Manager.MeterID, "2700583", strlen("2700583"));
//         memcpy(InputMainMeter_Manager.CollectionTime, "2024.7.17 20:24:00", strlen("2324.7.17 20:24:00"));

//         /************************************************/
//         setJsonItemData(&WTRequestData[0], "Type:%d;%d", 2, 0);            // 仪表类型栋阀
//         setJsonItemData(&WTRequestData[1], "eo:%s;%d", &ArrayID[1], 0);    // 02345678903
//         JsonItem ClassItem = {0};
//         setJsonItemData(&WTRequestData[2], "list:%p;%d", ClassItem, 0); // List 数组
//         setJsonItemData(&ClassItem, ":%lp;%d", MainlistItem, 1);                                            // List 中的对象
//         setJsonItemData(&MainlistItem[0], "R51:%s;%d", InputMainMeter_Manager.MeterID, 2);                  // R51    是	string	    热表编码
//         setJsonItemData(&MainlistItem[1], "L21:%lf;%d", InputMainMeter_Manager.InputWaterTemperature, 2);   // L21    是	double	    供水温度
//         setJsonItemData(&MainlistItem[2], "L22:%lf;%d", InputMainMeter_Manager.ReturnWaterTemperature, 2);  // L22    是	double	    回水温度
//         setJsonItemData(&MainlistItem[3], "L1000:%lf;%d", InputMainMeter_Manager.TemperatureDifference, 2); // L1000  是	double	    温差
//         setJsonItemData(&MainlistItem[4], "L26:%lf;%d", InputMainMeter_Manager.InstantaneousHeat, 2);       // L26    是	double	    瞬时热量
//         setJsonItemData(&MainlistItem[5], "L33:%lf;%d", InputMainMeter_Manager.AccumulatedHeat, 2);         // L33    是	double	    累计热量
//         setJsonItemData(&MainlistItem[6], "L25:%lf;%d", InputMainMeter_Manager.InstantaneousFlow, 2);       // L25    是	double	    瞬时流量
//         setJsonItemData(&MainlistItem[7], "L34:%lf;%d", InputMainMeter_Manager.AccumulatedFlow, 2);         // L34    是	double	    累计流量
//         setJsonItemData(&MainlistItem[8], "J1000:%s;%d", InputMainMeter_Manager.CollectionTime, 2);         // J1000  是	string	    采集时间(yyyy-MM-dd HH:mm:ss)
//         /************************************************/
//     } else {
//         JsonItem CopylistItem[10] = {0};
//         memcpy(InputCopyMeter_Manager.MeterID, "2700582", strlen("2700582"));
//         memcpy(InputCopyMeter_Manager.CollectionTime, "2324.7.17 20:24:00", strlen("2324.7.17 20:24:00"));
//                 /**************************/
//         setJsonItemData(&WTRequestData[0], "Type:%d;%d", 16, 0);           // 仪表类型栋阀
//         setJsonItemData(&WTRequestData[1], "eo:%s;%d", &ArrayID[1], 0);    // 02345678903
//         JsonItem ClassItem = {0};
//         setJsonItemData(&WTRequestData[2], "list:%p;%d", ClassItem, 0); // List 数组
//         setJsonItemData(&ClassItem, ":%lp;%d", CopylistItem, 1);                                          // List 中的对象
//         setJsonItemData(&CopylistItem[0], "R53:%s;%d", InputCopyMeter_Manager.MeterID, 2);                // RS3    是	string      温控阀编码
//         setJsonItemData(&CopylistItem[1], "S13:%lf;%d", InputCopyMeter_Manager.SetRoomTemperature, 2);    // S13    是	double	    设定温度
//         setJsonItemData(&CopylistItem[2], "S3:%lf;%d", InputCopyMeter_Manager.RoomTemperature, 2);        // 53     是	double	    室内温度
//         setJsonItemData(&CopylistItem[3], "L21:%lf;%d", InputCopyMeter_Manager.InputWaterTemperature, 2); // L21    是	double	    供水温度(无数据则为nult)
//         setJsonItemData(&CopylistItem[4], "L22:%lf;%d", InputCopyMeter_Manager.OutputWaterTemperature, 2);  // L22    是	double	    回水温度
//         setJsonItemData(&CopylistItem[5], "L27:%lf;%d", InputCopyMeter_Manager.ValveOpenDeg, 2);          // L27    是	double	    阀门开度(92.5%传92.5)
//         setJsonItemData(&CopylistItem[6], "J111:%lf;%d", InputCopyMeter_Manager.Power, 2);                // J11    是	double	    电量(单位%如50%那么数值就是50)
//         memcpy(InputCopyMeter_Manager.ControlStrategy, "0", strlen("0"));
//         setJsonItemData(&CopylistItem[7], "R64:%s;%d", InputCopyMeter_Manager.ControlStrategy, 2);        // R64    是	string	    控制策略(0:开度给定,1:室温控制,2:圆温控制)
//         memcpy(InputCopyMeter_Manager.FaultInformation, "00", strlen("00"));
//         setJsonItemData(&CopylistItem[8], "R65:%s;%d", InputCopyMeter_Manager.FaultInformation, 2);       // R65    是	string	    故障信息
//         setJsonItemData(&CopylistItem[9], "J1000:%s;%d", InputCopyMeter_Manager.CollectionTime, 2);       // J1000  是	string	    采集时间(yy-MM-dd HH:mm:ss)
//         memcpy(InputCopyMeter_Manager.Name, "AAAAA", strlen("AAAAA"));
//         setJsonItemData(&WTRequestData[3], "Name:%s;%d", InputCopyMeter_Manager.Name, 0);
//         /**************************/
//     }
//     strnew OutputStr = NEW_NAME(OutSting);
//     WTMqttJsonData.OutPushJsonString(OutputStr, &WTMqttJsonData);
//     printf("%s", OutSting);
// }
