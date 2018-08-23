// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : int_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __INTERRUPT_REG_H__
#define __INTERRUPT_REG_H__

#include "int_drv.h"
#include "int_reg.h"


#define INTPERI_BASEADDR        ((unsigned int) 0xE0000000)
#define EIC_OFFSET              ((unsigned int) 0x00000000)
#define EIC                     (( eic *) (INTPERI_BASEADDR + EIC_OFFSET))
#define EPT_OFFSET              ((unsigned int) 0x00001000)
#define EPT                     (( ept *) (INTPERI_BASEADDR + EPT_OFFSET))

#define EIC_BASEADDR 0xE0000000

#define PLSRV0  0x00
#define PLSRV1  0x40
#define PLSRV2  0x80
#define PLSRV3  0xC0

#define EIC_ICSR    (EIC_BASEADDR+0x00)    //EIC control & status register
#define EIC_IER     (EIC_BASEADDR+0x10)    //EIC interrupt enable register
#define EIC_IPSR    (EIC_BASEADDR+0x18)    //EIC interrupt pending set register
#define EIC_IPCR    (EIC_BASEADDR+0x1c)    //EIC interrupt pending clear register
#define EIC_PLSGR0  (EIC_BASEADDR+0x40)    //EIC priority register
#define EIC_PLSGR1  (EIC_BASEADDR+0x44)    //EIC priority register
#define EIC_PLSGR2  (EIC_BASEADDR+0x48)    //EIC priority register
#define EIC_PLSGR3  (EIC_BASEADDR+0x4c)    //EIC priority register
#define EIC_PLSGR4  (EIC_BASEADDR+0x50)    //EIC priority register
#define EIC_PLSGR5  (EIC_BASEADDR+0x54)    //EIC priority register
#define EIC_PLSGR6  (EIC_BASEADDR+0x58)    //EIC priority register
#define EIC_PLSGR7  (EIC_BASEADDR+0x5c)    //EIC priority register
#define EIC_SYSPLSR (EIC_BASEADDR+0x60)    //SYS priority register

#define EIC_ICSR_WRITE(val)   *(volatile UINT32 *) (EIC_ICSR  ) = val
#define EIC_IER_WRITE(val)    *(volatile UINT32 *) (EIC_IER   ) = val
#define EIC_IPSR_WRITE(val)   *(volatile UINT32 *) (EIC_IPSR  ) = val
#define EIC_IPCR_WRITE(val)   *(volatile UINT32 *) (EIC_IPCR  ) = val
#define EIC_PLSGR0_WRITE(val) *(volatile UINT32 *) (EIC_PLSGR0) = val
#define	EIC_PLSGR1_WRITE(val) *(volatile UINT32 *) (EIC_PLSGR1) = val
#define	EIC_PLSGR2_WRITE(val) *(volatile UINT32 *) (EIC_PLSGR2) = val
#define	EIC_PLSGR3_WRITE(val) *(volatile UINT32 *) (EIC_PLSGR3) = val
#define	EIC_PLSGR4_WRITE(val) *(volatile UINT32 *) (EIC_PLSGR4) = val
#define	EIC_PLSGR5_WRITE(val) *(volatile UINT32 *) (EIC_PLSGR5) = val
#define	EIC_PLSGR6_WRITE(val) *(volatile UINT32 *) (EIC_PLSGR6) = val
#define	EIC_PLSGR7_WRITE(val) *(volatile UINT32 *) (EIC_PLSGR7) = val
#define EIC_SYSPLSR_WRITE(val) *(volatile UINT32 *) (EIC_SYSPLSR) = val

#define EIC_ICSR_READ(val)   val = *(volatile UINT32 *) (EIC_ICSR  )
#define EIC_IER_READ(val)    val = *(volatile UINT32 *) (EIC_IER   )
#define EIC_IPSR_READ(val)   val = *(volatile UINT32 *) (EIC_IPSR  )
#define EIC_IPCR_READ(val)   val = *(volatile UINT32 *) (EIC_IPCR  )
#define EIC_PLSGR0_READ(val) val = *(volatile UINT32 *) (EIC_PLSGR0)
#define	EIC_PLSGR1_READ(val) val = *(volatile UINT32 *) (EIC_PLSGR1)
#define	EIC_PLSGR2_READ(val) val = *(volatile UINT32 *) (EIC_PLSGR2)
#define	EIC_PLSGR3_READ(val) val = *(volatile UINT32 *) (EIC_PLSGR3)
#define	EIC_PLSGR4_READ(val) val = *(volatile UINT32 *) (EIC_PLSGR4)
#define	EIC_PLSGR5_READ(val) val = *(volatile UINT32 *) (EIC_PLSGR5)
#define	EIC_PLSGR6_READ(val) val = *(volatile UINT32 *) (EIC_PLSGR6)
#define	EIC_PLSGR7_READ(val) val = *(volatile UINT32 *) (EIC_PLSGR7)
#define EIC_SYSPLSR_READ(val) val = *(volatile UINT32 *) (EIC_SYSPLSR)


