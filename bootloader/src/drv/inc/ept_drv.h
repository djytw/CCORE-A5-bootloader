// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : ept_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef __EPT_DRV_H__
#define __EPT_DRV_H__
#include "type.h"

typedef enum {EPT_CORE_CLK=0x04, EPT_EXT_CLK=0x00} EPT_CLK;
typedef enum {EPT_INT_EN=0x02, EPT_INT_DIS=0x00} EPT_INT;


#define EPT_CNTEN 0x01

void ept_init(EPT_CLK eptClk, EPT_INT eptInt);
void ept_RLD_set(UINT32 rldVal);
UINT32 ept_cnt_get();

#endif /* __EPT_DRV_H__ */
