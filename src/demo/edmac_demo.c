/*
 * edmac_test.c
 *
 *  Created on: 2017Äê3ÔÂ18ÈÕ
 *      Author: Administrator
 */

#include "edmac_drv.h"
#include "edmac_demo.h"
#include "type.h"
#include "debug.h"
#include <string.h>

UINT8 g_edmacsrcbuf[EDMAC_MAXLEN_TEST];
UINT8 g_edmacdstbuf[EDMAC_MAXLEN_TEST];



BOOL edmac_demo()
{
	BOOL ret_val;
	UINT8 i,j;
	msg_printf("edamc_demo test\r\n");
#if ( EDMAC_INTEN_TEST == 1 )
	edmac_inten(0,1);
	edmac_inten(1,1);
#endif

	for( j= 0; j< EDMAC1_ID; j++ )
	{
		for( i= 0; i< EDMAC_CH1_ID; i++ )
		{

			memset(g_edmacsrcbuf,(0x55+i+j),EDMAC_MAXLEN_TEST);
			memset(g_edmacdstbuf,0x00,EDMAC_MAXLEN_TEST);

			ret_val = edmac_sramtrans(EDMAC0_ID + j,EDMAC_CH0_ID + i,g_edmacsrcbuf, g_edmacdstbuf, (EDMAC_MAXLEN_TEST), EDMAC_INTEN_TEST);
			if( ret_val == FALSE )
			{
				return FALSE;
				msg_printf("edmac sramtrans error\r\n");
			}

			ret_val = memcmp(g_edmacsrcbuf,g_edmacdstbuf,EDMAC_MAXLEN_TEST);
			if( ret_val != 0 )
			{
				msg_printf("edmac memcmp error\r\n");
				assert(FALSE);
				return FALSE;
			}
		}
	}

#if ( EDMAC_INTEN_TEST == 1 )
	edmac_inten(0,0);
	edmac_inten(1,0);
#endif

	return TRUE;
}
