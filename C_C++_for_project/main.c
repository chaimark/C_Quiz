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

int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("please input : ./main float|double 12.35\n>:");
    }
    newString(OutBuff, 8);
    union DoubleOrFloat_T {
        float NumberF;
        double NumberD;
    }Data_S;
    double TempNum = 0;
    if (strcmp(argv[1], "float") != 0) {
        Data_S.NumberD = doneAsciiToDouble(argv[2]);
        DoubleOrFloatToBuff(OutBuff, Data_S.NumberD, true);
        printf("%s Buf = %02X %02X %02X %02X %02X %02X %02X %02X", argv[1],
            (uint8_t)OutBuff.Name._char[0],
            (uint8_t)OutBuff.Name._char[1],
            (uint8_t)OutBuff.Name._char[2],
            (uint8_t)OutBuff.Name._char[3],
            (uint8_t)OutBuff.Name._char[4],
            (uint8_t)OutBuff.Name._char[5],
            (uint8_t)OutBuff.Name._char[6],
            (uint8_t)OutBuff.Name._char[7]
        );
        BuffToFloatOrDouble(&TempNum, OutBuff, true);
        printf("\n%lf\n", (double)TempNum);
    } else {
        Data_S.NumberF = (float)doneAsciiToDouble(argv[2]);
        DoubleOrFloatToBuff(OutBuff, Data_S.NumberF, false);
        printf("%s Buf = %02X %02X %02X %02X", argv[1],
            (uint8_t)OutBuff.Name._char[0],
            (uint8_t)OutBuff.Name._char[1],
            (uint8_t)OutBuff.Name._char[2],
            (uint8_t)OutBuff.Name._char[3]
        );
        BuffToFloatOrDouble(&TempNum, OutBuff, false);
        printf("\n%f\n", (float)TempNum);
    }
}
