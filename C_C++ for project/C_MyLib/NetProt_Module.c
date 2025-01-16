#include "NetProt_Module.h"
#include "NumberBaseLib.h"
#include "Gpio.h"
#include "StrLib.h"
#include "AT24CXXDataLoader.h"
#include "SetTime.h"
#include "RTC_SetTime.h"
#include "NET_ATCmd_FunctionSum.h"

void ClearNetDataBuff(void) {
    memset(Now_NetDevParameter.NetDataBuff, 0, ARR_SIZE(Now_NetDevParameter.NetDataBuff)); // 释放 HTTPBuff_p
    Now_NetDevParameter.NetDataBuff_NowLen = 0;
}
void sendDataByNetProt(char * SendCmd, int SendCmdLen) {
    ClearNetDataBuff();
    Uart0Send((unsigned char *)SendCmd, SendCmdLen);
    for (int i = 0; i < 1000; i++) {
        if (checkUart()) {
            break;
        }
        IncludeDelayMs(1);
    }
}
strnew UartBuff = {0};    // Uart接收缓冲区
NetDevParameter Now_NetDevParameter;    // 网络状态标记与下行指令表
void _pushListStr(struct _TableOfCmdTask This, strnew InputStr) {     // 推入队列 DebugStr
    // 计算输入字符串长度
    int InputStrLen = strlen(InputStr.Name._char);
    // 如果输入字符串长度大于队列字符串长度，则截断
    if (InputStrLen > CmdStrLenMax) {
        memcpy(This.ListStr[This.NowListAddr], InputStr.Name._char, CmdStrLenMax);    // 将输入字符串复制到队列中
        This.ListStr[This.NowListAddr][CmdStrLenMax] = '\0';                          // 队列末尾字符串结束符
    } else {
        strcpy(This.ListStr[This.NowListAddr], InputStr.Name._char);                    // 将输入字符串复制到队列中
        This.ListStr[This.NowListAddr][strlen(This.ListStr[This.NowListAddr])] = '\0';  // 队列末尾字符串结束符
    }
    // 计数队列下一个
    This.NowListAddr = (This.NowListAddr + 1) % CmdListMax;
    // 队列已保存数加一
    if (This.NowListNum < CmdListMax) {
        This.NowListNum++;
    } else {
        This.NowListStartAddr = This.NowListAddr; // 记满时，首端地址在尾端的后一位
    }
}
strnew _popUpListStr(struct _TableOfCmdTask This) {   // 弹出队列 DebugStr
    strnew Outputstr = NEW_NAME(This.OututStrOnce);
    if (This.NowListNum == 0) {
        memset(Outputstr.Name._char, 0, CmdStrLenMax);
        strcpy(Outputstr.Name._char, "null");
        return Outputstr;
    }
    // 取出队列首端的字符串
    memcpy(Outputstr.Name._char, This.ListStr[This.NowListStartAddr], strlen(This.ListStr[This.NowListStartAddr]));
    // 清空首端字符串
    memset(This.ListStr[This.NowListStartAddr], 0, CmdStrLenMax);
    // 队列已保存数减一
    This.NowListNum--;
    // 队列首端地址后移
    This.NowListStartAddr = (This.NowListStartAddr + 1) % CmdListMax;
    return Outputstr;
}
void TableOfCmdTaskInit(void) { // 下行任务表初始化
    TableOfCmdTask ZeroData = {0};
    Now_NetDevParameter.CmdTable = ZeroData;
    Now_NetDevParameter.CmdTable.pushListStr = _pushListStr;
    Now_NetDevParameter.CmdTable.popUpListStr = _popUpListStr;
}
// 设置模组处于AT模式
bool SetDevATCMDModel_ThroughSendData(void) {
    // 先复位模组 ==========
    REBOOT_DEV_OFF;
    IncludeDelayMs(500); // 拉低 500 ms
    REBOOT_DEV_ON;
    IncludeDelayMs(2000); // 延时等待重启结束
    checkUart();
    bool ATConfig_Flag = true;
    // 清除 Now_NetDevParameter 状态标记
    Now_NetDevParameter.isCmdResFlag = false;
    Now_NetDevParameter.isWriteEEprom = false;
    // 进入AT模式 ==========
    // {"AT+ENTM\r\n", "\r\n+OK"}
    char cmdStr[2][2][20] = {{"+++", "a"}, {"a", "+ok"}};
    for (int i = 0; i < 2; i++) {
        sendDataByNetProt(cmdStr[i][0], strlen(cmdStr[i][0]));
        if (checkUart()) {
            if (myStrstr(Now_NetDevParameter.NetDataBuff, cmdStr[i][1], Now_NetDevParameter.NetDataBuff_NowLen) != NULL) {
                ATConfig_Flag = true;
                continue;
            } else {
                ATConfig_Flag = false; // 无法进入AT模式，直接退出，等待下一次重启
                break;
            }
        } else {
            if (i == 0) {
                sendDataByNetProt("\r\n", strlen("\r\n"));
                sendDataByNetProt("AT+ENTM\r\n", strlen("AT+ENTM\r\n"));
                ATConfig_Flag = false; // 无法进入AT模式，直接退出，等待下一次重启
            }
            break;
        }
    }
    if (ATConfig_Flag) {
        sendDataByNetProt("AT+VER\r\n", strlen("AT+VER\r\n"));
        ATConfig_Flag = checkUart();
        printf("Successfully entered the AT mode\r\n");
    } else {
        printf("Fail to enter the AT mode\r\n");
    }
#ifdef OPEN_AT_CMD_DEBUG
    ATCmdDebugTask();
    // RTC_TASK.InitSetTimeTask(SendTimeOverTask, 1, NULL); // 超过 1 s，需要关闭 NB
#endif
    return ATConfig_Flag;
}
void clearUartBuff(void) {
    memset(UartBuff.Name._char, 0, UartBuff.MaxLen);
    NowLenOfUartBuff = 0;   // 需要把外部传入的buff标记或长度复位才算清空
}
int IsOverTimeOfUart(int TempNowRxLen) {
    while (1) {
        IncludeDelayMs(30);    // 等待 30ms 接收数据，避免短数据占用太多时间
        if (TempNowRxLen == NowLenOfUartBuff) {
            return NowLenOfUartBuff;
        }
        TempNowRxLen = NowLenOfUartBuff;
    }
}
// 搬运串口数据
bool copyDataForUART(void) {
    if (NowLenOfUartBuff != 0) {
        int NowRxLen = IsOverTimeOfUart(NowLenOfUartBuff);  // 返回接收完全的数据长度
        UartDisableIRQ;
        if (Now_NetDevParameter.NetDataBuff_NowLen + NowRxLen <= ARR_SIZE(Now_NetDevParameter.NetDataBuff)) {                                                                                                                                 // 追加到 Now_NetDevParameter.NetDataBuff
            memcpy(&Now_NetDevParameter.NetDataBuff[Now_NetDevParameter.NetDataBuff_NowLen], UartBuff.Name._char, NowRxLen); // 接收数据
            Now_NetDevParameter.NetDataBuff_NowLen += NowRxLen;
        } else {
            ClearNetDataBuff();
            memcpy(Now_NetDevParameter.NetDataBuff, UartBuff.Name._char, NowRxLen);   // 接收数据
            Now_NetDevParameter.NetDataBuff_NowLen = NowRxLen;
        }
        clearUartBuff();
        UartEnableIRQ;
        return true;
    } else {
        return false;
    }
}
// 判断是否连接上MQTT
bool isMQTTLinkOnleng(void) {
    bool ATConfig_Flag = false;
    if (AT24CXX_Manager_NET.NetCheckENableFlag == false) {
        return true;
    }

    for (int i = 0; i < 10; i++) {
        if (SetDevATCMDModel_ThroughSendData()) {
            break;
        }
    }
    //if (UP_Mode_EC20_ON) {
        //ATConfig_Flag = isMQTTLinkOnleng_4G();
    //} else {
    ATConfig_Flag = isMQTTLinkOnleng_NET();
    //}

    if (ATConfig_Flag) {
        return true;
    }
    if (Now_NetDevParameter.isLongLinkModeFlag != true) {
        return false;
    }
    return false;
}
// 处理用户请求/命令
bool doingUserRequest(void) {
    return true;
}
// 处理模组回复,判断指令是否发送成功，或者模组再忙等待返回等操作
bool doingATCmdResult(NetDevATCmd NowATCmd) {
    return NowATCmd.DoingATCmdResData(&NowATCmd);
}
// 发送ATCmd
bool sendATCmdData(NetDevATCmd NowATCmd) {
    newString(ATCmd_SendBUFF, 500);
    // 装载指令
    NowATCmd.DataInstallation(ATCmd_SendBUFF, &NowATCmd);
    clearUartBuff();
    // 发送指令
    sendDataByNetProt(ATCmd_SendBUFF.Name._char, strlen(ATCmd_SendBUFF.Name._char));
    for (int ResCount_i = 0; ResCount_i <= NowATCmd.CmsResCount; ResCount_i++) {
        // 模组是否回复
        if (!checkUart()) {
            // 判断是否可以跳过
            if ((NowATCmd.DoingATReceiveFunName == ResetTrueFlagDoingFun) && ((ResCount_i + 1) == NowATCmd.CmsResCount)) {
                return true; // 发送结束也没收到回复，直接跳过
            }
            continue;
        }
        // 处理模组的回复
        if (doingATCmdResult(NowATCmd) == false) {
            return false; // AT 指令发送失败
        }
        // 该指令是否需要上位机回复，如果不需要直接回复 true
        if (NowATCmd.IsGetComputerResFlag == false) {
            return true; // 上位机回复成功
        }
        return doingUserRequest(); // 上位机回复成功
    }
    return true; // AT 指令发送限制为0,直接跳过该指令
}
// 获取指令
char copyComputerDownData(void) {
    if (checkUart()) { // 从 UART0Ddata 获取数据
        char * AddrStart = NULL;
        if (myStrstr(Now_NetDevParameter.NetDataBuff, "{\"gw\":", ARR_SIZE(Now_NetDevParameter.NetDataBuff)) != NULL) {
            if (NULL == (AddrStart = myStrstr(Now_NetDevParameter.NetDataBuff, "{\"gw\":", ARR_SIZE(Now_NetDevParameter.NetDataBuff)))) {
                ClearNetDataBuff();
                return false;
            }
            if (NULL == strstr(AddrStart, "}}")) {
                return false;
            }
            if (Now_NetDevParameter.CmdTable.NowListNum >= CmdListMax) {
                Now_NetDevParameter.CmdTable.popUpListStr(&Now_NetDevParameter.CmdTable);  // 弹出队列 List
            }
            // 将下行指令推入队列 List
            Now_NetDevParameter.CmdTable.pushListStr(&Now_NetDevParameter.CmdTable, NEW_NAME(Now_NetDevParameter.NetDataBuff));
            ClearNetDataBuff(); // 释放 HTTPBuff_p
            return true;
        } else {
            return true;
        }
    }
    return false;
}

