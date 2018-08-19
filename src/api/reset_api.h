// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : reset_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __RESET_API_H__
#define __RESET_API_H__

#include "includes.h"
#include "reset_drv.h"

typedef enum _RST_STATUS_ {
	RST_RESERVED,
	RST_SIM_CARD = 1,
	RST_FREQUENCE_DETECT,
	RST_POR,
	RST_WATCH_DOG_TIMER,
	RST_SOFT,
	RST_VOLTAGE_DETECT,
	RST_TC_TIMER
} RST_STATUS, *P_RST_STATUS;

typedef enum _RST_SOURCE_ {
	RST_SRC_HFD = 0,
	RST_SRC_LFD,
	RST_SRC_HVD,
	RST_SRC_LVD,
	RST_SRC_CRE
} RST_SOURCE, *P_RST_SOURCE;

extern void reset_soft_rst(void);
extern void reset_por_rst(void);
extern RST_STATUS reset_get_status(void);
extern void reset_disable_rstsrc(RST_SOURCE reset_source);

#endif /* __RESET_API_H__ */
