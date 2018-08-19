// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : spi_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "type.h"
#include "spi_api.h"
#include "spi_demo.h"

UINT8 g_spidemo_send[SPI_DEMO_DATALEN];
UINT8 g_spidemo_recv[SPI_DEMO_DATALEN];

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi demo
//
// Input:
//    none
//
// Output:
//    none.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BOOL spi_demo()
{
	BOOL ret_val;

#if ( SPI_DEMO_MS == (1) )

#if ( SPI_DEMO_SS == (1) )
	ret_val = spi_master_init(SPI_ID1, SPI_CPOL0CPHA0, SPI_BDDIV256, 1 );
#else
	ret_val = spi_master_init(SPI_ID1, SPI_CPOL0CPHA0, SPI_BDDIV256, 0 );
	spi_sspin_high(SPI_ID1);
#endif

	if( FALSE == ret_val )
	{
		return FALSE;
	}

	ret_val = spi_readwrite_byte(SPI_ID1, g_spidemo_send,g_spidemo_recv , SPI_DEMO_DATALEN,SPI_CPUTRANS);

	if( FALSE == ret_val )
	{
		return FALSE;
	}

	ret_val = spi_readwrite_byte(SPI_ID1, g_spidemo_send,g_spidemo_recv , SPI_DEMO_DATALEN,SPI_DMACTRANS);

	if( FALSE == ret_val )
	{
		return FALSE;
	}

	ret_val = spi_readwrite_byte(SPI_ID1, g_spidemo_send,g_spidemo_recv , SPI_DEMO_DATALEN,SPI_EDMACTRANS);

	if( FALSE == ret_val )
	{
		return FALSE;
	}



#if ( SPI_DEMO_SS == (SPI_DEMO_SSOD) )
	spi_sspin_low(SPI_ID1);
#endif


#elif( SPI_DEMO_MS == (0) )

	ret_val = spi_slave_init(SPI_ID1, SPI_CPOL0CPHA0 );

	if( FALSE == ret_val )
	{
		return FALSE;
	}

	ret_val = spi_readwrite_byte(SPI_ID1, g_spidemo_send, g_spidemo_recv, SPI_DEMO_DATALEN,SPI_CPUTRANS);

	if( FALSE == ret_val )
	{
		return FALSE;
	}

	ret_val = spi_readwrite_byte(SPI_ID1, g_spidemo_send, g_spidemo_recv, SPI_DEMO_DATALEN,SPI_DMACTRANS);

	if( FALSE == ret_val )
	{
		return FALSE;
	}

	ret_val = spi_readwrite_byte(SPI_ID1, g_spidemo_send, g_spidemo_recv, SPI_DEMO_DATALEN,SPI_EDMACTRANS);

	if( FALSE == ret_val )
	{
		return FALSE;
	}

#endif

	return TRUE;

}
