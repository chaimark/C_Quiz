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

void DoubleOrFloatToBuff(strnew OutBuff, double Number, bool IsDouble) {
#if __STDC_VERSION__ >= 199901L
    /*Now C99*/
    int ArraySize = 0;
    if (IsDouble) {
        ArraySize = sizeof(double);
    } else {
        ArraySize = sizeof(float);
    }
    char TempBuff[ArraySize];
    memset(TempBuff, 0, ArraySize);
    if ((IsDouble) && (OutBuff.MaxLen >= ArraySize)) {
        memcpy(TempBuff, &Number, ArraySize);
        swapStr(TempBuff, ArraySize);
        memcpy(OutBuff.Name._char, TempBuff, ArraySize);
    } else if (OutBuff.MaxLen >= ArraySize) {
        float tempNum = (float)Number;
        memcpy(TempBuff, &tempNum, ArraySize);
        swapStr(TempBuff, ArraySize);
        memcpy(OutBuff.Name._char, TempBuff, ArraySize);
    }
#else
    /*Not C99*/
    int ArraySize = 0;
    if (IsDouble) {
        ArraySize = sizeof(double);
    } else {
        ArraySize = sizeof(float);
    }
    char * TempBuff = (char *)malloc(ArraySize);
    memset(TempBuff, 0, ArraySize);
    if ((IsDouble) && (OutBuff.MaxLen >= ArraySize)) {
        memcpy(TempBuff, &Number, ArraySize);
        swapStr(TempBuff, ArraySize);
        memcpy(OutBuff.Name._char, TempBuff, ArraySize);
    } else if (OutBuff.MaxLen >= ArraySize) {
        float tempNum = (float)Number;
        memcpy(TempBuff, &tempNum, ArraySize);
        swapStr(TempBuff, ArraySize);
        memcpy(OutBuff.Name._char, TempBuff, ArraySize);
    }
#endif
}

int main(int argc, char * argv[]) {
    double Dome = 0;
    bool isDouble = false;
    if (strcmp(argv[1], "float") == 0) {
        isDouble = true;
    }
    if (isDouble == true) {
        Dome = 10.1;
    } else {
        Dome = 20.1;
    }
    newString(quizArr, 8);
    DoubleOrFloatToBuff(quizArr, Dome, isDouble);
    for (int i = 0; i < (isDouble ? 4 : 8); i++) {
        printf("%x\n", quizArr.Name._char[i]);
    }
}

