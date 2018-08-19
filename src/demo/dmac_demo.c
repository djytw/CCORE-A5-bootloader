// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : dma_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 dma_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Demo of dma.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#include "dmac_drv.h"
#include "dmac_demo.h"
#include "type.h"
#include "debug.h"
#include <string.h>

UINT8 srcbuf[DMAC_MAXLEN_TEST];
UINT8 dstbuf[DMAC_MAXLEN_TEST];

BOOL dmac_demo()
{
	BOOL ret_val;
	UINT8 i;
	msg_printf("damc_demo test\r\n");

#if ( DMAC_INTEN_TEST == 1 )
	dmac_inten(1);
#endif

	for( i= 0; i< DMAC_CH7_ID+1; i++ )
	{

		memset(srcbuf,(0x55+i),DMAC_MAXLEN_TEST);
		memset(dstbuf,0x00,DMAC_MAXLEN_TEST);

		ret_val = dmac_transword(DMAC_CH0_ID + i,srcbuf, dstbuf, (DMAC_MAXLEN_TEST>>2), DMAC_INTEN_TEST);
		if( ret_val == FALSE )
		{
			msg_printf("damc transbyte  error\r\n");
			return FALSE;
		}

		ret_val = memcmp(srcbuf,dstbuf,DMAC_MAXLEN_TEST);
		if( ret_val != 0 )
		{
			assert(FALSE);
			return FALSE;
		}

	}

	for( i= 0; i<DMAC_CH7_ID; i++ )
	{
		memset(srcbuf,(0x57+i),DMAC_MAXLEN_TEST);
		memset(dstbuf,0x00,DMAC_MAXLEN_TEST);

		ret_val = dmac_transhalfword(DMAC_CH0_ID + i,srcbuf, dstbuf, (DMAC_MAXLEN_TEST>>1), DMAC_INTEN_TEST );
		if( ret_val == FALSE )
		{
			return FALSE;
		}

		ret_val = memcmp(srcbuf,dstbuf,DMAC_MAXLEN_TEST);
		if( ret_val != 0 )
		{
			msg_printf("damc memcmp  error\r\n");
			assert(FALSE);
			return FALSE;
		}

	}

	for( i= 0; i<DMAC_CH7_ID; i++ )
	{
		memset(srcbuf,(0x59+i),DMAC_MAXLEN_TEST);
		memset(dstbuf,0x00,DMAC_MAXLEN_TEST);

		ret_val = dmac_transbyte(DMAC_CH0_ID + i,srcbuf, dstbuf, DMAC_MAXLEN_TEST, DMAC_INTEN_TEST );
		if( ret_val == FALSE )
		{
			msg_printf("damc transbyte  error\r\n");
			return FALSE;
		}

		ret_val = memcmp(srcbuf,dstbuf,DMAC_MAXLEN_TEST);
		if( ret_val != 0 )
		{
			msg_printf("damc memcmp  error\r\n");
			assert(FALSE);
			return FALSE;
		}

	}

#if ( DMAC_INTEN_TEST == 1 )
	dmac_inten(0);
#endif

	return TRUE;
}

