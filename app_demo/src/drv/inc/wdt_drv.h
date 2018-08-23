// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : wdt_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __WDT_DRV_H__
#define __WDT_DRV_H__

#include "type.h"

extern void wdt_reloadVal_set(UINT16 val);
extern void wdt_feed(void);
extern void wdt_enable(void);
extern void wdt_disable(void);
extern UINT16 wdt_get_remainCount(void);
extern UINT16 wdt_get_enableState(void);

#endif /* _WDT_DRV_H_ */
