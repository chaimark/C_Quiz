#ifndef __RTC_SETTIME_H
#define __RTC_SETTIME_H

#include "StrLib.h"
#include <stdbool.h>
#include <stdint.h>
#include "All.h"

// 将小时转换为分钟
#define HourToMin(x) (x*60)
// 将分钟转换为秒
#define MinToSec(x) (x*60)

#ifdef OPEN_AT_CMD_DEBUG_LEN
typedef enum _RTCTaskName {
    ATDebug,
    SendIntervalTask,
    SendTimeOverTask,
    DayOverCclkTask,
    EEpromWriteTime,
    EEpromWriteNB,
    IWDTClS,
}RTCTaskName;
#define RTCTimeTaskMAX 7
#else
typedef enum _RTCTaskName {
    SendIntervalTask,
    SendTimeOverTask,
    DayOverCclkTask,
    EEpromWriteTime,
    EEpromWriteNB,
    IWDTClS,
}RTCTaskName;
#define RTCTimeTaskMAX 6
#endif
typedef struct _USER_SET_TASK {
    struct {
        bool TimeTask_Falge;    // 当前计时任务是否完成
        bool isTaskStart;       // 当前计时任务是否开启
        uint64_t CountNumOnceSec;
        uint64_t MaxSecNum;
    } Task[RTCTimeTaskMAX];
    void (*InitSetTimeTask)(int TaskAddr, uint64_t SetMaxSecNum);
    void (*CloseTask)(int TaskAddr);
}USER_SET_TASK;
extern USER_SET_TASK RTC_TASK;
extern void InitRTC_TASK(void);
extern void CountRTCTask(void);
#endif 

