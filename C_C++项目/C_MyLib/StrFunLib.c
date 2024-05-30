/*-----------------------------------标准库------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "StrFunLib.h"
/*-----------------------------------基础定义----------------------------------*/

/*-----------------------------------函数说明----------------------------------*/
//追加字符
int catString(char *OutStr,char *IntStr,int MaxSize,int IntSize);
//复制字符
int copyString(char *OutStr,char *IntStr,int MaxSize,int IntSize);
//将字符串转换到数字
int strToNumber(int OutNum, char * InputStr, int Size);
//将数字转换到字符串
int numberToStr(char * OutStr, int InputNum, int Size);
//字符串输入函数
char* myFgets(char* Str, int Size);
//把字符串（str）按字符串（s）分隔
void myStrtok(char str[], int StrMaxLen, char s[], int ContAddr);

/*-----------------------------------函数定义----------------------------------*/
//追加字符
int catString(char *OutStr,char *IntStr,int MaxSize,int IntSize) {
	int AddrNow = 0;
	int run = 0;
	//找出"\0"
	while((OutStr[AddrNow]!='\0')&&(AddrNow < MaxSize)) {
		if(AddrNow > MaxSize) {
			return -1;
		}
		AddrNow++;
	}
	if(MaxSize >= AddrNow+IntSize) {
		//开始追加
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
//复制字符串
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
//字符串转数字
int strToNumber(int OutNum, char *InputStr, int Size)
{
    int H_ERROR_NUM = -1;	
	int cont_num = 0;
	char c;
	for(int i=0;((c = InputStr[i] ) != '\0')&&(i<Size);i++)  { // 读入直到结束符号
		if (c >= '0' && c <= '9') {  // 如果是数字字符
			OutNum = OutNum * 10 + (c - '0');  // 将字符转换为数字并累加到value中
		} else {
			return H_ERROR_NUM; // 如果读到非数字字符，返回错误标识-1
		}
		cont_num++;
	}
	return (cont_num == 0)?(H_ERROR_NUM):(OutNum); // 返回读入的整数值
}
//数字转字符串
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
				OutStr[i-1] = TempStr[OutLen-i];	//高位-->低位;
			}
		}
	}
	return OutLen;
}
//字符串输入函数
char* myFgets(char* Str, int Size) {
	if(fgets(Str, Size, stdin) != NULL) { // fgets()成功读入字符串
		int len = strlen(Str);
		if(Str[len - 1] == '\n') { // 判断最后一个字符是否是换行符
			Str[len - 1] = '\0'; // 去掉最后一个字符
		}
		return Str; // 返回字符串指针
	} else {
		return NULL; // 如果fgets()读入失败，返回NULL
	}
}
/*
	功能：将字符串 （str） 按 字符（s）分隔
	用法：
		char IntDataStr[]={"ab-cd-ef-gh"};
		ContAddr = 0,1,2,3,...
		IntDataStr = ab/cd/ef/gh
	备注：使用该函数后 IntDataStr 字符串的数据将会丢失
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
