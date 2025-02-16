#ifndef __RTC_SETTIME_H
#define __RTC_SETTIME_H
#include "StrLib.h"
#include <stdbool.h>
#include <stdint.h>
#include "PublicLib_No_One.h"
// 将小时转换为分钟
#define HourToMin(x) (x*60)
// 将分钟转换为秒
#define MinToSec(x) (x*60)

#ifdef OPEN_AT_CMD_DEBUG
typedef enum _RTCTaskName {
    ATDebug,
    CheckNet,
    Read_EEprom,
    HourTaskOfColorShow,
    MinTaskOfColorShow,
    WriteTimeOfLocal,
    AdjustSubDevTime,
    MBUSUARTReboot,
    ReadMainMeter,
    ReadCopyMeter,
    CloseLEDFlag,
    TestVoltgeAndMA,
    PauseTimeOfLinkErr,
    DayOverCclkTask,
    GetRSSIBy4G,
}RTCTaskName;
#define RTCTimeTaskMAX 15
#else
typedef enum _RTCTaskName {
    CheckNet,
    Read_EEprom,
    HourTaskOfColorShow,
    MinTaskOfColorShow,
    WriteTimeOfLocal,
    AdjustSubDevTime,
    MBUSUARTReboot,
    ReadMainMeter,
    ReadCopyMeter,
    CloseLEDFlag,
    TestVoltgeAndMA,
    PauseTimeOfLinkErr,
    DayOverCclkTask,
    GetRSSIBy4G,
}RTCTaskName;
#define RTCTimeTaskMAX 14
#endif
typedef struct _USER_SET_TASK {
    struct {
        bool TimeTask_Falge;    // 当前计时任务是否完成
        bool isTaskStart;       // 当前计时任务是否开启
        uint64_t CountNumOnceSec;
        uint64_t MaxSecNum;
        void (*TaskFunc)(void);
    } Task[RTCTimeTaskMAX];
    void (*InitSetTimeTask)(int TaskAddr, uint64_t SetMaxSecNum, void (*TaskFunc)(void));
    void (*CloseTask)(int TaskAddr);
    int NumberOfTimeTask;
}USER_SET_TASK;
extern USER_SET_TASK RTC_TASK;
extern void CountRTCTask(void);
#endif

