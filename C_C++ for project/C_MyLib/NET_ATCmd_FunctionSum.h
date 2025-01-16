#ifndef _NET_ATCMD_FUNCTIONSUM_H
#define _NET_ATCMD_FUNCTIONSUM_H

#include <stdio.h>
#include <stdint.h>
#include "StrLib.h"
#include "All.h"
#include "NetProt_Module.h"

#define This (*this)
#define IncludeUART0_NET_BAND UART0_BAND   // 需要引入外部变量或者常量

// 所有 AT指令 《发送时》 需要的用于 《组织指令》 的函数名
typedef enum _SendFun_NET { // 发送AT指令时调用什么函数发送，对应的函数名
    flagChangeUartIDFun = 0,           // 控制修改 AT 指令需要的串口号
    easyATCmdDataLoadFun = 1,          // 简单AT 指令装载
    setBandDataLoadFun = 2,            // 波特率装载设置
    setWannDataLoadFun = 3,            // 网口设置指令装载
    setRemoteIPDataLoadFun = 4,        // 目标IP设置指令装载
    setUserAndPassWordDataLoadFun = 5, // 设置用户名和密码
    setMQTTMassagePUBFun = 6,          // MQTT 发布主题
    setMQTTMassageSUBFun = 7,          // MQTT 订阅主题
    setMQTTUserIDDataLoadFun = 8,      // MQTT 客户端ID
} SendFun_NET;

// 所有 AT指令 《回复时》 需要的用于 《处理回复》 的函数名
typedef enum _receiveFun_NET {  // 发送AT指令时调用什么函数发送，对应的函数名
    ResetTrueFlagDoingFun = 0, // 作为特殊标记，用于忽略模组返回强制跳过某条指令
    easyATCmdDataDoingFun = 1, // 简单AT 指令处理
    ReBootDevFun = 2,          // 重启命令特殊处理
} receiveFun_NET;

extern NetDevATCmd NetDevice_ATData_NET[ATCMD_MAXNUMBER];
extern void DataInstallation_NET(strnew OutStr, struct _NetDevATCmdData This);
extern bool DoingATCmdResData_NET(struct _NetDevATCmdData This);
extern bool isMQTTLinkOnleng_NET(void);
#endif
