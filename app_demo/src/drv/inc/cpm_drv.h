// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : cpm_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef	__CPM_DRV_H__
#define	__CPM_DRV_H__
#include "type.h"

/* macro definition */
#define EFLASH_SYS_CLK_20M			(20000)
#define EFLASH_SYS_CLK_32M			(32000)
#define EFLASH_SYS_CLK_40M			(40000)
#define EFLASH_SYS_CLK_64M			(64000)
#define EFLASH_SYS_CLK_80M			(80000)

#define SYSCLK_OSC400M				0
#define SYSCLK_OSC24M				1
#define SYSCLK_OSC128K				2

#define ARITH_ENCR_A				0x0001
#define ARITH_AES					0x0002
#define ARITH_SCB2					0x0004
#define ARITH_SMS4					0x0008
#define ARITH_SSF33					0x0010
#define ARITH_CRYPTO				0x0020
#define ARITH_SHA					0x0040
#define ARITH_DES3					0x0080
#define ARITH_RFIFO					0x0100

#define IP_EFM_APB					0x00000001
#define IP_WDT						0x00000002
#define IP_TRNG						0x00000004
#define IP_PIT1						0x00000008
#define IP_PIT2						0x00000010
#define IP_LED						0x00000020
#define IP_LD						0x00000040
#define IP_PGD						0x00000080
#define IP_SPI4						0x00000100
#define IP_SEC_DET					0x00000200
#define IP_TC						0x00000400
#define IP_SWP						0x00000800
#define IP_USI1						0x00001000
#define IP_USI2						0x00002000
#define IP_USI3						0x00004000
#define IP_I2C						0x00008000
#define IP_SCI1						0x00010000
#define IP_SCI2						0x00020000
#define IP_EPORT					0x00040000
#define IP_SPI1						0x00080000
#define IP_SPI2						0x00100000
#define IP_SPI3						0x00200000
#define IP_ENCT_P					0x00400000
#define IP_EPORT2					0x00800000
#define IP_IOMUX_APB				0x01000000
#define IP_IPS_BUS					0x02000000

#define CLK_DIV(n)					((n - 2) / 2)

/* data structure */

/* global variables declaration */
extern UINT32 g_sys_clk;
extern UINT32 g_ips_clk;

/* functions declaration */
extern void cpm_isr(void);

extern BOOL cpm_sysclk_select(UINT8 clk_sel);

extern void cpm_set_sysclk_div(UINT8 divider);
extern void cpm_set_eptclk_div(UINT8 divider);
extern void cpm_set_clkout_div(UINT8 divider);

extern void cpm_clkout_enable(void);
extern void cpm_clkout_disable(void);

extern void cpm_arith_enable(UINT32 arith_en_mask);
extern void cpm_arith_disable(UINT32 arith_dis_mask);
extern BOOL cpm_arith_clk_status(UINT32 arith_module);

extern UINT8 cpm_ips_clk_divider(void);
extern void cpm_ip_enable(UINT32 ip_en_mask);
extern void cpm_ip_disable(UINT32 ip_disable_mask);
extern BOOL cpm_ip_clk_status(UINT32 ip_module);

extern UINT32 cpm_sysclk(void);
extern UINT32 cpm_ipsclk(void);
extern UINT32 cpm_efmclk(void);

#endif	/* __CPM_DRV_H__ */







