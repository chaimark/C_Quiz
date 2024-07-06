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
#include "StrLib.h"

extern void numberArrayToStrArray(char StrArray[], char NumberArray[], int ArrayMinLen);                                   // 将数组串转字符串 0x01 0x02 ==> 0x31 0x32
extern void strArrayToNumberArray(char NumberArray[], char StrArray[], int ArrayMinLen);                                   // 将字符串转数组串 0x31 0x32 ==> 0x01 0x02
extern uint64_t anyBaseToAnyBase(uint64_t Number, int IntputBase, int OutputBase);                                         // 任意进制互转
extern int anyBaseNumberToAnyBaseArray(uint64_t Number, int IntputBase, int OutputBase, char OutArray[], int ArrayMinLen); // 任意进制数 转 任意进制数组
extern int64_t anyBaseArrayToAnyBaseNumber(char IntArray[], int ArrayMinLen, int IntputBase, int OutputBase);              // 任意进制数组 转 任意进制数
extern int shortChStrToDoubleChStr(strnew inputArray, strnew OutputArray);                                                 // 单字节数组 转 双字节数组 0x23 --> 0x02 0x03
extern int doubleChStrToShortChStr(strnew inputArray, strnew OutputArray);                                                 // 双字节数组 转 单字节数组 0x02 0x03 --> 0x23
extern int64_t doneAsciiStrToAnyBaseNumberData(char AscArray[], int ArrayLen, int OutputBase);                             // 字符串 转 任意进制数
extern int doneBaseNumberDataToAsciiStr(char AscArray[], int ArrayLen, int NumberData, int IntputBase);                    // 任意进制数 转 字符串
extern bool readDataBit(uint64_t InputNumber, int BitNumber);                                                              // 读取某位 返回对应位的 bool 值
extern bool setDataBit(uint64_t *InputNumber, int BitNumber, bool Value);                                                  // 设置某位 返回是否设置成功
// 外部接口
extern void HEX2ToASCII(char *hex, int hex_len, char *asc, int asc_len);
extern int ASCIIToHEX2(char *asc, int asc_len, char *hex, int hex_len);
#endif
