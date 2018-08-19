// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : sci_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "memmap.h"
#include "sci_reg.h"
#include "sci_drv.h"

/* internal variables */

/* internal functions */
BOOL sci_init_dev(UINT8 ucid, UINT32 clk, UINT32 br);
static void sci_putc_dev(volatile const UINT8 c);

/*SCI base address*/
UINT32 const g_sci_baseaddr[SCI_HWNUM] = {SCI1_BASE, SCI2_BASE};

/* global variables */

volatile SCI_REG* pregspointer = 0;		//SCI registers pointer


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sci_init_dev
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    SCI device initialization.
//
// Input:
//    ucid:sic id
//    clk: sci clock frequence.
//    br: baudrate.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL sci_init_dev(UINT8 ucid, UINT32 clk, UINT32 br)
{
	UINT32 baud_rate;

	/*invalid parameters*/
	if ((ucid != SCI1) && (ucid != SCI2))
	{
		return	FALSE;
	}

	pregspointer = (SCI_REG *)(g_sci_baseaddr[ucid]);

	pregspointer->BRDF = (((clk * 8 / br) + 1) / 2) & 0x003f;

	baud_rate = (clk * 4 / br) >> 6;
	pregspointer->BDHL.BDH = (UINT8)((baud_rate >> 8) & 0x00ff);
	pregspointer->BDHL.BDL = (UINT8)(baud_rate & 0x00ff);

 	pregspointer->CR1 = 0x00;
 	pregspointer->CR2 = 0x00;

 	return TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sci_putc_dev
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Send a single byte.
//
// Input:
//    c: byte to be sent.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void sci_putc_dev(volatile const UINT8 c)
{
	if (c == '\n')
		sci_putc_dev('\r');

	SCI_ENABLE_TRANSMITTER;

	while (TC_MASK != (pregspointer->SR1 & TC_MASK))
	{
		;
	}

	pregspointer->DRL = c;

	while (0 == (pregspointer->SR1 & TC_MASK))
	{
		;
	}

	SCI_DISABLE_TRANSMITTER;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sci_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Main function of SCI initialization.
//
// Input:
//    ucid
//    sci_clk
//    baudrate
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL sci_init(UINT8 ucid, UINT32 sci_clk, UINT32 baudrate)
{
	return sci_init_dev(ucid, sci_clk, baudrate);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sci_puts_dev
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Send a string through SCI.
//
// Input:
//    s: string to be sent.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void sci_puts_dev (volatile const UINT8 *s)
{
	while (*s)
		sci_putc_dev (*s++);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sci_send_byte
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Send a single byte.
//
// Input:
//    Data to be sent.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void sci_send_byte(UINT8 outbyte)
{
	SCI_ENABLE_TRANSMITTER;

	while(0 == (pregspointer->SR1 & TDRE_MASK))
	{
		;
	}

	pregspointer->DRL = outbyte;

	while(0 == (pregspointer->SR1 & TC_MASK))
	{
		;
	}

	SCI_DISABLE_TRANSMITTER;

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sci_receive_byte
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Receive a single byte.
//
// Input:
//	  None.
// Output:
//    Received data.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 sci_receive_byte(void)
{
	UINT8 tmp;

	SCI_ENABLE_RECEIVER;

	while(0 == (pregspointer->SR1 & RDRF_MASK));

	tmp = pregspointer->DRL;

	return tmp;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sci_sel_di
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//	  set sci id
//
// Input:
//    ucid:
//
// Output:
//    true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL sci_set_id(UINT8 ucid)
{
	/*invalid parameters*/
	if ((ucid != SCI1) && (ucid != SCI2))
	{
		return	FALSE;
	}

	pregspointer = (SCI_REG *)(g_sci_baseaddr[ucid]);

	return	TRUE;

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sci_pin_config
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    config sci pins as gpio.
//
// Input:
//      ucid
//		pin
//		dir
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL sci_pin_config(UINT8 ucid, UINT8 pin, UINT8 dir)
{
	/*invalid parameters*/
	if ((ucid != SCI1) && (ucid != SCI2))
	{
		return	FALSE;
	}

	pregspointer = (SCI_REG *)(g_sci_baseaddr[ucid]);

	pregspointer->CR1 = 0x80;

	if (dir == GPIO_OUTPUT)
	{
		pregspointer->DDR |= (1<<pin);//output
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
//                 sci_pin_read
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    read sci pins status as gpio.
//
// Input:
//		pin
//
// Output:
//      Bit_SET or Bit_RESET
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 sci_pin_read(UINT8 pin)
{
	INT8 bitstatus = 0x00;

	bitstatus = pregspointer->PORT;

	if (bitstatus &(Bit_SET<<pin))
		bitstatus = Bit_SET;
	else
		bitstatus = Bit_RESET;

	return bitstatus;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sci_pin_write
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    read sci pins status as gpio.
//
// Input:
//		pin
//		val
//
// Output:
//      TRUE or FALSE
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL sci_pin_write(UINT8 pin, UINT8 val)
{
	if (val == Bit_SET)
		pregspointer->PORT |= (Bit_SET<<pin);
	else
		pregspointer->PORT &= (~(Bit_SET<<pin));

	return TRUE;
}

