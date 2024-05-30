/*
XXXX_XXX <==> 宏定义
Xxxx_Xxxx <==> 全局变量，对象名
_Xxxx_Xxx <==> 类名
XxxxXxxxx <==> 局部变量
xxxxXxxx() <==> 函数
xxxxx_xxxx <==> typedef(数据类型)
*/
#ifndef STRFUN_H  // 如果 MY_HEADER_FILE_H 未定义
#define STRFUN_H  // 定义 MY_HEADER_FILE_H
/*-----------------------------------标准库------------------------------------*/
#include <stdio.h>
#include <string.h>

/*-----------------------------------基础定义----------------------------------*/

/*-----------------------------------函数说明----------------------------------*/
//追加字符
extern int catString(char *OutStr,char *IntStr,int MaxSize,int IntSize);
//复制字符
extern int copyString(char *OutStr,char *IntStr,int MaxSize,int IntSize);
//将字符串转换到数字
extern int strToNumber(int OutNum, char * InputStr, int Size);
//将数字转换到字符串
extern int numberToStr(char * OutStr, int InputNum, int Size);
//字符串输入函数
extern char* myFgets(char* Str, int Size);
//把字符串（str）按字符串（s）分隔
extern void myStrtok(char str[], int StrMaxLen, char s[], int ContAddr);


#endif