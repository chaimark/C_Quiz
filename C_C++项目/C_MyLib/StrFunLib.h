/*
XXXX_XXX <==> �궨��
Xxxx_Xxxx <==> ȫ�ֱ�����������
_Xxxx_Xxx <==> ����
XxxxXxxxx <==> �ֲ�����
xxxxXxxx() <==> ����
xxxxx_xxxx <==> typedef(��������)
*/
#ifndef STRFUN_H  // ��� MY_HEADER_FILE_H δ����
#define STRFUN_H  // ���� MY_HEADER_FILE_H
/*-----------------------------------��׼��------------------------------------*/
#include <stdio.h>
#include <string.h>

/*-----------------------------------��������----------------------------------*/

/*-----------------------------------����˵��----------------------------------*/
//׷���ַ�
extern int catString(char *OutStr,char *IntStr,int MaxSize,int IntSize);
//�����ַ�
extern int copyString(char *OutStr,char *IntStr,int MaxSize,int IntSize);
//���ַ���ת��������
extern int strToNumber(int OutNum, char * InputStr, int Size);
//������ת�����ַ���
extern int numberToStr(char * OutStr, int InputNum, int Size);
//�ַ������뺯��
extern char* myFgets(char* Str, int Size);
//���ַ�����str�����ַ�����s���ָ�
extern void myStrtok(char str[], int StrMaxLen, char s[], int ContAddr);


#endif