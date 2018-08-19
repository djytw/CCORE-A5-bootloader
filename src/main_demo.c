// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : main.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "demo.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 main
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Main function of the project.
//
// Input:
//    None.
//
// Output:
//    0.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main(void)
{
	sys_init();

#ifdef GPIO_DEMO_EN
	gpio_led_demo();
#endif

#ifdef DMAC_DEMO_EN
	dmac_demo();
#endif

#ifdef EDMAC_DEMO_EN
	edmac_demo();
#endif

#ifdef USB_MS_DEMO_EN
	usb_ms_demo();
#endif

#ifdef USB_CDC_DEMO_EN
	usb_cdc_demo();
#endif

#ifdef ALG_DEMO_EN
	alg_demo();
#endif

#ifdef PIT_DEMO_EN
	pit_demo();
#endif

#ifdef LED_DEMO_EN
	led_demo();
#endif

#ifdef CPM_DEMO_EN
	cpm_demo();
#endif

#ifdef SCI_DEMO_EN
	sci_demo();
#endif

#ifdef RESET_DEMO_EN
	reset_demo();
#endif

#ifdef USI_7816_DEMO_EN
	usi_demo();
#endif

#ifdef EFLASH_DEMO_EN
	eflash_demo();
#endif

#ifdef SPI_DEMO_EN
	spi_demo();
#endif

#ifdef EPORT_DEMO_EN

#ifdef INTERRUPT_DEMO_EN
	interrupt_nest_demo();
#else
	eport_demo();
#endif

#endif

#ifdef SD_DEMO_EN
	sd_demo();
#endif


#ifdef VD_DEMO_EN
	vd_demo();
#endif

#ifdef TD_DEMO_EN
	td_demo();
#endif

#ifdef FD_DEMO_EN
	fd_demo();
#endif

#ifdef WDT_DEMO_EN
	 wdt_demo();
#endif

#ifdef TC_DEMO_EN
	 TC_demo();
#endif

#ifdef EPT_DEMO_EN
    ept_demo();
#endif

#ifdef LOWPOWER_DEMO_EN
    lowpower_demo();
#endif

#ifdef I2C_DEMO_EN
	i2c_demo();
#endif

#ifdef CRC_DEMO_EN
	crc_demo();
#endif

#ifdef TRNG_DEMO_EN
	trng_demo();
#endif

#ifdef GET_SN_DEMO_EN
	get_sn_demo();
#endif

#ifdef REBOOT_DEMO_EN
	reboot_demo();
#endif
//	asm("bkpt");
	while(1);
	return 0;
}


