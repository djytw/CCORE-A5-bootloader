#include "includes.h"
#include "wdt_api.h"
#include "cpm_api.h"
#include "eport_api.h"

void test();
void printf_version(void){
	MSG("\n\r\033[32m"
	   				 "\n\r"
	   				 "=======================================\n\r"
	   				 "      djytw C*Core bootloader test     \n\r"
	   				 "=======================================\n\r"
	   				 "\n\r"
	   				 "\033[33mCompiled in "__DATE__" "__TIME__"\n\r"
	   				 "copyright (c) 2018 djytw.\n\r\n\r\033[0m"
	   				 "\n\r");
	MSG("Congratulations, the app is successfully invoked by the bootloader!\n\r");
}
int main(void){
	cpm_init();
	sci_init(SCI_ID2, g_ips_clk, BAUDRATE_115200);
	wdt_disable();
	printf_version();
	u32 i;
	for(i=0;i<8;i++){
				eport_config(i, EPROT_OUTPUT, FALSE, FALSE);
		}
	test();
	return 0;
}
