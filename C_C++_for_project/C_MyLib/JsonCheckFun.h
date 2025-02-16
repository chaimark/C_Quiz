#ifndef JsonCheckFun
#define JsonCheckFun

#include "StrLib.h"
#include "JsonDataAnalyzeLib.h"
#include "JsonDataDoneLib.h"

#define AddCsToJsonAndPushJsonStr(JsonDataList, OutputJsonStr) \
JsonItem NowCheckNum = {0}; \
_AddCsToJsonAndPushJsonStr(&NowCheckNum, JsonDataList, OutputJsonStr)

extern void _AddCsToJsonAndPushJsonStr(JsonItem * NowCheckNum, newJsonList * JsonDataList, strnew OutputJsonStr);
extern bool checkOfCsJsonStrIsRight(strnew JsonInputStr, strnew JsonOutputStr);
#endif
