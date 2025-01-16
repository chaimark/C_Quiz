#ifndef _ATCMDDEBUG_H
#define _ATCMDDEBUG_H

#include "StrLib.h"
#include "All.h"

#ifdef OPEN_AT_CMD_DEBUG
#define DebugBuff Now_NetDevParameter.CmdTable.OututStrOnce
extern void SendDebug(unsigned char InputBuf[], unsigned int Len);
extern void ATCmdDebugTask(void);
#endif


#endif



