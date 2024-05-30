/*-----------------------------------��׼��------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "StrFunLib.h"
/*-----------------------------------��������----------------------------------*/

/*-----------------------------------����˵��----------------------------------*/
//׷���ַ�
int catString(char *OutStr,char *IntStr,int MaxSize,int IntSize);
//�����ַ�
int copyString(char *OutStr,char *IntStr,int MaxSize,int IntSize);
//���ַ���ת��������
int strToNumber(int OutNum, char * InputStr, int Size);
//������ת�����ַ���
int numberToStr(char * OutStr, int InputNum, int Size);
//�ַ������뺯��
char* myFgets(char* Str, int Size);
//���ַ�����str�����ַ�����s���ָ�
void myStrtok(char str[], int StrMaxLen, char s[], int ContAddr);

/*-----------------------------------��������----------------------------------*/
//׷���ַ�
int catString(char *OutStr,char *IntStr,int MaxSize,int IntSize) {
	int AddrNow = 0;
	int run = 0;
	//�ҳ�"\0"
	while((OutStr[AddrNow]!='\0')&&(AddrNow < MaxSize)) {
		if(AddrNow > MaxSize) {
			return -1;
		}
		AddrNow++;
	}
	if(MaxSize >= AddrNow+IntSize) {
		//��ʼ׷��
		for(run=0;run<IntSize;run++) {
			OutStr[AddrNow]=IntStr[run];
			if(OutStr[AddrNow++]=='\0') {
				break;
			}
		}
		if(run >= IntSize) {
			if(MaxSize == AddrNow) {
				OutStr[MaxSize-1]='\0';//could make conditional but not neccesary.
			} else {
				OutStr[AddrNow+0]='\0';//could make conditional but not neccesary.	
			}	
		}
		return 0;
	} else {
		return -1;
	}
}
//�����ַ���
int copyString(char *OutStr,char *IntStr,int MaxSize,int IntSize) {
	int run = 0;
	if(MaxSize >= IntSize) {
		for(run=0;run<IntSize;run++)	{//last reserved for'\0'
			OutStr[run]=IntStr[run];
			if(OutStr[run]=='\0') {
				break;
			}
		}
		if(run >= IntSize) {
			if(MaxSize == IntSize) {
				OutStr[run-1]='\0';//could make conditional but not neccesary.
			} else {
				OutStr[run+0]='\0';//could make conditional but not neccesary.
			}	
		}
		return 0;
	} else {
		return -1;
	}
}
//�ַ���ת����
int strToNumber(int OutNum, char *InputStr, int Size)
{
    int H_ERROR_NUM = -1;	
	int cont_num = 0;
	char c;
	for(int i=0;((c = InputStr[i] ) != '\0')&&(i<Size);i++)  { // ����ֱ����������
		if (c >= '0' && c <= '9') {  // ����������ַ�
			OutNum = OutNum * 10 + (c - '0');  // ���ַ�ת��Ϊ���ֲ��ۼӵ�value��
		} else {
			return H_ERROR_NUM; // ��������������ַ������ش����ʶ-1
		}
		cont_num++;
	}
	return (cont_num == 0)?(H_ERROR_NUM):(OutNum); // ���ض��������ֵ
}
//����ת�ַ���
int numberToStr(char * OutStr, int InputNum, int Size) {	
	char TempStr[10] = {0};
	int OutLen = 0;
	if(Size >= 10) {
		for(int i=0;(i<Size)&&(InputNum!=0);i++) {
			TempStr[i] = InputNum%10 + '0';
			InputNum = InputNum/10;
			OutLen++;
		}
		if((InputNum == 0)&&(OutLen == 0)) {
			OutStr[OutLen++] = '0';
		} else {
			for(int i=1;i<=OutLen;i++) {
				OutStr[i-1] = TempStr[OutLen-i];	//��λ-->��λ;
			}
		}
	}
	return OutLen;
}
//�ַ������뺯��
char* myFgets(char* Str, int Size) {
	if(fgets(Str, Size, stdin) != NULL) { // fgets()�ɹ������ַ���
		int len = strlen(Str);
		if(Str[len - 1] == '\n') { // �ж����һ���ַ��Ƿ��ǻ��з�
			Str[len - 1] = '\0'; // ȥ�����һ���ַ�
		}
		return Str; // �����ַ���ָ��
	} else {
		return NULL; // ���fgets()����ʧ�ܣ�����NULL
	}
}
/*
	���ܣ����ַ��� ��str�� �� �ַ���s���ָ�
	�÷���
		char IntDataStr[]={"ab-cd-ef-gh"};
		ContAddr = 0,1,2,3,...
		IntDataStr = ab/cd/ef/gh
	��ע��ʹ�øú����� IntDataStr �ַ��������ݽ��ᶪʧ
*/
void myStrtok(char Str[], int StrMaxLen, char s[], int ContAddr) {
	char *next_token = NULL;
	char *token = NULL;
	token = strtok_s(Str, s, &next_token);
	if (ContAddr != 0) {
		for (int i = 0; i < ContAddr; i++) {
			token = strtok_s(NULL, s, &next_token);
		}
		int addr=0;
		while((token[addr] != '\0')&&(addr < StrMaxLen)) {
			Str[addr] = token[addr];
			addr++;
		}
		Str[addr] = '\0';
	}
}
