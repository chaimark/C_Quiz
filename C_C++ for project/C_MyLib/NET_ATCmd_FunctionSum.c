#include "NET_ATCmd_FunctionSum.h"
#include "NetProt_Module.h"
#include "NumberBaseLib.h"
#include "AT24CXXDataLoader.h"
#define NowNETCtrol_UartNum 2
// 定义AT指令
struct _NetDevATCmdData NetDevice_ATData_NET[ATCMD_MAXNUMBER] = {
    // {0,1,"AT+E=ON\r\n","+OK",true,3,3,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置回显使能
    // {1,2,"AT+UART2=115200,8,1,NONE,NFC\r\n","+OK",false,3,3,false,setBandDataLoadFun,ResetTrueFlagDoingFun, NULL, NULL},	//查询/设置N号串口接口参数
    // {2,3,"AT+UARTCLBUF=ON\r\n","+OK",true,3,3,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置连接前是否清理串口缓存
    // {3,4,"AT+DNSTYPE=AUTO\r\n","+OK",true,3,3,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置模块DNS获取方式
    // {4,5,"AT+WANN=STATIC,192.168.1.117,255.255.255.0,192.168.1.1\r\n","+OK",true,3,3,false,setWannDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置模块获取到的WAN口IP（DHCP/STATIC）
    // {5,6,"AT+MAXSK2=1\r\n","+OK",true,3,3,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置N号串口的最大连接数量
    // {6,7,"AT+MQTTEN=ON\r\n","+OK",true,3,3,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置MQTT网关功能状态
    // {7,8,"AT+MQTTLPORT=0\r\n","+OK",true,3,3,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置MQTTsocket连接本地端口号
    // {8,9,"AT+MQTTAUTH=ON\r\n","+OK",true,3,3,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置MQTT连接验证开启状态
    // {9,10,"AT+MQTTCID=HY_QL\r\n","+OK",true,3,3,false,setMQTTUserIDDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置MQTT客户端ID
    // {10,11,"AT+MQTTUSER=ql\r\n","+OK",true,3,3,false,setUserAndPassWordDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置MQTT用户名
    // {11,12,"AT+MQTTPSW=ql\r\n","+OK",true,3,3,false,setUserAndPassWordDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置MQTT用户密码
    // {12,13,"AT+MQTTPUBCUSEN=OFF\r\n","+OK",true,3,3,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置MQTT主题发布自定义模式
    // {13,14,"AT+MQTTHEARTTM=60\r\n","+OK",true,3,3,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置MQTT心跳时间
    // {14,15,"AT+MQTTPUB=1,ON,hy/gw/set/02345678903,0,MY_PUB,0,OFF,3\r\n","+OK",true,3,3,false,setMQTTMassagePUBFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置MQTT的预置发布主题信息
    // {15,16,"AT+MQTTSUB=1,ON,hy/gw/get/02345678903,0,0,&#44,3\r\n","+OK",true,3,3,false,setMQTTMassageSUBFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置MQTT的预置订阅主题信息
    // {16,17,"AT+MQTTSER=59.110.170.225,1883\r\n","+OK",true,3,3,false,setRemoteIPDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//查询/设置MQTT网关功能的服务器IP地址，端口号
    // {17,-1,"AT+Z\r\n","+OK",true,3,3,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},	//设备重启
    // {18,-1,"","",false,3,3,false,easyATCmdDataLoadFun,easyATCmdDataDoingFun, NULL, NULL},
};

