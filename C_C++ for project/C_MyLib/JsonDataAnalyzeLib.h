#ifndef _JSON_DATA_ANALYZE_H
#define _JSON_DATA_ANALYZE_H

#include "StrLib.h"
// Json数组类
typedef struct _JsonArray
{
    strnew JsonString;
    bool (*isJsonNull)(JsonArray This, int ItemNum);                       // 判断Json是否为空
    int (*getInt)(struct _JsonArray This, int ItemNum);                    // 获取Json int
    double (*getDouble)(struct _JsonArray This, int ItemNum);              // 获取Json double
    bool (*getBool)(struct _JsonArray This, int ItemNum);                  // 获取Json bool
    void (*getString)(struct _JsonArray This, int ItemNum, strnew OutStr); // 获取Json String
    struct _JsonArray (*getArray)(struct _JsonArray This, int ItemNum);    // 获取Json array
    struct _JsonObject (*getObject)(struct _JsonArray This, int ItemNum);  // 获取Json Object
    
} JsonArray;
// 方法
bool Arr_isJsonNull(JsonArray This, int ItemNum);
int Arr_getInt(JsonArray This, int ItemNum);
double Arr_getDouble(JsonArray This, int ItemNum);
bool Arr_getBool(JsonArray This, int ItemNum);
void Arr_getString(JsonArray This, int ItemNum, strnew OutStr);
struct _JsonArray Arr_getArray(JsonArray This, int ItemNum);
struct _JsonObject Arr_getObject(JsonArray This, int ItemNum);
// 建立对象示例
extern JsonArray newJsonArrayByString(strnew DataInit); // 建立对象数组的函数

//==========================================================================================//
//==========================================================================================//
//==========================================================================================//
//==========================================================================================//
//==========================================================================================//

// json类
typedef struct _JsonObject
{
    strnew JsonString;
    bool (*isJsonNull)(struct _JsonObject This, const char Key[]);               // 判断Json是否为空
    int (*getInt)(struct _JsonObject This, const char Key[]);                    // 获取Json int
    double (*getDouble)(struct _JsonObject This, const char Key[]);              // 获取Json double
    bool (*getBool)(struct _JsonObject This, const char Key[]);                  // 获取Json bool
    void (*getString)(struct _JsonObject This, const char Key[], strnew OutStr); // 获取Json string
    struct _JsonArray (*getArray)(struct _JsonObject This, const char Key[]);    // 获取Json array
    struct _JsonObject (*getObject)(struct _JsonObject This, const char Key[]);  // 获取Json object
} JsonObject;
// 方法
bool Obj_isJsonNull(JsonArray This, const char Key[]);
int Obj_getInt(JsonObject This, const char Key[]);
double Obj_getDouble(JsonObject This, const char Key[]);
bool Obj_getBool(JsonObject This, const char Key[]);
void Obj_getString(JsonObject This, const char Key[], strnew OutStr);
struct _JsonArray Obj_getArray(JsonObject This, const char Key[]);
struct _JsonObject Obj_getObject(JsonObject This, const char Key[]);
// 建立对象示例
extern JsonObject newJsonObjectByString(strnew DataInit); // 建立对象的函数

#endif
