/*-----------------------------------��׼��------------------------------------*/
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"
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