//======================================发送时的指令装载函数 ================================================//
void easyATCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    copyString(OutStr.Name._char, NowATCmd.ATCmd, OutStr.MaxLen, strlen(NowATCmd.ATCmd));
}
// 需要替换指令，并执行简单装载的指令
void flagChangeUartIDCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    // int ArrayLen = strlen(OutStr.Name._char);
    // OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
    return;
}
// 波特率设置特殊处理
void setDevBandCmsDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    // char BandData[16] = {"2000000"};
    // int ArrayLen = doneBaseNumberDataToAsciiStr(BandData, 16, IncludeUART0_NET_BAND, 16);
    // int ArrayLen = strlen(OutStr.Name._char);
    // OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
    return;
}
// 网口设置特殊处理
void setWannCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    // int ArrayLen = strlen(OutStr.Name._char);
    // OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
    return;
}
// 目标IP特殊处理
void setRemoteIPCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    // int ArrayLen = strlen(OutStr.Name._char);
    // OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
    return;
}

// MQTT 用户名与密码特殊处理
void setUserAndPassWordDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    // int ArrayLen = strlen(OutStr.Name._char);
    // OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
    return;
}
// MQTT 主题发布处理
void setMQTTMassagePUBCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    // int ArrayLen = strlen(OutStr.Name._char);
    // OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
}
// MQTT 主题订阅处理
void setMQTTMassageSUBCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    // int ArrayLen = strlen(OutStr.Name._char);
    // OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
    return;
}
// MQTT 客户端ID特殊处理
void setMQTTUserIDDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    // int ArrayLen = strlen(OutStr.Name._char);
    // OutStr.Name._char[(ArrayLen < OutStr.MaxLen) ? ArrayLen : (OutStr.MaxLen - 1)] = '\0';
    return;
}
#warning "增加网口 ATCmd 装载函数";

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
#warning "增加网口 ATCmd 处理函数";

// 设置或查询 AT指令 的装载方法
void DataInstallation_NET(strnew OutStr, struct _NetDevATCmdData This) {
    // 调用实际装载的函数
    switch (This.LoadATSendFunName) {
        case flagChangeUartIDFun:
            flagChangeUartIDCmdDataLoad(OutStr, This);
            break;
        case easyATCmdDataLoadFun:
            easyATCmdDataLoad(OutStr, This);
            break;
        case setBandDataLoadFun:
            setDevBandCmsDataLoad(OutStr, This);
            break;
        case setWannDataLoadFun:
            setWannCmdDataLoad(OutStr, This);
            break;
        case setRemoteIPDataLoadFun:
            setRemoteIPCmdDataLoad(OutStr, This);
            break;
        case setUserAndPassWordDataLoadFun:
            setUserAndPassWordDataLoad(OutStr, This);
            break;
        case setMQTTMassagePUBFun:
            setMQTTMassagePUBCmdDataLoad(OutStr, This);
            break;
        case setMQTTMassageSUBFun:
            setMQTTMassageSUBCmdDataLoad(OutStr, This);
            break;
        case setMQTTUserIDDataLoadFun:
            setMQTTUserIDDataLoad(OutStr, This);
            break;
    }
}
// 处理指令返回的方法
bool DoingATCmdResData_NET(struct _NetDevATCmdData This) {
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
    }
    return ResFlag;
}

bool isMQTTLinkOnleng_NET(void) {
    bool ATConfig_Flag = false;
    char cmdStr[2][2][40] = {{"AT+PING=", "\r\n+OK=SUCCESS"}, {"AT+ENTM\r\n", "\r\n+OK"}};
    sprintf(cmdStr[0][0], "AT+PING=%s\r\n", AT24CXX_Manager_NET.NET_4G_Remote_Url);
    sendDataByNetProt(cmdStr[0][0], strlen(cmdStr[0][0]));
    for (int i = 0; i < 10000; i++) {
        IncludeDelayMs(1);
        if (strstr(Now_NetDevParameter.NetDataBuff, cmdStr[0][1]) != NULL) {
            ATConfig_Flag = true;
            break;
        }
    }
    for (int i = 0; i < 3; i++) {
        sendDataByNetProt(cmdStr[1][0], strlen(cmdStr[1][0]));
        if (strstr(Now_NetDevParameter.NetDataBuff, cmdStr[1][1])) {
            break;
        }
    }
    return ATConfig_Flag;
}

