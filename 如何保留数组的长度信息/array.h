#ifndef MY_ARRAY_H  // 如果 MY_HEADER_FILE_H 未定义
#define MY_ARRAY_H  // 定义 MY_HEADER_FILE_H

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
} newclass;

// 别名结构体类型
typedef struct New_Arr {
    newclass Name;
    int Len;
} strnew;

// 别名初始化函数（返回一个结构体数据）
strnew otherName(void *Master, int SizeNum) {
    strnew newArray;
    newArray.Len = SizeNum;
    newArray.Name._void = Master;
    return newArray;
}

#endif  // MY_ARRAY_H