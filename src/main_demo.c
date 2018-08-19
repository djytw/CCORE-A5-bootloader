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
	   				 );
}
u8 sci_read_notimeout();
int main(void){
	cpm_init();
	sci_init(SCI_ID2, g_ips_clk, BAUDRATE_115200);
	wdt_disable();
	printf_version();
	u32 i,j;
	u8 ser;
	for(i=20;i>0;i--){
		MSG("\rSystem will boot in %ds...",i);
		for(j=0;j<1000;j++){
			ser=sci_read_notimeout();
			if(ser!=0xff){
				//receive cmd
				MSG("\n\r");
				goto prog;
			}
			//TODO: a more precise delay
			delay(10000);
		}
	}

	//time out. starts the program.
	//app_starts()
app_starts:
	MSG("Starting app.\n\r");
	while(1);

	//receive cmd. Stop timing and proc.
prog:
	while(1){
		switch(ser){
		case 'h':
			//help cmd
			MSG("\033[33mdjytw C*Core bootloader.\n\r"
					"Version: 0.1 alpha\n\r"
					"\n\r\033[0m"
					"Usage:\n\r"
					"\ti  -  View chip info\n\r"
					"\th  -  Show this help\n\r"
					"\ts  -  Set writing start point. \n\r");
			MSG("\t\tFollowed by address which will be changed. 8 digits exactly, without '0x'. The default value is 00420000.\n\r"
					"\t\teg. s00420000\n\r"
					"\tl  -  Set writing length.\n\r");
			MSG("\t\tFollowed by data length (or file size of the bin file), 8 digits exactly, without '0x'. \n\r"
					"\tw  -  Direct writing to flash. \n\r");
			MSG("\t\tNeed to specify data length with 'l' command. Following LENGTH bytes will be write to flash.\n\r"
					"\tc  -  Writing with SHA-256 check\n\r");
			MSG("\t\tNeed to specify data length with 'l' command. Following 256 bytes is SHA-256 value of data, and then LENGTH bytes will be write to flash and be checked.\n\r"
					"\tb  -  Boot to program directly.\n\r\n\r");
			break;
		case 'b':
			goto app_starts;
			break;
		}
		MSG("\n\rbootloader> ");
		//will block
		ser=sci_receive_byte();
		MSG("%c\n\r",ser);

	}
	return 0;
}
