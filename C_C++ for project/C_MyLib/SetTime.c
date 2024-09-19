#include "SetTime.h"

// 可自定义的定时任务
BSTIM_USER_SET_TASK SetTime;
void _SetCloseTask(int TaskAddr) {
    if ((TaskAddr < 0) || (TaskAddr >= SetTimeTaskMAX)) {
        return;
    }
    SetTime.Task[TaskAddr].isTaskStart = false; // 初始化标记
    SetTime.Task[TaskAddr].TimeTask_Falge = false;
    SetTime.Task[TaskAddr].CountNumOnce10Ms = 0; // 复位初始
    SetTime.Task[TaskAddr].TaskFunc = NULL;
}
void _InitSetTimeTask(int TaskAddr, uint64_t SetMax10MsNum, void (*TaskFunc)(void)) {
    if ((TaskAddr < 0) || (TaskAddr >= SetTimeTaskMAX)) {
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
    for (int i = 0; i < SetTimeTaskMAX; i++) {
        if (SetTime.Task[i].isTaskStart == false) {
            continue;
        }
        if (SetTime.Task[i].CountNumOnce10Ms < SetTime.Task[i].Max10MsNum) {
            SetTime.Task[i].CountNumOnce10Ms++;
        } else {
            SetTime.Task[i].TimeTask_Falge = true;
        }
        if (SetTime.Task[i].TimeTask_Falge == true) {
            if (SetTime.Task[i].TaskFunc != NULL) {
                SetTime.Task[i].TaskFunc();
            }
        }
    }
}
// 定时任务结构体初始化
void InitSetTime(void) {
    SetTime.InitSetTimeTask = _InitSetTimeTask;
    SetTime.CloseTask = _SetCloseTask;
}
