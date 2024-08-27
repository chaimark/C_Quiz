#include "SetTime.h"

// 可自定义的定时任务
BSTIM_USER_SET_TASK SetTime;;
void _InitSetTimeTask(int TaskAddr, uint64_t SetMax10MsNum) {
    if ((TaskAddr < 0) || (TaskAddr >= SetTimeTaskMAX)) {
        return;
    }
    SetTime.Task[TaskAddr].RTC_Task_Falge = false; // 初始化标记
    SetTime.Task[TaskAddr].isTaskStart = true;     // 开启
    SetTime.Task[TaskAddr].Max10MsNum = SetMax10MsNum; // 定时任务点
    SetTime.Task[TaskAddr].CountNumOnce10Ms = 0; // 复位初始
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
            SetTime.Task[i].RTC_Task_Falge = true;
        }
    }
}
// 定时任务结构体初始化
void InitSetTime(void) {
    SetTime.InitSetTimeTask = _InitSetTimeTask;
}
