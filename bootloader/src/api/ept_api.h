// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : ept_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _EPT_API_H_
#define _EPT_API_H_
#include "includes.h"
#include "ept_drv.h"

void init_EPT(EPT_CLK eptClk, EPT_INT eptInt, UINT32 rldVal);
UINT32 get_EPT_count();

#endif /*_EPT_API_H_*/
