
#ifndef ARRAY_QUIZ_H
#define ARRAY_QUIZ_H
#include <stdio.h>
#include "../C_MyLib/WinExcel.h"

extern bool excelWirt(CsvDataTab ExcelData); // 写入 ExcelData 数据
extern bool excelRead(CsvDataTab ExcelData); // 读取 ExcelData 数据
extern void WinExcelQuiz(char FileName[]);

#endif

