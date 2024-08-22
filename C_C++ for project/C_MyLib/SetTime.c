#include "SetTime.h"

// 可自定义的定时任务
BSTIM_USER_SET_TASK SetTime_Task;;
void _InitSetTimeTask(int TaskAddr, uint64_t SetMax10MsNum) {
    if ((TaskAddr < 0) || (TaskAddr >= SetTimeTaskMAX)) {
        return;
    }
    SetTime_Task.setTime_Task[TaskAddr].RTC_Task_Falge = false; // 初始化标记
    SetTime_Task.setTime_Task[TaskAddr].isTaskStart = true;     // 开启
    SetTime_Task.setTime_Task[TaskAddr].Max10MsNum = SetMax10MsNum; // 定时任务点
    SetTime_Task.setTime_Task[TaskAddr].CountNumOnce10Ms = 0; // 复位初始
}
// 计数函数
void CountSetTimeTask(void) {
    for (int i = 0; i < SetTimeTaskMAX; i++) {
        if (SetTime_Task.setTime_Task[i].isTaskStart == false) {
            continue;
        }
        if (SetTime_Task.setTime_Task[i].CountNumOnce10Ms < SetTime_Task.setTime_Task[i].Max10MsNum) {
            SetTime_Task.setTime_Task[i].CountNumOnce10Ms++;
        } else {
            SetTime_Task.setTime_Task[i].RTC_Task_Falge = true;
        }
    }
}
// 定时任务结构体初始化
void InitSetTimeTask(void) {
    SetTime_Task.InitSetTimeTask = _InitSetTimeTask;
}
