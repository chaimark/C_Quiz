#ifndef WEB_NET_PROT_H
#define WEB_NET_PROT_H

#include <stdint.h>
#include <stdbool.h>
#include "StrLib.h"
#include "All.h"

struct {
    unsigned char RxBuf[10];
    uint16_t RxLen;
}UART0Ddata;
// 外部引入
#define REBOOT_DEV_OFF      //NET_RST_OFF                // 重启模块标记置高
#define REBOOT_DEV_ON       //NET_RST_ON                  // 重启模块标记置低
#define UartDisableIRQ      //NVIC_DisableIRQ(UART0_IRQn)  // 关闭中断使能
#define UartEnableIRQ       //NVIC_EnableIRQ(UART0_IRQn)   // 开启中断使能
#define UART_DATABUFF       UART0Ddata.RxBuf            //接收缓冲区
#define NowLenOfUartBuff    UART0Ddata.RxLen            //接收缓冲区长度


// 内部定义
#define BuffcheckTime10Ms 7 // 50ms 115200 == 11520字节/s
#define sendDataByNetProt Uart0Send // Uart0Send(unsigned char *, unsigned short int)

#define CmdListMax 5      // 最大队列数
#define CmdStrLenMax 600  // 最大字符串长度
typedef struct _TableOfCmdTask {
    char ListStr[CmdListMax][CmdStrLenMax + 1]; // Bebug 循环队列
    char NowListNum;        // 当前队列已保存数
    char NowListAddr;       // 当前队列尾端地址
    char NowListStartAddr;  // 当前队列首端地址
    void (*pushListStr)(struct _TableOfCmdTask This, strnew InputStr);  // 推入队列 DebugStr
    strnew(*popUpListStr)(struct _TableOfCmdTask This);                 // 弹出队列 DebugStr
    char OututStrOnce[CmdStrLenMax];  // 弹出队列时的临时输出字符串
} TableOfCmdTask; // 最多缓存三条指令的指令任务表
// 类方法
void _pushListStr(struct _TableOfCmdTask This, strnew InputStr);    // 推入队列 DebugStr
strnew _popUpListStr(struct _TableOfCmdTask This);                  // 弹出队列 DebugStr

// 类定义
typedef struct _NetDevParameter {
    uint16_t LineCheckTime;     // 检查网络在线的间隔时间
    bool NowNetOnlineFlag;      // 网络在线标记
    bool CheckOnlineFlag;       // 检查网络在线标记
    bool isLongLinkModeFlag;    // 是否是长连接标记
    uint8_t ReBootCount;        // 重启次数

    uint8_t NET_Receive_checkTime; // 检查接收 buff 的间隔时间
    char NetDataBuff[800];             // 接收数据或发送数据的缓存空间
    uint16_t NetDataBuff_NowLen;        // 接收 Buff的实际长度
    TableOfCmdTask CmdTable;            // 已接收的任务表队列

    void (*ShowdownNowDev)(void);       // 关闭当前设备
    void (*SendData)(void);             // 发送数据
    void (*DoneCmd)(void);              // 解析数据
    char isCmdResFlag;                  // 是否收到下行
    bool isWriteEEprom;         // 是否写eeprom

    unsigned char isSendOk;     // 是否发送成功
} NetDevParameter;
extern NetDevParameter Now_NetDevParameter;

// 公共接口
extern void setNetArgumentInit(void (*UserShowdownNowDev)(void));
extern void MOTT_Net_Task(void);
extern bool copyDataForUART(void);
extern void ClearNetDataBuff(void);
#endif


