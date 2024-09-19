#include "ATCmdDebug.h"
#include "RTC_SetTime.h"
#include "All.h"
#include "NetProt_Module.h"

#ifdef OPEN_AT_CMD_DEBUG_LEN
char DebugBuf[OPEN_AT_CMD_DEBUG_LEN];
int NowLen = 0;
void SendDebug(unsigned char InputBuf[], unsigned char Len) {
    copyString((char *)DebugBuf, (char *)InputBuf, OPEN_AT_CMD_DEBUG_LEN, (int)Len);
    NowLen = Len;
}
void ATCmdDebugTask(void) {
    IncludeDelayMs(100); // 100ms
    memset(Now_NetDevParameter.NetDataBuff, 0, ARR_SIZE(Now_NetDevParameter.NetDataBuff));
    Now_NetDevParameter.NetDataBuff_NowLen = 0;
    RTC_TASK.InitSetTimeTask(ATDebug, MinToSec(7));    // 10 min 后退出Debug模式
    MF_LPUART0_Init();
    MF_LPUART0_Interrupt_Init();
    CopyATDebugResDataToLPUart0("Start AT Debug Mode\n", strlen("Start AT Debug Mode\n"));
    IncludeDelayMs(100); // 100ms
    isSend_LPUART0();
    while (RTC_TASK.Task[ATDebug].TimeTask_Falge == false) {
        if (copyDataForUART()) {
            CopyATDebugResDataToLPUart0(Now_NetDevParameter.NetDataBuff, strlen(Now_NetDevParameter.NetDataBuff));
            memset(Now_NetDevParameter.NetDataBuff, 0, ARR_SIZE(Now_NetDevParameter.NetDataBuff));
            Now_NetDevParameter.NetDataBuff_NowLen = 0;
        }
        isSend_LPUART0();
        if (NowLen != 0) {
            // Send AT
            sendDataByNetProt((unsigned char *)DebugBuf, strlen(DebugBuf));
            // 清空BUFF
            memset(DebugBuf, 0, OPEN_AT_CMD_DEBUG_LEN);
            NowLen = 0;
            RTC_TASK.InitSetTimeTask(ATDebug, MinToSec(7)); // 10 min 后退出Debug模式
            RTC_TASK.InitSetTimeTask(IWDTClS, MinToSec(8)); // 8min 初始化喂狗定时器
        }
        IncludeDelayMs(100); // 100ms
    }
    CloseLPUart0TTL();
    RTC_TASK.CloseTask(ATDebug);
}

#endif

