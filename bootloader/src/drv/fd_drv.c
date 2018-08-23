// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : fd_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "memmap.h"
#include "fd_reg.h"
#include "fd_drv.h"
#include "reset_reg.h"
#include "cpm_reg.h"
#include "int_drv.h"
#include "ccm_reg.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 fd_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    fd module init code.
//
// Input:
//    	lfd_en
//		lfd_mode
//		lfd_cr
//		hfd_en
//		hfd_mode
//		hfd_cr
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL fd_init(UINT8 lfd_en, UINT8 lfd_mode, UINT8 lfd_cr, UINT8 hfd_en, UINT8 hfd_mode, UINT8 hfd_cr)
{
	EIC_REG *peicregspointer;
	CCM_REG *ccmregpointer;

	peicregspointer = (EIC_REG *)EIC_BASE;
	ccmregpointer = (CCM_REG *)CCM_BASE;
	ccmregpointer->FDCR = 0;


	if(lfd_en == LFD_EN)
	{
		RST_RCR |= LFDE;

		ccmregpointer->FDCR |= lfd_cr;

		if(lfd_mode == LFD_RST_MODE)
		{
			RST_RCR |= LFDRE;
		}
		else if(lfd_mode == LFD_INT_MODE)
		{
			RST_RCR |= LFDIE;
			peicregspointer->IER |= IER_ANALOG_MASK;

		}
		else
		{
			return FALSE;
		}
	}

	if(hfd_en == HFD_EN)
	{
		RST_RCR |= HFDE;

		ccmregpointer->FDCR |= (hfd_cr<<8);

		if(hfd_mode == HFD_RST_MODE)
		{
			RST_RCR |= HFDRE;
		}
		else if(hfd_mode == HFD_INT_MODE)
		{
			RST_RCR |= HFDIE;
			peicregspointer->IER |= IER_ANALOG_MASK;

		}
		else
		{
			return FALSE;
		}
	}

	return TRUE;

}


