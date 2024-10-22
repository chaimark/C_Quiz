#include "./MyCmdDos/CsvSplit.h"
#include "./array_quiz/ArrayQuiz.h"
#include "./C_MyLib/NumberBaseLib.h"
#include "./C_MyLib/StrLib.h"
#include "./C_MyLib/WinExcel.h"
#include "./C_MyLib/JsonDataDoneLib.h"
#include "./C_MyLib/JsonDataAnalyzeLib.h"
#include <stdio.h>

char NetDataBuff[1024] = {
    "\r\n{\"dev\": {\"msg_id\": 81,\"id\": \"12345678\"},\"data\": {\"IP\": \"192.168.1.1\",\"Prot\": \"5683\"}}",
};

// 处理 WT的JSON 指令
bool WT_MQTT_JSON_Analysis(void) {
    char ArrayID[8] = {"12345678"};
    strnew JsonStr = NEW_NAME(NetDataBuff);
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
    strnew TempIP = NEW_NAME("192.168.1.1");
    newString(TempProt, 100);
    dataStrObj.getString(&dataStrObj, "IP", TempIP);
    dataStrObj.getString(&dataStrObj, "Prot", TempProt);
    printf("%d", atoi(TempProt.Name._char));
    return true;
}

int main() {
    WT_MQTT_JSON_Analysis();
}

