// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : fd_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "type.h"
#include "fd_drv.h"
#include "fd_reg.h"
#include "fd_api.h"
#include "cpm_reg.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 fd_start
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    fd module starts test.
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
BOOL fd_start(UINT8 lfd_en, UINT8 lfd_mode, UINT8 lfd_cr, UINT8 hfd_en, UINT8 hfd_mode, UINT8 hfd_cr)
{
	UINT8 ret_val = 0;

	ret_val = fd_init(lfd_en, lfd_mode, lfd_cr, hfd_en, hfd_mode, hfd_cr);

	if(ret_val == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}


