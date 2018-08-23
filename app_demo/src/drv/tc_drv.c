// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : tc_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "tc_drv.h"
#include "tc_reg.h"

static UINT32 tc_tick = 0;

void tc_isr(void)
{
	TCCR |= TC_IF;
	tc_tick++;
	MSG("TC INT\r\n");
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 tc_reset_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    configuration for TC RESET system.
//
// Input:
//    wdp: prescaler of TC counter.
//    tcmr: reload value of TC when fed.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void tc_reset_init(TC_TIMER_PRESCALER wdp, UINT16 tcmr)
{
	UINT16 temp;

	TCMR = tcmr;
	temp = TCCR;
	temp &= (~0x7f);
	TCCR = temp|TC_RN|(wdp<<TC_WDP_SHIFT);
	TCCR |= TC_CU;
	MSG("TCCR=[%04x]\n",TCCR);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 tc_int_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    configuration for TC interrupt setting.
//
// Input:
//    wdp: prescaler of TC counter.
//    tcmr: reload value of TC when fed.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void tc_int_init(TC_TIMER_PRESCALER wdp, UINT16 tcmr)
{
	UINT16 temp;

	interrupt_setup(TC_INT_NUM, 0x00, tc_isr);
	TCMR = tcmr;
	temp = TCCR;
	temp &= (~0x7f);
	TCCR = temp|TC_IE|(wdp<<TC_WDP_SHIFT);
	TCCR |= TC_CU;
	MSG("TCCR=[%04x]\n",TCCR);
}

void tc_feed(void)
{
	TCSR = 0x5555;
	TCSR = 0xAAAA;
}

UINT32 tc_get_tick(void)
{
	return tc_tick;
}


UINT16 tc_get_remainCount(void)
{
   return TCCNTR;
}
