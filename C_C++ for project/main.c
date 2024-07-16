#include "./MyCmdDos/CsvSplit.h"
#include "./array_quiz/ArrayQuiz.h"
#include "./C_MyLib/NumberBaseLib.h"
#include "./C_MyLib/StrLib.h"
#include "./C_MyLib/WinExcel.h"
#include "./C_MyLib/JsonDataDoneLib.h"

void setJsonList(JsonItem * WTRequestData) {
    setJsonItemData(&WTRequestData[0], "Type:%d", 2);
}
int main(int argc, char * argv[]) {
    // csvSplit(argc, argv);
    // arrayQuiz();

    // 主表数据
    WTMqttJson JSONDATA = NEW_WT_JSON(&JSONDATA);
    struct _InputMainMeter_Manager {
        char MeterID[30];              // 采集表号
        int MeterType;                 // 采集表类型
        float MeterVoltage;            // 采集表电压
        char MeterVoltageUnit;         // 采集表电压单位
        double MeterVar;               // 采集值
    } InputMainMeter_Manager;

    JsonItem QuizItemData[5] = {0};
    copyString(InputMainMeter_Manager.MeterID, "AAAABBB", ARR_SIZE(InputMainMeter_Manager.MeterID), strlen("AAAABBB"));
    InputMainMeter_Manager.MeterType = 1000;
    InputMainMeter_Manager.MeterVoltage = 3.6;
    InputMainMeter_Manager.MeterVoltageUnit = 'V';
    InputMainMeter_Manager.MeterVar = 6586.25488;

    setJsonItemData(&QuizItemData[0], "Type:%d", 2);    // 将关键字Type 与 值 填入 QuizItemData 空间 ，并连接到 JSONDATA 链表
    setJsonItemData(&QuizItemData[1], "Type:%s", InputMainMeter_Manager.MeterID);
    setJsonItemData(&QuizItemData[2], "Type:%f", InputMainMeter_Manager.MeterVoltage);
    setJsonItemData(&QuizItemData[3], "Type:%c", InputMainMeter_Manager.MeterVoltageUnit);
    setJsonItemData(&QuizItemData[4], "Type:%lf", InputMainMeter_Manager.MeterVar);

    char OutSting[1000];
    strnew OutputStr = NEW_NAME(OutSting);
    JSONDATA.OutPushJsonString(OutputStr, &JSONDATA);
    printf("%s",OutSting);
}

