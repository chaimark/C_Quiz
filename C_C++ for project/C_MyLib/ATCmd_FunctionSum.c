#include "ATCmd_FunctionSum.h"
#include "NetProt_Module.h"
#include "NumberBaseLib.h"
#include "AT24CXXDataLoader.h"
// 定义AT指令
NetDevATCmd NetDevice_ATData[ATCMD_MAXNUMBER] = {0};

//======================================发送时的指令装载函数 ================================================//
void easyATCmdDataLoad(strnew OutStr, NetDevATCmd NowATCmd) {
    copyString(OutStr.Name._char, NowATCmd.ATCmd, OutStr.MaxLen, strlen(NowATCmd.ATCmd));
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
    FL_DelayMs(1000); // 延时等待重启结束
    return ReFalg;
}
#warning "增加网口 ATCmd 处理函数";

// 设置或查询 AT指令 的装载方法
void _DataInstallation(strnew OutStr, struct _NetDevATCmdData This) {
    // 调用实际装载的函数
    switch (This.LoadATSendFunName) {
        case easyATCmdDataLoadFun:
            easyATCmdDataLoad(OutStr, This);
            break;
    }
}
// 处理指令返回的方法
bool _DoingATCmdResData(struct _NetDevATCmdData This) {
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
// 建立对象的函数
NetDevATCmd New_NetDevAT_Obj(NetDevATCmd DataInit) {
    DataInit.DataInstallation = _DataInstallation;
    DataInit.DoingATCmdResData = _DoingATCmdResData;
    return DataInit;
}
void MQTT_NetAT_Init(void) {
    // 初始化 NetDevice_ATData
    for (int i = 0; i < ATCMD_MAXNUMBER; i++) {
        NetDevice_ATData[i] = New_NetDevAT_Obj(NetDevice_ATData[i]);
    }
    return;
}

