#include "JsonCheckFun.h"
#include "stdio.h"

void _AddCsToJsonAndPushJsonStr(JsonItem * NowCheckNum, newJsonList * JsonDataList, strnew OutputJsonStr) {
    int CheckNum = 0;
    (*JsonDataList).OutPushJsonString(OutputJsonStr, JsonDataList);   // 输出 jsonstr
    (*JsonDataList).ResJsonDataNote(JsonDataList);
    // 计算 cs 或其他检验算法
    for (int i = 0; i < OutputJsonStr.MaxLen; i++) {
        CheckNum += OutputJsonStr.Name._char[i];
    }
    memset(OutputJsonStr.Name._char, 0, OutputJsonStr.MaxLen);
    setJsonItemData(NowCheckNum, "NowCheckNum:%d;%d", CheckNum, 0);
    (*NowCheckNum).var.Dataint = CheckNum;
    return;
}
bool checkOfCsJsonStrIsRight(strnew JsonInputStr, strnew JsonOutputStr) {
    JsonObject JsonObj = newJsonObjectByString(JsonInputStr);
    int NowCheckNum = JsonObj.getInt(&JsonObj, "NowCheckNum");
    char * PEnd = strstr(JsonObj.JsonString.Name._char, ",\"NowCheckNum\"");
    (*(PEnd++)) = '}';
    (*PEnd) = '\0';
    // 计算 cs 或其他检验算法
    int CheckNum = 0;
    for (int i = 0; i < strlen(JsonInputStr.Name._char); i++) {
        CheckNum += JsonInputStr.Name._char[i];
    }
    if (JsonInputStr.Name._char != JsonOutputStr.Name._char) {
        copyString(JsonOutputStr.Name._char, JsonInputStr.Name._char, JsonOutputStr.MaxLen, JsonInputStr.MaxLen);
    }
    return ((CheckNum == NowCheckNum) ? true : false);
}