bool isNBOverTime(void) {
    if (Now_NetDevParameter.isLongLinkModeFlag == true) {
        return false;
    }
    // if (RTC_TASK.Task[SendTimeOverTask].TimeTask_Falge) {
    //     RTC_TASK.CloseTask(SendTimeOverTask); // 关闭定时任务
    //     RTC_TASK.Task[SendTimeOverTask].MaxSecNum = 0;
    //     RTC_TASK.Task[SendTimeOverTask].CountNumOnceSec = 0;
    //     return true;
    // }
    return false;
}
// 检查时间任务
void check_time_task(void) {
    if (Now_NetDevParameter.isLongLinkModeFlag) {
        if (SetLPTime.Task[checkNet].TimeTask_Falge) {   // 任务0 用于判断什么时候检查网络在线标记
            SetLPTime.LPInitSetTimeTask(checkNet, SecTo250Ms(Now_NetDevParameter.LineCheckTime), NULL);            // 初始化创建定时任务
            Now_NetDevParameter.CheckOnlineFlag = true;  // 检查网络在线标记
        }
    }
    if (Now_NetDevParameter.isLongLinkModeFlag == true) {
        Now_NetDevParameter.isCmdResFlag = (Now_NetDevParameter.isCmdResFlag | copyComputerDownData());  // 检查是否有收到数据  
    }
}
#define LinkContMax 1
void Net_Task(void) {
    static uint8_t LinkContinueTime = LinkContMax; // 连续 5 次都连接不上，则 480 min 后再尝试
    check_time_task();      // 检查时间任务
    if (!RTC_TASK.Task[PauseTimeOfLinkErr].TimeTask_Falge) {
        goto NetSubOver;
    }
    if (Now_NetDevParameter.CheckOnlineFlag == true) { // 检查当前设备 network 是否在线
        if (!isMQTTLinkOnleng()) {
            Now_NetDevParameter.NowNetOnlineFlag = false; // 标记不在线，下次运行这个任务时重启
            Now_NetDevParameter.ReBootCount++;
        } else {
            Now_NetDevParameter.CheckOnlineFlag = false; // 已在线，不用再检查 network
            Now_NetDevParameter.NowNetOnlineFlag = true;  // 标记在线
        }
    }
    if (isNBOverTime()) {
        goto NetSubOver;
    }
    // 不在线或无连接，重新联网通信
    if (Now_NetDevParameter.NowNetOnlineFlag == false) {
        // 设置模组进入 AT 模式
        for (int i = 0; i < 10; i++) {
            if (SetDevATCMDModel_ThroughSendData()) {
                if (isNBOverTime()) {
                    goto NetSubOver;
                }
                break;
            }
        }
        int NowStep = 0;
        while (NowStep != -1) {
            // 一个是否执行的开关，后续可扩展为指令控制
            if (NetDevice_ATData[NowStep].RunFlag) {
                for (int SendCount_i = 0; SendCount_i < NetDevice_ATData[NowStep].CmdSendCount; SendCount_i++) {
                    if (sendATCmdData(NetDevice_ATData[NowStep])) {
                        break;
                    }
                    // 联网遇到问题，中断联网进程
                    if ((SendCount_i + 1) == NetDevice_ATData[NowStep].CmdSendCount) {
                        Now_NetDevParameter.CheckOnlineFlag = false;  // TCP 连接失败，不需要检查，直接准备重启
                        Now_NetDevParameter.NowNetOnlineFlag = false; // 标记不在线，下次运行这个任务时重启
                        Now_NetDevParameter.ReBootCount++;            // 重连一次
                        printf("The network connection has been interrupted : %s\r\n", NetDevice_ATData[NowStep].ATCmd);
                        goto NetSubOver;
                    }
                }
            }
            NowStep = NetDevice_ATData[NowStep].Next_CmdID;
            if (isNBOverTime()) {
                goto NetSubOver;
            }
        }
        IncludeDelayMs(3000);   // 连接流程结束后等待 3 秒
        // 判断 MQTT 是否在线
        if (isMQTTLinkOnleng()) {
            // if (UP_Mode_EC20_ON) {
            //     RTC_TASK.InitSetTimeTask(WriteTimeOfLocal, 10, Write_RX8025T_AndRTC_By_UTC8); // 10s 后写入时间 (4G)
            // }
            Now_NetDevParameter.CheckOnlineFlag = false;  // TCP 连接成功后暂时不需要检查
            Now_NetDevParameter.NowNetOnlineFlag = true; // 设备已在线
            Now_NetDevParameter.ReBootCount = 0;         // 连接成功，重器计数清零
            JSON_Send_GW_Infor((Now_NetDevParameter.ReBootCount > 0 ? true : false));
            printf("Now the gateway is online\r\n");
            // JSON_Send_GW_Infor(0);//汇云上线需要先发一包心跳
        }
        if (isNBOverTime()) {
            goto NetSubOver;
        }
        Now_NetDevParameter.ReBootCount = 0; // 复位重启计数器
        ClearNetDataBuff();
    }
    if (!Now_NetDevParameter.isLongLinkModeFlag) { // 短链接，需要查询下行指令
        if (Now_NetDevParameter.isCheckDownCmd == false) { // 非实时监控模式需要主动获取指令
            Now_NetDevParameter.isCmdResFlag = (Now_NetDevParameter.isCmdResFlag | copyComputerDownData());  // 检查是否有收到数据
        }
        if (Now_NetDevParameter.SendData != NULL) {
            Now_NetDevParameter.SendData(); // 发送数据
            ClearNetDataBuff(); // 清空数据
        }
        if (Now_NetDevParameter.isCheckDownCmd == false) { // 非实时监控模式需要主动获取指令
            Now_NetDevParameter.isCmdResFlag = (Now_NetDevParameter.isCmdResFlag | copyComputerDownData());  // 检查是否有收到数据
        }
    }
NetSubOver:
    if (Now_NetDevParameter.isCmdResFlag) {
        if (Now_NetDevParameter.DoneCmd != NULL) {
            Now_NetDevParameter.DoneCmd(); // 处理指令
        }
        Now_NetDevParameter.isCmdResFlag = false;
        ClearNetDataBuff();
    }
    // 判断是长连接还是短链接
    if (!Now_NetDevParameter.isLongLinkModeFlag) {
        if (Now_NetDevParameter.ShowdownNowDev != NULL) {
            Now_NetDevParameter.ShowdownNowDev();   // 短链接，需要关闭设备
            Now_NetDevParameter.NowNetOnlineFlag = false;
        }
        return;
    }
    if (RTC_TASK.Task[PauseTimeOfLinkErr].TimeTask_Falge) {
        // 长连接状态下, 需要限制尝试联网的次数
        LinkContinueTime = (LinkContinueTime > 0 ? (LinkContinueTime - 1) : 10);
        if (LinkContinueTime != 0) {
            RTC_TASK.InitSetTimeTask(PauseTimeOfLinkErr, 5, NULL); // 5s 后继续尝试
        } else {
            RTC_TASK.InitSetTimeTask(PauseTimeOfLinkErr, MinToSec(480), NULL); // 一天连三次 1440/3 = 480
        }
    }
}
void UserSendData(void) {
    return;
}
void UserDoneCmd(void) {
    if (Now_NetDevParameter.CmdTable.NowListNum > 0) {
        strnew OnceLineListStr = Now_NetDevParameter.CmdTable.popUpListStr(&Now_NetDevParameter.CmdTable);   // 弹出一行数据
        char * AddrStart = NULL;
        if (strstr(OnceLineListStr.Name._char, "{\"gw\":") != NULL) {
            AddrStart = strstr(OnceLineListStr.Name._char, "{\"gw\":");
            MQTT_JSON_Analysis(AddrStart);
            printf("Received Command of HuiYun\r\n");
        } else {
            printf("Received Command of Other\r\n");
        }
    }
}
// AT 参数初始化
void setNetArgumentInit(void (*UserShowdownNowDev)(void)) {
    // 初始化 Now_NetDevParameter
    Now_NetDevParameter.LineCheckTime = 60;  // 60 秒后，判断你是否处于连接状态
    Now_NetDevParameter.ShowdownNowDev = UserShowdownNowDev;
    Now_NetDevParameter.NET_Receive_checkTime = BuffcheckTime10Ms;
    Now_NetDevParameter.isLongLinkModeFlag = true;
    Now_NetDevParameter.SendData = UserSendData;    // 长连接不需要发送函数
    Now_NetDevParameter.DoneCmd = UserDoneCmd;      // 处理指令
    Now_NetDevParameter.isCheckDownCmd = true;      // 是否需要监控下行指令
    TableOfCmdTaskInit();                           // 指令表初始化
    AT24CXXLoader_Init();                           // 读取 AT 参数
    UartBuff = NEW_NAME(UART_DATABUFF);             // 初始化缓存 UartBuff
    // 特殊定时任务
    if (Now_NetDevParameter.isLongLinkModeFlag == true) {
        SetLPTime.LPInitSetTimeTask(checkNet, SecTo250Ms(Now_NetDevParameter.LineCheckTime), NULL);
        RTC_TASK.InitSetTimeTask(PauseTimeOfLinkErr, 1, NULL);  // 开机可以尝试连接网络
    }
    // 初始化 SetTime 任务
    // 初始化 SetLPTime 任务
    // SetLPTime.LPInitSetTimeTask(RefreshLED, SecTo250Ms(0.5), Refresh_LED);
    // 初始化 RTC_TASK 任务
    RTC_TASK.InitSetTimeTask(Read_EEprom, MinToSec(80), NULL);
    RTC_TASK.InitSetTimeTask(TestVoltgeAndMA, 2, NULL);
    // RTC_TASK.InitSetTimeTask(MBUSUARTReboot, MinToSec(2160), MBUS_Uart1_Init);  // 启动 Uart 重启任务

    if (AT24CXX_Manager_NET.IsColorDislay) {
#ifdef _COLORSHOW_H
        initTaskOfColorShowTask();
#endif
    }
    return;
}

