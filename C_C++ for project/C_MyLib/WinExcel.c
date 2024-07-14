/*-----------------------------------标准库------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include "WinExcel.h"

/*-----------------------------------函数定义----------------------------------*/
bool save_file(FILE * Fp) {

}
//取绝对值
int resAbsoluteVar(int Input) {
    if (Input >= 0) {
        return Input;
    } else {
        return 0 - Input;
    }
}
//把数据写入Csv文件
void excelWriteCsv(char FileName[], funNamePtr writeFrom) {
    CsvDataTab ExcelData;
    FILE * Fp = fopen(FileName, "w");	// 打开csv文件
    if (Fp == NULL) {
        printf("无法打开文件\n");
        Fp = fopen(FileName, "w");		// 清空数据，新建csv文件
    }
    if (writeFrom(ExcelData) == true) {
        printf("写入成功\n");
    } else {
        printf("写入失败\n");
        fclose(Fp);							// 关闭文件 
        FILE * Fp = fopen(FileName, "w");	// 清空数据，新建csv文件
        printf("新建成功\n");
    }
    save_file(Fp);	//保存文件
    fclose(Fp);		// 关闭文件 
}
//读取Csv文件
void excelReadCsv(char FileName[], funNamePtr ReadFrom) {
    CsvDataTab ExcelData;
    FILE * Fp = fopen(FileName, "r"); 	// 打开csv文件
    if (Fp == NULL) {
        printf("无法打开文件\n");
        Fp = fopen(FileName, "w");		// 清空数据，新建csv文件
    }
    if (ReadFrom(ExcelData) == true) {
        printf("读取成功\n");
    } else {
        printf("读取失败\n");
        fclose(Fp);							// 关闭文件 
        FILE * Fp = fopen(FileName, "w");	// 清空数据，新建csv文件
        printf("新建成功\n");
    }
    save_file(Fp);	//保存文件
    fclose(Fp); // 关闭文件
}
