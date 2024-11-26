#ifndef __SETTIME_H
#define __SETTIME_H

#include "StrLib.h"
#include <stdbool.h>
#include <stdint.h>
#define BSTIM_OPEN_AND_TASK_NUM 6
#define LPTIM_OPEN_AND_TASK_NUM 3

#ifdef BSTIM_OPEN_AND_TASK_NUM
/********************BSTIM********************/
typedef enum _TimeTaskName {	// 发送AT指令时调用什么函数发送，对应的函数名
    RecTimeUART0,       // 用于判断 uart0   串口是否接收结束
    RecTimeUART1,       // 用于判断 uart1   串口是否接收结束
    RecTimeUART4,       // 用于判断 uart4   串口是否接收结束
    RecTimeUART5,       // 用于判断 uart5   串口是否接收结束
    RecTimeLPUART0,     // 用于判断 LPuart0 串口是否接收结束
    RecTimeLPUART1,     // 用于判断 LPuart1 串口是否接收结束
} TimeTaskName;

#define SecTo10Ms(sec) (uint64_t)((sec * 100 == 0) ? 1 : (sec * 100))
typedef struct _BSTIM_USER_SET_TASK {
    struct _setTime_Task {
        bool TimeTask_Falge;    // 当前计时任务是否完成
        bool isTaskStart;       // 当前计时任务是否开启
        uint64_t CountNumOnce10Ms;
        uint64_t Max10MsNum;
        void (*TaskFunc)(void);
    } Task[BSTIM_OPEN_AND_TASK_NUM];
    void (*InitSetTimeTask)(int TaskAddr, uint64_t SetMax10MsNum, void (*TaskFunc)(void));
    void (*CloseTask)(int TaskAddr);
    int NumberOfTimeTask;
}BSTIM_USER_SET_TASK;
extern BSTIM_USER_SET_TASK SetTime;
extern void InitSetTime(void);
extern void CountSetTimeTask(void);
#endif

#ifdef LPTIM_OPEN_AND_TASK_NUM
/********************LPTIM********************/
typedef enum _LPTimeTaskName {
    checkNet,           // 用于判断什么时候检查网络在线标记
    RefreshLED,         // 用于判断什么时候刷新LED
    PathSwitch,         // 用于判断什么时候切换到透传
}LPTimeTaskName;

#define SecTo250Ms(sec) (uint64_t)((sec * 4 == 0) ? 1 : (sec * 4))
typedef struct _LPTIM_USER_SET_TASK {
    struct _setLPTime_Task {
        bool TimeTask_Falge;    // 当前计时任务是否完成
        bool isTaskStart;       // 当前计时任务是否开启
        uint64_t CountNumOnce250Ms;
        uint64_t Max250MsNum;
        void (*TaskFunc)(void);
    } Task[LPTIM_OPEN_AND_TASK_NUM];
    void (*LPInitSetTimeTask)(int TaskAddr, uint64_t SetMax250MsNum, void (*TaskFunc)(void));
    void (*CloseTask)(int TaskAddr);
    int NumberOfTimeTask;
}LPTIM_USER_SET_TASK;
extern LPTIM_USER_SET_TASK SetLPTime;
extern void LPInitSetTime(void);
extern void LPCountSetTimeTask(void);
#endif 
#endif

