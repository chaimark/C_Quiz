#include "JsonDataDoneLib.h"
#include <stdarg.h>
#include <stdio.h>

WTMqttJson * _JsonData = NULL;
#define JSON_DATA (*_JsonData)

bool _AddPullWTJsonKeyAndVer(JsonItem * ItemData, struct _WTMqttJsonData This) {
    if (This.Head_WTjsonDataNote == NULL) {
        This.Head_WTjsonDataNote = ItemData;
        return true;
    }

    JsonItem * TempNode = This.Head_WTjsonDataNote;
    while (TempNode->next != NULL) {
        TempNode = TempNode->next;
    }

    TempNode->next = ItemData;
    ItemData->next = NULL;

    return true;
}

// 装载当前 json 数据到某数组
int setJsonItemToArrayStr(strnew OutputStr, JsonItem * TempNowNode) {
    char ItemLine[50] = {0};
    strnew NowItemLine = NEW_NAME(ItemLine);
    switch (TempNowNode->KeyType) {
        case 'd': // %d 或 %i：有符号十进制整数。
            sprintf(NowItemLine.Name._char, "\"%s\": %d", TempNowNode->key, TempNowNode->var.Dataint);
            break;
        case 'D': // %ld：有符号十进制长整数。
            sprintf(NowItemLine.Name._char, "\"%s\": %ld", TempNowNode->key, TempNowNode->var.Datalong);
            break;
        case 'f': // %f：浮点数。
            sprintf(NowItemLine.Name._char, "\"%s\": %f", TempNowNode->key, TempNowNode->var.Datafloat);
            break;
        case 'F': // %lf：双精度浮点数。
            sprintf(NowItemLine.Name._char, "\"%s\": %lf", TempNowNode->key, TempNowNode->var.Datadouble);
            break;
        case 'c': // %c：单个字符。
            sprintf(NowItemLine.Name._char, "\"%s\": \"%c\"", TempNowNode->key, TempNowNode->var.Datachar);
            break;
        case 's': // %s：字符串。
            sprintf(NowItemLine.Name._char, "\"%s\": \"%s\"", TempNowNode->key, TempNowNode->var._char);
            break;
        case 'p': // %p：指针地址。 对象数组
            sprintf(NowItemLine.Name._char, "\"%s\": [{}]", TempNowNode->key);
            break;
        case 'J': // %p：指针地址。 对象
            sprintf(NowItemLine.Name._char, "\"%s\": {}", TempNowNode->key);
            break;
    }
    char TempEndSing[10] = {0};
    int TempEndSingLen = 0;
    int OutputStrLen = strlen(OutputStr.Name._char) - 1;
    while (OutputStr.Name._char[OutputStrLen] == ']' || OutputStr.Name._char[OutputStrLen] == '}') {
        TempEndSing[TempEndSingLen++] = OutputStr.Name._char[OutputStrLen];
        OutputStr.Name._char[OutputStrLen] = 0;
        OutputStrLen--;
    }
    if ((OutputStr.Name._char[OutputStrLen] != '{') && (OutputStr.Name._char[OutputStrLen] != '[')) {
        catString(OutputStr.Name._char, ",", OutputStr.MaxLen, 1);
    }
    OutputStrLen = catString(OutputStr.Name._char, NowItemLine.Name._char, OutputStr.MaxLen, strlen(NowItemLine.Name._char));
    if (TempEndSingLen != 0) {
        swapStr(TempEndSing, TempEndSingLen);
        OutputStrLen = catString(OutputStr.Name._char, TempEndSing, OutputStr.MaxLen, TempEndSingLen);
    }
    return OutputStrLen;
}

bool _OutPushJsonString(strnew OutputStr, struct _WTMqttJsonData This) {
    JsonItem * TempNowNode = This.Head_WTjsonDataNote;
    memset(OutputStr.Name._char, 0, OutputStr.MaxLen); // 清空 OutputStr

    sprintf(OutputStr.Name._char, "{}");
    while (TempNowNode != NULL) {
        setJsonItemToArrayStr(OutputStr, TempNowNode);
        TempNowNode = TempNowNode->next;
    }
    return true;
}

// 建立对象的函数
WTMqttJson New_WT_Json_Obj(WTMqttJson * DataInit) {
    _JsonData = DataInit;
    (* DataInit).Head_WTjsonDataNote = NULL;
    (* DataInit).AddPullWTJsonKeyAndVer = _AddPullWTJsonKeyAndVer;
    (* DataInit).OutPushJsonString = _OutPushJsonString;
    return (* DataInit);
}

void setJsonItemData(JsonItem * ItemData, char * fmt, ...) {
    char keyFromStr[200] = {0};
    strcpy(keyFromStr, fmt);
    char * TempKeyChr = strchr(keyFromStr, ':');
    (*TempKeyChr) = '\0';
    strcpy(ItemData->key, keyFromStr); // 取出关键字

    va_list args;        // 定义一个 va_list 类型变量 args，用于存储可变参数列表
    va_start(args, fmt); // 初始化 args，使其指向传入的 fmt 参数后的第一个参数
    while (*fmt) {
        if (*fmt == '%' && *(fmt + 1) != '%') {
            char fmtChr = 0;
            fmt++;
            if (*fmt == 'l') {
                fmt++;
                fmtChr = (*fmt == 'f' ? 'F' : (*fmt == 'd' ? 'D' : 'p'));
            } else {
                fmtChr = *fmt;
            }
            switch (fmtChr) {
                case 'd': // %d 或 %i：有符号十进制整数。
                    ItemData->KeyType = 'd';
                    ItemData->var.Dataint = va_arg(args, int);
                    break;
                case 'D': // %ld：有符号十进制长整数。
                    ItemData->KeyType = 'D';
                    ItemData->var.Datalong = va_arg(args, long);
                    break;
                case 'f': // %f：浮点数。
                    ItemData->KeyType = 'f';
                    ItemData->var.Datafloat = va_arg(args, double);
                    break;
                case 'F': // %lf：双精度浮点数。
                    ItemData->KeyType = 'F';
                    ItemData->var.Datadouble = va_arg(args, double);
                    break;
                case 'c': // %c：单个字符。
                    ItemData->KeyType = 'c';
                    ItemData->var.Datachar = (char)va_arg(args, int);
                    break;
                case 's': // %s：字符串。
                    ItemData->KeyType = 's';
                    ItemData->var._char = va_arg(args, char *);
                    break;
                case 'p': // %p：指针地址。
                    ItemData->KeyType = 'p';
                    ItemData->var._JsonItem = va_arg(args, void *);
                    break;
                case 'J': // %p：指针地址。
                    ItemData->KeyType = 'J';
                    ItemData->var._JsonItem = va_arg(args, void *);
                    break;
            }
        } else {
            fmt++;
        }
    }
    ItemData->next = NULL; // 设置 ItemData 结构体中的指针
    va_end(args);          // 结束对 args 的访问

    JSON_DATA.AddPullWTJsonKeyAndVer(ItemData, _JsonData); // 向 WTMqttJson 中添加关键字与值
}


