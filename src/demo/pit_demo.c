// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : pit_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "pit_demo.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 pit_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Demo of pit.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pit_demo(void)
{
	FP32 time1, time2;

	cpm_ip_enable(IP_PIT1);

	eport_config(0, EPROT_OUTPUT, FALSE, 0);

	//eport_write_val(0, 0);

	pit_init(PIT_1, g_ips_clk, PIT_CLK_DIV_32, MS(1));			// divider = 32, period = 10ms
	//pit_init(PIT_1, 21140000, PIT_CLK_DIV_32, MS(1));			// divider = 32, period = 1ms

	delay(0x500);

	eport_write_val(0, 0);

	pit_time_start(PIT_1);

	delay(0x50000);

	time1 = pit_get_past_time(PIT_1);

	eport_write_val(0, 1);

	//MSG("time:%f\n", time);

	pit_time_start(PIT_1);

	delay(0x150000);

	time2 = pit_get_past_time(PIT_1);

	eport_write_val(0, 0);

	MSG("time1:%f\n", time1);
	MSG("time2:%f\n", time2);

//	asm("bkpt");

	//while(1);
}
