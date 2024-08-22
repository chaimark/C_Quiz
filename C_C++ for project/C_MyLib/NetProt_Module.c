#include "NetProt_Module.h"
#include "ATCmd_FunctionSum.h"
#include "NumberBaseLib.h"
#include "StrLib.h"
#include "AT24CXXDataLoader.h"
#include "SetTime.h"

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

void ClearNetDataBuff(void) {
    memset(Now_NetDevParameter.NetDataBuff, 0, ARR_SIZE(Now_NetDevParameter.NetDataBuff)); // 释放 HTTPBuff_p
    Now_NetDevParameter.NetDataBuff_NowLen = 0;
}
// 设置模组处于AT模式
bool SetDevATCMDModel_ThroughSendData(void) {
    // 先复位模组 ==========
    REBOOT_DEV_OFF;
    FL_DelayMs(500); // 拉低 500 ms
    REBOOT_DEV_ON;
    FL_DelayMs(2000); // 延时等待重启结束
    copyDataForUART();
    bool ATConfig_Flag = true;
    // 进入AT模式 ==========
    // {"AT+ENTM\r\n", "\r\n+OK"}
    char cmdStr[2][2][20] = {{"+++", "a"}, {"a", "+ok"}};
    for (int i = 0; i < 2; i++) {
        ClearNetDataBuff(); // 释放 HTTPBuff_p
        sendDataByNetProt((unsigned char *)cmdStr[i][0], strlen(cmdStr[i][0]));
        FL_DelayMs(500);
        if (copyDataForUART()) {
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
                FL_DelayMs(500);
                sendDataByNetProt("AT+ENTM\r\n", strlen("AT+ENTM\r\n"));
                ATConfig_Flag = false; // 无法进入AT模式，直接退出，等待下一次重启
            }
            break;
        }
    }
    if (ATConfig_Flag) {
        sendDataByNetProt("AT+VER\r\n", strlen("AT+VER\r\n"));
        FL_DelayMs(500);
        ATConfig_Flag = copyDataForUART();
        printf("Successfully entered the AT mode\r\n");
    } else {
        printf("Fail to enter the AT mode\r\n");
    }
    return ATConfig_Flag;
}
void clearUartBuff(void) {
    memset(UartBuff.Name._char, 0, UartBuff.MaxLen);
    // UART0Ddata.RxLen = 0;   // 需要把外部传入的buff标记或长度复位才算清空
}
// 搬运串口数据
bool copyDataForUART(void) {
    int NowRxLen = strlen(UartBuff.Name._char);
    if (NowRxLen != 0) {
        UartDisableIRQ;
        if (Now_NetDevParameter.NetDataBuff_NowLen + NowRxLen <= ARR_SIZE(Now_NetDevParameter.NetDataBuff)) {                                                                                                                                 // 追加到 Now_NetDevParameter.NetDataBuff
            memcpy(&Now_NetDevParameter.NetDataBuff[Now_NetDevParameter.NetDataBuff_NowLen], UartBuff.Name._char, NowRxLen); // 接收数据
            Now_NetDevParameter.NetDataBuff_NowLen += NowRxLen;
        } else {
            memset(Now_NetDevParameter.NetDataBuff, 0, ARR_SIZE(Now_NetDevParameter.NetDataBuff)); // 释放 HTTPBuff_p
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
// 检查当前设备 TCP 是否连接
bool TCPLinkOnlineFlga() {
    bool ATConfig_Flag = false;
    if (AT24CXX_Manager_NET.TCPCheckENableFlag == false) {
        return true;
    }

    for (int i = 0; i < 10; i++) {
        if (SetDevATCMDModel_ThroughSendData()) {
            break;
        }
    }
    char cmdStr[2][2][20] = {{"AT+SOCKLKA3\r\n", "CONNECTED"}, {"AT+ENTM\r\n", "\r\n+OK"}};
    for (int i = 0; i < 2; i++) {
        ClearNetDataBuff();
        sendDataByNetProt((unsigned char *)cmdStr[i][0], strlen(cmdStr[i][0]));
        FL_DelayMs(500);
        if (!copyDataForUART()) {
            break;
        }
        if ((i != 0) && (myStrstr(Now_NetDevParameter.NetDataBuff, cmdStr[i][1], Now_NetDevParameter.NetDataBuff_NowLen) == NULL)) {
            sendDataByNetProt((unsigned char *)cmdStr[i][0], strlen(cmdStr[i][0]));
            break; // 没有退出 AT 最后发一次
        }
        if (myStrstr(Now_NetDevParameter.NetDataBuff, cmdStr[i][1], Now_NetDevParameter.NetDataBuff_NowLen) != NULL) {
            ATConfig_Flag = (i == 0 ? true : ATConfig_Flag);
        } else {
            ATConfig_Flag = false; // 没链上TCP
        }
    }
    return ATConfig_Flag;
}
// 判断是否连接上MQTT
bool isMQTTLinkOnleng(void) {
    if (AT24CXX_Manager_NET.TCPCheckENableFlag == false) {
        return true;
    }
    return true;
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
    char Temp[500] = {0};
    strnew ATCmd_SendBUFF = NEW_NAME(Temp);
    // 清理接收缓存
    ClearNetDataBuff();
    // 装载指令
    NowATCmd.DataInstallation(ATCmd_SendBUFF, &NowATCmd);
    // 发送指令
    sendDataByNetProt((unsigned char *)ATCmd_SendBUFF.Name._char, strlen(ATCmd_SendBUFF.Name._char));
    FL_DelayMs(500);
    for (int ResCount_i = 0; ResCount_i <= NowATCmd.CmsResCount; ResCount_i++) {
        // 模组是否回复
        if (!copyDataForUART()) {
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
    if (copyDataForUART()) { // 从 UART0Ddata 获取数据
        char * AddrStart = NULL;
        if (strstr(Now_NetDevParameter.NetDataBuff, "{\"gw\":") != NULL) {
            if (NULL == (AddrStart = strstr(Now_NetDevParameter.NetDataBuff, "{\"gw\":"))) {
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
        }
    }
    return false;
}
// 检查时间任务
void check_time_task(void) {
    if (SetTime.Task[checkNet].RTC_Task_Falge) {   // 任务0 用于判断什么时候检查网络在线标记
    // 初始化创建定时任务
        SetTime.InitSetTimeTask(checkNet, BSTSecTo10Ms(Now_NetDevParameter.LineCheckTime));
        Now_NetDevParameter.CheckOnlineFlag = true;  // 检查网络在线标记
        Now_NetDevParameter.CheckTCPLinkFlag = true; // 检查TCP连接标记
    }
    // 长连接时 每 70ms 计数一次
    if ((Now_NetDevParameter.isLongLinkModeFlag) && (SetTime.Task[CopyDMA].RTC_Task_Falge)) {   // 任务0 用于判断什么时候Copy DMA
        SetTime.InitSetTimeTask(CopyDMA, Now_NetDevParameter.MQTT_NET_Receive_checkTime);
        Now_NetDevParameter.isCmdResFlag = (Now_NetDevParameter.isCmdResFlag | copyComputerDownData());  // 检查是否有收到数据
    }
}
void MOTT_Net_Task(void) {
    check_time_task();      // 检查时间任务
    AT24CXXLoader_Init();   // 载入AT24CXX参数

    if (Now_NetDevParameter.CheckTCPLinkFlag == true) { // 检查当前设备 TCP 是否连接
        if (!TCPLinkOnlineFlga()) { // 检查当前设备 TCP 是否连接
            Now_NetDevParameter.NowNetOnlineFlag = false; // 标记不在线，下次运行这个任务时重启
            Now_NetDevParameter.NowTCPLinkFlag = false;   // 标记不在线，下次运行这个任务时重启
            Now_NetDevParameter.ReBootCount++;
        } else
            Now_NetDevParameter.CheckTCPLinkFlag = false; // 已在线，不用再检查TCP
    } else if (Now_NetDevParameter.CheckOnlineFlag == true) { // 检查当前设备 network 是否在线
        if (!isMQTTLinkOnleng()) {
            Now_NetDevParameter.NowNetOnlineFlag = false; // 标记不在线，下次运行这个任务时重启
            Now_NetDevParameter.NowTCPLinkFlag = false;   // 标记不在线，下次运行这个任务时重启
            Now_NetDevParameter.ReBootCount++;
        } else
            Now_NetDevParameter.CheckOnlineFlag = false; // 已在线，不用再检查 network
    }
    // 不在线或无连接，重新联网通信
    if ((Now_NetDevParameter.NowNetOnlineFlag == false) || (Now_NetDevParameter.NowTCPLinkFlag == false)) {
        // 设置模组进入 AT 模式
        for (int i = 0; i < 10; i++) {
            if (SetDevATCMDModel_ThroughSendData()) {
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
                    if (SendCount_i == NetDevice_ATData[NowStep].CmdSendCount) {
                        Now_NetDevParameter.CheckTCPLinkFlag = false; // TCP 连接失败，不需要检查，直接准备重启
                        Now_NetDevParameter.CheckOnlineFlag = false;  // TCP 连接失败，不需要检查，直接准备重启
                        Now_NetDevParameter.NowNetOnlineFlag = false; // 标记不在线，下次运行这个任务时重启
                        Now_NetDevParameter.NowTCPLinkFlag = false;   // 标记不在线，下次运行这个任务时重启
                        Now_NetDevParameter.ReBootCount++;            // 重连一次
                        printf("The network connection has been interrupted : %s\r\n", NetDevice_ATData[NowStep].ATCmd);
                        goto NetSubOver;
                    }
                }
            }
            NowStep = NetDevice_ATData[NowStep].Next_CmdID;
        }
        // 检查当前设备 TCP 是否连接，低电平有效
        if (TCPLinkOnlineFlga()) {
            Now_NetDevParameter.CheckTCPLinkFlag = false; // TCP 连接成功后暂时不需要检查
            Now_NetDevParameter.CheckOnlineFlag = false;  // TCP 连接成功后暂时不需要检查
            Now_NetDevParameter.NowTCPLinkFlag = true;    // TCP 已连接
            printf("Successful TCP connection\r\n");
            // 判断 MQTT 是否在线
            if (isMQTTLinkOnleng()) {
                Now_NetDevParameter.NowNetOnlineFlag = true; // 设备已在线
                Now_NetDevParameter.ReBootCount = 0;         // 连接成功，重器计数清零
                JSON_Send_GW_Infor((Now_NetDevParameter.ReBootCount > 0 ? true : false));
                printf("Now the gateway is online\r\n");
                JSON_Send_GW_Infor(0);//汇云上线需要先发一包心跳
            }
            Now_NetDevParameter.ReBootCount = 0; // 复位重启计数器
        }
        ClearNetDataBuff();
    }
    if (!Now_NetDevParameter.isLongLinkModeFlag) { // 短链接，需要查询下行指令
        Now_NetDevParameter.isCmdResFlag = (Now_NetDevParameter.isCmdResFlag | copyComputerDownData());  // 检查是否有收到数据
        if (Now_NetDevParameter.SendData != NULL) {
            Now_NetDevParameter.SendData(); // 发送数据
            ClearNetDataBuff(); // 清空数据
        }
        Now_NetDevParameter.isCmdResFlag = (Now_NetDevParameter.isCmdResFlag | copyComputerDownData());  // 检查是否有收到数据
    }
    if (Now_NetDevParameter.isCmdResFlag) {
        if (Now_NetDevParameter.DoneCmd != NULL) {
            Now_NetDevParameter.DoneCmd(); // 处理指令
        }
        Now_NetDevParameter.isCmdResFlag = false;
        ClearNetDataBuff();
    }
NetSubOver:
    // 判断是长连接还是短链接
    if (Now_NetDevParameter.isLongLinkModeFlag) {
        return; // 长链接，不需要做任何操作，在需要发送的时候才发送数据
    }
    if (Now_NetDevParameter.ShowdownNowDev != NULL) {
        Now_NetDevParameter.ShowdownNowDev();   // 短链接，需要关闭设备
        Now_NetDevParameter.NowNetOnlineFlag = false;
        Now_NetDevParameter.NowTCPLinkFlag = false;
    }
}
void UserDoneCmd(void) {
    if (Now_NetDevParameter.CmdTable.NowListNum > 0) {
        strnew OnceLineListStr = Now_NetDevParameter.CmdTable.popUpListStr(&Now_NetDevParameter.CmdTable);   // 弹出一行数据
        memcpy(Now_NetDevParameter.NetDataBuff, OnceLineListStr.Name._char, OnceLineListStr.MaxLen);
        char * AddrStart = strstr(Now_NetDevParameter.NetDataBuff, "{\"gw\":");
        MQTT_JSON_Analysis(AddrStart);
        printf("Received Command of HuiYun\r\n");
    }
}
// AT 参数初始化
void setNetArgumentInit(void (*UserShowdownNowDev)(void)) {
    // 初始化 Now_NetDevParameter
    Now_NetDevParameter.LineCheckTime = 60;  // 60 秒后，判断你是否处于连接状态
    Now_NetDevParameter.ShowdownNowDev = UserShowdownNowDev;
    Now_NetDevParameter.MQTT_NET_Receive_checkTime = BuffcheckTime10Ms;
    Now_NetDevParameter.isLongLinkModeFlag = true;
    Now_NetDevParameter.SendData = NULL;        // 长连接不需要发送函数
    Now_NetDevParameter.DoneCmd = UserDoneCmd;  // 处理指令
    TableOfCmdTaskInit();                       // 指令表初始化
    AT24CXXLoader_Init();                       // 读取 AT 参数
    UartBuff = NEW_NAME(UART_DATA_BUFF);        // 初始化缓存 UartBuff
    // 初始化创建定时任务
    SetTime.InitSetTimeTask(0, BSTSecTo10Ms(Now_NetDevParameter.LineCheckTime));
    SetTime.InitSetTimeTask(1, Now_NetDevParameter.MQTT_NET_Receive_checkTime);
    return;
}
