/*
XXXX_XXX <==> 宏定义
Xxxx_Xxxx <==> 全局变量，对象名
_Xxxx_Xxx <==> 类名
XxxxXxxxx <==> 局部变量
xxxxXxxx() <==> 函数
xxxxx_xxxx <==> typedef(数据类型)
*/
#ifndef WINEXCEL_H  // 如果 MY_HEADER_FILE_H 未定义
#define WINEXCEL_H  // 定义 MY_HEADER_FILE_H
/*-----------------------------------标准库------------------------------------*/
#include <stdio.h>
#include <stdbool.h>

/*-----------------------------------基础定义----------------------------------*/
#define EXCEL_MAX_LEN 3000 //excel 每行最大长度
typedef struct __CsvDataTab {
    char CsvData[3000][EXCEL_MAX_LEN];
} CsvDataTab;

// 声明一个返回值为bool，参数为FILE *的函数指针类型
typedef bool (*funNamePtr)(CsvDataTab ExcelData);
/*-----------------------------------函数说明----------------------------------*/
//取绝对值
extern int resAbsoluteVar(int Input);
//写入表格
extern void excelWriteCsv(char FileName[], funNamePtr writeFrom);
//读取表格
extern void excelReadCsv(char FileName[], funNamePtr ReadFrom);


#endif