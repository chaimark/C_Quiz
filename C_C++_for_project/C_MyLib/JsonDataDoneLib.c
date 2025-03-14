#include "JsonDataDoneLib.h"
#include "JsonDataAnalyzeLib.h"
#include <stdarg.h>
#include <stdio.h>

#define JSON_DATA (*_JsonData)

bool AddPullWTJsonKeyAndVer(JsonItem * ItemData, struct _JsonData This) {
    if (This.Head_JsonDataNote == NULL) {
        This.Head_JsonDataNote = ItemData;
        return true;
    }

    JsonItem * TempNode = This.Head_JsonDataNote;
    while ((*TempNode).next != NULL) {
        TempNode = (*TempNode).next;
    }

    (*ItemData).next = NULL;
    (*TempNode).next = ItemData;
    return true;
}

// 装载当前 json 数据到某数组
void setJsonItemToArrayStr(strnew OutputStr, JsonItem * TempNowNode) {
    static char Front_JsonItemLevel = 0;
    static char TempStr[50] = {0}; // 先进后出的栈区，用户缓存 {{}}

    if ((Front_JsonItemLevel - TempNowNode->JsonItemLevel) > 0) {
        for (int i = 0; i < (Front_JsonItemLevel - TempNowNode->JsonItemLevel); i++) {
            OutputStr.Name._char[OutputStr.getStrlen(&OutputStr)] = TempStr[strlen(TempStr) - 1]; // 括号出栈
            TempStr[strlen(TempStr) - 1] = 0;
        }
        catString(OutputStr.Name._char, ",", OutputStr.MaxLen, 1);
    }
    strnew NowItemLine = OutputStr;
    NowItemLine.Name._char += OutputStr.getStrlen(&OutputStr);
    NowItemLine.MaxLen = OutputStr.MaxLen - OutputStr.getStrlen(&OutputStr);
    switch (TempNowNode->KeyType) {
        case 'd': // %d 或 %i：有符号十进制整数。
            if (strcmp(TempNowNode->key, "") != 0) {
                sprintf(NowItemLine.Name._char, "\"%s\":%d", TempNowNode->key, TempNowNode->var.Dataint);
            } else {
                sprintf(NowItemLine.Name._char, "%d", TempNowNode->var.Dataint);
            }
            break;
        case 'D': // %ld：有符号十进制长整数。
            if (strcmp(TempNowNode->key, "") != 0) {
                sprintf(NowItemLine.Name._char, "\"%s\":%ld", TempNowNode->key, TempNowNode->var.Datalong);
            } else {
                sprintf(NowItemLine.Name._char, "%ld", TempNowNode->var.Datalong);
            }
            break;
        case 'f': // %f：浮点数。
            if (strcmp(TempNowNode->key, "") != 0) {
                sprintf(NowItemLine.Name._char, "\"%s\":%f", TempNowNode->key, TempNowNode->var.Datafloat);
            } else {
                sprintf(NowItemLine.Name._char, "%f", TempNowNode->var.Datafloat);
            }
            break;
        case 'F': // %lf：双精度浮点数。
            if (strcmp(TempNowNode->key, "") != 0) {
                sprintf(NowItemLine.Name._char, "\"%s\":%lf", TempNowNode->key, TempNowNode->var.Datadouble);
            } else {
                sprintf(NowItemLine.Name._char, "%lf", TempNowNode->var.Datadouble);
            }
            break;
        case 'c': // %c：单个字符。
            if (strcmp(TempNowNode->key, "") != 0) {
                sprintf(NowItemLine.Name._char, "\"%s\":\"%c\"", TempNowNode->key, TempNowNode->var.Datachar);
            } else {
                sprintf(NowItemLine.Name._char, "%c", TempNowNode->var.Datachar);
            }
            break;
        case 's': // %s：字符串。
            if (strcmp(TempNowNode->key, "") != 0) {
                sprintf(NowItemLine.Name._char, "\"%s\":\"%s\"", TempNowNode->key, TempNowNode->var._char);
            } else {
                sprintf(NowItemLine.Name._char, "%s", TempNowNode->var._char);
            }
            break;
        case 'S': // %ls：不含引号的字符串，如 bool:null、true、false。
            if (strcmp(TempNowNode->key, "") != 0) {
                sprintf(NowItemLine.Name._char, "\"%s\":%s", TempNowNode->key, TempNowNode->var._char);
            } else {
                sprintf(NowItemLine.Name._char, "%s", TempNowNode->var._char);
            }
            break;
        case 'p': // %p：指针地址。 对象数组
            if (strcmp(TempNowNode->key, "") != 0) {
                sprintf(NowItemLine.Name._char, "\"%s\":", TempNowNode->key);
            }
            catString(NowItemLine.Name._char, "[", NowItemLine.MaxLen, 1);
            catString(TempStr, "]", ARR_SIZE(TempStr), 1); // 括号入栈区
            break;
        case 'J': // %p：指针地址。 对象
            if (strcmp(TempNowNode->key, "") != 0) {
                sprintf(NowItemLine.Name._char, "\"%s\":", TempNowNode->key);
            }
            catString(NowItemLine.Name._char, "{", NowItemLine.MaxLen, 1);
            catString(TempStr, "}", ARR_SIZE(TempStr), 1); // 括号入栈区
            break;
    }

    if ((TempNowNode->KeyType != 'p') && (TempNowNode->KeyType != 'J')) {
        if ((TempNowNode->next != NULL) && (TempNowNode->JsonItemLevel <= TempNowNode->next->JsonItemLevel)) {
            catString(NowItemLine.Name._char, ",", NowItemLine.MaxLen, 1);
        }
    }
    Front_JsonItemLevel = TempNowNode->JsonItemLevel;
    if (TempNowNode->next == NULL) { // 无下一个节点，推出栈区所有括号
        int TempStr_OverLen = strlen(TempStr);
        for (int i = 0; i < TempStr_OverLen; i++) {
            OutputStr.Name._char[OutputStr.getStrlen(&OutputStr)] = TempStr[strlen(TempStr) - 1]; // 括号出栈
            TempStr[strlen(TempStr) - 1] = 0;
        }
        Front_JsonItemLevel = 0;
        memset(TempStr, 0, ARR_SIZE(TempStr)); // 清空栈区
    }
    return;
}
void _ResJsonDataNote(struct _JsonData This) {
    This._JsonData = &This;
}
bool _OutPushJsonString(strnew OutputStr, struct _JsonData This) {
    JsonItem * TempNowNode = This.Head_JsonDataNote;
    memset(OutputStr.Name._char, 0, OutputStr.MaxLen); // 清空 OutputStr
    catString(OutputStr.Name._char, "{", OutputStr.MaxLen, 1);
    while (TempNowNode != NULL) {
        setJsonItemToArrayStr(OutputStr, TempNowNode);
        TempNowNode = TempNowNode->next;
    }
    catString(OutputStr.Name._char, "}", OutputStr.MaxLen, 1);
    This._JsonData = NULL;
    return true;
}
void _setJsonItemData(struct _JsonData This, JsonItem * ItemData, char * fmt, ...) {
    JsonItem * TempNext = NULL;
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
                fmtChr = (*fmt == 'f' ? 'F' : (*fmt == 'd' ? 'D' : (*fmt == 'p' ? 'J' : (*fmt == 's' ? 'S' : ' '))));
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
                case 'S': // %s：字符串。
                    ItemData->KeyType = 'S';
                    ItemData->var._char = va_arg(args, char *);
                    break;
                case 'p': // %p：指针地址。
                    ItemData->KeyType = 'p';
                    ItemData->var._char = va_arg(args, void *);
                    ItemData->var._char = NULL;
                    break;
                case 'J': // %p：指针地址。
                    ItemData->KeyType = 'J';
                    ItemData->var._char = va_arg(args, void *);
                    ItemData->var._char = NULL;
                    break;
            }
            break;
        } else {
            fmt++;
        }
    }
    ItemData->JsonItemLevel = va_arg(args, int);
    ItemData->next = TempNext; // 设置 ItemData 结构体中的指针
    va_end(args);              // 结束对 args 的访问

    AddPullWTJsonKeyAndVer(ItemData, This._JsonData); // 向 WTMqttJson 中添加关键字与值
}

// 建立对象的函数
newJsonList NEW_JSON_LIST(newJsonList * DataInit) {
    (*DataInit)._JsonData = DataInit;
    (*DataInit).Head_JsonDataNote = NULL;
    (*DataInit).ResJsonDataNote = _ResJsonDataNote;
    (*DataInit).OutPushJsonString = _OutPushJsonString;
    (*DataInit).setJsonItemData = _setJsonItemData;
    return (*DataInit);
}

