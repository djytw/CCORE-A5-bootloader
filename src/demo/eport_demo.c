// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eport_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "eport_demo.h"
#include "demo.h"
#include "eport_reg.h"
#include "int_drv.h"
#include "memmap.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Demo of eport.
//    Eport[0:3] are configured as output,
//    meanwhile eport[4:7] are configured as input
//    Any connection between input and output will shown on SCI tool
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_demo(void)
{
	UINT8 i, data;
	BOOL interrupt;

	//mim_cfg_eport();

	interrupt = TRUE;

	// eport0~3 are configured as output with rising-edged interrupt
	for (i = 0; i < 4; i++)
	{
		eport_config(i, EPROT_OUTPUT, interrupt, RISING_EDGE_INT);
	}

	interrupt = FALSE;

	// eport4~7 are configured as input without interrupt
	for (i = 4; i < 8; i++)
	{
		eport_config(i, EPORT_INPUT, interrupt, 0);
	}

	while(1)
	{
		eport_write_data(0x0f, 0x0f);						// eport0~3 output 1
		delay(0x10000);
		data = eport_read_data(0xf0);
		MSG("input data: 0x%x\n", data);
		eport_write_data(0x0f, 0);							// eport0~3 output 0
		delay(0x10000);
		data = eport_read_data(0xf0);
		MSG("input data: 0x%x\n", data);
	}
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 interrupt_nest_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Demo of interrupt nest.
//    eport7_isr has a higher priority than eport6_isr and eport5_isr.
//    eport6_isr has a higher priority than eport5_isr
//    When enter eport6_isr, eport7_isr is also accessible and eport5_isr is not accessible.
//    Any connection between input and output will shown on SCI tool.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void interrupt_nest_demo(void)
{
	MSG("Interrupt nest demo.\n");

	eport_pullup_enable(EPORT_PIN5);		//enable EPORT_PIN5 pull-up
	eport_pullup_enable(EPORT_PIN6);		//enable EPORT_PIN6 pull-up
	eport_pullup_enable(EPORT_PIN7);		//enable EPORT_PIN7 pull-up

	eport_config_isrtype(EPORT_PIN5, LOW_LEVEL_INT);	//low level interrupt
	eport_config_isrtype(EPORT_PIN6, LOW_LEVEL_INT);	//low level interrupt
	eport_config_isrtype(EPORT_PIN7, LOW_LEVEL_INT);	//low level interrupt

	//eport7_isr has a higher priority than eport6_isr and eport5_isr
	//eport6_isr has a higher priority than eport5_isr
	interrupt_setup(EPORT5_ISR_NUM, 2, eport5_isr);
	interrupt_setup(EPORT6_ISR_NUM, 1, eport6_isr);
	interrupt_setup(EPORT7_ISR_NUM, 0, eport7_isr);

	eport_int_enable(EPORT_PIN5);		//EPORT5 interrupt enable
	eport_int_enable(EPORT_PIN6);		//EPORT6 interrupt enable
	eport_int_enable(EPORT_PIN7);		//EPORT7 interrupt enable

	while(1);
}
