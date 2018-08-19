// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eport_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "eport_api.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_config
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Configure eport.
//
// Input:
//    eport_num: eport pin number
//    direction: 0:input;
//               1:output.
//    interrupt: interrupt mode or not
//    int_mode: interrupt type
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_config(UINT8 eport_num, UINT8 direction, BOOL interrupt, EPORT_INT_MODE int_mode)
{

	if (TRUE == interrupt)
	{
		eport_init_int(eport_num);
		eport_config_isrtype(eport_num, int_mode);
		eport_int_enable(eport_num);
	}

	eport_make_dir(eport_num, direction);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_write_port_data
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Write eport port output data(single pin).
//
// Input:
//    eport_num: eport number
//    data: data to output
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_write_port_data(UINT8 eport_num, UINT8 data)
{
	eport_write_val(eport_num, data);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_read_port_data
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Read eport port input data(single pin).
//
// Input:
//    eport_num: eport number
//
// Output:
//    Get eport input data.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 eport_read_port_data(UINT8 eport_num)
{
	return (eport_read_val(eport_num));
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_write_data
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Write eport output data.
//
// Input:
//    eport_mask: eport number mask
//    data: data to output
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_write_data(UINT8 eport_mask, UINT8 data)
{
	UINT8 i, pin_data;

	for (i = 0; i < 8; i++) {
		if (0 != (eport_mask & (1 << i)))
		{
			pin_data = ((data >> i) & 0x01);
			eport_write_val(i, pin_data);
		}
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_read_data
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Read eport input data.
//
// Input:
//    eport_mask: eport number mask
//
// Output:
//    Get eport input data.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 eport_read_data(UINT8 eport_mask)
{
	UINT8 i, data;

	data = 0;

	for (i = 0; i < 8; i++)
	{
		if (0 != (eport_mask & (1 << i)))
		{
			data |= (eport_read_val(i) << i);
		}
	}

	return data;
}
