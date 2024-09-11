#include "JsonDataAnalyzeLib.h"
#include <stdio.h>
#include <stdlib.h>

//==========================================================================================//
//==========================================================================================//
#define MAX_STACK_SIZE 100  // 定义栈的最大容量
typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} Stack;
// 初始化栈
void initStack(Stack * s) {
    s->top = -1;
}
// 判断栈是否为空
int isEmpty(Stack * s) {
    return s->top == -1;
}
// 入栈
void push(Stack * s, char ch) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->data[++(s->top)] = ch;
    }
}
// 出栈
char pop(Stack * s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return '\0';  // 返回一个空字符
}
// 获取栈顶元素
char peek(Stack * s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return '\0';  // 返回一个空字符
}
//==========================================================================================//
//==========================================================================================//

// 查找双重字符位置
char * getDoubleChrOnString(char * MotherString, char HeadChr, char EndChr) {
    Stack s;
    initStack(&s);
    char * result = NULL;
    for (int i = 0; (MotherString[i] != '\0'); i++) {
        if (MotherString[i] == HeadChr) {
            push(&s, HeadChr);
        } else if (MotherString[i] == EndChr) {
            if (!isEmpty(&s)) {
                pop(&s);
                if (isEmpty(&s)) {
                    result = &MotherString[i];
                    break;
                }
            }
        }
    }
    return result;
}

// 拼接 关键字 字符串
void _getKeyName(char * SonStr, char Key[]) {
    catString(SonStr, "\"", 100, 1);
    catString(SonStr, Key, 100, strlen(Key));
    catString(SonStr, "\":", 100, 2);
}
#define getKeyName(name, len, key)   \
    char name[len] = {0};\
    _getKeyName(name,key)


//==========================================================================================//
JsonArray newJsonArrayByString(strnew DataInit);
JsonObject newJsonObjectByString(strnew DataInit);
//==========================================================================================//

int Arr_sizeItemNum(struct _JsonArray This) {
    Stack s;        // 定义栈
    initStack(&s);  // 初始化栈
    int ItemNum = 0;
    char * HeadItem = This.JsonString.Name._char + 1;   // 获取第一个元素位置
    char * EndItem = HeadItem;
    while (*EndItem != '\0') {
        if (isEmpty(&s)) {          // 判断当前栈是否为空，
            if (*EndItem == '{' || *EndItem == '[') {   // 如果是 { 或者 [ 就入栈，
                push(&s, *EndItem);
            } else if ((*EndItem == ',') || (*(EndItem + 1) == '\0')) {   // 如果为空，则判断 EndItem 是否是‘,’
                ItemNum++;                  // 如果是‘,’，则说明是一个元素结束 ItemNum++;
                HeadItem = EndItem + 1;
                EndItem = HeadItem;
                continue;
            }
        } else {
            if (*EndItem == '}' || *EndItem == ']') {   // 如果当前栈不为空，则在遇到 } 或者 ] 出栈，
                pop(&s);
            }
        }
        EndItem++;
    }
    return (This.isJsonNull(&This) ? 0 : ItemNum);
}
bool Arr_isJsonNull(struct _JsonArray This) {
    return ((strcmp(This.JsonString.Name._char, "[]") == 0) ? true : false);
}

void Arr_get(struct _JsonArray This, strnew OutStr, int ItemNum) {
    Stack s;        // 定义栈
    initStack(&s);  // 初始化栈
    ItemNum++;
    char * HeadItem = This.JsonString.Name._char + 1;   // 获取第一个元素位置
    char * EndItem = HeadItem;
    while (ItemNum > 0 && *EndItem != '\0') {
        if (isEmpty(&s)) {          // 判断当前栈是否为空，
            if (*EndItem == '{' || *EndItem == '[') {   // 如果是 { 或者 [ 就入栈，
                push(&s, *EndItem);
            } else if ((*EndItem == ',') || (*(EndItem + 1) == '\0')) {   // 如果为空，则判断 EndItem 是否是‘,’
                ItemNum--;                  // 如果是‘,’，则说明是一个元素结束 ItemNum--;
                if (ItemNum != 0) {
                    HeadItem = EndItem + 1;
                    EndItem = HeadItem;
                    continue;
                }
            }
        } else {
            if (*EndItem == '}' || *EndItem == ']') {   // 如果当前栈不为空，则在遇到 } 或者 ] 出栈，
                pop(&s);
            }
        }
        EndItem++;
    }
    char Temp = *(EndItem - 1);
    *(EndItem - 1) = '\0';
    memset(OutStr.Name._char, 0, OutStr.MaxLen);
    copyString(OutStr.Name._char, HeadItem, OutStr.MaxLen, strlen(HeadItem));
    *(EndItem - 1) = Temp;
}

JsonArray newJsonArrayByString(strnew DataInit) {
    JsonArray Temp;
    Temp.JsonString = DataInit;
    Temp.sizeItemNum = Arr_sizeItemNum;
    Temp.isJsonNull = Arr_isJsonNull;
    Temp.get = Arr_get;
    return Temp;
}

//==========================================================================================//
//==========================================================================================//
//==========================================================================================//
//==========================================================================================//
//==========================================================================================//

