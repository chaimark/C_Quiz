
#ifndef STRLIB_H // ��� MY_HEADER_FILE_H δ����
#define STRLIB_H // ���� MY_HEADER_FILE_H

#include <string.h>

/*-----------------------------------����������----------------------------------*/
#define This (*this)
#define ARR_SIZE(ArrName) sizeof(ArrName) / sizeof(ArrName[0]) // ��������Ԫ�ظ���
#define WIFI_BUFF_MAXLEN 1024								   // ���ջ���ռ�
#define ONCE_PACKAGE_LEN 1000								   // http�ֿ鷢�͵ĵ���size
/*
�����࣬��������ָ��ͳ���
��Ҫע�����
������Ҫ���ظ�����ʱ
��ָ��ָ���������Ҫ������ȫ�ֿռ�
��������������Ϊ��ʵ�������Ҫע��
���Զ���һ��ȫ�ֿռ䣬������ʱ��� strnew ���������
����Ҫʹ��ʱֱ�Ӷ������ݣ�����Ϊ��������
*/
// �ඨ��
typedef struct New_Arr
{
	union _newclass
	{
		void *_void;		   // �޶�����ָ��
		char *_char;		   // �ַ���ָ��
		short *_short;		   // ������ָ��
		int *_int;			   // ����ָ��
		long *_long;		   // ������ָ��
		long long *_LLong;	   // ��������ָ��
		float *_float;		   // �����ȸ�����ָ��
		double *_double;	   // ˫���ȸ�����ָ��
		long double *_Ldouble; // ��չ���ȸ�����ָ��
	} Name;
	int MaxLen;
} strnew;
// ��������
#define NEW_NAME(ArrName) New_Str_Obj(ArrName, ARR_SIZE(ArrName))
extern strnew New_Str_Obj(void *Master, int SizeNum); // ��������ĺ���
extern char TempBuff[WIFI_BUFF_MAXLEN];

/*-----------------------------------�ⲿ�ӿ�----------------------------------*/

extern int catString(char *OutStr,char *IntStr,int MaxSize,int IntSize);
extern int copyString(char *OutStr,char *IntStr,int MaxSize,int IntSize);
extern int strToNumber(int OutNum, char * InputStr, int Size);
extern int numberToStr(char * OutStr, int InputNum, int Size);
extern char* myFgets(char* Str, int Size);
extern void myStrtok(char str[], int StrMaxLen, char s[], int ContAddr);
#endif
