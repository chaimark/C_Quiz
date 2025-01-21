#include "./MyCmdDos/CsvSplit.h"
#include "./array_quiz/ArrayQuiz.h"
#include "./C_MyLib/NumberBaseLib.h"
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

typedef uint8_t  byte;
typedef uint32_t word;

#define MD5_BLOCK_SIZE 64
#define MD5_DIGEST_SIZE 16

// MD5的4个常数
static const word S[] = {7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21};
static const word K[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};
void base64_encode(strnew output, const char * input) {
    static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int input_len = strlen(input);
    int padding = 0;
    int output_len = 4 * ((input_len + 2) / 3); // 计算输出的大小
    for (int i = 0, j = 0; i < input_len;) {
        uint32_t buffer = 0;

        // 获取3个字节（24位）
        for (int k = 0; k < 3; k++) {
            if (i < input_len) {
                buffer |= (unsigned char)(input[i++]) << (16 - 8 * k);
            } else {
                padding++;
                buffer |= 0 << (16 - 8 * k); // 填充零
            }
        }

        // 将24位的数据分成4个6位部分
        for (int k = 0; k < 4 - padding; k++) {
            output.Name._char[j++] = base64_table[(buffer >> (18 - 6 * k)) & 0x3F];
        }

        // 添加填充符号（=）
        while (padding-- > 0) {
            output.Name._char[j++] = '=';
        }
    }
    output.Name._char[output_len] = '\0';  // 确保字符串结尾
}
// MD5函数步骤
void md5_transform(word * state, const byte * block) {
    word a = state[0], b = state[1], c = state[2], d = state[3], x[16];

    // 解密数据块
    for (int i = 0; i < 16; ++i) {
        x[i] = ((word)block[i * 4 + 3] << 24) | ((word)block[i * 4 + 2] << 16) |
            ((word)block[i * 4 + 1] << 8) | (word)block[i * 4 + 0];
    }

    // 四轮操作
    for (int i = 0; i < 64; ++i) {
        word f, g;

        if (i < 16) {
            f = (b & c) | (~b & d);
            g = i;
        } else if (i < 32) {
            f = (d & b) | (~d & c);
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = b ^ c ^ d;
            g = (3 * i + 5) % 16;
        } else {
            f = c ^ (b | ~d);
            g = (7 * i) % 16;
        }

        word temp = d;
        d = c;
        c = b;
        b = b + ((a + f + K[i] + x[g]) << S[i % 4] | (a + f + K[i] + x[g]) >> (32 - S[i % 4]));
        a = temp;
    }

    // 更新哈希值
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}
// 填充消息并进行MD5处理
void md5_encrypt(char * result, const char * data, const char * key) {
    word state[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};

    size_t len = strlen(data);
    size_t full_len = len + 1 + (56 - (len + 1) % 64);
    byte * message = (byte *)malloc(full_len + 8);

    memcpy(message, data, len);
    message[len] = 0x80; // 添加位填充

    // 长度信息（bit位）
    word bit_len = len * 8;
    message[full_len - 4] = (bit_len >> 24) & 0xFF;
    message[full_len - 3] = (bit_len >> 16) & 0xFF;
    message[full_len - 2] = (bit_len >> 8) & 0xFF;
    message[full_len - 1] = bit_len & 0xFF;

    // 对每个块进行MD5计算
    for (size_t i = 0; i < full_len / MD5_BLOCK_SIZE; ++i) {
        md5_transform(state, message + i * MD5_BLOCK_SIZE);
    }

    // 将结果保存到输出中
    for (int i = 0; i < MD5_DIGEST_SIZE; ++i) {
        sprintf(result + i * 2, "%02x", ((byte *)state)[i]);
    }

    free(message);
}
// URL 编码函数
void url_encode(strnew outStr, const char * str) {
    int len = strlen(str);
    char * encoded = outStr.Name._char;
    int j = 0;

    for (int i = 0; i < len; i++) {
        unsigned char c = str[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded[j++] = c;
        } else {
            sprintf(encoded + j, "%%%02X", c);
            j += 3;
        }
    }
    encoded[j] = '\0';
    return;
}
// BCD网关数组转字符串 （bcd 必须沾满）
void BCD_To_String(strnew str, strnew bcd) {
    HEX2ToASCII(bcd.Name._char, bcd.MaxLen, str.Name._char, str.MaxLen);
}
void assemble_token(strnew Outoken, long OverTimeSec) {
    char EEprom_METERID[4] = {0x75,0x44,0x02,0x71};
    char IDTemp[13] = {0};
    BCD_To_String(NEW_NAME(IDTemp), NEW_NAME(EEprom_METERID));

    const char * signature_method = "md5";
    const char * version = "2018-10-31";
    char * access_key = ML307.Access_key;
    newString(resource, 50);
    sprintf(resource.Name._char, "products/%s", ML307.UserName);

    // 计算签名
    char encrypt_text[70];
    sprintf(encrypt_text, "%ld\n%s\n%s\n%s", OverTimeSec, signature_method, resource.Name._char, version);
    printf("%s\n", encrypt_text);
    // 加密签名并转为 base64
    newString(res, 70);
    newString(sig, 258);
    md5_encrypt(sig.Name._char, encrypt_text, access_key);   // 暂存到 sig
    // printf("sign=HhSJmJUChxGbjnQaGiRbCQ%%3D%%3D\n");
    base64_encode(Outoken, sig.Name._char);    // 暂存到 Outoken
    memset(sig.Name._char, 0, 258); // 清空 sig
    url_encode(res, resource.Name._char);
    url_encode(sig, Outoken.Name._char);

    // 组装 token
    memset(Outoken.Name._char, 0, Outoken.MaxLen); // 复原 Outoken
    sprintf(Outoken.Name._char, "version=%s&res=%s/devices/%s&et=%ld&method=%s&sign=%s", version, res.Name._char, IDTemp, OverTimeSec, signature_method, sig.Name._char);
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



