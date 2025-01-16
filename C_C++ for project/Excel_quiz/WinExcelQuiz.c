/*
XXXX_XXX <==> 宏定义
Xxxx_Xxxx <==> 全局变量，对象名
_Xxxx_Xxx <==> 类名
XxxxXxxxx <==> 局部变量
xxxxXxxx() <==> 函数
xxxxx_xxxx <==> typedef(数据类型)
*/
#include "../C_MyLib/StrLib.h"
#include "WinExcelQuiz.h"
#include <stdio.h>

/*-----------------------------------基础定义----------------------------------*/
CsvDataTab ExcelData;
/*-----------------------------------函数定义----------------------------------*/

bool excelWirt(CsvDataTab CsvData) {
    /*
    写入code
    */
}
bool excelRead(CsvDataTab CsvData) {
    /*
    整理code
    */
    CsvData = ExcelData;
}
void WinExcelQuiz(char FileName[]) {
    excelWriteCsv(FileName, excelWirt);
    excelReadCsv(FileName, excelRead);
}
