#include "JsonDataAnalyzeLib.h"

int Arr_getInt(JsonArray This, int ItemNum)
{
    return 0;
}
double Arr_getDouble(JsonArray This, int ItemNum)
{
    return 0.0;
}
bool Arr_getBool(JsonArray This, int ItemNum)
{
    return false;
}
void Arr_getString(JsonArray This, int ItemNum, strnew OutStr)
{
    return;
}
struct _JsonArray Arr_getArray(JsonArray This, int ItemNum)
{
    return (JsonArray){0};
}
struct _JsonObject Arr_getObject(JsonArray This, int ItemNum)
{
    return (JsonObject){0};
}

JsonArray newJsonArrayByString(strnew DataInit)
{
    JsonArray Temp;
    Temp.JsonString = DataInit;
    return Temp;
}

//==========================================================================================//
//==========================================================================================//
//==========================================================================================//
//==========================================================================================//
//==========================================================================================//

int Obj_getInt(JsonObject This, const char Key[])
{
    return 0;
}
double Obj_getDouble(JsonObject This, const char Key[])
{
    return 0.0;
}
bool Obj_getBool(JsonObject This, const char Key[])
{
    return false;
}
void Obj_getString(JsonObject This, const char Key[], strnew OutStr)
{
    return;
}
struct _JsonArray Obj_getArray(JsonObject This, const char Key[])
{
    return (JsonArray){0};
}
struct _JsonObject Obj_getObject(JsonObject This, const char Key[])
{
    return (JsonObject){0};
}

JsonObject newJsonObjectByString(strnew DataInit)
{
    JsonObject Temp;
    Temp.JsonString = DataInit;
    return Temp;
}
