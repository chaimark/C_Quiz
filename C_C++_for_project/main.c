// #include "./MyCmdDos/CsvSplit.h"
// #include "./array_quiz/ArrayQuiz.h"
// #include "./MyCmdDos/CsvSplit.h"
// #include "./array_quiz/ArrayQuiz.h"
#include "./C_MyLib/NumberBaseLib.h"
#include "./C_MyLib/StrLib.h"
// #include "./C_MyLib/WinExcel.h"
#include "./C_MyLib/JsonDataDoneLib.h"
#include "./C_MyLib/JsonDataDoneLib.h"
#include "./C_MyLib/JsonDataAnalyzeLib.h"
#include "./C_MyLib/JsonCheckFun.h"
//#include "./C_MyLib/SendDataBySerial.h"
// #include "./mbedtls/token.h"
#include <stdio.h>

// {"NowPackNum":0,"Code":"11223344556677889900","CsCheckNum":114}
int main(int argc, char * argv[]) {
    char Head[1000] = {0};
    memcpy(Head, argv[1], strlen(argv[1]));
    int Len = strlen(Head);
    uint8_t CsNum = 0;
    for (int i = 0; i < Len; i++) {
        CsNum += Head[i];
    }
    char CS_END[3] = {0};
    sprintf(CS_END, "%02x", CsNum);
    catString(Head, CS_END, 1000, strlen(CS_END));
    catString(Head, "16", 1000, 2);
    printf("\n=================================\nchar of SendBuff\n");
    printf("%s \n", Head);
}
