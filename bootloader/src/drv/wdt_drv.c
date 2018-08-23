// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : wdt_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#include "includes.h"
#include "memmap.h"
#include "wdt_drv.h"
#include "wdt_reg.h"

void wdt_reloadVal_set(UINT16 val)
{
	WDT_WMR = val;
}

void wdt_feed(void)
{
	WDT_WSR = 0x5555;
	WDT_WSR = 0xAAAA;
}

void wdt_enable(void)
{
	WDT_WCR |= WDT_EN;
}

void wdt_disable(void)
{
	WDT_WCR &= (~WDT_EN);
}

UINT16 wdt_get_enableState(void)
{
	return (WDT_WCR&WDT_EN);
}

UINT16 wdt_get_remainCount(void)
{
   return WDT_WCNTR;
}
