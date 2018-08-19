// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : led_reg.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __LED_REG_H__
#define __LED_REG_H__

/* macro definition */

#define LED_PIER				(*(volatile UINT8 *)(LED_BASE + 0x0000))	// SCI baud register
#define LED_WDR					(*(volatile UINT8 *)(LED_BASE + 0x0001))	// SCI baud register high
#define LED_FDR					(*(volatile UINT8 *)(LED_BASE + 0x0002))	// SCI baud register low
#define LED_PER					(*(volatile UINT8 *)(LED_BASE + 0x0003))	// SCI control register1

#define LED_CLK_EN				(LED_PER |= 4)
#define LED_EN					(LED_PER |= 2)

#endif /* __LED_REG_H__ */
