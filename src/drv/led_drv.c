// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : led_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "memmap.h"
#include "led_reg.h"
#include "led_drv.h"

/* internal variables */

/* internal functions */

/* global variables */


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 led_cfg
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    LED configuration.
//
// Input:
//    pin: output pin
//    wd&fd: if wd == 0 or wd == fd, led is always been driven low
//		     if wd == 0xf or wd > fd, led is always been driven high
//           freq = 11.44hz / (fd+1)
//           positive dutycycle:(wd + 1) / (fd + 1)
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void led_cfg(UINT8 pin, UINT32 wd, UINT32 fd)
{
	LED_PER |= ((pin << 4) & 0xF0);
	LED_WDR = wd & 0xF;
	LED_FDR = fd & 0xF;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 led_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    LED enable.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void led_enable(void)
{
	LED_CLK_EN;
	LED_EN;
}

