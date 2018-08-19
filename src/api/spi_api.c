// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : spi_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "type.h"
#include "spi_drv.h"
#include "spi_reg.h"
#include "edmac_drv.h"
#include "dmac_drv.h"
#include "ccm_drv.h"
#include "spi_api.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_master_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi master mode initialize.
//
// Input:
//    module:
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_master_init(UINT8 ucid, UINT8 ucframemode, UINT8 bauddiv, UINT8 ucssoe )
{
	BOOL	ret_val;
	UINT8	framemode;

	if( ucid == SPI4 )
	{
		ccm_spi4en(1);//enable spi4 port
	}
	else if( ucid > SPI4 )
	{
		return FALSE;
	}

	switch(ucframemode)
	{
		case SPI_CPOL0CPHA0:
			framemode = SPI_FSL_MODE0;
			break;
		case SPI_CPOL0CPHA1:
			framemode = SPI_FSL_MODE1;
			break;
		case SPI_CPOL1CPHA0:
			framemode = SPI_FSL_MODE2;
			break;
		case SPI_CPOL1CPHA1:
			framemode = SPI_FSL_MODE3;
			break;
		case SPI_TIMODE:
			framemode = SPI_TI_MODE;
			break;
		default:
			return FALSE;
			break;
	}

	ret_val = spi_enable(ucid, 0);
	if(ret_val == FALSE)
	{
		return FALSE;
	}

	if( ucssoe == 1 )
	{
		ret_val = spi_config(ucid, (SPI_MASTER|SPI_SSOE), bauddiv, FMSZ4_16(8), framemode, SPI_DFT_GT);
	}
	else
	{
		ret_val = spi_config(ucid, SPI_MASTER, bauddiv, FMSZ4_16(8), framemode, SPI_DFT_GT);
	}

	if(ret_val == FALSE)
	{
		return FALSE;
	}

	ret_val = spi_enable(ucid, 1);
	if(ret_val == FALSE)
	{
		return FALSE;
	}

	return ret_val;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_slave_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi slave mode initialize.
//
// Input:
//    module:
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_slave_init(UINT8 ucid, UINT8 ucframemode )
{
	BOOL	ret_val;

	if( ucid == SPI4 )
	{
		ccm_spi4en(1);//enable spi4 port
	}
	else if( ucid > SPI4 )
	{
		return FALSE;
	}

	ret_val = spi_enable(ucid, 0);
	if(ret_val == FALSE)
	{
		return FALSE;
	}

	ret_val = spi_config(ucid, SPI_SLAVE, SPI_BR_2, FMSZ4_16(8), ucframemode, SPI_DFT_GT);

	if(ret_val == FALSE)
	{
		return FALSE;
	}

	ret_val = spi_enable(ucid, 1);
	if(ret_val == FALSE)
	{
		return FALSE;
	}

	return ret_val;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_readwritebyte
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi read write.
//
// Input:
//    module:
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_readwrite_byte(UINT8 ucid, UINT8 *pwrite, UINT8 *pread, UINT32 uldatalen,UINT8 uctrsmode)
{
	BOOL ret_val;

	if( ucid == SPI4 )
	{
		if( uctrsmode == SPI_EDMACTRANS )
		{
			return FALSE;
		}
		else
		{
			ccm_spi4en(1);//enable spi4 port
		}
	}
	else if( ucid > SPI4 )
	{
		return FALSE;
	}

	switch(uctrsmode)
	{
		case SPI_CPUTRANS:
			ret_val = spi_trans8bit(ucid, pwrite, pread, uldatalen);
			break;
		case SPI_DMACTRANS:
			ret_val = spi_dmacen(ucid, 1);
			ret_val &= dmac_spitrans(ucid, pwrite, pread, uldatalen,0);
			ret_val &= spi_dmacen(ucid, 0);
			break;
		case SPI_EDMACTRANS:
			ret_val = edmac_spitrans(EDMACCH0, ucid, pwrite, pread, uldatalen,0);
			break;
		default:
			ret_val = FALSE;
			break;
	}

	return ret_val;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_sspin_high
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi sspin output high.
//
// Input:
//    module:
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_sspin_high(UINT8 ucid )
{
	BOOL ret_val;

	ret_val = spi_ssout(ucid, 1);

	return ret_val;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 spi_sspin_low
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    spi sspin output low.
//
// Input:
//    module:
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL spi_sspin_low(UINT8 ucid )
{
	BOOL ret_val;

	ret_val = spi_ssout(ucid, 0);

	return ret_val;
}

/*******************************************************************************
* Function Name  : spi_config_gpio
* Description    : SPI���ó�GPIO��;��
*
*                  ע�⣺
*
*                  ʹ��SPI��GPIO����ǰ��Ҫ��֤SPE��־λ�رգ��Ȳ��ܹ�����SPI��ͨ�Ź��ܣ�
*                  ���򣬱��밴���ֲ�Table 18-4�е����Ʒ��������á�
* Input          : - ucid: ȡֵ SPI_ID1, SPI_ID2, SPI_ID3, SPI_ID4.
*                  - pin��SPI��Ӧ��PIN�ţ�ȡֵSPI_MISO��SPI_MOSI��SPI_SCK��SPI_SS.
*                  - dir������GPIO����   GPIO_OUTPUT�����    GPIO_INPUT������
*
* Output         : None
* Return         : TRUE or FALSE
* ******************************************************************************/
BOOL spi_config_gpio(UINT8 ucid, UINT8 pin, UINT8 dir)
{
	BOOL ret_val;

	/*invalid port number*/
	if(ucid > SPI4)
	{
		return	FALSE;
	}

	if(!IS_SPI_PINx(pin))
	{
		return	FALSE;
	}

	ret_val = spi_pin_config(ucid, pin, dir);

	return ret_val;
}

/*******************************************************************************
* Function Name  : spi_read_gpio
* Description    : ��ȡpin��Ӧ���ŵĵ�ƽ
* Input          : - ucid: ȡֵ SPI_ID1, SPI_ID2, SPI_ID3, SPI_ID4.
*                  - pin��SPI��Ӧ��PIN�ţ�ȡֵSPI_MISO��SPI_MOSI��SPI_SCK��SPI_SS.
*
* Output         : None
* Return         : Bit_SET:�ߵ�ƽ  Bit_RESET���͵�ƽ
******************************************************************************/
UINT8 spi_read_gpio(UINT8 ucid, UINT8 pin)
{
	UINT8 val = 0x00;

	/*invalid port number*/
	if(ucid > SPI4)
	{
		return	FALSE;
	}

	if(!IS_SPI_PINx(pin))
	{
		return	FALSE;
	}

	val = spi_pin_read(ucid, pin);

	return val;
}

/*******************************************************************************
* Function Name  : spi_write_gpio
* Description    : ����SPI_Pin��Ӧ���ŵĵ�ƽ
* Input          : - ucid: SPIͨ��ѡ��ȡֵ SPI_ID1, SPI_ID2, SPI_ID3, SPI_ID4.
*                  - pin��SPI��Ӧ��PIN�ţ�ȡֵSPI_MISO��SPI_MOSI��SPI_SCK��SPI_SS.
*                  - val�����õĵ�ƽ��Bit_SET������Ϊ�ߵ�ƽ  Bit_RESET������Ϊ�͵�ƽ
*
* Output         : None
* Return         : TRUE or FALSE
******************************************************************************/
BOOL spi_write_gpio(UINT8 ucid, UINT8 pin, UINT8 val)
{
	BOOL ret_val;

	/*invalid port number*/
	if(ucid > SPI4)
	{
		return	FALSE;
	}

	if(!IS_SPI_PINx(pin))
	{
		return	FALSE;
	}

	ret_val = spi_pin_write(ucid, pin, val);

	return ret_val;
}

