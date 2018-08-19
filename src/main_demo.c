#include "includes.h"
#include "wdt_api.h"
#include "cpm_api.h"
#include "eport_api.h"
#include "eflash_api.h"
#include "eflash_demo.h"

void test();
void printf_version(void){
	MSG("\033[2J\n\r\033[32m"
	   				 "\n\r"
	   				 "=======================================\n\r"
	   				 "      djytw C*Core bootloader test     \n\r"
	   				 "=======================================\n\r"
	   				 "\n\r"
	   				 "\033[33mCompiled in "__DATE__" "__TIME__"\n\r"
	   				 "copyright (c) 2018 djytw.\n\r\n\r\033[0m"
	   				 "\n\r"
	   				 "Waiting for commands, h for help.\n\r"
	   				 "System will boot in 2s...\n\r");
}
int main(void){
	cpm_init();
	sci_init(SCI_ID2, g_ips_clk, BAUDRATE_115200);
	wdt_disable();
	printf_version();
	u32 i;
#ifdef CONF_DEBUG
	u8 a;UINT32 ret_code,data,efm_clk;


	efm_clk = cpm_get_efmclk();
	eflash_init(efm_clk);
	for(i = 0x00420000; i < 0x00440000; i += 512)
	{
		ret_code = eflash_page_erase(i);
		if(ret_code == EFLASH_PROG_ERASE_FAIL)
		{
			asm("bkpt");
		}
	}
	u8 flag=0;
	i=0x00420000;
	while(!flag){
		data=0;
		a=sci_receive_byte();
		data|=a<<24;
		a=sci_receive_byte();
		data|=a<<16;
		a=sci_receive_byte();
		data|=a<<8;
		a=sci_receive_byte();
		data|=a;

		ret_code = eflash_program(i, data);
		if(ret_code == EFLASH_PROG_ERASE_FAIL){
			PRINTF("  addr = %08x program fail, data=%08x\r\n",i,data);
			asm("bkpt");
			flag=1;
		}
		PRINTF("  addr = %08x program success, data=%08x\r\n",i,data);
		i+=4;
		if(data==0)break;
	}
#endif
	//reset
	//eflash_init(g_efm_clk);
	//eflash_recovery_to_rom();
	//eflash_demo();
	for(i=0;i<8;i++){
			eport_config(i, EPROT_OUTPUT, FALSE, FALSE);
	}
#ifdef CONF_DEBUG
	void (*app_start)(void);
	app_start = (void (*) (void))(UINT32*)0x00420000;
	app_start();
#endif

#ifdef CONF_RELEASE
	test();
#endif
	return 0;
}
