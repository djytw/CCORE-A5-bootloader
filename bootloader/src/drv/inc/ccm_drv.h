// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : ccm_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __CCM_DRV_H__
#define __CCM_DRV_H__

#include "type.h"

extern void ccm_spi4en(BOOL ben);
extern BOOL ccm_spiswapsd(UINT8 ucspiid);
extern BOOL ccm_spiswapdata(UINT8 ucspiid);
extern BOOL ccm_eport2swapspi(UINT8 ucspiid);

#endif /* __CCM_DRV_H__ */
