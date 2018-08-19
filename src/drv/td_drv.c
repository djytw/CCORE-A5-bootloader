// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : td_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "memmap.h"
#include "td_reg.h"
#include "td_drv.h"
#include "reset_reg.h"
#include "cpm_reg.h"
#include "int_drv.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 td_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    td module init code.
//
// Input:
//    	td_ch_num
//		td_ht_en
//		td_ht_set
//		td_ht_mode
//		td_lt_en
//		td_lt_set
//		td_lt_mode
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL td_init(UINT8 td_ch_num, UINT8 td_ht_en, UINT8 td_ht_set, UINT8 td_ht_mode, UINT8 td_lt_en, UINT8 td_lt_set, UINT8 td_lt_mode)
{
	volatile UINT32 *ts_cr;

	EIC_REG *peicregspointer;
	peicregspointer = (EIC_REG *)EIC_BASE;

	if(td_ch_num > 1)
	{
		return FALSE;
	}

	ts_cr = (UINT32 *)(SEC_DET_BASE + 0x4*td_ch_num);

	if(td_ht_en == TD_HT_EN)
	{
		*ts_cr &= 0x03ffffff;

		*ts_cr |= (td_ht_set<<26);

		*ts_cr |= TD_LAT_CLR_MASK;

		if(td_ht_mode == TD_RST_MODE)
		{
			*ts_cr |= TD_HT_RST_MASK;
		}
		else if(td_ht_mode == TD_INT_MODE)
		{
			*ts_cr |= TD_HT_INT_MASK;
			peicregspointer->IER |= IER_ANALOG_MASK;

		}
		else
		{
			return FALSE;
		}

	}

	if(td_lt_en == TD_LT_EN)
	{
		*ts_cr &= 0xffff7f1f;

		*ts_cr |= ((td_lt_set & 0x07)<<5) | ((td_lt_set & 0x08)<<12);

		*ts_cr |= TD_LAT_CLR_MASK;

		if(td_lt_mode == TD_RST_MODE)
		{
			*ts_cr |= TD_LT_RST_MASK;
		}
		else if(td_lt_mode == TD_INT_MODE)
		{
			*ts_cr |= TD_LT_INT_MASK;
			peicregspointer->IER |= IER_ANALOG_MASK;

		}
		else
		{
			return FALSE;
		}
	}

	*ts_cr |= TD_SEL_MASK;

	return TRUE;
}
