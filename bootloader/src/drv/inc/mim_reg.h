// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : mim_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __MIM_REG_H__
#define __MIM_REG_H__

/* macro definition */
#define MIM_CSCR0				(*(volatile UINT32*)(MIM_BASE + 0x00))
#define MIM_CSCR1				(*(volatile UINT32*)(MIM_BASE + 0x04))
#define MIM_NPCR				(*(volatile UINT8 *)(MIM_BASE + 0x0E))
#define MIM_IMCR				(*(volatile UINT16*)(MIM_BASE + 0x10))
#define MIM_IOCR				(*(volatile UINT16*)(MIM_BASE + 0x12))

#define MIM_GPIODO				(*(volatile UINT32*)(MIM_BASE + 0x14))
#define MIM_GPIODIR				(*(volatile UINT32*)(MIM_BASE + 0x18))
#define MIM_GPIODI				(*(volatile UINT32*)(MIM_BASE + 0x1C))

/* MIM_CSCR0 */
#define CSEN					(1<<0)
#define WWS						(1<<1)
#define WE						(1<<2)

#define PS_32BITS				(0<<12)
#define PS_8BITS				(1<<12)
#define PS_16BITS				(2<<12)

#define RO						(1<<14)
#define SO						(1<<15)

/* MIM_IOCR */
#define D0_GP0					(1<<0)
#define D1_GP1					(1<<1)
#define D2_GP2					(1<<2)
#define D3_GP3					(1<<3)

#define CS0_SELECT				(MIM_CSCR0 |= CSEN)
#define CS1_SELECT				(MIM_CSCR1 |= CSEN)

#define CS0_DIS_SELECT			(MIM_CSCR0 &= ~CSEN)
#define CS1_DIS_SELECT			(MIM_CSCR1 &= ~CSEN)

#endif /* __MIM_REG_H__ */
