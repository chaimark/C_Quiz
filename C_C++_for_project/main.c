#include "./MyCmdDos/CsvSplit.h"
#include "./array_quiz/ArrayQuiz.h"
#include "./MyCmdDos/CsvSplit.h"
#include "./array_quiz/ArrayQuiz.h"
#include "./C_MyLib/NumberBaseLib.h"
#include "./C_MyLib/StrLib.h"
#include "./C_MyLib/WinExcel.h"
#include "./C_MyLib/JsonDataDoneLib.h"
#include "./C_MyLib/JsonDataDoneLib.h"
#include "./C_MyLib/JsonDataAnalyzeLib.h"
#include "./C_MyLib/JsonCheckFun.h"
#include "./C_MyLib/SendDataBySerial.h"
#include "./mbedtls/token.h"
#include <stdio.h>

////////////////////////////

typedef struct _ModelDevData {
    char Sing;             // 初始化标志
    char Access_key[60];
    char UserName[20];     // 用户名
    char PassWord[512];     // 密码
} ModelDevData;

ModelDevData ML307 = {
    .Sing = 0xB2,
    .Access_key = "kxc3VSPtJXnf66FlG21Hh9kTL1dXU9F1FSPJ4yHPSxE=",
    .UserName = "c4bPG3v7Ii",
    .PassWord = "version=2018-10-31&res=products%2Fc4bPG3v7Ii%2Fdevices%2F75440271&et=1959846627&method=md5&sign=HhSJmJUChxGbjnQaGiRbCQ%3D%3D",
};

#include <string.h>
#include <stdint.h>

// BCD网关数组转字符串 （bcd 必须沾满）
void BCD_To_String(strnew str, strnew bcd) {
    HEX2ToASCII(bcd.Name._char, bcd.MaxLen, str.Name._char, str.MaxLen);
}
char EEprom_METERID[4] = {0x75,0x44,0x02,0x71};
void assemble_token(strnew Outoken, long OverTimeSec) {
    char IDTemp[13] = {0};
    BCD_To_String(NEW_NAME(IDTemp), NEW_NAME(EEprom_METERID));
    onenet_msg_t MyMsg = {0};
    memcpy(MyMsg.produt_id, ML307.UserName, strlen(ML307.UserName));
    memcpy(MyMsg.key, ML307.Access_key, strlen(ML307.Access_key));
    memcpy(MyMsg.device_name, IDTemp, strlen(IDTemp));
    onenet_creat_token_init(&MyMsg, OverTimeSec, Outoken.Name._char, Outoken.MaxLen);
    printf("%s\n", Outoken.Name._char);
}

typedef struct {
    /** 年 */
    uint32_t year;
    /** 月 */
    uint32_t month;
    /** 日 */
    uint32_t day;
    /** 周 */
    uint32_t week;
    /** 时 */
    uint32_t hour;
    /** 分 */
    uint32_t minute;
    /** 秒 */
    uint32_t second;

} TimrFl;
TimrFl RTC_Date;
#define NowYear RTC_Date.year
#define NowMonth RTC_Date.month
#define NowDay RTC_Date.day
#define NowWeek RTC_Date.week
#define NowHour RTC_Date.hour
#define NowMinute RTC_Date.minute
#define NowSecond RTC_Date.second


// 判断是否为闰年
int isLeapYear(uint32_t year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// 计算从1970年1月1日到指定日期的总天数
int calculate_days(int year, int month, int day) {
    year = (uint32_t)anyBaseToAnyBase((uint64_t)year, 10, 16) + 2000;
    month = (uint32_t)anyBaseToAnyBase((uint64_t)month, 10, 16);
    day = (uint32_t)anyBaseToAnyBase((uint64_t)day, 10, 16);
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int total_days = 0;
    int i;

    // 计算从1970年到当前年份的总天数
    for (i = 1970; i < year; i++) {
        total_days += isLeapYear(i) ? 366 : 365;
    }

    // 计算当前年份从1月1日到指定日期的天数
    for (i = 0; i < month - 1; i++) {
        total_days += days_in_month[i];
        if (i == 1 && isLeapYear(year)) { // 2月需要额外加一天（闰年）
            total_days++;
        }
    }
    // 加上当前月份的天数
    total_days += (day - 1);
    return total_days;
}
// 计算时间戳（秒数）
long get_timestamp(void) {
    // 计算从1970年1月1日到指定日期的总天数
    int days = calculate_days(NowYear & 0x00FF, NowMonth, NowDay) - 1;
    // 转换为秒数
    long OverTimeSec = days * 86400;    // 每天86400秒
    OverTimeSec += 57600; // 1970年1月1日早上8点开始; 外加 8 小时时区
    OverTimeSec += (uint32_t)anyBaseToAnyBase((uint64_t)NowHour, 10, 16) * 3600;      // 小时转秒
    OverTimeSec += (uint32_t)anyBaseToAnyBase((uint64_t)NowMinute, 10, 16) * 60;      // 分钟转秒
    OverTimeSec += (uint32_t)anyBaseToAnyBase((uint64_t)NowSecond, 10, 16);           // 加上秒
    return OverTimeSec;
}
// 计算 OneNET token
void CalculateOneNetToken(void) {
    RTC_Date.year = 0x2032;
    RTC_Date.month = 0x02;
    RTC_Date.day = 0x08;
    RTC_Date.hour = 0x17;
    RTC_Date.minute = 0x50;
    RTC_Date.second = 0x27;

    memset(ML307.PassWord, 0, ARR_SIZE(ML307.PassWord));
    // 当前时间戳 + 100天的秒数
    // long OverTimeSec = (100 * 24 * 60 * 60) + get_timestamp();
    long OverTimeSec = get_timestamp();
    assemble_token(NEW_NAME(ML307.PassWord), OverTimeSec);   // 生成token
}

void main(void) {
    CalculateOneNetToken();
    printf("%s\n", ML307.PassWord);
}

