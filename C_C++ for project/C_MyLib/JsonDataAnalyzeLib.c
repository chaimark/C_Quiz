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

// 查找双重字符位置
char * getDoubleChrOnString(char * MotherString, char HeadChr, char EndChr) {
    Stack s;
    initStack(&s);
    char * result = NULL;
    for (int i = 0; ((MotherString[i] != '\0') && (!isEmpty(&s))); i++) {
        if (MotherString[i] == HeadChr) {
            push(&s, HeadChr);
        } else if (MotherString[i] == EndChr) {
            if (!isEmpty(&s)) {
                pop(&s);
                if (isEmpty(&s)) {
                    result = &MotherString[i];
                }
            }
        }
    }
    return result;
}

void _getKeyName(char * SonStr, char Key[]) {
    catString(SonStr, "\"", 100, 1);
    catString(SonStr, Key, 100, strlen(Key));
    catString(SonStr, "\":", 100, 2);
}
#define getKeyName(name, len, key)   \
    char name[len] = {0};\
    _getKeyName(name,key)
//==========================================================================================//
//==========================================================================================//

int Arr_sizeItemNum(struct _JsonArray This) {
    return 0;
}
bool Arr_isJsonNull(struct _JsonArray This, int ItemNum) {
    return false;
}
void * Arr_get(struct _JsonArray This, int ItemNum) {
    return NULL;
}
struct _JsonArray Arr_getArray(struct _JsonArray This, int ItemNum) {
    return (JsonArray) { 0 };
}
struct _JsonObject Arr_getObject(struct _JsonArray This, int ItemNum) {
    return (JsonObject) { 0 };
}

JsonArray newJsonArrayByString(strnew DataInit) {
    JsonArray Temp;
    Temp.JsonString = DataInit;
    Temp.sizeItemNum = Arr_sizeItemNum;
    Temp.isJsonNull = Arr_isJsonNull;
    Temp.get = Arr_get;
    Temp.getArray = Arr_getArray;
    Temp.getObject = Arr_getObject;
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
#include <stdio.h>
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
        strcpy(OutStr.Name._char, (KeyP + 1));
        *EndP = Temp;
    }
    return;
}
struct _JsonArray Obj_getArray(struct _JsonObject This, char Key[], strnew OutStr) {
    JsonArray tempJsonArr = {0};
    getKeyName(SonStr, 50, Key);
    char * KeyP = NULL;
    if ((KeyP = strstr(This.JsonString.Name._char, SonStr)) != NULL) {
        KeyP += strlen(SonStr);
        while ((*KeyP) == ' ') {
            KeyP++;
        }
        char * EndP = NULL;
        if ((EndP = getDoubleChrOnString(KeyP, '[', ']')) != NULL) {
            char Temp = *EndP;
            *EndP = '\0';
            strcpy(OutStr.Name._char, KeyP);
            tempJsonArr.JsonString = OutStr;
            *EndP = Temp;
        }
    }
    return tempJsonArr;
}
struct _JsonObject Obj_getObject(struct _JsonObject This, char Key[]) {
    JsonObject temp = {0};


    return temp;
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
