/*
XXXX_XXX <==> �궨��
Xxxx_Xxxx <==> ȫ�ֱ�����������
_Xxxx_Xxx <==> ����
XxxxXxxxx <==> �ֲ�����
xxxxXxxx() <==> ����
xxxxx_xxxx <==> typedef(��������)
*/
#ifndef NUMBERBASELIC_H
#define NUMBERBASELIC_H

#include <stdint.h>

#define int8_t char                 // �з���08λ��������
#define uint8_t unsigned char       // �޷���08λ��������
#define int16_t int                 // �з���16λ��������
#define uint16_t unsigned int       // �޷���16λ��������
#define int32_t long int            // �з���32λ��������
#define uint32_t unsigned long int  // �޷���32λ��������
#define int64_t long long           // �з���64λ��������
#define uint64_t unsigned long long // �з���64λ��������

extern void numberArrayToStrArray(char StrArray[], uint8_t NumberArray[], int ArrayMinLen);  // �����鴮ת�ַ���
extern void strArrayToNumberArray(uint8_t NumberArray[], char StrArray[], int ArrayMinLen);  // ���ַ���ת���鴮
extern uint64_t anyBaseNumberToStr(uint8_t *Output, int StrSize, uint64_t InputNumber); // ���������ת��Ӧ�����ַ��� ���س���
extern uint64_t strToAnyBaseNumber(int NumberBase, uint8_t *IntputStr, int StrSize);    // ��������ַ���ת��Ӧ������
extern uint64_t anyBaseToOtherBase(uint64_t Number, int IntputBase, int OutputBase);    // ������ƻ�ת

#endif
