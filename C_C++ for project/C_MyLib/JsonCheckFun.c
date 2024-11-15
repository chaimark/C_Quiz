#include "JsonCheckFun.h"
#include "stdio.h"

void _AddCsToJsonAndPushJsonStr(JsonItem * NowCheckNum, newJsonList * JsonDataList, strnew OutputJsonStr) {
    int CheckNum = 0;
    setJsonItemData(NowCheckNum, "NowCheckNum:%d;%d", CheckNum, 0);
    (*JsonDataList).OutPushJsonString(OutputJsonStr, JsonDataList);   // 输出 jsonstr
    // 计算 cs 或其他检验算法
    for (int i = 0; i < OutputJsonStr.MaxLen; i++) {
        CheckNum += OutputJsonStr.Name._char[i];
    }
    memset(OutputJsonStr.Name._char, 0, OutputJsonStr.MaxLen);
    (*NowCheckNum).var.Dataint = CheckNum;
    return;
}
bool checkOfCsJsonStrIsRight(strnew JsonStr) {
    JsonObject JsonObj = newJsonObjectByString(JsonStr);
    int NowCheckNum = JsonObj.getInt(&JsonObj, "NowCheckNum");
    char * PEnd = strstr(JsonObj.JsonString.Name._char, ",\"NowCheckNum\"");
    (*(PEnd++)) = '}';
    (*PEnd) = '\0';
    return true;
}
