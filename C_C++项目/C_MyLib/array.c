/*-----------------------------------标准库------------------------------------*/
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"
/*-----------------------------------函数说明----------------------------------*/
// 别名初始化函数（返回一个结构体数据）
strnew otherName(void *Master, int SizeNum);
//生成随机数组
void srandArray(int Num[], int MaxVar);

/*-----------------------------------函数定义----------------------------------*/
// 别名初始化函数（返回一个结构体数据）
strnew otherName(void *Master, int SizeNum) {
    strnew newArray;
    newArray.Len = SizeNum;
    newArray.Name._void = Master;
    return newArray;
}
//生成随机数组
void srandArray(int Num[], int MaxVar) {
	int id_num = 0;
	int temp = 0;
	for(int i=0;i<MaxVar;i++) {
		srand((unsigned)time(NULL)); //随机种子
		Num[i] = i + 1;
		id_num = rand()%(i+1)+0; //x为0-i之间的随机数
		temp = Num[id_num];
		Num[id_num] = Num[i];
		Num[i] = temp;
	}
}
