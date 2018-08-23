// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : cpm_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "includes.h"
#include "memmap.h"
#include "cpm_drv.h"
#include "cpm_reg.h"

/* internal variables */
static UINT8 clk_src;

/* internal functions */
static void osc_enable(UINT8 osc_src);
static void cpm_clk_enable(UINT32 module);
static void cpm_clk_disable(UINT32 module);
static void cpm_arith_clk_enable(UINT32 module);
static void cpm_arith_clk_disable(UINT32 module);
static void cpm_ip_clk_enable(UINT32 module);
static void cpm_ip_clk_disable(UINT32 module);

/* global variables */


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 osc_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Enable OSC source.
//
// Input:
//    osc_src: source.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void osc_enable(UINT8 osc_src)
{
	if (OSC400M == osc_src)
	{
		CPM_OCSR |= (OSC400M_EN);
		while(0 == (CPM_OCSR & OSC400M_STABLE));
	}
	else if (OSC24M == osc_src)
	{
		CPM_OCSR |= (OSC24M_EN);
		while(0 == (CPM_OCSR & OSC24M_STABLE));
	}
	else if (OSC128K == osc_src)
	{
		CPM_OCSR |= (OSC128K_EN);
		while(0 == (CPM_OCSR & OSC128K_STABLE));
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_clk_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Enable module clock.
//
// Input:
//    module: Corresponding clock to be enabled
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void cpm_clk_enable(UINT32 module)
{
	UINT32 cur_data;

	cur_data = CPM_CGTCR;
	cur_data |= module;
	CPM_CGTCR = cur_data;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_clk_disable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Disable module clock.
//
// Input:
//    module: Corresponding clock to be disabled
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void cpm_clk_disable(UINT32 module)
{
	UINT32 cur_data;

	cur_data = CPM_CGTCR;
	cur_data &= ~(module);
	CPM_CGTCR = cur_data;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_arith_clk_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Enable module clock.
//
// Input:
//    module: Corresponding arith_clk  to be enabled
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void cpm_arith_clk_enable(UINT32 module)
{
	UINT32 cur_data;

	cur_data = CPM_ARITHCGTCR;
	cur_data |= module;
	CPM_ARITHCGTCR = cur_data;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_arith_clk_disable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Disable arith clock.
//
// Input:
//    module: Corresponding arith_clk to be disabled
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void cpm_arith_clk_disable(UINT32 module)
{
	UINT32 cur_data;

	cur_data = CPM_ARITHCGTCR;
	cur_data &= ~(module);
	CPM_ARITHCGTCR = cur_data;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_ip_clk_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Enable ip clock.
//
// Input:
//    module: Corresponding ip_clk to be enabled
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void cpm_ip_clk_enable(UINT32 module)
{
	UINT32 cur_data;

	cur_data = CPM_IPSCGTCR;
	cur_data |= module;
	CPM_IPSCGTCR = cur_data;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_ip_clk_disable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Disable ip clock.
//
// Input:
//    module: Corresponding ip_clk to be disabled
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void cpm_ip_clk_disable(UINT32 module)
{
	UINT32 cur_data;

	cur_data = CPM_IPSCGTCR;
	cur_data &= ~(module);
	CPM_IPSCGTCR = cur_data;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    CPM isr.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_isr(void)
{
	//TODO...
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_sysclk_select
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Enable osc_source.
//
// Input:
//    clk_sel: 0:OSC400M
//             1:OSC24M
//             2:OSC128K
//
// Output:
//    Return TRUE if osc select is done, otherwise return FALSE.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL cpm_sysclk_select(UINT8 clk_sel)
{
	if (SYSCLK_OSC400M == clk_sel)
		clk_src = OSC400M;
	else if (SYSCLK_OSC24M == clk_sel)
		clk_src = OSC24M;
	else if (SYSCLK_OSC128K == clk_sel)
		clk_src = OSC128K;
	else
		return FALSE;									// only OSC400MHz\OSC24MHz\OSC128kHz support

	osc_enable(clk_src);

	if (SYSCLK_OSC400M == clk_sel)
	{
		CPM_CSWCFGR |= SYSCLK_SEL;
	}
	else if (SYSCLK_OSC24M == clk_sel)
	{
		CPM_CSWCFGR &= ~(SYSCLK_SEL | LOSC_SEL);
	}
	else if (SYSCLK_OSC128K == clk_sel)
	{
		CPM_CSWCFGR = (CPM_CSWCFGR &~ SYSCLK_SEL) | LOSC_SEL;	//zfj20171214两次赋值合并成两次赋值
	}

	CLK_SWI_UPDATE;										//update switch of clock

	return TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_set_sysclk_div
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Set system clock divider.
//
// Input:
//    divider: divide value equals to 2*(divider+1)
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_set_sysclk_div(UINT8 divider)
{
	CPM_SCDIVR &= ~(SYS_DIV_BITS);
	CPM_SCDIVR |= divider;
	CLK_DIV_UPDATE;										//update divide of clock

	g_sys_clk /= SYS_CLK_DIV;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_set_eptclk_div
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Set ept clock divider.
//
// Input:
//    divider: divide value equals to 2*(divider+1)
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_set_eptclk_div(UINT8 divider)
{
	CPM_SCDIVR &= ~(EPT_DIV_BITS);
	CPM_SCDIVR |= (divider << 8);
	CLK_DIV_UPDATE;										//update divide of clock
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_set_clkout_div
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Set CLKOUT divider.
//
// Input:
//    divider: divide value equals to 2*(divider+1)
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_set_clkout_div(UINT8 divider)
{
	CPM_PCDIVR &= ~(CLKOUT_DIV_BITS);
	CPM_PCDIVR |= (divider << 4);
	CLK_DIV_UPDATE;										//update divide of clock
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_clkout_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Enable clkout.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_clkout_enable(void)
{
	cpm_clk_enable(CLKOUT_CGT);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_clkout_disable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Disable clkout.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_clkout_disable(void)
{
	cpm_clk_disable(CLKOUT_CGT);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_arith_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Enable arith module.
//
// Input:
//    arith_en_mask: mask of ariths to be enabled
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_arith_enable(UINT32 arith_en_mask)
{
	cpm_arith_clk_enable(arith_en_mask);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_arith_disable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Enable all arith module.
//
// Input:
//    arith_dis_mask: mask of ariths to be disabled
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_arith_disable(UINT32 arith_dis_mask)
{
	cpm_arith_clk_disable(arith_dis_mask);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_arith_clk_status
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Return arith module's clock status.
//
// Input:
//    arith_module: arith module
//
// Output:
//    TRUE: if arith module is enable;
//    FALSE: arith module is disable.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL cpm_arith_clk_status(UINT32 arith_module)
{
	if (0 != (CPM_ARITHCGTCR & arith_module))
		return TRUE;
	else
		return FALSE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_ips_clk_divider
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Return ips clock divider, which configured in CPM_PCDIVR.
//
// Input:
//    None
//
// Output:
//    Divider.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 cpm_ips_clk_divider(void)
{
	return IPS_CLK_DIV;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_ip_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Enable ip module.
//
// Input:
//    ip_en_mask: mask of ips to be enabled
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_ip_enable(UINT32 ip_en_mask)
{
	cpm_ip_clk_enable(ip_en_mask);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_ip_disable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Disable ip module.
//
// Input:
//    ip_disable_mask: mask of ips to be disabled
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_ip_disable(UINT32 ip_disable_mask)
{
	cpm_ip_clk_disable(ip_disable_mask);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_ip_clk_status
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Return ips' clock status.
//
// Input:
//    ip_module: ip module
//
// Output:
//    TRUE: if ip module is enable;
//    FALSE: ip module is disable.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL cpm_ip_clk_status(UINT32 ip_module)
{
	if (0 != (CPM_IPSCGTCR & ip_module))
		return TRUE;
	else
		return FALSE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_sysclk
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Return system clock frequence.
//
// Input:
//    None.
//
// Output:
//    System clock.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT32 cpm_sysclk(void)
{
	UINT32 sysclk_raw;

	if (0 != (SYSCLK_SEL & CPM_CSWCFGR))
		sysclk_raw = 400 * 1000 * 1000;
	else if (0 != (LOSC_SEL & CPM_CSWCFGR))
		sysclk_raw = 128 * 1000;
	else
		sysclk_raw = 24 * 1000 * 1000;

	return ((UINT32)(sysclk_raw / SYS_CLK_DIV));
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_ipsclk
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Return ips clock frequence.
//
// Input:
//    None.
//
// Output:
//    IPS clock.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT32 cpm_ipsclk(void)
{
	UINT32 sysclk;

	sysclk = cpm_sysclk();

	return ((UINT32)(sysclk / IPS_CLK_DIV));
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_get_efmclk
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Return efm clock frequence.
//
// Input:
//    None.
//
// Output:
//    IPS clock.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT32 cpm_efmclk(void)
{
	UINT32 sysclk;

	sysclk = cpm_sysclk();

	return ((UINT32)(sysclk / EFM_CLK_DIV));
}
