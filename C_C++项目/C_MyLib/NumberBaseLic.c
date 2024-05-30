#include "NumberBaseLic.h"
/*
// �ÿ����ᵽ�����н�����ȫ��ֱ�ӱ�ʾ������
// hex(0x125)   //��ʾ dec(125)
// hex(0x1010)  //��ʾ bin(1010)
// hex(0x1f)    //��ʾ hex(0x1f)
*/
void numberArrayToStrArray(char StrArray[], uint8_t NumberArray[], int ArrayMinLen);  // �����鴮ת�ַ���
void strArrayToNumberArray(uint8_t NumberArray[], char StrArray[], int ArrayMinLen);  // ���ַ���ת���鴮
uint64_t anyBaseNumberToStr(uint8_t *Output, int StrSize, uint64_t InputNumber); // ���������ת��Ӧ�����ַ��� ���س���
uint64_t strToAnyBaseNumber(int NumberBase, uint8_t *IntputStr, int StrSize);    // ��������ַ���ת��Ӧ������
uint64_t anyBaseToOtherBase(uint64_t Number, int IntputBase, int OutputBase);    // ������ƻ�ת

/*
0x61 == 'a' => 0x0a;
0x41 == 'A' => 0x0A;
0x31 == '1' => 0x01;
*/
// �����鴮ת�ַ���
void numberArrayToStrArray(char StrArray[], uint8_t NumberArray[], int ArrayMinLen)
{
    int Addr = 0;
    do
    {
        if (NumberArray[Addr] < 10)
        {
            StrArray[Addr] = NumberArray[Addr] + '0';
        }
        else if ((NumberArray[Addr] >= 0x0A) && (NumberArray[Addr] <= 0x0F))
        {
            StrArray[Addr] = NumberArray[Addr] + 0x37;
        }
        Addr++;
    } while (Addr < ArrayMinLen);
}
// ���ַ���ת���鴮
void strArrayToNumberArray(uint8_t NumberArray[], char StrArray[], int ArrayMinLen)
{
    int Addr = 0;
    do
    {
        if ((StrArray[Addr] >= '0') && (StrArray[Addr] <= '9'))
        {
            NumberArray[Addr] = StrArray[Addr] - '0';
        }
        else if ((StrArray[Addr] >= 'A') && (StrArray[Addr] <= 'Z'))
        {
            NumberArray[Addr] = StrArray[Addr] - 0x37;
        }
        else if ((StrArray[Addr] >= 'a') && (StrArray[Addr] <= 'z'))
        {
            NumberArray[Addr] = StrArray[Addr] - 0x57;
        }
        Addr++;
    } while (Addr < ArrayMinLen);
}

// ���������ת��Ӧ�������� ���س���
uint64_t anyBaseNumberToStr(uint8_t *Output, int StrSize, uint64_t InputNumber)
{
    uint8_t Add_i = 0;
    uint8_t TempArray[16] = {0}; // uint64_tҲֻ��16λ�� 0x0000000000000001
    uint64_t OutLen = 0;
    // �ַ����ռ����ﵽ16���ֽ�
    if (StrSize < 16)
    {
        return OutLen;
    }
    // ������תΪ�ַ���
    for (Add_i = 0; Add_i < 16; Add_i++)
    {
        TempArray[Add_i] = InputNumber & 0x000000000000000F; // �ȴ��λ
        InputNumber = InputNumber >> 4;
    }
    for (Add_i = 0; Add_i < 16; Add_i++)
    {
        Output[Add_i] = TempArray[Add_i];
    }
    // ���㳤��
    OutLen = 16;
    Add_i = 16;
    while (TempArray[--Add_i] == 0)
    {
        OutLen--;
    }
    return OutLen;
}
// �����������ת��Ӧ������
uint64_t strToAnyBaseNumber(int NumberBase, uint8_t *InputStr, int StrSize)
{
    uint8_t Add_i = 0;
    uint8_t TempArray[16] = {0}; // uint64_tҲֻ��16λ�� 0x0000000000000001
    uint64_t ResNumber = 0;
    // ��������鳤�ȴ���16ֱ�ӷ���
    if (StrSize > 16)
    {
        return ResNumber;
    }
    // copy ���������
    for (int Add_i = 0; Add_i < StrSize; Add_i++)
    {
        TempArray[Add_i] = InputStr[Add_i];
    }
    // �����鴮��װ��ֱ�ӱ�ʾ����
    // �磺hex(0x125) ==> dec(125)
    for (int Add_i = 15; Add_i >= 0; Add_i--)
    {
        ResNumber = ResNumber << 4;
        uint64_t Number = TempArray[Add_i] & 0x0F; // 0b:00001111
        ResNumber = ResNumber | Number;
    }
    return ResNumber;
}
// �����������תΪ16����
uint64_t anyBaseToHexadecimal(uint64_t Number, int IntputBase)
{
    uint64_t ResNumber = 0;
    uint8_t TempArray[16] = {0}; // uint64_tҲֻ��16λ�� 0x0000000000000001
    // 16����ֱ�ӷ���
    if (IntputBase == 16)
    {
        return Number;
    }
    // �Ƚ�����תΪ���鴮
    for (int Add_i = 0; Add_i < 16; Add_i++)
    {
        TempArray[Add_i] = Number & 0x000000000000000F; // �ȴ��λ
        Number = Number >> 4;
    }
    // �������鴮�͸���ԭ���Ľ��� ת��Ϊ16���� �磺Dex(0x31)==>Hex(0x1f)
    for (int Add_i = 0; Add_i < 16; Add_i++)
    {
        uint64_t TempNumber = TempArray[Add_i];
        for (int i = 0; i < Add_i; i++) // ��������ÿ���ռ��Ӧ�����Ĵ�С
        {
            TempNumber = TempNumber * IntputBase;
        }
        ResNumber += TempNumber;
    }
    return ResNumber;
}
// ��16������תΪ�������
uint64_t hexadecimalToAnyBase(uint64_t Number, int OutputBase)
{
    uint64_t ResNumber = 0;
    // uint64_tҲֻ��16λ�� 0x0000000000000001(//0b:...00001111)
    uint8_t TempArray[16] = {0};
    // 16����ֱ�ӷ���
    if (OutputBase == 16)
    {
        return Number;
    }
    // �Ƚ����ݸ���Ŀ�����תΪ���鴮
    for (int Add_i = 0; Add_i < 16; Add_i++)
    {
        TempArray[Add_i] = Number % OutputBase; // �ȴ��λ
        Number /= OutputBase;
    }
    // �ٽ����鴮��װ��ֱ�ӱ�ʾ����
    // �磺hex(0x125) ==> dec(125)
    for (int Add_i = 15; Add_i >= 0; Add_i--)
    {
        ResNumber = ResNumber << 4;
        Number = TempArray[Add_i] & 0x0F; // 0b:00001111
        ResNumber = ResNumber | Number;
    }
    return ResNumber;
}
// ������ƻ�ת
uint64_t anyBaseToOtherBase(uint64_t Number, int IntputBase, int OutputBase)
{
    uint64_t ResNumber = Number;
    ResNumber = anyBaseToHexadecimal(ResNumber, IntputBase); // ��ת��16����
    ResNumber = hexadecimalToAnyBase(ResNumber, OutputBase); // ��ת���������
    return ResNumber;
}