/******************************/
NetDevATCmd NetDevice_ATData[ATCMD_MAXNUMBER] = {0};
// 设置或查询 AT指令 的装载方法
void _DataInstallation(strnew OutStr, struct _NetDevATCmdData This) {
    //if (UP_Mode_EC20_ON) {
        //DataInstallation_4G(OutStr, &This);
    //} else {
    DataInstallation_NET(OutStr, &This);
    //}
}
// 处理指令返回的方法
bool _DoingATCmdResData(struct _NetDevATCmdData This) {
    bool ResFlag = false;
    //if (UP_Mode_EC20_ON) {
        //ResFlag = DoingATCmdResData_4G(&This);
    //} else {
    ResFlag = DoingATCmdResData_NET(&This);
    //}
    return ResFlag;
}
// 建立对象的函数
NetDevATCmd New_NetDevAT_Obj(NetDevATCmd DataInit) {
    DataInit.DataInstallation = _DataInstallation;
    DataInit.DoingATCmdResData = _DoingATCmdResData;
    return DataInit;
}

void MQTT_NetAT_Init(void) {
    // 初始化 NetDevice_ATData
    for (int i = 0; i < ATCMD_MAXNUMBER; i++) {
        //if (UP_Mode_EC20_ON) {
            //NetDevice_ATData[i] = NetDevice_ATData_4G[i];
        //} else {
        NetDevice_ATData[i] = NetDevice_ATData_NET[i];
        //}
        NetDevice_ATData[i] = New_NetDevAT_Obj(NetDevice_ATData[i]);
    }
    return;
}
