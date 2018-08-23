// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : cpm_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "cpm_api.h"

#define CLK_SRC			400 * 1000 * 1000	// system clock maximum 400MHz

/* internal variables */

/* internal functions */

/* global variables */
UINT32 g_sys_clk;		                    // system clock frequence
UINT32 g_ips_clk;							// peripheral ips' clock frequence
UINT32 g_efm_clk;							// Eflash's clock frequence

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_get_sysclk
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
UINT32 cpm_get_sysclk(void)
{
	return(cpm_sysclk());
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_get_ipsclk
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
UINT32 cpm_get_ipsclk(void)
{
	return (cpm_ipsclk());
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
//    EFM clock.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT32 cpm_get_efmclk(void)
{
	return (cpm_efmclk());
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_set_sysclk
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Set system clock frequence.
//
// Input:
//    sys_clk, system clock.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL cpm_set_sysclk(UINT32 sys_clk)
{
	UINT32 div;

	div = (CLK_SRC / sys_clk);

	if ((0 == (CLK_SRC % sys_clk) && (0 == (div % 2))))
	{
		cpm_sysclk_select(SYSCLK_OSC400M);
		cpm_set_sysclk_div(CLK_DIV(div));
		return TRUE;
	}

	else
		return FALSE;


}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Initialize global variables in CPM module.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_init(void)
{
	cpm_set_sysclk(100000000);
	g_sys_clk = cpm_get_sysclk();
	g_ips_clk = cpm_get_ipsclk();
	g_efm_clk = cpm_get_efmclk();
}
