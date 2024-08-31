#include "RTC_SetTime.h"

USER_SET_TASK RTC_TASK;

void _InitRTCTask(int TaskAddr, uint64_t SetMaxSecNum) {
    if ((TaskAddr < 0) || (TaskAddr >= 1)) {
        return;
    }
    RTC_TASK.Task[TaskAddr].TimeTask_Falge = false; // 初始化标记
    RTC_TASK.Task[TaskAddr].isTaskStart = true;     // 开启
    RTC_TASK.Task[TaskAddr].MaxSecNum = SetMaxSecNum; // 定时任务点
    RTC_TASK.Task[TaskAddr].CountNumOnceSec = 0; // 复位初始
}
// 计数函数
void CountRTCTask(void) {
    for (int TaskAddr = 0; TaskAddr < 1; TaskAddr++) {
        if (RTC_TASK.Task[TaskAddr].isTaskStart == false) {
            return;
        }
        if (RTC_TASK.Task[TaskAddr].CountNumOnceSec < RTC_TASK.Task[TaskAddr].MaxSecNum) {
            RTC_TASK.Task[TaskAddr].CountNumOnceSec++;
        } else {
            RTC_TASK.Task[TaskAddr].TimeTask_Falge = true;
        }
    }
}
// 定时任务结构体初始化
void InitRTC_TASK(void) {
    RTC_TASK.InitSetTimeTask = _InitRTCTask;
}
