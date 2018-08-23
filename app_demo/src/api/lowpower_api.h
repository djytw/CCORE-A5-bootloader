// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : lowpower_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef LOWPOWER_API_H_
#define LOWPOWER_API_H_

#include "includes.h"
#include "lowpower_drv.h"

#define POFF1_MODE		(0)
#define POFF2_MODE		(1)
#define HIBER_AT_ONCE	(0)
#define AUTO_HIBER		(1)

#define WKPPAD0			(0)
#define WKPPAD1			(1)
#define WKPPAD2			(2)
#define WKPPAD3			(3)


extern void lp_enter_POFF1(UINT8 pad_num, BOOL interrupt_en, BOOL vref_lower_en);
extern void lp_enter_POFF2(UINT8 pad_num, BOOL interrupt_en, UINT8 mode);
extern UINT8 lp_get_wkp_status(UINT8 mode);
extern void lp_clr_wkp_flag(UINT8 pad_num);

#endif /* LOWPOWER_API_H_ */
