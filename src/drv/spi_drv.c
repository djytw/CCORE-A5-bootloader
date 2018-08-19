// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : spi_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "spi_drv.h"




//------------------------------------------------------------------
//                        Headers
//------------------------------------------------------------------
#include "memmap.h"
#include "spi_reg.h"
#include "int_drv.h"
#include "type.h"

//------------------------------------------------------------------

/*SPI global error status*/
static VUINT8 g_spi_errstatus[SPI_HWNUM] = {0};

/*SPI base address*/
UINT32 const g_spi_baseaddr[SPI_HWNUM] = {SPI1_BASE, SPI2_BASE, SPI3_BASE, SPI4_BASE};


#define SPI_MAX_WAIT_CNT		(0x100000)
#define BSP_SPIADDCNT	{ ulspiwaitcnt++; if(ulspiwaitcnt > SPI_MAX_WAIT_CNT)\
							{return	FALSE;}}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_config
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi config code.
//
// Input:
//    	ucid
//		ucms
//		ucbauddivisor
//		ucframesize
//		ucframemode
//		ucgtime
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_config(UINT8 ucid, UINT8 ucms, UINT8 ucbauddivisor, UINT8 ucframesize, UINT8 ucframemode, UINT8 ucgtime)
{
	/*SPI registers pointer*/
	SPI_REG* pregspointer = 0;

	/*invalid parameters*/
	if (ucid > SPI4)
	{
		return	FALSE;
	}

	/*reset error status*/
	g_spi_errstatus[ucid] = 0;

	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	/*clear possible errors*/
	pregspointer->SR16 = 0xffff;

	/*flush FIFO*/
	pregspointer->TXFCR = SPITXFCR_TXFCLR_MASK;
	pregspointer->RXFCR = SPIRXFCR_RXFCLR_MASK;

	/*set CPOL, CPHA*/
	if(SPI_TI_MODE == ucframemode)//TI mode
	{
		/*set FFSEL in TI mode*/
		pregspointer->FR |= SPIFR_FFSEL_MASK;
		pregspointer->CR1 = 0;
	}
	else//Freescale mode
	{
		pregspointer->CR1 = ucframemode;
	}

	/*set frame size*/
	pregspointer->FR = ucframesize & 0x0f;

	if( (ucgtime)&(SPIFR_GTE_MASK) )/*enable GT in master mode*/
	{
		pregspointer->FR |= SPIFR_GTE_MASK;
	}
	else
	{
		pregspointer->FR &= ~SPIFR_GTE_MASK;
	}

	pregspointer->BR = ucbauddivisor;
	pregspointer->CR2 = (UINT8)(ucgtime << 2);
#if SPI_TIMEOUT_EN
	pregspointer->TXFTOCTR = 0x7f;
	pregspointer->RXFTOCTR = 0x7f;
#else
	pregspointer->TXFTOCTR = 0x3f;
	pregspointer->RXFTOCTR = 0x3f;
#endif

	pregspointer->TXFCR = 0x00;
	pregspointer->RXFCR = 0x00;
	pregspointer->BSCDR = 0x00;
	pregspointer->ASCDR = 0x00;
	pregspointer->PURD = 0x01;
	pregspointer->DDR = 0x00;
	pregspointer->ICR = 0x00;
	pregspointer->FDCR = 0x00;
	pregspointer->DMATHR = 0x00;
	pregspointer->DMACR = 0x00;

	if( (ucms)&(SPICR1_MSTR_MASK) )/*master mode*/
	{
		if (SPI_TI_MODE == ucframemode)/*TI mode*/
		{
			pregspointer->PORT = 0x00; /*SS, SCK low*/
		}
		else
		{
			if(ucframemode & (0x08))/*CPOL*/
			{
				/*SS,SCK high when CPOL=1*/
				pregspointer->PORT = SPIDDR_SCK_MASK | SPIDDR_SS_MASK;
			}
			else
			{
				/*SS high, SCK low*/
				pregspointer->PORT = SPIDDR_SS_MASK;
			}
		}
		//pregspointer->CR1 |= SPICR1_MSTR_MASK | SPICR1_SSOE_MASK;
		pregspointer->CR1 |= SPICR1_MSTR_MASK|((ucms)&(SPICR1_SSOE_MASK))|((ucms)&(SPICR1_LSBFE_MASK));
		pregspointer->DDR = SPIDDR_SS_MASK | SPIDDR_SCK_MASK | SPIDDR_MOSI_MASK;
	}
	else  /*slave mode*/
	{
		pregspointer->CR1 |= ((ucms)&(SPICR1_LSBFE_MASK));
		pregspointer->DDR = SPIDDR_MISO_MASK;
	}

	return TRUE;

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_inten
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi interrupt enable.
//
// Input:
//    	ucid
//		ben
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_inten(UINT8 ucid, BOOL ben)
{
	EIC_REG *peicregspointer;
	SPI_REG* pspiregspointer = 0;

	/*invalid port number*/
	if(ucid > SPI4)
	{
		return	FALSE;
	}

	peicregspointer = (EIC_REG *)EIC_BASE;
	pspiregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	if(ben)
	{
		pspiregspointer->CR1 |= SPICR1_SPIE_MASK;
		switch(ucid)
		{
			case SPI1:
			case SPI4:
				peicregspointer->IER |= IER_SPI14INT_MASK;
				break;
			case SPI2:
			case SPI3:
				peicregspointer->IER |= IER_SPI23INT_MASK;
				break;
			default:
				break;
		}
	}
	else
	{
		pspiregspointer->CR1 &= ~SPICR1_SPIE_MASK;
		switch(ucid)
		{
			case SPI1:
			case SPI4:
				peicregspointer->IER &= ~IER_SPI14INT_MASK;
				break;
			case SPI2:
			case SPI3:
				peicregspointer->IER &= ~IER_SPI23INT_MASK;
				break;
			default:
				break;
		}
	}

	return TRUE;

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_dmacen
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi damc enable.
//
// Input:
//    	ucid
//		ben
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_dmacen(UINT8 ucid, BOOL ben)
{
	SPI_REG* pregspointer = 0;

	/*invalid port number*/
	if(ucid > SPI4)
	{
		return	FALSE;
	}

	/*enable/disable SPI*/
	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	if(ben)
	{
		pregspointer->DMACR |= SPISR_TXDMAE_MASK|SPISR_RXDMAE_MASK;
	}
	else
	{
		pregspointer->DMACR &= (~(SPISR_TXDMAE_MASK|SPISR_RXDMAE_MASK));
	}

	return	TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_ssout
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi ss output valu .
//
// Input:
//    	ucid
//		bval
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_ssout(UINT8 ucid, BOOL bval)
{
	SPI_REG* pregspointer = 0;

	/*invalid port number*/
	if(ucid > SPI4)
	{
		return	FALSE;
	}

	/*enable/disable SPI*/
	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	if(bval)
	{
		pregspointer->PORT |= SPIDDR_SS_MASK;
	}
	else
	{
		pregspointer->PORT &= (~(SPIDDR_SS_MASK));
	}

	return	TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_clrfifo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi clear fifo .
//
// Input:
//    	ucid
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_clrfifo(UINT8 ucid)
{
	SPI_REG* pregspointer = 0;

	/*invalid port number*/
	if(ucid > SPI4)
	{
		return	FALSE;
	}

	/*enable/disable SPI*/
	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	/*flush FIFO*/
	pregspointer->TXFCR |= SPITXFCR_TXFCLR_MASK;
	pregspointer->RXFCR |= SPIRXFCR_RXFCLR_MASK;

	return	TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi enable.
//
// Input:
//    	ucid
//		ben
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_enable(UINT8 ucid, BOOL ben)
{
	SPI_REG* pregspointer = 0;

	/*invalid port number*/
	if(ucid > SPI4)
	{
		return	FALSE;
	}

	/*enable/disable SPI*/
	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	if(ben)
	{
		pregspointer->CR1 |= SPICR1_SPE_MASK;
	}
	else
	{
		pregspointer->CR1 &= ~SPICR1_SPE_MASK;
	}

	return	TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_dbltxdr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi double fifo enable ,only for slave mode.
//
// Input:
//    	ucid
//		ben
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_dbltxdr(UINT8 ucid, BOOL ben)
{
	SPI_REG* pregspointer = 0;

	/*invalid port number*/
	if(ucid > SPI4)
	{
		return	FALSE;
	}

	/*enable/disable SPI*/
	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	if(ben)
	{
		pregspointer->PURD |= SPIPURD_DBLTXDR_MASK;
	}
	else
	{
		pregspointer->PURD &= ~SPIPURD_DBLTXDR_MASK;
	}

	return	TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_hsenable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi high speed mode enable ,only for slave mode.
//
// Input:
//    	ucid
//		ben
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_hsenable(UINT8 ucid, BOOL ben)
{
	SPI_REG* pregspointer = 0;

	/*invalid port number*/
	if(ucid > SPI4)
	{
		return	FALSE;
	}

	/*enable/disable SPI*/
	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	if(ben)
	{
		pregspointer->PURD |= SPIPURD_HS_MASK;
	}
	else
	{
		pregspointer->PURD &= ~SPIPURD_HS_MASK;
	}

	return	TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_writed8r
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi write data.
//
// Input:
//    	pregspointer
//		ucdata
//
// Output:
//      none
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void spi_writed8r(SPI_REG* pregspointer,UINT8 ucdata)
{
	*((UINT8*) (&pregspointer->DRHL.DR_L)) = (UINT8)(ucdata);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_writed16r
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi write data.
//
// Input:
//    	pregspointer
//		usdata
//
// Output:
//      none
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void spi_writed16r(SPI_REG* pregspointer,UINT16 usdata)
{
	*((UINT16*) (&pregspointer->DR16)) = (UINT16)(usdata);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 BSP_SPIReadD8R
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi write data.
//
// Input:
//    	pregspointer
//
// Output:
//      ucdata
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline UINT8 BSP_SPIReadD8R(SPI_REG* pregspointer)
{
	return (*(UINT8*) (&pregspointer->DRHL.DR_L));
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 BSP_SPIReadD16R
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi write data.
//
// Input:
//    	pregspointer
//
// Output:
//      usdata
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline UINT16 BSP_SPIReadD16R(SPI_REG* pregspointer)
{
	return (*(UINT16*) (&pregspointer->DR16));
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_trans8bit
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi trans 8bit data.
//
// Input:
//    	ucid
//		psend
//		precv
//		uldatalen
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_trans8bit(UINT8 ucid, UINT8 *psend, UINT8 *precv, UINT32 uldatalen)
{
	UINT32 ulsendcnt = 0;/*store frame send count*/
	UINT32 ulrecvcnt = 0;/*frame receive count*/
	UINT8 uctxfilllen = 0;/*tx fifo fill length*/
	UINT32 ulspiwaitcnt = 0;
	SPI_REG* pregspointer;/*SPI register pointer*/

	/*no action needed*/
	if ((0 == uldatalen) || (ucid > SPI3))
	{
		return FALSE;
	}

	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	/*flush FIFO*/
	pregspointer->TXFCR |= SPITXFCR_TXFCLR_MASK;
	pregspointer->RXFCR |= SPIRXFCR_RXFCLR_MASK;
	pregspointer->TXFCR &= ~SPITXFCR_TXFCLR_MASK;
	pregspointer->RXFCR &= ~SPIRXFCR_RXFCLR_MASK;

	/*clear possible error flags and EOTF*/
	pregspointer->SR16 = 0xffff;

	/*fill Tx FIFO*/
	if(uldatalen <= SPI_FIFO_SIZE)
	{
		uctxfilllen = uldatalen;
	}
	else
	{
		uctxfilllen = SPI_FIFO_SIZE;
	}

	for (ulsendcnt = 0; ulsendcnt < uctxfilllen; ulsendcnt++)
	{
		spi_writed8r(pregspointer, psend[ulsendcnt]);
	}

	while(ulrecvcnt < uldatalen)
	{
		/*wait until RxFIFO is not empty*/
		while(SPISR_RXFEMP_MASK & pregspointer->SR16)
		{
			if(SPISR_TXFTO_MASK & pregspointer->SR16) /*return if txFIFO time out*/
			{
				g_spi_errstatus[ucid] |= 0x80; /*store TXFTO error status*/
				return FALSE;
			}
		}

		/*read out data in RxFIFO*/
		ulspiwaitcnt = 0;
		while(!(SPISR_RXFEMP_MASK & pregspointer->SR16))
		{
			precv[ulrecvcnt++] = (UINT8) BSP_SPIReadD8R(pregspointer);

			if(ulsendcnt < uldatalen)
			{
				spi_writed8r(pregspointer, psend[ulsendcnt++]);
			}
			BSP_SPIADDCNT;
		}
	}

	return TRUE;

 }


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_trans16bit
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi trans 16bit data.
//
// Input:
//    	ucid
//		psend
//		precv
//		uldatalen
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_trans16bit(UINT8 ucid, UINT16 *psend, UINT16 *precv, UINT32 uldatalen)
{

	UINT32 ulsendcnt = 0;/*store frame send count*/
	UINT32 ulrecvcnt = 0;/*frame receive count*/
	UINT8 uctxfilllen = 0;/*tx fifo fill length*/
	SPI_REG* pregspointer = 0;/*SPI register pointer*/

	UINT32 ulspiwaitcnt = 0;

	/*no action needed*/
	if ((0 == uldatalen)||(ucid > SPI4))
	{
		return	FALSE;
	}

	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	/*flush FIFO*/
	pregspointer->TXFCR |= SPITXFCR_TXFCLR_MASK;
	pregspointer->RXFCR |= SPIRXFCR_RXFCLR_MASK;
	pregspointer->TXFCR &= ~SPITXFCR_TXFCLR_MASK;
	pregspointer->RXFCR &= ~SPIRXFCR_RXFCLR_MASK;

	/*clear possible error flags and EOTF*/
	pregspointer->SR16 = 0xffff;

	/*fill the TxFIFO*/
	if (uldatalen <= (SPI_FIFO_SIZE >> 1))
	{
		uctxfilllen = uldatalen;
	}
	else
	{
		uctxfilllen = SPI_FIFO_SIZE >> 1;
	}
	for (ulsendcnt = 0; ulsendcnt < uctxfilllen; ++ulsendcnt)
	{
		spi_writed16r(pregspointer, psend[ulsendcnt]);
	}

	while(ulrecvcnt < uldatalen)
	{
		/*wait until RxFIFO is not empty*/
		while(SPISR_RXFEMP_MASK & pregspointer->SR16)
		{
			if(SPISR_TXFTO_MASK & pregspointer->SR16) /*return if txFIFO time out*/
			{
				g_spi_errstatus[ucid] |= 0x80; /*store TXFTO error status*/
				return FALSE;
			}
		}

		/*read out data in RxFIFO*/
		ulspiwaitcnt = 0;
		while(!(SPISR_RXFEMP_MASK & pregspointer->SR16))
		{
			precv[ulrecvcnt++] = BSP_SPIReadD16R(pregspointer);

			if(ulsendcnt < uldatalen)
			{
				spi_writed16r(pregspointer, psend[ulsendcnt++]);
			}

			BSP_SPIADDCNT;
		}
	}

	return TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_pin_config
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    config spi pins as gpio.
//
// Input:
//    	ucid
//		pin
//		dir
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_pin_config(UINT8 ucid, UINT8 pin, UINT8 dir)
{
	SPI_REG* pregspointer = 0;

	/*enable/disable SPI*/
	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	if (dir == GPIO_OUTPUT)
	{
		pregspointer->DDR  |= (1<<pin);//output
	}
	else if (dir == GPIO_INPUT)
	{
		pregspointer->DDR &= (~(1<<pin));//input
	}
	else
	{
		return FALSE;
	}

	return	TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_pin_read
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    read spi pins status as gpio.
//
// Input:
//    	ucid
//		pin
//
// Output:
//      Bit_SET or Bit_RESET
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 spi_pin_read(UINT8 ucid, UINT8 pin)
{
	SPI_REG* pregspointer = 0;
	UINT8 bitstatus = 0x00;

	/*enable/disable SPI*/
	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	bitstatus = pregspointer->PORT;

	if (bitstatus &(Bit_SET << pin))
		bitstatus = Bit_SET;
	else
		bitstatus = Bit_RESET;

	return bitstatus;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_pin_write
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    read spi pins status as gpio.
//
// Input:
//    	ucid
//		pin
//		val
//
// Output:
//      TRUE or FALSE
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_pin_write(UINT8 ucid, UINT8 pin, UINT8 val)
{
	SPI_REG* pregspointer = 0;

	/*enable/disable SPI*/
	pregspointer = (SPI_REG *)(g_spi_baseaddr[ucid]);

	if (val == Bit_SET)
		pregspointer->PORT |= (Bit_SET << pin);
	else
		pregspointer->PORT &= (~(Bit_SET << pin));

	return TRUE;
}

