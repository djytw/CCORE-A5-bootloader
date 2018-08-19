// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : lowpower_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "lowpower_demo.h"
#include "wdt_api.h"
#include "cpm_drv.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lowpower_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Demo of lowpower.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void lowpower_demo(void)
{
	UINT8 wkp_num;
#ifdef POFF1_TEST
	lp_enter_POFF1(WKPPAD0, FALSE, TRUE);			//pad0 enable, disable interrupt, lower VREF
	wkp_num = lp_get_wkp_status(POFF1_MODE);		//get wakeup pad number
	stop_WDT();										//disable WDT
	lp_clr_wkp_flag(wkp_num);						//clear wakeup flag after leave lowpower
	sci_init(SCI_ID1, g_sys_clk, BAUDRATE_115200);
	MSG("Pad%d wake up system from POFF1!\r\n",wkp_num);
#endif
#ifdef POFF2_TEST
	wkp_num = lp_get_wkp_status(POFF2_MODE);		//get wakeup pad number
	MSG("Pad%d wake up system from POFF2!\r\n",wkp_num);
	lp_enter_POFF2(WKPPAD1, FALSE, HIBER_AT_ONCE);	//pad1 enable, disable interrupt, Hiber at once
#endif
}
