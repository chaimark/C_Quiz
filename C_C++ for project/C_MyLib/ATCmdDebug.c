#include "ATCmdDebug.h"
#include "RTC_SetTime.h"
#include "All.h"
#include "NetProt_Module.h"
// #include "../Src/LPUart.h"

#ifdef OPEN_AT_CMD_DEBUG

#define UartTxBuff LPUART0_TxBuf
#define UartTxBuffLen LPUART0_Tx_Len

void CopyATDebugResDataToLPUart0(char * data, int len) {
    memcpy(UartTxBuff, data, len);
    UartTxBuffLen = len;
}

int NowLen = 0;
void SendDebug(unsigned char InputBuf[], unsigned int Len) {
    copyString(DebugBuff, (char *)InputBuf, ARR_SIZE(DebugBuff), Len);
    NowLen = Len;
}

#define My_UART_Init            __NOP
#define My_UART_Interrupt_Init  __NOP
#define My_UART_Close           __NOP
#define My_UART_isSend          LPUart1Send(UartTxBuff, UartTxBuffLen)

void ATCmdDebugTask(void) {
    IncludeDelayMs(100); // 100ms
    memset(Now_NetDevParameter.NetDataBuff, 0, ARR_SIZE(Now_NetDevParameter.NetDataBuff));
    Now_NetDevParameter.NetDataBuff_NowLen = 0;
    RTC_TASK.InitSetTimeTask(ATDebug, MinToSec(7), NULL);    // 10 min 后退出Debug模式
    My_UART_Init();
    My_UART_Interrupt_Init();
    CopyATDebugResDataToLPUart0("Start AT Debug Mode\n", strlen("Start AT Debug Mode\n"));
    IncludeDelayMs(100); // 100ms
    My_UART_isSend;
    while (RTC_TASK.Task[ATDebug].TimeTask_Falge == false) {
        if (checkUart()) {
            CopyATDebugResDataToLPUart0(Now_NetDevParameter.NetDataBuff, strlen(Now_NetDevParameter.NetDataBuff));
            memset(Now_NetDevParameter.NetDataBuff, 0, ARR_SIZE(Now_NetDevParameter.NetDataBuff));
            Now_NetDevParameter.NetDataBuff_NowLen = 0;
        }
        My_UART_isSend;
        if (NowLen != 0) {
            // Send AT
            sendDataByNetProt(DebugBuff, strlen(DebugBuff));
            // 清空BUFF
            memset(DebugBuff, 0, ARR_SIZE(DebugBuff));
            NowLen = 0;
            RTC_TASK.InitSetTimeTask(ATDebug, MinToSec(7), NULL); // 10 min 后退出Debug模式
            RTC_TASK.InitSetTimeTask(IWDTClS, MinToSec(8), NULL); // 8min 初始化喂狗定时器
        }
    }
    My_UART_Close();
    RTC_TASK.CloseTask(ATDebug);
}

#endif

