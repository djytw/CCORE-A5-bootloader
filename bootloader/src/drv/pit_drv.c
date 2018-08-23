// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : pit_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "memmap.h"
#include "int_drv.h"
#include "cpm_drv.h"
#include "pit_drv.h"
#include "pit_reg.h"
#include <math.h>

#include "eport_drv.h"
#include "eport_reg.h"


/* internal variables */
static UINT32 count1, count2;
static FP32 past_time1, past_time2;
static FP32 peirod1_in_sec, peirod2_in_sec;

/* internal functions */
static UINT32 pit_cycle_calc(UINT32 clk, UINT32 div, UINT32 per);

/* global variables */

#if 0
	extern void Timer1msCnt(void);
	extern volatile ulong    k_Ic_TotalTimeCount;         //????????????
	extern volatile ulong    k_Ic_TimeCount;              //????????????
	extern volatile ulong    k_IcMax_TotalTimeCount;      //????????
	extern volatile ulong    k_IcMax_TimeCount;           //?????????
	extern volatile int      k_timeover,k_total_timeover; //????,?????
#endif


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 pit_cycle_calc
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Calculate cycles under the given period.
//
// Input:
//    div: pit's clock divider.
//    per: period
//    clk: pit's clock
//
// Output:
//    Cycles.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static UINT32 pit_cycle_calc(UINT32 clk, UINT32 div, UINT32 per)
{
	UINT32 cnt;

	cnt = clk / per / pow(2, div);

	return cnt;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 pit_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    PIT ISR.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pit_isr(void)
{
#if 0
	UINT32 tmp1 = PIT1_PCSR;
	UINT32 tmp2 = PIT2_PCSR;

	if (tmp1 & PCSR_PIF)//pit1
	{
		//PRINTF("PIT1 INT\r\n");
		PIT1_PCSR |= PIT_PIF;
		
		//EPDR = ~EPDR;
		Timer1msCnt();
	}
	if (tmp2 & PCSR_PIF)//pit2
	{
		//PRINTF("PIT2 INT\r\n");
		PIT2_PCSR |= PIT_PIF;
	    if((k_IcMax_TotalTimeCount>0)&&(k_total_timeover==0))
	    {
	          k_Ic_TotalTimeCount++;
	         if(k_Ic_TotalTimeCount>k_IcMax_TotalTimeCount)
	         {k_total_timeover=1;}
	         if(k_total_timeover==1)
	         {
	           k_Ic_TotalTimeCount=0;
	           pit_stop(PIT2);
	         }
	         else{
	         }
	     }
	     if((k_IcMax_TimeCount>0)&&(k_timeover==0)){
	          k_Ic_TimeCount++;
	         if(k_Ic_TimeCount>k_IcMax_TimeCount)
	         {k_timeover=1;}
	         if(k_timeover==1)
	        {
	          k_Ic_TimeCount=0;
	          pit_stop(PIT2);
	        }
	        else{
	        }
	     }
	}
#endif

	UINT32 tmp1, tmp2;

	tmp1 = PIT1_PCSR;
	tmp2 = PIT2_PCSR;

	//eport_write_val(0, ~EPORT_EPDR);

	if (tmp1 & PCSR_PIF)//pit1
	{
		count1++;
		PIT1_PCSR |= PIT_PIF;
	}

	if (tmp2 & PCSR_PIF)//pit1
	{
		count2++;
		PIT2_PCSR |= PIT_PIF;
	}

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 pit_enalbe
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Enable PIT.
//
// Input:
//    pit_no: 1:PIT1
//            2:PIT2
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pit_enable(PIT_NUM pit_no)
{
	if(PIT1 == pit_no)
	{
		PIT1_PCSR |= PCSR_EN;
	}
	else
	{
		PIT2_PCSR |= PCSR_EN;
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 pit_config
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Start PIT.
//
// Input:
//    pit_no: 1:PIT1
//            2:PIT2
//    div: pit clock divider;
//    val: counter cycles.
//
// Output:
//    FALSE if overflow for given value.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL pit_config(UINT8 pit_no, UINT32 clk, UINT32 div, UINT16 val)
{
	UINT32 value_tmp;

	interrupt_setup(PIT_INT_NUM, 0x00, pit_isr);

	value_tmp = pit_cycle_calc(clk, div, val);

	if (value_tmp > 0xffff)
		return FALSE;
	else
	{
		if(PIT1 == pit_no)
		{
			count1 = 0;
			past_time1 = 0.0;
			peirod1_in_sec = 1 / (FP32)val;
			PIT1_PMR = (UINT16)value_tmp;
		}
		else
		{
			count2 = 0;
			past_time2 = 0.0;
			peirod2_in_sec = 1 / (FP32)val;
			PIT2_PMR = (UINT16)value_tmp;
		}
	}

#ifdef PIT_INT
	PIT1_PCSR = (div<<8) | PCSR_OVW | PCSR_PIE | PCSR_RLD; //????
#else
	PIT1_PCSR = (div<<8) | PCSR_OVW | PCSR_RLD;    //????
#endif

	pit_enable(pit_no);

	return TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 pit_restart
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Restart PIT.
//
// Input:
//    pit_no: 1:PIT1
//            2:PIT2
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pit_restart(PIT_NUM pit_no)
{
	UINT16 pcsr_bkup, pwr_bkup;

	if(PIT1 == pit_no)
	{
		pcsr_bkup = PIT1_PCSR;
		pwr_bkup = PIT1_PMR;
		PIT1_PCSR = (pcsr_bkup | PCSR_EN);
		PIT1_PMR = pwr_bkup;
	}
	else
	{
		pcsr_bkup = PIT2_PCSR;
		pwr_bkup = PIT2_PMR;
		PIT2_PCSR = (pcsr_bkup | PCSR_EN);
		PIT1_PMR = pwr_bkup;
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 pit_stop
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Stop PIT.
//
// Input:
//    pit_no: 1:PIT1
//            2:PIT2
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pit_stop(PIT_NUM pit_no)
{
	if(PIT1 == pit_no)
	{
		PIT1_PCSR &= ~PCSR_EN;
	}
	else
	{
		 PIT2_PCSR &= ~PCSR_EN;
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 pit_time_count_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Init start counter of pit.
//
// Input:
//    pit_no: 1:PIT1
//            2:PIT2
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pit_time_count_init(PIT_NUM pit_no)
{
	if(PIT1 == pit_no)
	{
		count1 = 0;
		past_time1 = 0.0;
	}
	else
	{
		count2 = 0;
		past_time2 = 0.0;
	}
}


FP32 pit_past_time(PIT_NUM pit_no)
{
	FP32 time_integer, time_float;

	time_integer = (PIT1 == pit_no) ? (peirod1_in_sec * count1) : (peirod2_in_sec * count1);
	time_float = (FP32)((PIT1 == pit_no)
			? ((FP32)((PIT1_PMR - PIT1_PCNTR) * peirod1_in_sec / PIT1_PMR))
			: ((FP32)((PIT2_PMR - PIT2_PCNTR) * peirod2_in_sec / PIT2_PMR)));

	//eport_write_val(0, 0);

	return ((FP32)(time_integer + time_float));
}
