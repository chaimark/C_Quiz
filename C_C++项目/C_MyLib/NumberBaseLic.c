#include "NumberBaseLic.h"
/*
// 该库中提到的所有进制数全是直接表示，比如
// hex(0x125)   //表示 dec(125)
// hex(0x1010)  //表示 bin(1010)
// hex(0x1f)    //表示 hex(0x1f)
*/
void numberArrayToStrArray(char StrArray[], uint8_t NumberArray[], int ArrayMinLen);  // 将数组串转字符串
void strArrayToNumberArray(uint8_t NumberArray[], char StrArray[], int ArrayMinLen);  // 将字符串转数组串
uint64_t anyBaseNumberToStr(uint8_t *Output, int StrSize, uint64_t InputNumber); // 任意进制数转对应进制字符串 返回长度
uint64_t strToAnyBaseNumber(int NumberBase, uint8_t *IntputStr, int StrSize);    // 任意进制字符串转对应进制数
uint64_t anyBaseToOtherBase(uint64_t Number, int IntputBase, int OutputBase);    // 任意进制互转

/*
0x61 == 'a' => 0x0a;
0x41 == 'A' => 0x0A;
0x31 == '1' => 0x01;
*/
// 将数组串转字符串
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
// 将字符串转数组串
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

// 任意进制数转对应进制数组 返回长度
uint64_t anyBaseNumberToStr(uint8_t *Output, int StrSize, uint64_t InputNumber)
{
    uint8_t Add_i = 0;
    uint8_t TempArray[16] = {0}; // uint64_t也只有16位数 0x0000000000000001
    uint64_t OutLen = 0;
    // 字符串空间必须达到16个字节
    if (StrSize < 16)
    {
        return OutLen;
    }
    // 将数据转为字符串
    for (Add_i = 0; Add_i < 16; Add_i++)
    {
        TempArray[Add_i] = InputNumber & 0x000000000000000F; // 先存低位
        InputNumber = InputNumber >> 4;
    }
    for (Add_i = 0; Add_i < 16; Add_i++)
    {
        Output[Add_i] = TempArray[Add_i];
    }
    // 计算长度
    OutLen = 16;
    Add_i = 16;
    while (TempArray[--Add_i] == 0)
    {
        OutLen--;
    }
    return OutLen;
}
// 任意进制数组转对应进制数
uint64_t strToAnyBaseNumber(int NumberBase, uint8_t *InputStr, int StrSize)
{
    uint8_t Add_i = 0;
    uint8_t TempArray[16] = {0}; // uint64_t也只有16位数 0x0000000000000001
    uint64_t ResNumber = 0;
    // 输入的数组长度大于16直接返回
    if (StrSize > 16)
    {
        return ResNumber;
    }
    // copy 输入的数据
    for (int Add_i = 0; Add_i < StrSize; Add_i++)
    {
        TempArray[Add_i] = InputStr[Add_i];
    }
    // 将数组串组装成直接表示的数
    // 如：hex(0x125) ==> dec(125)
    for (int Add_i = 15; Add_i >= 0; Add_i--)
    {
        ResNumber = ResNumber << 4;
        uint64_t Number = TempArray[Add_i] & 0x0F; // 0b:00001111
        ResNumber = ResNumber | Number;
    }
    return ResNumber;
}
// 将任意进制数转为16进制
uint64_t anyBaseToHexadecimal(uint64_t Number, int IntputBase)
{
    uint64_t ResNumber = 0;
    uint8_t TempArray[16] = {0}; // uint64_t也只有16位数 0x0000000000000001
    // 16进制直接返回
    if (IntputBase == 16)
    {
        return Number;
    }
    // 先将数据转为数组串
    for (int Add_i = 0; Add_i < 16; Add_i++)
    {
        TempArray[Add_i] = Number & 0x000000000000000F; // 先存低位
        Number = Number >> 4;
    }
    // 根据数组串和该数原来的进制 转换为16进制 如：Dex(0x31)==>Hex(0x1f)
    for (int Add_i = 0; Add_i < 16; Add_i++)
    {
        uint64_t TempNumber = TempArray[Add_i];
        for (int i = 0; i < Add_i; i++) // 单独计算每个空间对应的数的大小
        {
            TempNumber = TempNumber * IntputBase;
        }
        ResNumber += TempNumber;
    }
    return ResNumber;
}
// 将16进制数转为任意进制
uint64_t hexadecimalToAnyBase(uint64_t Number, int OutputBase)
{
    uint64_t ResNumber = 0;
    // uint64_t也只有16位数 0x0000000000000001(//0b:...00001111)
    uint8_t TempArray[16] = {0};
    // 16进制直接返回
    if (OutputBase == 16)
    {
        return Number;
    }
    // 先将数据根据目标进制转为数组串
    for (int Add_i = 0; Add_i < 16; Add_i++)
    {
        TempArray[Add_i] = Number % OutputBase; // 先存低位
        Number /= OutputBase;
    }
    // 再将数组串组装成直接表示的数
    // 如：hex(0x125) ==> dec(125)
    for (int Add_i = 15; Add_i >= 0; Add_i--)
    {
        ResNumber = ResNumber << 4;
        Number = TempArray[Add_i] & 0x0F; // 0b:00001111
        ResNumber = ResNumber | Number;
    }
    return ResNumber;
}
// 任意进制互转
uint64_t anyBaseToOtherBase(uint64_t Number, int IntputBase, int OutputBase)
{
    uint64_t ResNumber = Number;
    ResNumber = anyBaseToHexadecimal(ResNumber, IntputBase); // 先转到16进制
    ResNumber = hexadecimalToAnyBase(ResNumber, OutputBase); // 再转到任意进制
    return ResNumber;
}
