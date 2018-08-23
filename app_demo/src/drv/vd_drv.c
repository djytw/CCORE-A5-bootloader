// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : vd_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "memmap.h"
#include "vd_reg.h"
#include "vd_drv.h"
#include "reset_reg.h"
#include "cpm_reg.h"
#include "int_drv.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 vd_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    vd module init code.
//
// Input:
//    	lvd_en
//		lvd_mode
//		lvd_cr
//		hvd_en
//		hvd_mode
//		hvd_cr
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL vd_init(UINT8 lvd_en, UINT8 lvd_mode, UINT8 lvd_cr, UINT8 hvd_en, UINT8 hvd_mode, UINT8 hvd_cr)
{
	EIC_REG *peicregspointer;
	peicregspointer = (EIC_REG *)EIC_BASE;


	if(lvd_en == LVD_EN)
	{
		RST_RCR |= LVDE;

		RST_LVDCR = lvd_cr;

		if(lvd_mode == LVD_RST_MODE)
		{
			RST_RCR |= LVDRE;
		}
		else if(lvd_mode == LVD_INT_MODE)
		{
			RST_RCR |= LVDIE;
			peicregspointer->IER |= IER_ANALOG_MASK;

		}
		else
		{
			return FALSE;
		}
	}

	if(hvd_en == HVD_EN)
	{
		RST_RCR |= HVDE;

		RST_HVDCR = hvd_cr;

		if(hvd_mode == HVD_RST_MODE)
		{
			RST_RCR |= HVDRE;
		}
		else if(hvd_mode == HVD_INT_MODE)
		{
			RST_RCR |= HVDIE;
			peicregspointer->IER |= IER_ANALOG_MASK;

		}
		else
		{
			return FALSE;
		}
	}

	return TRUE;

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 vd_power_select
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    vd power select code.
//
// Input:
//    	power_mode
//
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL vd_power_select(UINT8 power_mode)
{
	if(power_mode == VD_POWER_3V3)
	{
		CPM_VCCQLTRIMR |= VD_PWRSEL_MASK;
	}
	else if(power_mode == VD_POWER_1V8)
	{
		CPM_VCCQLTRIMR &= ~VD_PWRSEL_MASK;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

