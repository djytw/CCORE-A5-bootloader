// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : rst_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __RST_REG_H__
#define __RST_REG_H__

#include "includes.h"
#include "memmap.h"

#define RST_RCR					(*(volatile UINT32 *)(RESET_BASE + 0x0000))
#define RST_LVDCR				(*(volatile UINT8 *)(RESET_BASE + 0x0004))
#define RST_HVDCR				(*(volatile UINT8 *)(RESET_BASE + 0x0005))
#define RST_RTR					(*(volatile UINT8 *)(RESET_BASE + 0x0006))
#define RST_RSR					(*(volatile UINT8 *)(RESET_BASE + 0x0007))


/* RST_RCR */
#define HFDE					(1<<0)
#define HFDRE					(1<<1)
#define HFDIE					(1<<2)
#define HFDF					(1<<3)
#define LFDE					(1<<8)
#define LFDRE					(1<<9)
#define LFDIE					(1<<10)
#define LFDF					(1<<11)
#define HVDE					(1<<16)
#define HVDRE					(1<<17)
#define HVDIE					(1<<18)
#define HVDF					(1<<19)
#define CRWE					(1<<22)
#define CRE						(1<<23)
#define LVDE					(1<<24)
#define LVDRE					(1<<25)
#define LVDIE					(1<<26)
#define LVDF					(1<<27)
#define FRCR_STOUT				(1<<30)
#define SOFTRST					(1<<31)

/* RST_RSR */
#define CR						(1<<1)
#define FD						(1<<2)
#define POR						(1<<3)
#define WDR						(1<<4)
#define SOFT					(1<<5)
#define VD						(1<<6)
#define TCR						(1<<7)

/* RST_RTR */
#define FDTME					(1<<0)
#define HVDTME					(1<<1)
#define LVDTME					(1<<2)
#define FPOR					(1<<7)

#endif /* __RST_REG_H__ */
