/*
XXXX_XXX <==> �궨��
Xxxx_Xxxx <==> ȫ�ֱ�����������
_Xxxx_Xxx <==> ����
XxxxXxxxx <==> �ֲ�����
xxxxXxxx() <==> ����
xxxxx_xxxx <==> typedef(��������)
*/
#ifndef MY_ARRAY_H  // ��� MY_HEADER_FILE_H δ����
#define MY_ARRAY_H  // ���� MY_HEADER_FILE_H
/*-----------------------------------��׼��------------------------------------*/
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/*-----------------------------------��������----------------------------------*/
// ��������Ԫ�ظ���
#define ARR_SIZE(ArrName) sizeof(ArrName) / sizeof(ArrName[0])
#define NEW_NAME(ArrName) otherName(ArrName, ARR_SIZE(ArrName))
// ����һ������������ Data_Class�����ڴ洢��ͬ���͵�ָ������
typedef union Data_Class {
    void *_void;            // �޶�����ָ��
    char *_char;            // �ַ���ָ��
    short *_short;          // ������ָ��
    int *_int;              // ����ָ��
    long *_long;            // ������ָ��
    long long *_LLong;      // ��������ָ��
    float *_float;          // �����ȸ�����ָ��
    double *_double;        // ˫���ȸ�����ָ��
    long double *_Ldouble;  // ��չ���ȸ�����ָ��
} _newclass;
// �����ṹ������
typedef struct New_Arr {
    _newclass Name;
    int Len;
} strnew;

/*-----------------------------------����˵��----------------------------------*/
// ������ʼ������������һ���ṹ�����ݣ�
strnew otherName(void *Master, int SizeNum);
//�����������
void srandArray(int Num[], int MaxVar);

/*-----------------------------------��������----------------------------------*/
// ������ʼ������������һ���ṹ�����ݣ�
strnew otherName(void *Master, int SizeNum) {
    strnew newArray;
    newArray.Len = SizeNum;
    newArray.Name._void = Master;
    return newArray;
}
//�����������
void srandArray(int Num[], int MaxVar) {
	int id_num = 0;
	int temp = 0;
	for(int i=0;i<MaxVar;i++) {
		srand((unsigned)time(NULL)); //�������
		Num[i] = i + 1;
		id_num = rand()%(i+1)+0; //xΪ0-i֮��������
		temp = Num[id_num];
		Num[id_num] = Num[i];
		Num[i] = temp;
	}
}
#endif  // MY_ARRAY_H