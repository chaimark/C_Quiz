#ifndef _COLORSHOW_H
//#define _COLORSHOW_H

#ifdef _COLORSHOW_H
#include "PublicLib_No_One.h"

typedef struct _ColorDisPlayOfMainDev {
    bool IsStartHeat;
    struct _HourData {
        double InWaterTemp;       // 进水温度
        double OutWaterTemp;      // 回水温度
        double SumEnergy;         // 累计耗能
        double SumFlow;           // 累计耗流
    } HourData;
    struct _MinData {
        double FlowSpeed; // 流速
    } MinData;
} ColorDisPlayOfMainDev;
extern ColorDisPlayOfMainDev ColorShowData;

extern void initTaskOfColorShowTask(void);
extern void saveMeterDataMainDev(char InputData[], int InputDataLen);
extern void hourTaskOfColorShowTask(void);
extern void minTaskOfColorShowTask(void);

#endif
#endif
