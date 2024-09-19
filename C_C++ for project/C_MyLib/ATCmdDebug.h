#ifndef _ATCMDDEBUG_H
#define _ATCMDDEBUG_H

#include "StrLib.h"
#include "All.h"

#ifdef OPEN_AT_CMD_DEBUG_LEN
extern void SendDebug(unsigned char InputBuf[], unsigned char Len);
extern void ATCmdDebugTask(void);
#endif


#endif



