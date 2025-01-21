#ifndef ATCMD_FUNCTIONSUM_H
#define ATCMD_FUNCTIONSUM_H

#include "StrLib.h"
#include "NetProt_Module.h"
#include "PublicLib_No_One.h"

extern void sendDataBy_Module_Prot(char * txBuffer, int length);
#define IncludeUART0_4G_BAND UART0_BAND   // 需要引入外部变量或者常量

#define This (*this)
// 所有 AT指令 《发送时》 需要的用于 《组织指令》 的函数名
typedef enum _SendFun {
    easyATCmdDataLoadFun,           // 简单AT 指令装载
    setUartBandDataLoadFun,         // 波特率装载设置
    setSIMBandDataLoadFun,          // 波特率装载设置
    cleanOldSocketFun,              // 清理老旧的 Socket     
    setRemoteIPDataLoadFun,         // 目标IP设置
    setUserNameAndPassWordLoadFun,  // 设置登录用户名与密码
    setAPNForSIMLoadFun,            // 设置APN
    setUserAndPassWordDataLoadFun,  // 设置用户名与密码
    setMQTTMassageSUBFun,           // 设置MQTT消息订阅
} SendFun;
// 所有 AT指令 《回复时》 需要的用于 《处理回复》 的函数名
typedef enum _receiveFun {
    ResetTrueFlagDoingFun,  // 作为特殊标记，用于忽略模组返回强制跳过某条指令
    easyATCmdDataDoingFun,  // 简单AT 指令处理
    ReBootDevFun,           // 重启命令特殊处理
    get_Module_DevCSQFun,         // 获取信号强度 
    get_Module_DevIMEIFun,        // 获取 IMEI
    get_Module_DevCCIDFun,        // 获取 CCID
    get_Module_DevCCLKFun,        // 校时机制
    get_Module_DevIMSIFun,        // 获取 IMSI
    get_Module_DevCESQFun,        // 获取扩展信号强度
} receiveFun;

extern NetDevATCmd NetDevice_ATData__NB[ATCMD_MAXNUMBER];
extern void DataInstallation__NB(strnew OutStr, struct _NetDevATCmdData This);
extern bool DoingATCmdResData__NB(struct _NetDevATCmdData This);
extern bool isMQTTLinkOnleng__NB(void);
extern bool EnterATMode__NB(void);

#endif
