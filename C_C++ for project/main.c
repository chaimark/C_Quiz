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

    // 主表数据
    WTMqttJson JSONDATA = NEW_WT_JSON(&JSONDATA);
    struct _InputMainMeter_Manager {
        int MeterType;                 // 采集表类型
        char eo[30];              // 采集表号
        char Name[30];              // 采集表号
    } InputMainMeter_Manager;

    JsonItem QuizItemData[3] = {0};
    copyString(InputMainMeter_Manager.Name, "AAAABBB", ARR_SIZE(InputMainMeter_Manager.Name), strlen("AAAABBB"));
    InputMainMeter_Manager.MeterType = 2;
    copyString(InputMainMeter_Manager.eo, "02345678903", ARR_SIZE(InputMainMeter_Manager.eo), strlen("02345678903"));

    setJsonItemData(&QuizItemData[0], "Type:%d;%d", InputMainMeter_Manager.MeterType, 0);    // 将关键字Type 与 值 填入 QuizItemData 空间 ，并连接到 JSONDATA 链表
    setJsonItemData(&QuizItemData[1], "eo:%s;%d", InputMainMeter_Manager.eo, 0);

    JsonItem List1Data = {0};
    JsonItem ClassData = {0};
    JsonItem VarDataList[10] = {0};
    setJsonItemData(&List1Data, "list:%p;%d", &ClassData, 0); // list:[]
    setJsonItemData(&ClassData, ":%lp;%d", &VarDataList, 1);// NULL{}
    setJsonItemData(&VarDataList[0], "R53:%d;%d", 1, 2);
    setJsonItemData(&VarDataList[1], "S13:%d;%d", 2, 2);
    setJsonItemData(&VarDataList[2], "S3:%d;%d", 3, 2);
    setJsonItemData(&VarDataList[3], "L21:%d;%d", 3, 2);
    setJsonItemData(&VarDataList[4], "L22:%d;%d", 3, 2);
    setJsonItemData(&VarDataList[5], "L27:%d;%d", 3, 2);
    setJsonItemData(&VarDataList[6], "J111:%d;%d", 3, 2);
    setJsonItemData(&VarDataList[7], "R64:%d;%d", 3, 2);
    setJsonItemData(&VarDataList[8], "R65:%d;%d", 3, 2);
    setJsonItemData(&VarDataList[9], "J1000:%d;%d", 3, 2);

    setJsonItemData(&QuizItemData[2], "Name:%s;%d", InputMainMeter_Manager.Name, 0);

    strnew OutputStr = NEW_NAME(OutSting);
    JSONDATA.OutPushJsonString(OutputStr, &JSONDATA);
    printf("%s", OutSting);
}

