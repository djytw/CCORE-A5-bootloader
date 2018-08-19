// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : cpm_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __CPM_REG_H__
#define __CPM_REG_H__

#include "memmap.h"

/* macro definition */
#define CPM_SLPCFGR				(*(volatile UINT32*)(CPM_BASE + 0x00))
#define CPM_SLPCR				(*(volatile UINT32*)(CPM_BASE + 0x04))
#define CPM_SCDIVR				(*(volatile UINT32*)(CPM_BASE + 0x08))
#define CPM_PCDIVR				(*(volatile UINT32*)(CPM_BASE + 0x0C))

#define CPM_OCSR				(*(volatile UINT32*)(CPM_BASE + 0x10))
#define CPM_CSWCFGR				(*(volatile UINT32*)(CPM_BASE + 0x14))
#define CPM_CSWUPDR				(*(volatile UINT32*)(CPM_BASE + 0x18))

#define CPM_CGTCR				(*(volatile UINT32*)(CPM_BASE + 0x20))
#define CPM_SYSCGTCR			(*(volatile UINT32*)(CPM_BASE + 0x24))
#define CPM_ARITHCGTCR			(*(volatile UINT32*)(CPM_BASE + 0x28))
#define CPM_IPSCGTCR			(*(volatile UINT32*)(CPM_BASE + 0x2C))

#define CPM_PWRCR				(*(volatile UINT32*)(CPM_BASE + 0x30))
#define CPM_SLPCNTR				(*(volatile UINT32*)(CPM_BASE + 0x34))
#define CPM_WKPCNTR				(*(volatile UINT32*)(CPM_BASE + 0x38))
#define CPM_SRSTMASKR			(*(volatile UINT32*)(CPM_BASE + 0x3C))

#define CPM_VCCQLTRIMR			(*(volatile UINT32*)(CPM_BASE + 0x44))
#define CPM_VCCQVTRIMR      	(*(volatile UINT32*)(CPM_BASE + 0x48))

#define CPM_OSCLSTIMER      	(*(volatile UINT32*)(CPM_BASE + 0x70))
#define CPM_OSCHSTIMER      	(*(volatile UINT32*)(CPM_BASE + 0x74))
#define CPM_STABLE       		(*(volatile UINT32*)(CPM_BASE + 0x78))
#define CPM_PWRSR				(*(volatile UINT32*)(CPM_BASE + 0x7C))

#define CPM_MULTISRSTMR			(*(volatile UINT32*)(CPM_BASE + 0x80))
#define CPM_SYSSRSTMR			(*(volatile UINT32*)(CPM_BASE + 0x84))
#define CPM_ARITHSRSTMR			(*(volatile UINT32*)(CPM_BASE + 0x88))
#define CPM_IPSSRSTMR			(*(volatile UINT32*)(CPM_BASE + 0x8C))

#define CPM_CSWSSR				(*(volatile UINT32*)(CPM_BASE + 0x90))
#define CPM_FILTCNTR			(*(volatile UINT32*)(CPM_BASE + 0x94))
#define CPM_HIBERCNTR			(*(volatile UINT32*)(CPM_BASE + 0x98))
#define CPM_WKPCSR				(*(volatile UINT32*)(CPM_BASE + 0x9C))

#define CPM_MPDSLPCR			(*(volatile UINT32*)(CPM_BASE + 0xA0))
#define CPM_APDSLPCR			(*(volatile UINT32*)(CPM_BASE + 0xA4))
#define CPM_LVDTFILTCNTR		(*(volatile UINT32*)(CPM_BASE + 0xA8))
#define CPM_PWRINDICR			(*(volatile UINT32*)(CPM_BASE + 0xAC))

#define CPM_LPWKPSCR			(*(volatile UINT32*)(CPM_BASE + 0xB0))
#define CPM_LPWKPSSR			(*(volatile UINT32*)(CPM_BASE + 0xB4))
#define CPM_POFFWKPSCR			(*(volatile UINT32*)(CPM_BASE + 0xB8))
#define CPM_POFFWKPSSR			(*(volatile UINT32*)(CPM_BASE + 0xBC))

/* CPM_PWRCR */
#define CPM_PWRCR_SD_PWSEL_BIT		BIT(16)

/* CPM_SCDIVR */
#define SYS_DIV_BITS			0xf
#define SLP_SYS_DIV_BITS		0xf0
#define EPT_DIV_BITS			0xf00
#define XSTP_DIV_BITS			0xf000

/* CPM_PCDIVR */
#define IPS_DIV_BITS			0xf
#define CLKOUT_DIV_BITS			0xf0
#define ARITH_DIV_BITS			0xf00
#define EFM_DIV_BITS			0xf000
#define INT_DIV_BITS			0xf0000
#define LED_DIV_BITS			0xf00000
#define TC_DIV_BITS				0xf000000
#define DET_DIV_BITS			0xf0000000

/* CPM_OSCR */
#define OSC24M_EN				(1<<0)
#define OSC128K_EN				(1<<1)
#define OSC400M_EN				(1<<2)
#define OSCEXT_EN				(1<<4)
#define OSC24M_STABLE			(1<<8)
#define OSC128K_STABLE			(1<<9)
#define OSC400M_STABLE			(1<<10)
#define OSCEXTM_STABLE			(1<<12)

