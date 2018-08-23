// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : vd_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __VD_DRV_H__
#define __VD_DRV_H__

#include "type.h"

extern BOOL vd_init(UINT8 lvd_en, UINT8 lvd_mode, UINT8 lvd_cr, UINT8 hvd_en, UINT8 hvd_mode, UINT8 hvd_cr);
extern BOOL vd_power_select(UINT8 power_mode);


#endif /* __VD_DRV_H__ */
