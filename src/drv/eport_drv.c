// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eport_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "demo.h"
#include "includes.h"
#include "memmap.h"
#include "int_drv.h"
#include "eport_reg.h"
#include "eport_drv.h"

/* internal variables */
static EPORT_ISR_SET eport_isr_set[8] = {
	{EPORT0_ISR_NUM, 0, eport0_isr},
	{EPORT1_ISR_NUM, 1, eport1_isr},
	{EPORT2_ISR_NUM, 2, eport2_isr},
	{EPORT3_ISR_NUM, 3, eport3_isr},
	{EPORT4_ISR_NUM, 4, eport4_isr},
	{EPORT5_ISR_NUM, 5, eport5_isr},
	{EPORT6_ISR_NUM, 6, eport6_isr},
	{EPORT7_ISR_NUM, 7, eport7_isr}
};

/* internal functions */

/* global variables */


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport0_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Eport0 ISR.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport0_isr(void)
{
	EPORT_EPFR = 0x01;			//clear flag by writing 1 to it.
	//MSG("Enter eport0 interrupt.\r\n");
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport1_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Eport1 ISR.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport1_isr(void)
{
	EPORT_EPFR = 0x02;			//clear flag by writing 1 to it.
	//MSG("Enter eport1 interrupt.\r\n");
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport2_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Eport2 ISR.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport2_isr(void)
{
	EPORT_EPFR = 0x04;			//clear flag by writing 1 to it.
	//MSG("Enter eport2 interrupt.\r\n");
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport3_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Eport3 ISR.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport3_isr(void)
{
	EPORT_EPFR = 0x08;			//clear flag by writing 1 to it.
	//MSG("Enter eport3 interrupt.\r\n");
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport4_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Eport4 ISR.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport4_isr(void)
{
	EPORT_EPFR = 0x10;			//clear flag by writing 1 to it.
	//MSG("Enter eport4 interrupt.\r\n");
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport5_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Eport5 ISR.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport5_isr(void)
{
	EPORT_EPFR = 0x20;			//clear flag by writing 1 to it.
	MSG("Enter eport5 interrupt.\r\n");
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport6_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Eport6 ISR.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport6_isr(void)
{
	EPORT_EPFR = 0x40;			//clear flag by writing 1 to it.

#ifdef INTERRUPT_DEMO_EN
	while(1)
	{
		MSG("Enter eport6 interrupt.\r\n");
	}
#else
	MSG("Enter eport6 interrupt.\r\n");
#endif

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport7_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Eport7 ISR.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport7_isr(void)
{
	EPORT_EPFR = 0x80;			//clear flag by writing 1 to it.
	MSG("Enter eport7 interrupt.\r\n");
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_make_dir
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Configure eport input or output.
//
// Input:
//    eport_no: eport number
//    dir: direction
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_make_dir(UINT8 eport_no, UINT8 dir)
{
	UINT32 temp = 0x01;

	if (dir == EPORT_INPUT)
		EPORT_EPDDR &= ~(temp << eport_no);
	else
		EPORT_EPDDR |= (temp << eport_no);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_write_val
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Eport output high or low.
//
// Input:
//    eport_no:eport number
//    val: value.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_write_val(UINT8 eport_no, UINT8 val)
{
	UINT8 temp;

	temp = 0x01;

	//EPORT_EPDDR |= (temp << eport_no);
	if (val == LEVEL_L)
	{
		EPORT_EPDR &= ~(temp << eport_no);
	}
	else
	{
		EPORT_EPDR |= (temp << eport_no);
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_read_val
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Return eport pin data.
//
// Input:
//    eport_no: eport number.
//
// Output:
//    eport pin level high or low.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 eport_read_val(UINT8 eport_no)
{
	UINT8 temp;

	temp = 0x01;

	//EPORT_EPDDR &= ~(temp << eport_no);
	if ((EPORT_EPPDR & (temp << eport_no)) == LEVEL_L)
	{
		return LEVEL_L;
	}
	else
	{
		return LEVEL_H;
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_config_isrtype
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    configure eport isr type.
//
// Input:
//    eport_no: eport number
//    int_mode: interrupt type
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_config_isrtype(UINT8 eport_no, EPORT_INT_MODE int_mode)
{
	EPORT_EPDDR &= ~(0x01 << eport_no);		//输入

	switch (int_mode)
	{
		case LOW_LEVEL_INT:			//低电平触发
		{
			EPORT_EPPAR &= ~(0x0003 << (eport_no * 2));
			break;
		}
		case HIGH_LEVEL_INT:			//高电平触发
		{
			EPORT_EPPAR &= ~(0x0003 << (eport_no * 2));
			EPORT_EPLPR |= (0x01 << eport_no);
			break;
		}
		case RISING_EDGE_INT:			//上升沿触发
		{
			EPORT_EPPAR &= ~(0x0003 << (eport_no * 2));
			EPORT_EPPAR |= (0x0001 << (eport_no * 2));
			break;
		}
		case FALLING_EDGE_INT:			//下降沿触发
		{
			EPORT_EPPAR &= ~(0x0003 << (eport_no * 2));
			EPORT_EPPAR |= (0x0002 << (eport_no * 2));
			break;
		}
		case RISING_FALLING_EDGE_INT:			//上升沿和下降沿都触发
		{
			EPORT_EPPAR |= (0x0003 << (eport_no * 2));
			break;
		}
		default:
		{
			break;
		}
	}
	//EPORT_EPIER |= (0x01 << eport_no);		//使能中断
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_int_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Eport is configured as interrupt mode.
//
// Input:
//    eport_no: eport number.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_int_enable(UINT8 eport_no)
{
	EPORT_EPIER |= (0x01 << eport_no);		//使能中断
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_int_disable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Disable eport interrupt.
//
// Input:
//    eport_no: eport number.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_int_disable(UINT8 eport_no)
{
	EPORT_EPIER &= ~(0x01 << eport_no);		//disable中断
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_pullup_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    configure eport input as pullup.
//
// Input:
//    eport_no: eport number.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_pullup_enable(UINT8 eport_no)
{
	EPORT_EPPUER |= (0x01 << eport_no);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_pullup_disable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Disable pullup.
//
// Input:
//    eport_no: eport number.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_pullup_disable(UINT8 eport_no)
{
	EPORT_EPPUER &= ~(0x01 << eport_no);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_init_int
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Install corresponding eport interrupt.
//
// Input:
//    eport_no: eport number.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_init_int(UINT8 eport_no)
{
	interrupt_setup(eport_isr_set[eport_no].eport_isr_num,
					eport_isr_set[eport_no].eport_int_priority,
					eport_isr_set[eport_no].eport_isr_entr);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 eport_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Install all eports interrupt.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eport_init(void)
{
	interrupt_setup(EPORT0_ISR_NUM, 0x00, eport0_isr);
	interrupt_setup(EPORT1_ISR_NUM, 0x00, eport1_isr);
	interrupt_setup(EPORT2_ISR_NUM, 0x00, eport2_isr);
	interrupt_setup(EPORT3_ISR_NUM, 0x00, eport3_isr);
	interrupt_setup(EPORT4_ISR_NUM, 0x00, eport4_isr);
	interrupt_setup(EPORT5_ISR_NUM, 0x00, eport5_isr);
	interrupt_setup(EPORT6_ISR_NUM, 0x00, eport6_isr);
	interrupt_setup(EPORT7_ISR_NUM, 0x00, eport7_isr);
}
