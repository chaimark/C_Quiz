#include "AT24CXXDataLoader.h"
#include "stddef.h"

GetNBData_T GetNBData;  // NB数据
AT24CXX_MANAGER_T * _AT24CXX_Manager_NET = NULL;

void AT24CXXLoader_Init(void) {
    _AT24CXX_Manager_NET = &AT24CXX_Manager;
}