int Obj_sizeStr(struct _JsonObject This) {
    return 0;
}
bool Obj_isJsonNull(struct _JsonObject This, char Key[]) {
    bool ResBool = false;
    getKeyName(SonStr, 50, Key);
    char * KeyP = NULL;
    if ((KeyP = strstr(This.JsonString.Name._char, SonStr)) != NULL) {
        KeyP += strlen(SonStr);
        while ((*KeyP) == ' ') {
            KeyP++;
        }
        char Temp = *(KeyP + 4);
        *(KeyP + 4) = '\0';
        if ((strcmp(KeyP, "null") == 0) || (strcmp(KeyP, "NULL") == 0) || (strcmp(KeyP, "Null") == 0)) {
            ResBool = true;
        }
        *(KeyP + 4) = Temp;
    }
    return ResBool;
}
int Obj_getInt(struct _JsonObject This, char Key[]) {
    getKeyName(SonStr, 50, Key);
    char * KeyP = NULL;
    if ((KeyP = strstr(This.JsonString.Name._char, SonStr)) != NULL) {
        KeyP += strlen(SonStr);
        while ((*KeyP) == ' ') {
            KeyP++;
        }
        return atol(KeyP);
    }
    return 0;
}
double Obj_getDouble(struct _JsonObject This, char Key[]) {
    getKeyName(SonStr, 50, Key);
    char * KeyP = NULL;
    if ((KeyP = strstr(This.JsonString.Name._char, SonStr)) != NULL) {
        KeyP += strlen(SonStr);
        while ((*KeyP) == ' ') {
            KeyP++;
        }
        return atof(KeyP);
    }
    return 0.0;
}
bool Obj_getBool(struct _JsonObject This, char Key[]) {
    bool ResBool = false;
    getKeyName(SonStr, 50, Key);
    char * KeyP = NULL;
    if ((KeyP = strstr(This.JsonString.Name._char, SonStr)) != NULL) {
        KeyP += strlen(SonStr);
        while ((*KeyP) == ' ') {
            KeyP++;
        }
        char Temp = *(KeyP + 4);
        *(KeyP + 4) = '\0';
        if ((strcmp(KeyP, "true") == 0) || (strcmp(KeyP, "TRUE") == 0) || (strcmp(KeyP, "True") == 0)) {
            ResBool = true;
        }
        *(KeyP + 4) = Temp;
    }
    return ResBool;
}
void Obj_getString(struct _JsonObject This, char Key[], strnew OutStr) {
    getKeyName(SonStr, 50, Key);
    char * KeyP = NULL;
    if ((KeyP = strstr(This.JsonString.Name._char, SonStr)) != NULL) {
        KeyP += strlen(SonStr);
        while ((*KeyP) == ' ') {
            KeyP++;
        }
        char * EndP = strstr((KeyP + 1), "\"");
        char Temp = *EndP;
        *EndP = '\0';
        memset(OutStr.Name._char, 0, OutStr.MaxLen);
        copyString(OutStr.Name._char, KeyP, OutStr.MaxLen, strlen(KeyP));
        *EndP = Temp;
    }
    return;
}
struct _JsonArray Obj_getArray(struct _JsonObject This, char Key[], strnew OutStr) {
    JsonArray tempJsonArr = newJsonArrayByString(OutStr);
    getKeyName(SonStr, 50, Key);
    char * KeyP = NULL;
    if ((KeyP = strstr(This.JsonString.Name._char, SonStr)) != NULL) {
        KeyP += strlen(SonStr);
        while ((*KeyP) == ' ') {
            KeyP++;
        }
        char * EndP = NULL;
        if ((EndP = getDoubleChrOnString(KeyP, '[', ']')) != NULL) {
            char Temp = *(EndP + 1);
            *(EndP + 1) = '\0';
            memset(tempJsonArr.JsonString.Name._char, 0, tempJsonArr.JsonString.MaxLen);
            copyString(tempJsonArr.JsonString.Name._char, KeyP, tempJsonArr.JsonString.MaxLen, strlen(KeyP));
            *(EndP + 1) = Temp;
        }
    }
    return tempJsonArr;
}
struct _JsonObject Obj_getObject(struct _JsonObject This, char Key[], strnew OutStr) {
    JsonObject tempJsonObj = newJsonObjectByString(OutStr);
    getKeyName(SonStr, 50, Key);
    char * KeyP = NULL;
    if ((KeyP = strstr(This.JsonString.Name._char, SonStr)) != NULL) {
        KeyP += strlen(SonStr);
        while ((*KeyP) == ' ') {
            KeyP++;
        }
        char * EndP = NULL;
        if ((EndP = getDoubleChrOnString(KeyP, '{', '}')) != NULL) {
            char Temp = *(EndP + 1);
            *(EndP + 1) = '\0';
            memset(tempJsonObj.JsonString.Name._char, 0, tempJsonObj.JsonString.MaxLen);
            copyString(tempJsonObj.JsonString.Name._char, KeyP, tempJsonObj.JsonString.MaxLen, strlen(KeyP));
            *(EndP + 1) = Temp;
        }
    }
    return tempJsonObj;
}

JsonObject newJsonObjectByString(strnew DataInit) {
    JsonObject Temp;
    Temp.JsonString = DataInit;
    Temp.sizeStr = Obj_sizeStr;
    Temp.isJsonNull = Obj_isJsonNull;
    Temp.getInt = Obj_getInt;
    Temp.getDouble = Obj_getDouble;
    Temp.getBool = Obj_getBool;
    Temp.getString = Obj_getString;
    Temp.getArray = Obj_getArray;
    Temp.getObject = Obj_getObject;
    return Temp;
}
