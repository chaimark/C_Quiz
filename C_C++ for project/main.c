#include "./MyCmdDos/CsvSplit.h"
#include "./array_quiz/ArrayQuiz.h"
#include "./C_MyLib/NumberBaseLib.h"
#include "./C_MyLib/StrLib.h"
#include "./C_MyLib/WinExcel.h"
#include "./C_MyLib/JsonDataDoneLib.h"
#include "./C_MyLib/JsonDataAnalyzeLib.h"

char JsonStrDown[1000] = {
    "{\
        \"string\": \"Hello, world!\",\
        \"number\": 42,\
        \"boolean\": true,\
        \"nullValue\": null,\
        \"array\": [1, 2, 3, \"four\", true, null],\
        \"object\": {\
        \"key1\": \"value1\",\
        \"key2\": 100,\
        \"key3\": {\"nestedKey1\": \"nestedValue1\",\
        \"nestedKey2\": [10, 20, 30]},\
        \"key4\": [\"a\", \"b\", \"c\"]},\
        \"nestedArray\": [\
            {\"id\": 1, \"name\": \"Item 1\"},\
            {\"id\": 2, \"name\": \"Item 2\"}\
        ]\
    }"};

// 处理 WT的JSON 指令
bool WT_MQTT_JSON_Analysis(void)
{
    return true;
}

int main()
{
    JsonObject JsonObj = newJsonObjectByString(NEW_NAME(JsonStrDown));
    newString(TempStr, 100);
    JsonObj.getString(&JsonObj, "string", TempStr);
    int number = JsonObj.getInt(&JsonObj, "number");
    bool boolean = JsonObj.getBool(&JsonObj, "boolean");
    

}
