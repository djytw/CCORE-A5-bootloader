// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : sys_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "sys_api.h"


#define	VERSION_STRING	"V1.1"
char  Firmware_date[] = __DATE__;
char  Firmware_time[] = __TIME__;

static void reback_boot(void)
{
	i2c_config_gpio(I2C_SDA,GPIO_INPUT);
	if(i2c_read_gpio(I2C_SDA) == Bit_RESET)
	{
		reboot_demo();
	}
}


void printf_version(void)
{
	MSG("/**************************************************/\n");
	MSG("\t");
	MSG((char *)__DATE__);
	MSG("\t");
	MSG(( char *)__TIME__);
	MSG("\n\t");
	MSG(( char *)"C*CORE A5(ET300) DEMO");
	MSG("\n\t");
	MSG(( char *)"Version : ");
	MSG("\t");
	MSG(( char *)VERSION_STRING);
	MSG("\n");
	MSG("/**************************************************/\n");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sys_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Initialize system setting of the project.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void sys_init(void)
{

	cpm_init();
	sci_init(SCI_ID1, g_ips_clk, BAUDRATE_115200);		// g_ips_clk = g_sys_clk/2
//	sci_init(SCI_ID1, g_ips_clk*21/20, BAUDRATE_115200);		// g_ips_clk = g_sys_clk/2
	//tc_init(TC_WDP_0_5, 1);
//	wdt_init(100);
//	wdt_close();
	stop_WDT();

	printf_version();
	reback_boot();
}
