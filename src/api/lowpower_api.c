// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : lowpower_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "lowpower_api.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_enter_POFF1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    enter POFF1 mode.
//
// Input:
//    pad_num: 0/1/2/3: select pad0/1/2/3 to wakeup the chip from POFF1.
//    interrupt_en: 0: disable wakeup interrupt;
//					1: enable wakeup interrupt.
//    vref_lower_en: 0: not change VREF in POFF1;
//					 1: lower VREF in POFF1.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void lp_enter_POFF1(UINT8 pad_num, BOOL interrupt_en, BOOL vref_lower_en)
{
	lp_drv_POFF1_cfg();
	lp_drv_enable_wkppad(pad_num, interrupt_en);
	if(vref_lower_en)
		lp_drv_change_VREF(0x0);

	lp_drv_enter_sleep();

	if(vref_lower_en)
		lp_drv_change_VREF(0x8);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_enter_POFF2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    enter POFF2 mode.
//
// Input:
//    pad_num: 0/1/2/3: select pad0/1/2/3 to wakeup the chip from POFF2.
//    interrupt_en: 0: disable wakeup interrupt;
//					1: enable wakeup interrupt.
//    mode: 0: Hiber at once;
//			1: Auto Hiber.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void lp_enter_POFF2(UINT8 pad_num, BOOL interrupt_en, UINT8 mode)
{
	lp_drv_POFF2_cfg(mode);
	lp_drv_enable_wkppad(pad_num, interrupt_en);

	lp_drv_enter_sleep();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_get_wkp_status
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    get wakuup pad number.
//
// Input:
//    mode: 0: POFF1 mode;
//			1: POFF2 mode.
//
// Output: 0/1/2/3: the chip was waked up by pad0/1/2/3;
// 		   others: invalid.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 lp_get_wkp_status(UINT8 mode)
{
	UINT8 flag=0,num=0;
	if(mode == POFF1_MODE)
		flag = lp_drv_get_wkp_flag();
	else if(mode == POFF2_MODE)
		flag = lp_drv_get_wkppad_val();
	while(flag)
	{
		num ++;
		flag >>= 1;
	}
	return (num - 1);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_clr_wkp_flag
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    clear wakeup flag.
//
// Input:
//    pad_num: 0: clear pad0 wakeup flag;
//			   1: clear pad1 wakeup flag;
//			   2: clear pad2 wakeup flag;
//			   3: clear pad3 wakeup flag.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void lp_clr_wkp_flag(UINT8 pad_num)
{
	lp_drv_clr_wkp_flag(pad_num);
}