/* CPM_CSWCFGR */
#define SYSCLK_SEL				(1<<0)
#define TCCLK_SEL				(1<<2)
#define DETCLK_SEL				(1<<3)
#define LOSC_SEL				(1<<4)
#define ARITH_DIVSEL			(1<<8)
#define TC_DIVSEL				(1<<10)
#define DET_DIVSEL				(1<<11)
#define IPS_DIVSEL				(1<<12)
#define EFM_DIVSEL				(1<<13)

#define CLKOUT_SRC_OSC24M		(0<<24)
#define CLKOUT_SRC_OSC128K		(1<<24)
#define CLKOUT_SRC_OSC400M		(2<<24)
#define CLKOUT_SRC_OSCEXT		(4<<24)
#define CLKOUT_SRC_OSC2K		(5<<24)
#define CLKOUT_SRC_USBPHY		(6<<24)
#define CLKOUT_SRC_PADSD		(7<<24)

#define PORCLK_GTE_ENABLE		(1<<28)
#define XSTP_EN					(1<<29)
#define XSTP_SRC_SEL			(0<<30)
#define CLKOUT_SRC_SEL			(1<<31)

/* CPM_IPSCGTCR */
#define EFM_APB_GTE				(1<<0)
#define WDT_GTE					(1<<1)
#define TRNG_GTE				(1<<2)
#define PIT1_GTE				(1<<3)
#define PIT2_GTE				(1<<4)
#define LED_GTE					(1<<5)
#define LD_GTE					(1<<6)
#define PGD_GTE					(1<<7)
#define SPI4_GTE				(1<<8)
#define SEC_DET_GTE				(1<<9)
#define TC_GTE					(1<<10)
#define SWP_GTE					(1<<11)
#define USI1_GTE				(1<<12)
#define USI2_GTE				(1<<13)
#define USI3_GTE				(1<<14)
#define I2C_GTE					(1<<15)
#define SCI1_GTE				(1<<16)
#define SCI2_GTE				(1<<17)
#define EPORT_GTE				(1<<18)
#define SPI1_GTE				(1<<19)
#define SPI2_GTE				(1<<20)
#define SPI3_GTE				(1<<21)
#define ENCT_P_GTE				(1<<22)
#define EPORT2_GTE				(1<<23)
#define IOMUX_APB				(1<<24)
#define IPS_BUS_GTE				(1<<25)

/* CPM_VCCQLTRIMR */
#define VD_PWRSEL_MASK			(1<<31)

/* CPM_CSWUPDR */
#define DIVUPD					(1<<1)
#define CSWUPD					(1<<0)

/* CPM_CGTCR */
#define CPM_CGT					(1<<0)
#define PWR_CGT					(1<<1)
#define EMMC_CGT				(1<<2)
#define EMMC_PAD_CGT			(1<<3)
#define USBPHY_REF_CGT			(1<<4)
#define USBPHY_X_CGT			(1<<5)
#define TC_CGT					(1<<6)
#define DET_CGT					(1<<7)
#define SWP_DECODE_CGT			(1<<11)
#define INIT_CGT				(1<<12)
#define LED_CGT					(1<<13)
#define EFM_AHB_CGT				(1<<14)
#define CLKOUT_CGT				(1<<15)
#define HIBER_CGT				(1<<16)
#define USBC_CGT				(1<<17)
#define MPU_CGT					(1<<18)
#define ROM_CGT					(1<<19)
#define ROM_CODE_CGT			(1<<20)

/* CPM_CSWDSR */
#define IPSDIV_SWD				(1<<12)

/* CPM_ARITHCGTCR */
#define ENCR_A_CGT				(1<<0)
#define AES_CGT					(1<<1)
#define SCB2_CGT				(1<<2)
#define SMS4_CGT				(1<<3)
#define SSF33_CGT				(1<<4)
#define CRYPTO_CGT				(1<<5)
#define SHA_CGT					(1<<6)
#define DES3_CGT				(1<<7)
#define RFIFO_CGT				(1<<8)

#define PWRCR_PHY_PSWEN_BIT			(24)
#define PWRCR_PHY_RSTMASK_BIT		(25)
#define PWRCR_PHY_O_ISOEN_BIT		(26)
#define PWRCR_PHY_I_ISOEN_BIT		(27)

#define CLK_SWI_UPDATE			(CPM_CSWUPDR |= CSWUPD); \
								delay(100)

#define CLK_DIV_UPDATE			(CPM_CSWUPDR |= DIVUPD); \
								delay(100)

#define SYS_CLK_DIV				(((CPM_SCDIVR & SYS_DIV_BITS) + 1) * 2)
#define IPS_CLK_DIV				(((CPM_PCDIVR & IPS_DIV_BITS) + 1) * 2)
#define EFM_CLK_DIV				((((CPM_PCDIVR & EFM_DIV_BITS) >> 12) + 1) * 2)

/* internal data structure */
typedef enum _CLK_SRC_SEL_ {
	OSC400M = 0,
	OSC24M,
	OSC128K
} CLK_SRC_SEL, *P_CLK_SRC_SEL;

#endif /* __CPM_REG_H__ */
