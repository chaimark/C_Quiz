#include "./MyCmdDos/CsvSplit.h"
#include "./array_quiz/ArrayQuiz.h"
#include "./C_MyLib/NumberBaseLib.h"
#include "./C_MyLib/StrLib.h"
#include "./C_MyLib/WinExcel.h"
#include "./C_MyLib/JsonDataDoneLib.h"


void IPstrToHexArray(strnew IpHex, const char * Ipstr) { //IP字符串转16进制
    char IP_String[] = {"255.255.255.255."};
    memset(IP_String, 0, strlen("255.255.255.255."));
    memcpy(IP_String, Ipstr, strlen(Ipstr));
    catString(IP_String, ".", strlen("255.255.255.255."), 1); //字符串拼接
    char Str[4] = {0};
    char * P_piont = NULL;
    char * Head = IP_String;
    int temp = 0;
    for (int i = 0; i < 4; i++) {
        memset(Str, 0, 3);
        if ((P_piont = strchr(Head, '.')) != NULL) {
            *P_piont = '\0';
            memcpy(Str, Head, strlen(Head));
            *P_piont = '.';
            Head = P_piont + 1;
            temp = doneAsciiStrToAnyBaseNumberData(Str, strlen(Str), 16);  //字符串转任意进制数
            IpHex.Name._char[i] = (unsigned char)temp;
        }
    }
}

int main() {
    unsigned char IpHex[4] = {0};
    IPstrToHexArray(NEW_NAME(IpHex), "192.168.1.1");
    return 0;
}
