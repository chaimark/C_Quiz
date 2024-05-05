/*
XXXX_XXX <==> 宏定义
Xxxx_Xxxx <==> 全局变量，对象名
_Xxxx_Xxx <==> 类名
XxxxXxxxx <==> 局部变量
xxxxXxxx() <==> 函数
xxxxx_xxxx <==> typedef(数据类型)
*/
#ifndef MY_ARRAY_H  // 如果 MY_HEADER_FILE_H 未定义
#define MY_ARRAY_H  // 定义 MY_HEADER_FILE_H
/*-----------------------------------标准库------------------------------------*/
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/*-----------------------------------基础定义----------------------------------*/
// 计算数组元素个数
#define ARR_SIZE(ArrName) sizeof(ArrName) / sizeof(ArrName[0])
#define NEW_NAME(ArrName) otherName(ArrName, ARR_SIZE(ArrName))
// 定义一类型联合体类 Data_Class，用于存储不同类型的指针数据
typedef union Data_Class {
    void *_void;            // 无定义形指针
    char *_char;            // 字符型指针
    short *_short;          // 短整型指针
    int *_int;              // 整型指针
    long *_long;            // 长整型指针
    long long *_LLong;      // 长长整型指针
    float *_float;          // 单精度浮点型指针
    double *_double;        // 双精度浮点型指针
    long double *_Ldouble;  // 扩展精度浮点型指针
} _newclass;
// 别名结构体类型
typedef struct New_Arr {
    _newclass Name;
    int Len;
} strnew;

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
#endif  // MY_ARRAY_H