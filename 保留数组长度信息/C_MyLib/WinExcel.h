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
#define EXCEL_MAX_LEN 300 //excel 每行最大长度
// 声明一个返回值为bool，参数为FILE *的函数指针类型
typedef bool (* funNamePtr1)(FILE *Fp);
typedef bool (* funNamePtr2)(char ReadExcel[][EXCEL_MAX_LEN]);
char Read_Excel[1000][EXCEL_MAX_LEN];

/*-----------------------------------函数说明----------------------------------*/
//取绝对值
int resAbsoluteVar(int Input);
//写入表格
bool excelWriteCsv(char FileName[],bool funNamePtr1(FILE *fp));
//读取表格
bool excelReadCsv(char FileName[],bool funNamePtr2(char ReadExcel[][EXCEL_MAX_LEN]));


/*-----------------------------------函数定义----------------------------------*/
//取绝对值
int resAbsoluteVar(int Input) {
	if(Input >= 0) {
		return Input;
	} else {
		return 0-Input;
	}
}
//把数据写入Csv文件
bool excelWriteCsv(char FileName[], funNamePtr1 CallFun) {
	bool ResData = false;
    FILE *Fp = fopen(FileName, "w");	// 打开csv文件
    if (Fp == NULL) {
        printf("无法打开文件\n");
		Fp = fopen(FileName, "w");		// 清空数据，新建csv文件
        ResData = false;
    } else {
		if(CallFun(Fp) == true) {
			ResData = true;
			printf("写入成功\n");
		} else {
			printf("写入失败\n");
			fclose(Fp);							// 关闭文件 
			FILE *Fp = fopen(FileName, "w");	// 清空数据，新建csv文件
			ResData = false;
		}
	}
	fclose(Fp);		// 关闭文件 
	return ResData;
}
//读取Csv文件
bool excelReadCsv(char FileName[], funNamePtr2 CallFun) {
	bool ResData = false;
    FILE *Fp = fopen(FileName, "r"); 	// 打开csv文件
    if (Fp == NULL) {
        printf("无法打开文件\n");
		Fp = fopen(FileName, "w");		// 清空数据，新建csv文件
        ResData = false;
    } else {
		if(CallFun(Read_Excel) == true) {
			ResData = true;
			printf("读取成功\n");
		} else {
			printf("读取失败\n");
			fclose(Fp);							// 关闭文件 
			FILE *Fp = fopen(FileName, "w");	// 清空数据，新建csv文件
			ResData = false;
		}
	}
    fclose(Fp); // 关闭文件
    return ResData;
}

#endif