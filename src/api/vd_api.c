// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : vd_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "type.h"
#include "vd_drv.h"
#include "vd_reg.h"
#include "vd_api.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 vd_start
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    vd module starts test.
//
// Input:
//		power_mode
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
BOOL vd_start(UINT8 power_mode, UINT8 lvd_en, UINT8 lvd_mode, UINT8 lvd_cr, UINT8 hvd_en, UINT8 hvd_mode, UINT8 hvd_cr)
{
	UINT8 ret_val = 0;

	ret_val = vd_power_select(power_mode);

	if(ret_val == FALSE)
	{
		return FALSE;
	}

	ret_val = vd_init(lvd_en, lvd_mode, lvd_cr, hvd_en, hvd_mode, hvd_cr);

	if(ret_val == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}


