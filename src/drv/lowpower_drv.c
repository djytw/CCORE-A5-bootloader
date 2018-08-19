// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : lowpower_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "lowpower_drv.h"
#include "int_drv.h"
#include "cpm_reg.h"
#include "cpm_drv.h"
#include "memmap.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 pad_wkp_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    PAD wakeup ISR.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pad_wkp_isr(void)
{
	UINT8 flag;
	flag = lp_drv_get_wkp_flag();
	CPM_POFFWKPSSR |= 0x0f;			//clear wakeup flag
	CPM_WKPCSR |= 0x00f00000;
	sci_init(SCI_ID1, g_sys_clk, BAUDRATE_115200);
	MSG("Enter pad wakeup interrupt.\r\n");
	MSG("wakeup flag: %x.\r\n",flag);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_drv_module_off
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Close some modules to reduce power consumption.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void lp_drv_module_off(void)
{
	CPM_PWRCR |= PWRCR_PHY_PSWEN_BIT;				//USB PHY OFF
	delay(0x100);
	CPM_PWRCR &= ~(PWRCR_PHY_I_ISOEN_BIT|PWRCR_PHY_O_ISOEN_BIT);
	delay(0x100);
	CPM_PWRCR &= ~(PWRCR_PHY_RSTMASK_BIT);

	(*(VUINT16*)(CCM_BASE + 0x0a)) = 0x0100;		//VD BG OFF
  	(*(VUINT8*)(RESET_BASE + 0x06)) = 0x00;

  	(*(VUINT16*)(CCM_BASE + 0x06)) |= 0x0844;		//USB - USBPHY power down otg

	(*(VUINT8*)(USI1_BASE + 0x0c)) = 0x07;			//USI1 input pullup
	(*(VUINT8*)(USI1_BASE + 0x0e)) = 0x00;

	(*(VUINT32*)(TRNG_BASE + 0x00)) = 0x00000000;	//close TRNG

  	(*(VUINT16*)(CCM_BASE + 0x02)) |= 0x0800;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_drv_POFF1_cfg
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    POFF1 mode register configuration.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void lp_drv_POFF1_cfg(void)
{
	lp_drv_module_off();

	CPM_SLPCFGR = 0x210069ee;
	CPM_PWRCR |= CPM_PWRCR_SD_PWSEL_BIT;	//EMMC I/O 1.8v
	CPM_SLPCNTR = 0x00800080;
	CPM_WKPCNTR = 0x00000000;
	CPM_OSCLSTIMER = 0x00330033;
	CPM_OSCHSTIMER = 0x00330033;
	CPM_FILTCNTR = 0x00000065;				//EFlash Power on timing(30us)
	CPM_APDSLPCR = 0xffffffff;				//Power down all analog IP
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_drv_POFF2_cfg
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    POFF2 mode register configuration.
//
// Input:
//    mode: 0: Hiber at once;
//    		1: Auto Hiber.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void lp_drv_POFF2_cfg(UINT8 mode)
{
	if(mode == 0)
		CPM_SLPCFGR = 0xe1006dec;			//Hiber at once
	else
		CPM_SLPCFGR = 0xe10069ec;			//Auto Hiber
	CPM_SLPCNTR = 0x00800080;
	CPM_WKPCNTR = 0x00000000;
	CPM_OSCLSTIMER = 0x00330033;
	CPM_OSCHSTIMER = 0x00330033;
	CPM_FILTCNTR = 0x00000065;				//EFlash Power on timing(30us)
	CPM_HIBERCNTR = 0x00000000;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_drv_enable_wkppad
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Pad Wakeup enable.
//
// Input:
//    pad_num: 0: enable pad0 wakeup;
//			   1: enable pad1 wakeup;
//			   2: enable pad2 wakeup;
//			   3: enable pad3 wakeup.
//
//    interrupt_en: 0: disable interrupt
//					1: enable interrupt
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void lp_drv_enable_wkppad(UINT8 pad_num, BOOL interrupt_en)
{
	CPM_POFFWKPSCR |= BIT(pad_num);
	CPM_WKPCSR |= BIT(pad_num);
	CPM_WKPCSR &=~ BIT(pad_num + 4);
	if(interrupt_en == 1)
	{
		CPM_WKPCSR |= BIT(pad_num + 4);
		interrupt_setup(0x20, 0x0, pad_wkp_isr);
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_drv_disable_wkppad
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Disable Pad Wakeup.
//
// Input:
//    pad_num: 0: disable pad0 wakeup;
//			   1: disable pad1 wakeup;
//			   2: disable pad2 wakeup;
//			   3: disable pad3 wakeup.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void lp_drv_disable_wkppad(UINT8 pad_num)
{
	CPM_POFFWKPSCR &=~ BIT(pad_num);
	CPM_WKPCSR &=~ BIT(pad_num);
	CPM_WKPCSR &=~ BIT(pad_num + 4);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_drv_change_VREF
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//   Change VCCQ VREF.
//
// Input:
//    verf_val: VREF value
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void lp_drv_change_VREF(UINT8 vref_val)
{
	CPM_VCCQVTRIMR = vref_val & 0x0f;				//Write value to the trim reg
	CPM_VCCQVTRIMR |= 0x00000200;			//Update the value
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_drv_enter_sleep
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//   Enter lowpower.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void lp_drv_enter_sleep(void)
{
	CPM_SLPCR = 0x00000001;					//enter sleep(POFF1/POFF2)
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_drv_get_wkp_flag
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    get wakeuppad flag, just for POFF1 mode.
//
// Input:
//    None.
//
// Output:
//    BIT0: Pad0 wake up flag;
//	  BIT1: Pad1 wake up flag;
//    BIT2: Pad2 wake up flag;
//	  BIT3: Pad3 wake up flag.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 lp_drv_get_wkp_flag(void)
{
	UINT8 wkp_flag;
	wkp_flag = (CPM_WKPCSR >> 20) & 0x0f;
	return wkp_flag;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_drv_get_wkppad_val
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    get present wakeuppad value.
//
// Input:
//    None.
//
// Output:
//    BIT0: Pad0 wake up valid;
//	  BIT1: Pad1 wake up valid;
//    BIT2: Pad2 wake up valid;
//	  BIT3: Pad3 wake up valid.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 lp_drv_get_wkppad_val(void)
{
	UINT8 wkppad_val;
	wkppad_val = (CPM_WKPCSR >> 16) & 0x0f;
	return wkppad_val;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 lp_drv_clr_wkp_flag
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    clear wakeup flag.
//
// Input:
//    pad_num: 0: clear pad0 wakeup flag;
//			   1: clear pad1 wakeup flag;
//			   2: clear pad2 wakeup flag;
//			   3: clear pad3 wakeup flag.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void lp_drv_clr_wkp_flag(UINT8 pad_num)
{
	CPM_POFFWKPSSR |= BIT(pad_num);
	CPM_WKPCSR |= BIT(pad_num + 20);
}
