// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : ept_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "includes.h"
#include "ept_drv.h"
#include "ept_reg.h"

void ept_isr(void)
{
	MSG("EPT isr.\r\n");
	//MSG("-1-EPTCSR: %08x\r\n", EPTCSR);
	IO_WRITE32(EPT_CNT, 0x00);
	//MSG("-2-EPTCSR: %08x\r\n", EPTCSR);
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 ept_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    init Embedded Programmable Timer bulit-in C0 CORE.
//
// Input:
//    eptClk: clk source selection.
//    eptInt: enable Interrupt or Not
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ept_init(EPT_CLK eptClk, EPT_INT eptInt)
{
	IO_WRITE32(EPT_CSR, eptClk|eptInt|EPT_CNTEN);
}


void ept_RLD_set(UINT32 rldVal)
{
	IO_WRITE32(EPT_RLD, rldVal);
}

UINT32 ept_cnt_get()
{
	return IO_READ32(EPT_CNT);
}