////priority
//#define PRIORITY0	(0x00<<6)
//#define PRIORITY1	(0x01<<6)
//#define PRIORITY2	(0x02<<6)
//#define PRIORITY3	(0x03<<6)
//
//#define EIC_BASEADDR	0xE0000000
//
//#define EIC_ICSR 			(EIC_BASEADDR|0x00)
//#define EIC_IER				(EIC_BASEADDR|0x10)
//
////interrupt pend set register
//#define EIC_IPSR		(EIC_BASEADDR|0x18)
////interrut pend clear register
//#define EIC_IPCR		(EIC_BASEADDR|0x1C)

//priority level select registers

#define PLSR				(EIC_BASEADDR|0x40)
#if 0
#define PLSR0_3				(EIC_BASEADDR|0x40)
#define PLSR4_7				(EIC_BASEADDR|0x44)
#define PLSR8_11			(EIC_BASEADDR|0x48)
#define PLSR12_15			(EIC_BASEADDR|0x4C)
#define PLSR16_19			(EIC_BASEADDR|0x50)
#define PLSR20_23			(EIC_BASEADDR|0x54)
#define PLSR24_27			(EIC_BASEADDR|0x58)
#define PLSR28_31			(EIC_BASEADDR|0x5C)
#endif
//system priority level select register 
#define SYS_PRIORITY_LEVEL_SELECT	(EIC_BASEADDR|0x60)

//bit define
#define bit31 0x80000000
#define bit30 0x40000000
#define bit29 0x20000000
#define bit28 0x10000000
#define bit27 0x08000000
#define bit26 0x04000000
#define bit25 0x02000000
#define bit24 0x01000000
#define bit23 0x00800000
#define bit22 0x00400000
#define bit21 0x00200000
#define bit20 0x00100000
#define bit19 0x00080000
#define bit18 0x00040000
#define bit17 0x00020000
#define bit16 0x00010000
#define bit15 0x00008000
#define bit14 0x00004000
#define bit13 0x00002000
#define bit12 0x00001000
#define bit11 0x00000800
#define bit10 0x00000400
#define bit09 0x00000200
#define bit08 0x00000100
#define bit07 0x00000080
#define bit06 0x00000040
#define bit05 0x00000020
#define bit04 0x00000010
#define bit03 0x00000008
#define bit02 0x00000004
#define bit01 0x00000002
#define bit00 0x00000001

//PSR bit
#define PSR_S bit31
//#define PSR_SP bint29+bit28

#define PSR_VEC bit22+bit21+bit20+bit19+bit18+bit17+bit16
//#define TM bit15+bit14
//#define TP bit13
//#define TCTL bit12
//#define SC bit10
//#define MM bit09
#define EE bit08
//#define IC bit07
#define IE bit06
//#define FE bit04
//#define AF bit01
#define C bit00

#define VECTOR_OFFSET	32

//core interrupt
#define Enable_Interrupts Write_PSR(Read_PSR() | EE | IE)
#define Disable_Interrupts Write_PSR(Read_PSR() & ~EE & ~IE)

#define Clear_VBR Write_VBR((Read_VBR() & 0) | 0x00801000)
//#define Clear_VBR Write_VBR((Read_VBR() & 0))

#define INTERRUPT_SOURCE_SCI1			31
#define INTERRUPT_SOURCE_SD_EMMC		27
#define INTERRUPT_SOURCE_USI3			26
#define INTERRUPT_SOURCE_USB			25
#define INTERRUPT_SOURCE_RTC			24
#define INTERRUPT_SOURCE_USI2			23
#define INTERRUPT_SOURCE_EFM			22
#define INTERRUPT_SOURCE_I2C			21
#define INTERRUPT_SOURCE_SCI2			20
#define INTERRUPT_SOURCE_PIT2			19
#define INTERRUPT_SOURCE_MPU			17
#define INTERRUPT_SOURCE_AES			15
#define INTERRUPT_SOURCE_SPI1_SPI4		14
#define INTERRUPT_SOURCE_USI1			13
#define INTERRUPT_SOURCE_EPORT7			12
#define INTERRUPT_SOURCE_EPORT6			11
#define INTERRUPT_SOURCE_EPORT5			10
#define INTERRUPT_SOURCE_EPORT4			9
#define INTERRUPT_SOURCE_EPORT3			8
#define INTERRUPT_SOURCE_EPORT2			7
#define INTERRUPT_SOURCE_EPORT1			6
#define INTERRUPT_SOURCE_EPORT0			5
#define INTERRUPT_SOURCE_DMA			4
#define INTERRUPT_SOURCE_SPI			3
#define INTERRUPT_SOURCE_PIT			2
#define INTERRUPT_SOURCE_CPM			1
#define INTERRUPT_SOURCE_RSA			0


#endif  /* __INTERRUPT_REG_H__ */
