#include "./MyCmdDos/CsvSplit.h"
#include "./array_quiz/ArrayQuiz.h"
#include "./C_MyLib/NumberBaseLib.h"
#include "./C_MyLib/StrLib.h"
#include "./C_MyLib/WinExcel.h"
#include "./C_MyLib/JsonDataDoneLib.h"

char OutSting[1000] = {0};
void setJsonList(JsonItem * WTRequestData) {
    setJsonItemData(&WTRequestData[0], "Type:%d", 2);
}
int main(int argc, char * argv[]) {
    // csvSplit(argc, argv);
    // arrayQuiz();

    // 主表数据
    WTMqttJson JSONDATA = NEW_WT_JSON(&JSONDATA);
    struct _InputMainMeter_Manager {
        int MeterType;                 // 采集表类型
        char MeterID[30];              // 采集表号
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

    setJsonItemData(&QuizItemData[0], "MeterType:%d;%d", InputMainMeter_Manager.MeterType, 0);    // 将关键字Type 与 值 填入 QuizItemData 空间 ，并连接到 JSONDATA 链表
    setJsonItemData(&QuizItemData[1], "MeterID:%s;%d", InputMainMeter_Manager.MeterID, 0);
    setJsonItemData(&QuizItemData[2], "MeterVoltage:%f;%d", InputMainMeter_Manager.MeterVoltage, 0);
    setJsonItemData(&QuizItemData[3], "MeterVoltageUnit:%c;%d", InputMainMeter_Manager.MeterVoltageUnit, 0);
    setJsonItemData(&QuizItemData[4], "MeterVar:%lf;%d", InputMainMeter_Manager.MeterVar, 0);

    JsonItem ListData = {0};
    JsonItem ClassDataA = {0};
    JsonItem VarDataListA[3] = {0};
    JsonItem ClassDataB = {0};
    JsonItem VarDataListB[3] = {0};

    setJsonItemData(&ListData, "List1:%p;%d", &ClassDataA, 0); // List1:[]
    setJsonItemData(&ClassDataA, ":%lp;%d", &VarDataListA, 1);// NULL{}
    setJsonItemData(&VarDataListA[0], "B1:%d;%d", 1, 2);
    setJsonItemData(&VarDataListA[1], "B2:%d;%d", 2, 2);
    setJsonItemData(&VarDataListA[2], "B3:%d;%d", 3, 2);
    setJsonItemData(&ClassDataB, ":%lp;%d", &VarDataListB, 1);// NULL{}
    setJsonItemData(&VarDataListB[0], "B1:%d;%d", 1, 2);
    setJsonItemData(&VarDataListB[1], "B2:%d;%d", 2, 2);
    setJsonItemData(&VarDataListB[2], "B3:%d;%d", 3, 2);

    JsonItem QuizData = {0};
    setJsonItemData(&QuizData, "quiz:%lf;%d", 0.1, 0);

    JsonItem VarDataClass[3] = {0};
    JsonItem ClassData = {0};
    setJsonItemData(&ClassData, "Class:%lp;%d", &VarDataClass, 0);    // Class:{}
    setJsonItemData(&VarDataClass[0], "B1:%d;%d", 1, 1);
    setJsonItemData(&VarDataClass[1], "B2:%d;%d", 2, 1);
    setJsonItemData(&VarDataClass[2], "B3:%d;%d", 3, 1);
    strnew OutputStr = NEW_NAME(OutSting);
    JSONDATA.OutPushJsonString(OutputStr, &JSONDATA);
    printf("%s", OutSting);
}

