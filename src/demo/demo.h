// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : demo.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __DEMO_H__
#define __DEMO_H__
#include "includes.h"
#include "sys_api.h"

#define USI_7816_DEMO_EN
#define LED_DEMO_EN
#define CPM_DEMO_EN
#define SCI_DEMO_EN
#define MIM_DEMO_EN
#define PIT_DEMO_EN
#define ALG_DEMO_EN
#define SPI_DEMO_EN
#define DMAC_DEMO_EN
#define EDMAC_DEMO_EN
#define EFLASH_DEMO_EN
#define RESET_DEMO_EN
#define SD_DEMO_EN
#define VD_DEMO_EN     //注意需要关闭CPM_EN
#define TD_DEMO_EN     //注意需要关闭CPM_EN
#define FD_DEMO_EN     //注意需要关闭CPM_EN
#define USB_MS_DEMO_EN
#define USB_CDC_DEMO_EN
#define WDT_DEMO_EN
#define TC_DEMO_EN
#define EPT_DEMO_EN
#define LOWPOWER_DEMO_EN
#define I2C_DEMO_EN
#define CRC_DEMO_EN
#define TRNG_DEMO_EN
#define GET_SN_DEMO_EN
#define EPORT_DEMO_EN
#define GPIO_DEMO_EN
#define REBOOT_DEMO_EN

#ifdef EPORT_DEMO_EN
#define INTERRUPT_DEMO_EN
#endif


#ifdef USI_7816_DEMO_EN
	#include "usi_demo.h"
#endif

#ifdef SCI_DEMO_EN
	#include "sci_demo.h"
#endif

#ifdef CPM_DEMO_EN
	#include "cpm_demo.h"
#endif

#ifdef LED_DEMO_EN
	#include "led_demo.h"
#endif

#ifdef SPI_DEMO_EN
	#include "spi_demo.h"
#endif

#ifdef GPIO_DEMO_EN
	#include "gpio_led_demo.h"
#endif

#ifdef DMAC_DEMO_EN
	#include "dmac_demo.h"
#endif

#ifdef EDMAC_DEMO_EN
    #include "edmac_demo.h"
#endif

#ifdef EFLASH_DEMO_EN
	#include "eflash_demo.h"
#endif

#ifdef RESET_DEMO_EN
	#include "reset_demo.h"
#endif

#ifdef ALG_DEMO_EN
	#include "alg_demo.h"
#endif

#ifdef SM2_DEMO_EN
	#include "sm2_demo.h"
#endif

#ifdef RSA_DEMO_EN
	#include "rsa_demo.h"
#endif

#ifdef EPORT_DEMO_EN
	#include "eport_demo.h"
#endif

#ifdef SD_DEMO_EN
	#include "sd_demo.h"
#endif

#ifdef USB_MS_DEMO_EN
	#include "usb_ms_demo.h"
#endif

#ifdef USB_CDC_DEMO_EN
	#include "usb_cdc_demo.h"
#endif

#ifdef WDT_DEMO_EN
	#include "wdt_demo.h"
#endif

#ifdef PIT_DEMO_EN
	#include "pit_demo.h"
#endif

#ifdef TC_DEMO_EN
    #include "TC_demo.h"
#endif

#ifdef EPT_DEMO_EN
    #include "EPT_demo.h"
#endif

#ifdef LOWPOWER_DEMO_EN
	#include "lowpower_demo.h"
#endif

#ifdef I2C_DEMO_EN
	#include "i2c_demo.h"
#endif
#ifdef CRC_DEMO_EN
	void crc_demo(void);
#endif

#ifdef TRNG_DEMO_EN
	#include "trng_demo.h"
#endif

#ifdef GET_SN_DEMO_EN
	#include "get_sn_demo.h"
#endif

#ifdef FD_DEMO_EN
#include "fd_demo.h"
#endif

#ifdef TD_DEMO_EN
#include "td_demo.h"
#endif

#ifdef VD_DEMO_EN
#include "vd_demo.h"
#endif

#ifdef REBOOT_DEMO_EN
#include "reboot_demo.h"
#endif
#endif /* __DEMO_H__ */
