// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : mim_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "memmap.h"
#include "debug.h"
#include "mim_reg.h"
#include "mim_drv.h"

/* internal variables */

/* internal functions */

/* global variables */

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 mim_pin_config
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    config pins as gpio.
//
// Input:
//		pin
//		dir
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL mim_pin_config(UINT8 pin, UINT8 dir)
{
	MIM_IOCR |= 0x000F;

	if (dir == GPIO_OUTPUT)
	{
		MIM_GPIODIR |= (1<<pin);		//output
	}
	else if (dir == GPIO_INPUT)
	{
		MIM_GPIODIR &= ~(1<<pin);	//intput
	}
	else
	{
		return FALSE;
	}

	return	TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 mim_pin_read
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    read gpio pins status.
//
// Input:
//		pin
//
// Output:
//      Bit_SET or Bit_RESET
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 mim_pin_read(UINT8 pin)
{
	UINT32  bitstatus = 0x00;

	bitstatus = MIM_GPIODI;
	if (bitstatus&(Bit_SET<<pin))
	{
		return Bit_SET;
	}
	else
	{
		return Bit_RESET;
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 mim_pin_write
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    write pins status.
//
// Input:
//		pin
//		val
//
// Output:
//      TRUE or FALSE
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL mim_pin_write(UINT8 pin, UINT8 val)
{
	if (val == Bit_SET)
	{
		MIM_GPIODO |= (Bit_SET<<pin);
	}
	else
	{
		MIM_GPIODO &= ~(Bit_SET<<pin);
	}

	return TRUE;
}

