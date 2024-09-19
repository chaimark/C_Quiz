#ifndef _JSON_DATA_ANALYZE_LIB_H
#define _JSON_DATA_ANALYZE_LIB_H

#include "JsonDataDoneLib.h"
#include "StrLib.h"
// Json数组类
typedef struct _JsonArray {
    strnew JsonString;
    int (*sizeItemNum)(struct _JsonArray This);                         // 获取Json 数组个数
    bool (*isJsonNull)(struct _JsonArray This);                         // 判断Json 是否为空
    void (*get)(struct _JsonArray This, strnew OutStr, int ItemNum);    // 获取Json 某元素
    // 增加流函数
} JsonArray;
// 方法
int Arr_sizeItemNum(struct _JsonArray This);
bool Arr_isJsonNull(struct _JsonArray This);
void Arr_get(struct _JsonArray This, strnew OutStr, int ItemNum); // 获取Json 某元素
// 建立对象示例
extern JsonArray newJsonArrayByString(strnew DataInit); // 建立对象数组的函数

//==========================================================================================//
//==========================================================================================//
//==========================================================================================//
//==========================================================================================//
//==========================================================================================//

// json类
typedef struct _JsonObject {
    strnew JsonString;
    int (*sizeStr)(struct _JsonObject This);                                            // 获取Json 键值对的个数
    bool (*isJsonNull)(struct _JsonObject This, char Key[]);                            // 判断Json 是否为空
    int (*getInt)(struct _JsonObject This, char Key[]);                                 // 获取Json int
    double (*getDouble)(struct _JsonObject This, char Key[]);                           // 获取Json double
    bool (*getBool)(struct _JsonObject This, char Key[]);                               // 获取Json bool
    void (*getString)(struct _JsonObject This, char Key[], strnew OutStr);              // 获取Json string
    struct _JsonArray(*getArray)(struct _JsonObject This, char Key[], strnew OutStr);   // 获取Json array
    struct _JsonObject(*getObject)(struct _JsonObject This, char Key[], strnew OutStr); // 获取Json object
} JsonObject;
// 方法
int Obj_sizeStr(struct _JsonObject This);
bool Obj_isJsonNull(struct _JsonObject This, char Key[]);
int Obj_getInt(struct _JsonObject This, char Key[]);
double Obj_getDouble(struct _JsonObject This, char Key[]);
bool Obj_getBool(struct _JsonObject This, char Key[]);
void Obj_getString(struct _JsonObject This, char Key[], strnew OutStr);
struct _JsonArray Obj_getArray(struct _JsonObject This, char Key[], strnew OutStr);
struct _JsonObject Obj_getObject(struct _JsonObject This, char Key[], strnew OutStr);
// 建立对象示例
extern JsonObject newJsonObjectByString(strnew DataInit); // 建立对象的函数


#endif
