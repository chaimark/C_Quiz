#ifndef __SETTIME_H
#define __SETTIME_H

#include "StrLib.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum _TimeTaskName {	// 发送AT指令时调用什么函数发送，对应的函数名
    CheckDownCmd,       // 用于判断什么时候检查下行指令
    checkNet,           // 用于判断什么时候检查网络在线标记
    UartIRQOverTime,    // 用于判断什么时候 uart 中断是否超时
} TimeTaskName;

#define SecTo10Ms(sec) (uint64_t)(sec * 100)
#define SetTimeTaskMAX 4
typedef struct _BSTIM_USER_SET_TASK {
    struct _setTime_Task {
        bool TimeTask_Falge;    // 当前计时任务是否完成
        bool isTaskStart;       // 当前计时任务是否开启
        uint64_t CountNumOnce10Ms;
        uint64_t Max10MsNum;
        void (*TaskFunc)(void);
    } Task[SetTimeTaskMAX];
    void (*InitSetTimeTask)(int TaskAddr, uint64_t SetMax10MsNum, void (*TaskFunc)(void));
    void (*CloseTask)(int TaskAddr);
}BSTIM_USER_SET_TASK;
extern BSTIM_USER_SET_TASK SetTime;
extern void InitSetTime(void);
extern void CountSetTimeTask(void);
#endif 

