#ifndef MY_ARRAY_H  // ��� MY_HEADER_FILE_H δ����
#define MY_ARRAY_H  // ���� MY_HEADER_FILE_H

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
} newclass;

// �����ṹ������
typedef struct New_Arr {
    newclass Name;
    int Len;
} strnew;

// ������ʼ������������һ���ṹ�����ݣ�
strnew otherName(void *Master, int SizeNum) {
    strnew newArray;
    newArray.Len = SizeNum;
    newArray.Name._void = Master;
    return newArray;
}

#endif  // MY_ARRAY_H