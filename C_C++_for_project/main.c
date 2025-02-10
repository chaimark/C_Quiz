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
    if ((IsDouble) && (OutBuff.MaxLen >= sizeof(double))) {
        memcpy(OutBuff.Name._char, &Number, sizeof(double));
    } else if (OutBuff.MaxLen >= sizeof(float)) {
        float tempNum = (float)Number;
        memcpy(OutBuff.Name._char, &tempNum, sizeof(float));
    }
}

void main(void) {
    float Dome = 10.2;
    newString(quizArr, 8);
    DoubleOrFloatToBuff(quizArr, Dome, false);
    for (int i = 0; i < quizArr.MaxLen; i++) {
        printf("%x\n", quizArr.Name._char[i]);
    }
}

