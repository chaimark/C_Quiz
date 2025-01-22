#ifndef SENDDATABYSERIAL_H
#define SENDDATABYSERIAL_H

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "StrLib.h"

extern void SendDataTask(const char * comPort, char (*SwitchNeedSendData)(strnew data));
extern void list_serial_ports();

#endif