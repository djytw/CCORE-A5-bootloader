// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : ccm_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ccm_reg.h"
#include "memmap.h"
#include "spi_drv.h"
#include "type.h"



void ccm_spi4en(BOOL ben)
{
	CCM_REG *pregspointer = (CCM_REG *)(CCM_BASE);

	if(ben)//enable spi4 pin function
	{
		(pregspointer->CCR) = CCM_SPI4EN_MASK;
	}
	else
	{
		(pregspointer->CCR) &= ~CCM_SPI4EN_MASK;
	}
}


BOOL ccm_spiswapsd(UINT8 ucspiid)
{
	CCM_REG *pregspointer = (CCM_REG *)(CCM_BASE);

	if( ucspiid > SPI3 )
	{
		return FALSE;
	}

	switch(ucspiid)
	{
		case SPI1:
			pregspointer->HSSPI1PADCTRL |= CCM_SWAPSD_MASK;
			break;
		case SPI2:
			pregspointer->HSSPI2PADCTRL |= CCM_SWAPSD_MASK;
			break;
		case SPI3:
			pregspointer->HSSPI3PADCTRL |= CCM_SWAPSD_MASK;
			break;
		default:
			return FALSE;
			break;
	}

	return TRUE;
}


BOOL ccm_spiswapdata(UINT8 ucspiid)
{
	CCM_REG *pregspointer = (CCM_REG *)(CCM_BASE);

	if( ucspiid > SPI3 )
	{
		return FALSE;
	}

	switch(ucspiid)
	{
		case SPI1:
			pregspointer->HSSPI1PADCTRL &= ~CCM_SWAPSD_MASK;
			pregspointer->HSSPI1PADCTRL |= CCM_SWAPDBUS_MASK;
			break;
		case SPI2:
			pregspointer->HSSPI2PADCTRL &= ~CCM_SWAPSD_MASK;
			pregspointer->HSSPI2PADCTRL |= CCM_SWAPDBUS_MASK;
			break;
		case SPI3:
			pregspointer->HSSPI3PADCTRL &= ~CCM_SWAPSD_MASK;
			pregspointer->HSSPI3PADCTRL |= CCM_SWAPDBUS_MASK;
			break;
		default:
			return FALSE;
			break;
	}

	return TRUE;
}


BOOL ccm_eport2swapspi(UINT8 ucspiid)
{
	CCM_REG *pregspointer = (CCM_REG *)(CCM_BASE);

	if( ucspiid > SPI3 )
	{
		return FALSE;
	}

	switch(ucspiid)
	{
		case SPI1:
			pregspointer->HSSPI1PADCTRL &= ~(CCM_SWAPSD_MASK|CCM_SWAPDBUS_MASK);
			pregspointer->HSSPI1PADCTRL |= CCM_SPIINTEN_MASK;
			break;
		case SPI2:
			pregspointer->HSSPI2PADCTRL &= ~(CCM_SWAPSD_MASK|CCM_SWAPDBUS_MASK);
			pregspointer->HSSPI2PADCTRL |= CCM_SPIINTEN_MASK;
			break;
		case SPI3:
			pregspointer->HSSPI3PADCTRL &= ~(CCM_SWAPSD_MASK|CCM_SWAPDBUS_MASK);
			pregspointer->HSSPI3PADCTRL |= CCM_SPIINTEN_MASK;
			break;
		default:
			return FALSE;
			break;
	}

	return TRUE;
}


