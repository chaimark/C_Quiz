/*
XXXX_XXX <==> 宏定义
Xxxx_Xxxx <==> 全局变量，对象名
_Xxxx_Xxx <==> 类名
XxxxXxxxx <==> 局部变量
xxxxXxxx() <==> 函数
xxxxx_xxxx <==> typedef(数据类型)
*/
#ifndef NUMBERBASELIC_H
#define NUMBERBASELIC_H

#include <stdint.h>

#define int8_t char                 // 有符号08位整数类型
#define uint8_t unsigned char       // 无符号08位整数类型
#define int16_t int                 // 有符号16位整数类型
#define uint16_t unsigned int       // 无符号16位整数类型
#define int32_t long int            // 有符号32位整数类型
#define uint32_t unsigned long int  // 无符号32位整数类型
#define int64_t long long           // 有符号64位整数类型
#define uint64_t unsigned long long // 有符号64位整数类型

extern void numberArrayToStrArray(char StrArray[], uint8_t NumberArray[], int ArrayMinLen);  // 将数组串转字符串
extern void strArrayToNumberArray(uint8_t NumberArray[], char StrArray[], int ArrayMinLen);  // 将字符串转数组串
extern uint64_t anyBaseNumberToStr(uint8_t *Output, int StrSize, uint64_t InputNumber); // 任意进制数转对应进制字符串 返回长度
extern uint64_t strToAnyBaseNumber(int NumberBase, uint8_t *IntputStr, int StrSize);    // 任意进制字符串转对应进制数
extern uint64_t anyBaseToOtherBase(uint64_t Number, int IntputBase, int OutputBase);    // 任意进制互转

#endif
