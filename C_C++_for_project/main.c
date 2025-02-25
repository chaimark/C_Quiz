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

// // IPstrToHexArray 函数定义
// void IPstrToHexArray(strnew IpHex, const char * Ipstr) { //IP字符串转16进制
//     char IP_String[] = {"255.255.255.255.."};
//     memset(IP_String, 0, strlen("255.255.255.255.."));
//     memcpy(IP_String, Ipstr, strlen(Ipstr));
//     catString(IP_String, ".", strlen("255.255.255.255.."), 1); //字符串拼接
//     char Str[4] = {0};
//     char * P_piont = NULL;
//     char * Head = IP_String;
//     int temp = 0;
//     for (int i = 0; i < 4; i++) {
//         memset(Str, 0, 3);
//         if ((P_piont = strchr(Head, '.')) != NULL) {
//             *P_piont = '\0';
//             memcpy(Str, Head, strlen(Head));
//             *P_piont = '.';
//             Head = P_piont + 1;
//             temp = doneAsciiStrToAnyBaseNumberData(Str, 16);  //字符串转任意进制数
//             IpHex.Name._char[i] = (unsigned char)temp;
//         }
//     }
// }

// // 主函数
// //int main(int argc, char * argv[]) {
// int main(void) {
//     unsigned char NET_Remote_Url[] = "221.214.219.202\0";
//     newString(EEprom_IP, 4);
//     IPstrToHexArray(EEprom_IP, NET_Remote_Url);
//     for (int i = 0; i < 4; i++) {
//         printf("%2x %d\n", (EEprom_IP.Name._char[i] & 0xff), (unsigned char)(EEprom_IP.Name._char[i]));
//     }
//     return 0;
// }

// // 主函数
// int main(int argc, char * argv[]) {
//     if (argc != 3) {
//         fprintf(stderr, "Usage: %s <-f / -d> <number>\n", argv[0]);
//         return 1;
//     }
//     double number = doneAsciiToDouble(argv[2]);
//     newString(outBuff, sizeof(double));

//     int buffLen = 0;
//     if (strstr(argv[1], "-f") != NULL) {
//         DoubleOrFloatToBuff(outBuff, (float)number, false);
//         buffLen = 4;
//     } else if (strstr(argv[1], "-d") != NULL) {
//         DoubleOrFloatToBuff(outBuff, (double)number, true);
//         buffLen = 8;
//     } else {
//         fprintf(stderr, "Usage: %s <-f / -d> <number>\n", argv[0]);
//         return 1;
//     }

//     printf("%lf == ", number);
//     for (int i = 0; i < buffLen; i++) {
//         printf("%02x", (unsigned char)outBuff.Name._char[i] & 0xFF);
//     }
//     printf("\n");

//     return 0;
// }

int main(void) {
    float insideT = 10.2;
    unsigned char TempBuf[5] = {0};
    sprintf(TempBuf, "%f", insideT);
    for (int i = 0; i < 4; i++) {
        printf("%c\n",TempBuf[i]);
    }
}