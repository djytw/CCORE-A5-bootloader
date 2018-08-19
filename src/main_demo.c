#include "includes.h"
#include "wdt_api.h"
#include "cpm_api.h"
#include "eport_api.h"
#include "eflash_api.h"
#include "eflash_demo.h"
#define __VER__  "\033[33mdjytw C*Core bootloader.\n\rVersion: 0.1 alpha\n\r\n\r\033[0m"
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
u8 direct_write(u32 ds, u32 dl){
	u32 efm_clk,i,ret_code;
	efm_clk = cpm_get_efmclk();
	eflash_init(efm_clk);
	for(i = ds; i <= ds+dl; i += 512){
		ret_code = eflash_page_erase(i);
		if(ret_code == EFLASH_PROG_ERASE_FAIL){
			asm("bkpt");
		}
	}
	i=ds;
	while(i<ds+dl){
		u32 data=0;u8 a;
		a=sci_receive_byte();
		data|=a;
		a=sci_receive_byte();
		data|=a<<8;
		a=sci_receive_byte();
		data|=a<<16;
		a=sci_receive_byte();
		data|=a<<24;

		ret_code = eflash_program(i, data);
		if(ret_code == EFLASH_PROG_ERASE_FAIL){
			asm("bkpt");
		}
		i+=4;
	}
	return 0;
}
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
	asm("nop");
	u32 ds,dl;
	ds=0x00420000;
	dl=0;
	while(1){
		switch(ser){
		case 'h':
			//help cmd
			MSG(__VER__
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
		case 'i':
			MSG(__VER__);
			break;
		case 's':
			ds=0;
			MSG("New start point: ");
			for(i=0;i<8;i++){
				u8 t;
				t=sci_receive_byte();
				MSG("%c",t);
				ds*=16;
				if(t>='0'&&t<='9'){
					ds+=t-'0';
				}else if(t>='a'&&t<='f'){
					ds+=t-'a'+10;
				}else if(t>='A'&&t<='F'){
					ds+=t-'A'+10;
				}else{
					MSG("\n\rMalformed command. Reset start point.\n\r");
					ds=0x00420000;
					break;
				}
			}
			MSG("\n\rStart point = 0x%08x now.\n\r",ds);
			break;
		case 'l':
			dl=0;
			MSG("Enter data length: ");
			for(i=0;i<8;i++){
				u8 t;
				t=sci_receive_byte();
				MSG("%c",t);
				dl*=16;
				if(t>='0'&&t<='9'){
					dl+=t-'0';
				}else if(t>='a'&&t<='f'){
					dl+=t-'a'+10;
				}else if(t>='A'&&t<='F'){
					dl+=t-'A'+10;
				}else{
					MSG("\n\rMalformed command.\n\r");
					dl=0;
					break;
				}
			}
			if(dl==0||dl%4)
				MSG("\n\rSet length failed. length should be divisible by 4 and not 0\n\r");
			else
				MSG("\n\rSet length ok. New value is 0x%08x.\n\r",dl);
			break;
		case 'w':
			direct_write(ds,dl);
			break;
		default:
			MSG("Unrecognized command - %c, Use 'h' to get help.\n\r",ser);
		}
		MSG("\n\rbootloader> ");
		//will block
		ser=sci_receive_byte();
		MSG("%c\n\r",ser);

	}
	return 0;
}
