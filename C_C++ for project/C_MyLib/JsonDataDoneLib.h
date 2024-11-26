#ifndef _JSON_DATA_DONELIB_H
#define _JSON_DATA_DONELIB_H

#include "StrLib.h"

typedef struct __JsonItem {
    char KeyType;
    char key[50];
    union _newVar {
        int Dataint;       // 整型指针
        long Datalong;     // 长整型指针
        float Datafloat;   // 单精度浮点型指针
        double Datadouble; // 双精度浮点型指针
        char Datachar;     // 字符型指针

        char * _char; // 字符型指针
    } var;
    char JsonItemLevel; // json数据层级
    struct __JsonItem * next;
} JsonItem;
// 类定义
typedef struct _JsonData {
    JsonItem * Head_JsonDataNote;
    void (*ResJsonDataNote)(struct _JsonData This);
    bool (*OutPushJsonString)(strnew OutputStr, struct _JsonData This);
} newJsonList;
// 类方法
void _ResJsonDataNote(struct _JsonData This);
bool _OutPushJsonString(strnew OutputStr, struct _JsonData This);        // 输出 json 字符串
// 建立对象
extern newJsonList NEW_JSON_LIST(newJsonList * DataInit); // 建立对象的函数
extern void setJsonItemData(JsonItem * ItemData, char * fmt, ...);
#endif
