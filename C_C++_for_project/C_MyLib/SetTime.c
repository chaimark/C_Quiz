#include "SetTime.h"
#ifdef BSTIM_OPEN_AND_TASK_NUM

void _SetCloseTask(int TaskAddr);
void _InitSetTimeTask(int TaskAddr, uint64_t SetMax10MsNum, void (*TaskFunc)(void));

// 可自定义的定时任务
BSTIM_USER_SET_TASK SetTime = {
    .Task = {0},
    .InitSetTimeTask = _InitSetTimeTask,
    .CloseTask = _SetCloseTask,
    .NumberOfTimeTask = BSTIM_OPEN_AND_TASK_NUM, // 定时任务数量
};

void _SetCloseTask(int TaskAddr) {
    if ((TaskAddr < 0) || (TaskAddr >= BSTIM_OPEN_AND_TASK_NUM)) {
        return;
    }
    SetTime.Task[TaskAddr].isTaskStart = false; // 初始化标记
    SetTime.Task[TaskAddr].TimeTask_Falge = false;
    SetTime.Task[TaskAddr].CountNumOnce10Ms = 0; // 复位初始
    SetTime.Task[TaskAddr].TaskFunc = NULL;
}
void _InitSetTimeTask(int TaskAddr, uint64_t SetMax10MsNum, void (*TaskFunc)(void)) {
    if ((TaskAddr < 0) || (TaskAddr >= BSTIM_OPEN_AND_TASK_NUM)) {
        return;
    }
    SetTime.Task[TaskAddr].TimeTask_Falge = false; // 初始化标记
    SetTime.Task[TaskAddr].isTaskStart = true;     // 开启
    SetTime.Task[TaskAddr].Max10MsNum = SetMax10MsNum; // 定时任务点
    SetTime.Task[TaskAddr].CountNumOnce10Ms = 0; // 复位初始
    SetTime.Task[TaskAddr].TaskFunc = TaskFunc;
}
// 计数函数
void CountSetTimeTask(void) {
    for (int TaskAddr = 0; TaskAddr < BSTIM_OPEN_AND_TASK_NUM; TaskAddr++) {
        if (SetTime.Task[TaskAddr].isTaskStart == false) {
            continue;
        }
        if (SetTime.Task[TaskAddr].CountNumOnce10Ms < SetTime.Task[TaskAddr].Max10MsNum) {
            SetTime.Task[TaskAddr].CountNumOnce10Ms++;
        } else {
            SetTime.Task[TaskAddr].TimeTask_Falge = true;
        }
        if (SetTime.Task[TaskAddr].TimeTask_Falge == true) {
            if (SetTime.Task[TaskAddr].TaskFunc != NULL) {
                SetTime.Task[TaskAddr].TaskFunc(); // 注意:该函数，执行时不要太长，也不要启动同一个定时器的其他任务
            }
        }
    }
}
#endif

////////////////////////////////////////////////////
#ifdef LPTIM_OPEN_AND_TASK_NUM

void _LPSetCloseTask(int TaskAddr);
void _LPInitSetTimeTask(int TaskAddr, uint64_t SetMax250MsNum, void (*TaskFunc)(void));

// 可自定义的定时任务
LPTIM_USER_SET_TASK SetLPTime = {
    .Task = {0},
    .LPInitSetTimeTask = _LPInitSetTimeTask,
    .CloseTask = _LPSetCloseTask,
    .NumberOfTimeTask = LPTIM_OPEN_AND_TASK_NUM, // 定时任务数量
};

void _LPSetCloseTask(int TaskAddr) {
    if ((TaskAddr < 0) || (TaskAddr >= LPTIM_OPEN_AND_TASK_NUM)) {
        return;
    }
    SetLPTime.Task[TaskAddr].isTaskStart = false; // 初始化标记
    SetLPTime.Task[TaskAddr].TimeTask_Falge = false;
    SetLPTime.Task[TaskAddr].CountNumOnce250Ms = 0; // 复位初始
    SetLPTime.Task[TaskAddr].TaskFunc = NULL;
}
void _LPInitSetTimeTask(int TaskAddr, uint64_t SetMax250MsNum, void (*TaskFunc)(void)) {
    if ((TaskAddr < 0) || (TaskAddr >= LPTIM_OPEN_AND_TASK_NUM)) {
        return;
    }
    SetLPTime.Task[TaskAddr].TimeTask_Falge = false; // 初始化标记
    SetLPTime.Task[TaskAddr].isTaskStart = true;     // 开启
    SetLPTime.Task[TaskAddr].Max250MsNum = SetMax250MsNum; // 定时任务点
    SetLPTime.Task[TaskAddr].CountNumOnce250Ms = 0; // 复位初始
    SetLPTime.Task[TaskAddr].TaskFunc = TaskFunc;
}
// #include "mf_config.h"
// 计数函数
void LPCountSetTimeTask(void) {
    /*****************************************************/
    // if (!SetLPTime.Task[IWDTClS].TimeTask_Falge) {  // 8 分钟后没有返回主函数重新复位计数器，复位MCU
    //     FL_IWDT_ReloadCounter(IWDT);    // 8 分钟之内 RTC 帮忙喂狗
    // }
    /*****************************************************/
    for (int TaskAddr = 0; TaskAddr < LPTIM_OPEN_AND_TASK_NUM; TaskAddr++) {
        if (SetLPTime.Task[TaskAddr].isTaskStart == false) {
            continue;
        }
        if (SetLPTime.Task[TaskAddr].CountNumOnce250Ms < SetLPTime.Task[TaskAddr].Max250MsNum) {
            SetLPTime.Task[TaskAddr].CountNumOnce250Ms++;
        } else {
            SetLPTime.Task[TaskAddr].TimeTask_Falge = true;
        }
        if (SetLPTime.Task[TaskAddr].TimeTask_Falge == true) {
            if (SetLPTime.Task[TaskAddr].TaskFunc != NULL) {
                SetLPTime.Task[TaskAddr].TaskFunc(); // 注意:该函数，执行时不要太长，也不要启动同一个定时器的其他任务
            }
        }
    }
}
#endif

