// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : cpm_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "cpm_api.h"
#include "cpm_demo.h"
#include "cpm_reg.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 cpm_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Demo of cpm.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cpm_demo(void)
{
#if 0
	UINT32 arith_mask;
	UINT32 arith_full_mask;
	BOOL clk_status;

	cpm_sysclk_select(SYSCLK_OSC24M);

	cpm_set_sysclk_div(CLK_DIV(10));
	g_sys_clk = 2400000;

	cpm_set_clkout_div(CLK_DIV(2));
	asm("bkpt");

	cpm_clkout_disable();
	asm("bkpt");

	arith_full_mask = 0xffffffff;
	cpm_arith_disable(arith_full_mask);
	clk_status = cpm_arith_clk_status(ARITH_ENCR_A);
	asm("bkpt");

	arith_mask = ARITH_ENCR_A | ARITH_AES | ARITH_SCB2 | ARITH_SMS4;
	cpm_arith_enable(arith_mask);
	clk_status = cpm_arith_clk_status(ARITH_AES);
	asm("bkpt");

	cpm_arith_disable(arith_mask);
	clk_status = cpm_arith_clk_status(ARITH_SCB2);
	asm("bkpt");
#else
	UINT32 system_clock, ips_clock, efm_clock;
	BOOL sysclk_set_result1, sysclk_set_result2, sysclk_set_result3;

	system_clock = cpm_get_sysclk();
	ips_clock = cpm_get_ipsclk();
	efm_clock = cpm_get_efmclk();

	MSG("sysclk:%d, ipsclk:%d, efmclk:%d\n", system_clock, ips_clock, efm_clock);

	sysclk_set_result1 = cpm_set_sysclk(100000000);
	sysclk_set_result2 = cpm_set_sysclk(80000000);
	sysclk_set_result3 = cpm_set_sysclk(40000000);

	if (0 == (sysclk_set_result1 & sysclk_set_result2 & sysclk_set_result3))
		MSG("System clock that you set is not allowed\n");
	MSG("CPM test success\n");
#endif
}
