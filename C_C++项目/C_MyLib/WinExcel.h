/*
XXXX_XXX <==> �궨��
Xxxx_Xxxx <==> ȫ�ֱ�����������
_Xxxx_Xxx <==> ����
XxxxXxxxx <==> �ֲ�����
xxxxXxxx() <==> ����
xxxxx_xxxx <==> typedef(��������)
*/
#ifndef WINEXCEL_H  // ��� MY_HEADER_FILE_H δ����
#define WINEXCEL_H  // ���� MY_HEADER_FILE_H
/*-----------------------------------��׼��------------------------------------*/
#include <stdio.h>
#include <stdbool.h>

/*-----------------------------------��������----------------------------------*/
#define EXCEL_MAX_LEN 300 //excel ÿ����󳤶�
// ����һ������ֵΪbool������ΪFILE *�ĺ���ָ������
typedef bool (* funNamePtr1)(FILE *Fp);
typedef bool (* funNamePtr2)(char ReadExcel[][EXCEL_MAX_LEN]);
char Read_Excel[1000][EXCEL_MAX_LEN];

/*-----------------------------------����˵��----------------------------------*/
//ȡ����ֵ
extern int resAbsoluteVar(int Input);
//д����
extern bool excelWriteCsv(char FileName[],bool funNamePtr1(FILE *fp));
//��ȡ���
extern bool excelReadCsv(char FileName[],bool funNamePtr2(char ReadExcel[][EXCEL_MAX_LEN]));


#endif