// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : crc_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "crc_reg.h"
#include "crc_drv.h"
#include "memmap.h"
#include "includes.h"


BOOL crc0_get_lasterr()
{
	if(((AHB_CRC_CR)&(CRC_LATERR)) == CRC_LATERR)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL crc1_get_lasterr()
{
	if(((AHB_CRC1_CR)&(CRC_LATERR)) == CRC_LATERR)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL crc0_get_status()
{
	if( ((AHB_CRC_CR)&(CRC_OK)) == CRC_OK )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


BOOL crc1_get_status()
{
	if( ((AHB_CRC1_CR)&(CRC_OK)) == CRC_OK )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void crc0_init(UINT32 ulval)
{
	AHB_CRC_INI = ulval;
	AHB_CRC_CR |= CLEAR;
}

void crc1_init(UINT32 ulval)
{
	AHB_CRC1_INI = ulval;
	AHB_CRC1_CR |= CLEAR;
}

void crc0_crconfig(UINT32 ulcrreg)
{
	AHB_CRC_CR = ulcrreg;
}

void crc1_crconfig(UINT32 ulcrreg)
{
	AHB_CRC1_CR = ulcrreg;
}

void crc_mode_config(UINT8 crc_mode)
{
	if (0 == crc_mode)				// crc 8 bits mode
		CRC_CTRL = CRC8;
	else if (1 == crc_mode)			// crc 16 bits mode
		CRC_CTRL = CRC16;
	else if (2 == crc_mode)			// crc 32 bits mode
		CRC_CTRL = CRC32;
}

void crc_swap_config(BOOL byte_swap)
{
	if (TRUE == byte_swap)
		CRC_CTRL |= BYTESWAP;
	else
		CRC_CTRL &= ~BYTESWAP;
}

void crc_init_update(UINT32 init_data)
{
	CRC_INIT_DATA = init_data;
	CRC_CTRL |= UPDATA;
}

void crc_input(UINT32 data)
{
	CRC_DATA_IN = data;
}

UINT32 crc_get_result(void)
{
	return CRC_RESULT;
}
