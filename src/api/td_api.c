// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : td_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "type.h"
#include "td_drv.h"
#include "td_reg.h"
#include "td_api.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 td_start
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    td module starts test.
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
BOOL td_start(UINT8 td_ch_num, UINT8 td_ht_en, UINT8 td_ht_set, UINT8 td_ht_mode, UINT8 td_lt_en, UINT8 td_lt_set, UINT8 td_lt_mode)
{
	UINT8 ret_val = 0;

	ret_val = td_init(td_ch_num, td_ht_en, td_ht_set, td_ht_mode, td_lt_en, td_lt_set, td_lt_mode);

	if(ret_val == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}
