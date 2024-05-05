/*
XXXX_XXX <==> 宏定义
Xxxx_Xxxx <==> 全局变量，对象名
_Xxxx_Xxx <==> 类名
XxxxXxxxx <==> 局部变量
xxxxXxxx() <==> 函数
xxxxx_xxxx <==> typedef(数据类型)
*/
#include "../C_MyLib/StrFunLib.h"
#include "../C_MyLib/WinExcel.h"
#include <stdio.h>

/*-----------------------------------基础定义----------------------------------*/
#define N 300
/*-----------------------------------函数说明----------------------------------*/
//按一定规则写入EXCEL
bool excelWirt(FILE *fp);
//读取EXCEL，并规整到ReadExcel[][]
void excelRead(char ReadExcel[][N]);
/*-----------------------------------函数定义----------------------------------*/
bool excelWirt(FILE *Fp) {	
	/*
	写入code
	*/
	save_file();	//保存文件
}
void excelRead(char ReadExcel[][N]) {
	/*
	整理code
	*/
	save_file();	//保存文件
}
void main() {
	excelReadCsv("Flag_No.csv",excelRead);
	excelWriteCsv("Flag_No.csv",excelWirt);
}
