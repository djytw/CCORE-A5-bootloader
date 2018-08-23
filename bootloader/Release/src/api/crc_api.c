// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : crc_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "crc_api.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 crc_calc
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Calculate CRC.
//
// Input:
//    p_crc_data: data to be calculated
//    crc_data_length: data length
//    crc_init_data: CRC initial data
//    crc_mode: CRC mode: 8/16/32 bits
//    swap_mode: byte swap, TRUE for default
//
// Output:
//    CRC value.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT32 crc_calc(UINT8 *p_crc_data, UINT32 crc_data_length, UINT32 crc_init_data, UINT8 crc_mode, UINT8 swap_mode)
{
	UINT32 i, data_temp;
	void *p_data_buf;

	p_data_buf = (void *)p_crc_data;

	crc_mode_config(crc_mode);
	crc_swap_config(TRUE);					// byte swap should always be true in default
	crc_init_update(crc_init_data);

	if (CRC_8 == crc_mode)
	{
		for (i = 0; i < crc_data_length; i++)
			crc_input(*((UINT8 *)(p_data_buf + i)));
		return (crc_get_result());
	}

	else if (CRC_16 == crc_mode)
	{
		if (0 == (crc_data_length % 2))
		{
			for (i = 0; i < crc_data_length; i += 2)
				crc_input(*((UINT16 *)(p_data_buf + i)));
		}
		else
		{
			for (i = 0; i < crc_data_length - 1; i += 2)
				crc_input(*((UINT16 *)(p_data_buf + i)));
			data_temp = *((UINT16 *)(p_data_buf + i)) & 0xff;
			crc_input(data_temp);
		}
		return (crc_get_result());
	}

	else //if (CRC_32 == crc_mode)
	{
		if (0 == (crc_data_length % 4))
		{
			for (i = 0; i < crc_data_length; i += 4)
				crc_input(*((UINT32 *)(p_data_buf + i)));
		}

		else if (1 == (crc_data_length % 4))
		{
			for (i = 0; i < crc_data_length - 1; i += 4)
				crc_input(*((UINT32 *)(p_data_buf + i)));
			data_temp = *((UINT32 *)(p_data_buf + i)) & 0xff;
			crc_input(data_temp);
		}

		else if (2 == (crc_data_length % 4))
		{
			for (i = 0; i < crc_data_length - 2; i += 4)
				crc_input(*((UINT32 *)(p_data_buf + i)));
			data_temp = *((UINT32 *)(p_data_buf + i)) & 0xffff;
			crc_input(data_temp);
		}

		else //if (3 == (crc_data_length % 4))
		{
			for (i = 0; i < crc_data_length - 3; i += 4)
				crc_input(*((UINT32 *)(p_data_buf + i)));
			data_temp = *((UINT32 *)(p_data_buf + i)) & 0xffffff;
			crc_input(data_temp);
		}
		return (crc_get_result());
	}
}
