// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : wdt_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef __WDT_API_H__
#define __WDT_API_H__
#include "type.h"
#include "wdt_drv.h"


typedef enum {
	WDT_RUNNING=0,
	WDT_STOPPED
} WDT_state;

extern void start_WDT();
extern void stop_WDT();
extern void feed_WDT();
extern void set_WDT_span(UINT16 val);
extern UINT16 check_WDT_life();
extern WDT_state get_WDT_state();

#endif /* __WDT_API_H__ */
