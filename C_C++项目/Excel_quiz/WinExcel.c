/*
XXXX_XXX <==> �궨��
Xxxx_Xxxx <==> ȫ�ֱ�����������
_Xxxx_Xxx <==> ����
XxxxXxxxx <==> �ֲ�����
xxxxXxxx() <==> ����
xxxxx_xxxx <==> typedef(��������)
*/
#include "../C_MyLib/StrFunLib.h"
#include "../C_MyLib/WinExcel.h"
#include <stdio.h>

/*-----------------------------------��������----------------------------------*/
#define N 300
/*-----------------------------------����˵��----------------------------------*/
//��һ������д��EXCEL
bool excelWirt(FILE *fp);
//��ȡEXCEL����������ReadExcel[][]
void excelRead(char ReadExcel[][N]);
/*-----------------------------------��������----------------------------------*/
bool excelWirt(FILE *Fp) {	
	/*
	д��code
	*/
	save_file();	//�����ļ�
}
void excelRead(char ReadExcel[][N]) {
	/*
	����code
	*/
	save_file();	//�����ļ�
}
void main() {
	excelReadCsv("Flag_No.csv",excelRead);
	excelWriteCsv("Flag_No.csv",excelWirt);
}
