#ifndef _JSON_DATA_H
#define _JSON_DATA_H

#include "StrLib.h"

typedef struct __JsonItem {
    char KeyType;
    char key[20];
    union _newVar {

        int Dataint;       // 整型指针
        long Datalong;     // 长整型指针
        float Datafloat;   // 单精度浮点型指针
        double Datadouble; // 双精度浮点型指针
        char Datachar;     // 字符型指针

        char * _char;                  // 字符型指针
        void * _void;                  // 无定义形指针
        struct __JsonItem * _JsonItem; // 结构体指针
    } var;
    char JsonItemLevel;     // json数据层级
    struct __JsonItem * next;
} JsonItem;
// 类定义
typedef struct _WTMqttJsonData {
    JsonItem * Head_WTjsonDataNote;
    bool (*AddPullWTJsonKeyAndVer)(JsonItem * ItemData, struct _WTMqttJsonData This);
    bool (*OutPushJsonString)(strnew OutputStr, struct _WTMqttJsonData This);
} WTMqttJson;
// 类方法
bool _AddPullWTJsonKeyAndVer(JsonItem * ItemData, struct _WTMqttJsonData This);              // 向 WTMqttJson 中添加关键字与值
bool _OutPushJsonString(strnew OutputStr, struct _WTMqttJsonData This); // 输出json 字符串
// 建立对象
#define NEW_WT_JSON(DataInit) New_WT_Json_Obj(DataInit)
extern WTMqttJson New_WT_Json_Obj(WTMqttJson * DataInit); // 建立对象的函数
extern void setJsonItemData(JsonItem * ItemData, char * fmt, ...);

#endif


