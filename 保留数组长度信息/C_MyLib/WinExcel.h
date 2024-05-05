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
int resAbsoluteVar(int Input);
//д����
bool excelWriteCsv(char FileName[],bool funNamePtr1(FILE *fp));
//��ȡ���
bool excelReadCsv(char FileName[],bool funNamePtr2(char ReadExcel[][EXCEL_MAX_LEN]));


/*-----------------------------------��������----------------------------------*/
//ȡ����ֵ
int resAbsoluteVar(int Input) {
	if(Input >= 0) {
		return Input;
	} else {
		return 0-Input;
	}
}
//������д��Csv�ļ�
bool excelWriteCsv(char FileName[], funNamePtr1 CallFun) {
	bool ResData = false;
    FILE *Fp = fopen(FileName, "w");	// ��csv�ļ�
    if (Fp == NULL) {
        printf("�޷����ļ�\n");
		Fp = fopen(FileName, "w");		// ������ݣ��½�csv�ļ�
        ResData = false;
    } else {
		if(CallFun(Fp) == true) {
			ResData = true;
			printf("д��ɹ�\n");
		} else {
			printf("д��ʧ��\n");
			fclose(Fp);							// �ر��ļ� 
			FILE *Fp = fopen(FileName, "w");	// ������ݣ��½�csv�ļ�
			ResData = false;
		}
	}
	fclose(Fp);		// �ر��ļ� 
	return ResData;
}
//��ȡCsv�ļ�
bool excelReadCsv(char FileName[], funNamePtr2 CallFun) {
	bool ResData = false;
    FILE *Fp = fopen(FileName, "r"); 	// ��csv�ļ�
    if (Fp == NULL) {
        printf("�޷����ļ�\n");
		Fp = fopen(FileName, "w");		// ������ݣ��½�csv�ļ�
        ResData = false;
    } else {
		if(CallFun(Read_Excel) == true) {
			ResData = true;
			printf("��ȡ�ɹ�\n");
		} else {
			printf("��ȡʧ��\n");
			fclose(Fp);							// �ر��ļ� 
			FILE *Fp = fopen(FileName, "w");	// ������ݣ��½�csv�ļ�
			ResData = false;
		}
	}
    fclose(Fp); // �ر��ļ�
    return ResData;
}

#endif