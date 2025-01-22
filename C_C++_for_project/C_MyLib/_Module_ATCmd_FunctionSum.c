#include "_Module_ATCmd_FunctionSum.h"
#include "NetProt_Module.h"
#include "NumberBaseLib.h"
#include "AT24CXXDataLoader.h"
#include "RTC_SetTime.h"
#include "../Src/Define.h"

// 发送报文
void sendDataBy_Module_Prot(char * SendCmd, int SendCmdLen) {
    ClearNetDataBuff();
    UART1_Send((unsigned char *)SendCmd, SendCmdLen);
}
// 定义AT指令
NetDevATCmd NetDevice_ATData__NB[ATCMD_MAXNUMBER] = {
    {0,1,"AT+CFUN=0\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//关闭射频
    {1,2,"ATE1\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//打开回显
    {2,3,"AT+IPR=115200\r\n","OK",true,3,3,1000,false,setUartBandDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//设置波特率
    {3,4,"AT&W\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//保存波特率
    {4,5,"AT+SETLOCK=0,0\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//解锁 band, 全网通模组不要锁 band
    {5,6,"AT+QSCLK=0\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//关闭自动休眠锁
    {6,7,"AT+NNMI=2\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//关闭下行数据回显
    {7,8,"AT+SGSW\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//获取版本信息
    {8,9,"AT+CGSN\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,get_Module_DevIMEIFun, NULL, NULL},	//请求产品序列号IMEI
    {9,10,"AT+CFUN=1\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//开启射频
    {10,11,"AT+CSQ\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,get_Module_DevCSQFun, NULL, NULL},	//获取信号质量
    {11,12,"AT+CESQ\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,get_Module_DevCESQFun, NULL, NULL},	//获得扩展的信号质量
    {12,13,"AT+CPIN?\r\n","READY",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//识别sm卡
    {13,14,"AT+CIMI\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,get_Module_DevIMSIFun, NULL, NULL},	//获得SIM卡的IMSI
    {14,15,"AT+ICCID\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,get_Module_DevCCIDFun, NULL, NULL},	//获取CCID
    {15,16,"AT+CGDCONT=1,\"IPV4V6\",\"M2M\"\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//设置APN
    {16,17,"AT+CGDCONT?\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询APN
    {17,18,"AT+CCLK?\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,get_Module_DevCCLKFun, NULL, NULL},	//校时
    {18,19,"AT+QMTCFG=\"keepalive\",0,3600\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//设置超时时间
    {19,20,"AT+QMTCFG=\"version\",0,3\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//设置MQTT版本
    {20,21,"AT+QMTCFG=\"timeout\",0,60,3,0\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//设置发送超时时间
    {21,22,"AT+QMTCFG=\"session\",0,1\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//设置服务器放弃以前维护的有关订阅
    {22,23,"AT+QMTCFG=\"recv/mode\",0,0,1\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//设置按模式接收
    {23,24,"AT+QMTCFG=\"hexmode\",0,0\r\n","OK",true,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//设置收发字符串模式
    {24,25,"AT+QMTOPEN=0,\"59.110.170.225\",1883\r\n","+QMTOPEN: 0,0",true,3,3,1000,false,setRemoteIPDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//连接服务器
    {25,26,"AT+QMTCONN=0,\"ql\",\"admin\"\r\n","+QMTCONN: 0,0,0",true,3,3,1000,false,setUserAndPassWordDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//登录服务器
    {26,27,"AT+QMTSUB=0,0,\"hy/gw/get/02345678903\",2\r\n","+QMTSUB",true,3,3,1000,false,setMQTTMassageSUBFun,easyATCmdDataDoingFun, NULL, NULL},	//订阅地址
    {27,-1,"AT+QMTPUBEX=0,0,0,0,\"hy/gw/set/023456789033\",Len\r\n","+QMTPUBEX",false,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//发送数据
    {28,-1,"","",false,3,3,1000,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},
};

//======================================发送时的指令装载函数 ================================================//
void easyATCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    copyString(OutStr.Name._char, NowATCmd.ATCmd, OutStr.MaxLen, strlen(NowATCmd.ATCmd));
}
// 波特率设置特殊处理
void setDevBandCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    memset(OutStr.Name._char, 0, OutStr.MaxLen);
    sprintf(OutStr.Name._char, "AT+IPR=%d\r\n", UART_BAND);
}
// 设置 SIM BAND 
void setSIMBandCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    // AT+ECBAND=0,5\r\n
    memset(OutStr.Name._char, 0, OutStr.MaxLen);
    sprintf(OutStr.Name._char, "AT+SETLOCK=1,0,%d\r\n", (AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_BAND != 0) ? AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_BAND : IMSI_BAND);
    int ArrayLen = strlen(OutStr.Name._char);
    OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
}
// 清除旧的socket连接
void cleanOldSocketFunCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    // AT+SKTDELETE=1 
    int ArrayLen = 0;
    for (int i = 0; i < 10; i++) {
        memset(OutStr.Name._char, 0, OutStr.MaxLen);
        sprintf(OutStr.Name._char, "AT+SKTDELETE=%d\r\n", i);
        ArrayLen = strlen(OutStr.Name._char);
        OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
        sendDataBy_Module_Prot(OutStr.Name._char, ArrayLen);
        IncludeDelayMs(100); // 连接流程结束后等待 500ms
    }
    sprintf(OutStr.Name._char, "AT+SKTDELETE=1\r\n");
    ArrayLen = strlen(OutStr.Name._char);
    OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
}
// 目标IP特殊处理
void setRemoteIPCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    memset(OutStr.Name._char, 0, OutStr.MaxLen);
    sprintf(OutStr.Name._char, "AT+QMTOPEN=0,\"%s\",%d\r\n", AT24CXX_Manager_NET.NET_Remote_Url, AT24CXX_Manager_NET.NET_Remote_Port);
    int ArrayLen = strlen(OutStr.Name._char);
    OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
}
// APN 设置 
void setAPNForSIMCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    memset(OutStr.Name._char, 0, OutStr.MaxLen);
    char APNString[50] = {"M2M"};   //CMIOT
    sprintf(OutStr.Name._char, "AT+CGDCONT=1,\"IPV4V6\",\"%s\"\r\n", APNString);
    int ArrayLen = strlen(OutStr.Name._char);
    OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
}
void setUserAndPassWord(strnew OutStr, NetDevATCmd NowATCmd) {
    memset(OutStr.Name._char, 0, OutStr.MaxLen);
    sprintf(OutStr.Name._char, "AT+QMTCONN=0,\"%s\",\"%s\"\r\n", WT_DATA.UserName, WT_DATA.PassWord);
    int ArrayLen = strlen(OutStr.Name._char);
    OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
    return;
}
void setMQTTMassageSUB(strnew OutStr, NetDevATCmd NowATCmd) {
    memset(OutStr.Name._char, 0, OutStr.MaxLen);
    sprintf(OutStr.Name._char, "AT+QMTSUB=0,0,\"%s\",2\r\n", WT_DATA.PATH_SUB);
    int ArrayLen = strlen(OutStr.Name._char);
    OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
    return;
}

//========================接受模组反馈的信息，判断是否发送成功，或执行其他操作===================================//
bool easyATCmdDataDoing(NetDevATCmd NowATCmd) {
    if (myStrstr(Now_NetDevParameter.NetDataBuff, NowATCmd.SucessStr, Now_NetDevParameter.NetDataBuff_NowLen) != NULL)
        return true;
    else
        return false;
}
// 重启指令特殊处理
bool ReBootDevATCmdDoing(NetDevATCmd NowATCmd) {
    bool ReFalg = easyATCmdDataDoing(NowATCmd);
    IncludeDelayMs(1000); // 延时等待重启结束
    return ReFalg;
}
// 获取  CSQ
bool get_Module_DevCSQ(NetDevATCmd NowATCmd) {
    // +CSQ: 31,0
    char * StartAddr = NULL;
    if ((StartAddr = myStrstr(Now_NetDevParameter.NetDataBuff, "+CSQ:", Now_NetDevParameter.NetDataBuff_NowLen)) != NULL) {
        StartAddr += strlen("+CSQ:");
        char * EndAddr = NULL;
        if ((EndAddr = strchr(StartAddr, ',')) == NULL) {
            AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_CSQ = 0;
            return false;
        }
        (*EndAddr) = '\0';
        AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_CSQ = atoi(StartAddr);
        return true;
    }
    AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_CSQ = 0;
    return false;
}
// 获取 CESQ
bool get_Module_DevCESQ(NetDevATCmd NowATCmd) {
    // +CESQ: 99,99,255,255,34,84 ==> <rsrq = 34>,<rsrp = 84>
    char * StartAddr = NULL;
    if ((StartAddr = myStrstrCont(Now_NetDevParameter.NetDataBuff, ",", Now_NetDevParameter.NetDataBuff_NowLen, 4)) != NULL) {
        StartAddr++;
        char * EndAddr = NULL;
        if ((EndAddr = strchr(StartAddr, ',')) == NULL) {
            (*EndAddr) = '\0';
        }
        AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_RSRQ = atoi(StartAddr);    // 获取 RSRQ

        StartAddr = EndAddr + 1;
        if ((EndAddr = strchr(StartAddr, '\r')) == NULL) {
            (*EndAddr) = '\0';
        }
        AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_RSRP = atoi(StartAddr);
        return true;
    }
    AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_RSRQ = 0;
    AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_RSRP = 0;
    return false;
}
// 获取 IMEI
bool get_Module_DevIMEI(NetDevATCmd NowATCmd) {
    // 869254068477234
    char * StartAddr = NULL;
    if ((StartAddr = myStrstr(Now_NetDevParameter.NetDataBuff, "\r\n\r\nOK\r\n", Now_NetDevParameter.NetDataBuff_NowLen)) != NULL) {
        char * EndAddr = StartAddr;
        (*EndAddr) = '\0';
        StartAddr -= strlen("869254068477234");
        Now_NetDevParameter.isWriteEEprom = ((strcmp(StartAddr, AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_IMEI) == 0) ? false : true);  // 如果相同则不写入
        strcpy(AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_IMEI, StartAddr);
        if (Now_NetDevParameter.isWriteEEprom) {    // 如果需要修改 IMEI 同步修改表号
            EndAddr -= strlen("68477234");
            char MeterIDStr[10] = {0};
            strcpy(MeterIDStr, EndAddr);
            ASCIIToHEX2(MeterIDStr, 10, MeterIDStr, 10);
            memcpy(AT24CXX_Manager_NET.MeterID, MeterIDStr, 4);
        }
        return true;
    }
    memset(AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_IMEI, 0, ARR_SIZE(AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_IMEI));
    return false;
}
// 获取 IMSI
bool get_Module_DevIMSI(NetDevATCmd NowATCmd) {
    // 460113081449928
    char * StartAddr = NULL;
    if ((StartAddr = myStrstr(Now_NetDevParameter.NetDataBuff, "\r\n\r\nOK\r\n", Now_NetDevParameter.NetDataBuff_NowLen)) != NULL) {
        char * EndAddr = StartAddr;
        (*EndAddr) = '\0';
        StartAddr -= strlen("460113081449928");
        Now_NetDevParameter.isWriteEEprom = ((strcmp(StartAddr, AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_IMSI) == 0) ? false : true);  // 如果相同则不写入
        strcpy(AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_IMSI, StartAddr);
        return true;
    }
    memset(AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_IMSI, 0, ARR_SIZE(AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_IMSI));
    return false;
}
// 获取 CCID
bool get_Module_DevCCID(NetDevATCmd NowATCmd) {
    // +ECICCID: 89861122244006676924
    char * StartAddr = NULL;
    if ((StartAddr = myStrstr(Now_NetDevParameter.NetDataBuff, "+ICCID: ", Now_NetDevParameter.NetDataBuff_NowLen)) != NULL) {
        StartAddr += strlen("+ICCID: ");
        char * EndAddr = NULL;
        if ((EndAddr = strchr(StartAddr, '\r')) == NULL) {
            memset(AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_ICCID, 0, ARR_SIZE(AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_ICCID));
            return false;
        }
        (*EndAddr) = '\0';
        Now_NetDevParameter.isWriteEEprom = ((strcmp(StartAddr, AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_ICCID) == 0) ? false : true);  // 如果相同则不写入
        strcpy(AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_ICCID, StartAddr);
        return true;
    }
    memset(AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_ICCID, 0, ARR_SIZE(AT24CXX_Manager_NET.Get_Module_Data._Module_SIM_ICCID));
    return false;
}
#include "../Src/SLM130.h"
// CCLK 校时
bool get_Module_DevCCLK(NetDevATCmd NowATCmd) {
    if ((_Module_Start_Flage == _Module_UserSend) || (RTC_TASK.Task[DayOverCclkTask].TimeTask_Falge)) {
        RTC_TASK.InitSetTimeTask(DayOverCclkTask, MinToSec(HourToMin(AT24CXX_Manager_NET.DaysNumberOfCCLK * 24)), NULL); // 604,800
    } else {
        return true;
    }
    // +CCLK: 2024/08/16,01:41:25+32
    int Min15Cont = 0;
    FL_RTC_InitTypeDef _Module_Time_Data = {0};
    char * StartAddr = NULL;
    if ((StartAddr = myStrstr(Now_NetDevParameter.NetDataBuff, "+CCLK: ", Now_NetDevParameter.NetDataBuff_NowLen)) != NULL) {
        sscanf(StartAddr, "+CCLK: \"%d/%d/%d,%d:%d:%d+%d\"", &_Module_Time_Data.year, &_Module_Time_Data.month, &_Module_Time_Data.day,
            &_Module_Time_Data.hour, &_Module_Time_Data.minute, &_Module_Time_Data.second, &Min15Cont);
        _Module_Time_Data = RTCTimeAddSecToNewTime(_Module_Time_Data, (Min15Cont * 15 * 60));

        _Module_Time_Data.year = (uint32_t)anyBaseToAnyBase((uint64_t)_Module_Time_Data.year, 16, 10);     // 将 _Module_Time_Data.year 16进制转换成10进制
        _Module_Time_Data.month = (uint32_t)anyBaseToAnyBase((uint64_t)_Module_Time_Data.month, 16, 10);   // 将 _Module_Time_Data.month 16进制转换成10进制
        _Module_Time_Data.day = (uint32_t)anyBaseToAnyBase((uint64_t)_Module_Time_Data.day, 16, 10);       // 将 _Module_Time_Data.day 16进制转换成10进制
        _Module_Time_Data.hour = (uint32_t)anyBaseToAnyBase((uint64_t)_Module_Time_Data.hour, 16, 10);     // 将 _Module_Time_Data.hour 16进制转换成10进制
        _Module_Time_Data.minute = (uint32_t)anyBaseToAnyBase((uint64_t)_Module_Time_Data.minute, 16, 10); // 将 _Module_Time_Data.minute 16进制转换成10进制
        _Module_Time_Data.second = (uint32_t)anyBaseToAnyBase((uint64_t)_Module_Time_Data.second, 16, 10); // 将 _Module_Time_Data.second 16进制转换成10进制
        _Module_Time_Data.week = getDayOfWeek(_Module_Time_Data.year, _Module_Time_Data.month, _Module_Time_Data.day);

        if (!checkTimeFrom(_Module_Time_Data) || AT24CXX_Manager_NET.Get_Module_Data._Module_DEV_CSQ < 5) {
            return false;    // 时间错误
        }

        char setStrOfTime[32] = {0};
        strnew NowTimeData = NEW_NAME(setStrOfTime);
        sprintf(NowTimeData.Name._char, "20%02x-%02x-%02x %02x:%02x:%02x", _Module_Time_Data.year, _Module_Time_Data.month, _Module_Time_Data.day, _Module_Time_Data.hour, _Module_Time_Data.minute, _Module_Time_Data.second);
        setRtcDate(NowTimeData, false); // 设置时间
        RTC_TASK.InitSetTimeTask(EEpromWrite_Module_, MinToSec(1), NULL); // 1min 后写 eeprom
        // Now_NetDevParameter.isWriteEEprom = true;
        return true;
    } else {
        return false;
    }
}

// 设置或查询 AT指令 的装载方法
void DataInstallation__NB(strnew OutStr, struct _NetDevATCmdData This) {
    // 调用实际装载的函数
    switch (This.LoadATSendFunName) {
        case easyATCmdDataLoadFun:
            easyATCmdDataLoad(OutStr, This);
            break;
        case setUartBandDataLoadFun:
            setDevBandCmdDataLoad(OutStr, This);
            break;
        case setSIMBandDataLoadFun:
            setSIMBandCmdDataLoad(OutStr, This);
            break;
        case cleanOldSocketFun:
            cleanOldSocketFunCmdDataLoad(OutStr, This);
            break;
        case setRemoteIPDataLoadFun:
            setRemoteIPCmdDataLoad(OutStr, This);
            break;
        case setAPNForSIMLoadFun:
            setAPNForSIMCmdDataLoad(OutStr, This);
            break;
        case setUserAndPassWordDataLoadFun:
            setUserAndPassWord(OutStr, This);
            break;
        case setMQTTMassageSUBFun:
            setMQTTMassageSUB(OutStr, This);
            break;
    }
}
// 处理指令返回的方法
bool DoingATCmdResData__NB(struct _NetDevATCmdData This) {
    bool ResFlag = false;
    // 调用实际处理回复的函数
    switch (This.DoingATReceiveFunName) {
        case ResetTrueFlagDoingFun:
            ResFlag = true;
            break;
        case easyATCmdDataDoingFun:
            ResFlag = easyATCmdDataDoing(This);
            break;
        case ReBootDevFun:
            ResFlag = ReBootDevATCmdDoing(This);
            break;
        case get_Module_DevIMEIFun:
            ResFlag = get_Module_DevIMEI(This);
            break;
        case get_Module_DevCSQFun:
            ResFlag = get_Module_DevCSQ(This);
            break;
        case get_Module_DevCESQFun:
            ResFlag = get_Module_DevCESQ(This);
            break;
        case get_Module_DevIMSIFun:
            ResFlag = get_Module_DevIMSI(This);
            break;
        case get_Module_DevCCIDFun:
            ResFlag = get_Module_DevCCID(This);
            break;
        case get_Module_DevCCLKFun:
            ResFlag = get_Module_DevCCLK(This);
            break;
    }
    return ResFlag;
}
bool isMQTTLinkOnleng__NB(void) {
    #warning("未测试 Ping 失败的回复指令未知");
    bool ResFlag;
    newString(IPaddres, 30);
    sprintf(IPaddres.Name._char, "AT+PING=\"%s\",20,36,30", AT24CXX_Manager_NET.NET_Remote_Url);
    sendDataByTTLProt(IPaddres.Name._char, IPaddres.getStrlen(&IPaddres));      // 查询 MQTT 连接状态
    for (int i = 0; i < 3; i++) {
        if (FindStr_WaitTime(NEW_NAME("Reply from"), 1000) == true) {
            ResFlag = true;
            break;
        }
        ClearNetDataBuff();
        ResFlag = false;
    }
    return ResFlag;
}
bool EnterATMode__NB(void) {
    // 供电
    REBOOT_DEV_OFF;
    IncludeDelayMs(100);
    MF_UART1_Init();
    MF_UART1_Interrupt_Init();
    REBOOT_DEV_ON;
    IncludeDelayMs(200);
    // 开机
    _Module_PWR_RES_HIGH;
    _Module_PWR_KEY_HIGH;
    IncludeDelayMs(500);
    _Module_PWR_RES_LOW;
    _Module_PWR_KEY_LOW;
    IncludeDelayMs(1000);
    _Module_PWR_RES_LOW;
    _Module_PWR_KEY_HIGH;
    IncludeDelayMs(3500);
    _Module_PWR_RES_LOW;
    _Module_PWR_KEY_LOW;
    return true;
}
/////////////////////////////////////
// 主动获取指令,并返回是否有指令已存入缓存区
// bool UserGetDownCmd__XXX(void) {}
