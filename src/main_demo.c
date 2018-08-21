#include "includes.h"
#include "wdt_api.h"
#include "cpm_api.h"
#include "eport_api.h"
#include "eflash_api.h"
#include "eflash_demo.h"
#define __VER__  "\033[33mdjytw C*Core bootloader.\n\rVersion: 0.1 alpha\n\r\n\r\033[0m"
#define DEBUG_BREAK asm("bkpt")
#define PMSG(...) if(!is_programmer)MSG(__VA_ARGS__)
#define DMSG(...) if(is_programmer)MSG(__VA_ARGS__)




// is_programmer: 0: command user interface/ 1:programmer interface
u8 is_programmer=0;

// ds = download start point;  dl=data_length
u32 ds,dl;

void show_help(){
	//show help msg. only in cui mode
	PMSG(__VER__
			"Usage:\n\r"
			"\ti  -  View chip info\n\r"
			"\th  -  Show this help\n\r"
			"\ts  -  Set writing start point. \n\r");
	PMSG("\t\tFollowed by address which will be changed. 8 digits exactly, without '0x'. The default value is 00420000.\n\r"
			"\t\teg. s00420000\n\r"
			"\tl  -  Set writing length.\n\r");
	PMSG("\t\tFollowed by data length (or file size of the bin file), 3 digits exactly, less than 200. Default: 200\n\r"
			"\tw  -  Direct writing to flash. \n\r");
	PMSG("\t\tNeed to specify data length with 'l' command. Following LENGTH bytes will be write to flash.\n\r"
			"\tc  -  Writing with SHA-256 check\n\r");
	PMSG("\t\tNeed to specify data length with 'l' command. Following 256 bytes is SHA-256 value of data, and then LENGTH bytes will be write to flash and be checked.\n\r"
			"\tb  -  Boot to program directly.\n\r\n\r");
}
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
u8 set_data_length(){
	dl=0;
	PMSG("Enter data length: ");
	//data_length: 4digits
	for(i=0;i<4;i++){
		u8 t;
		t=sci_receive_byte();
		PMSG("%c",t);
		dl*=16;
		if(t>='0'&&t<='9'){
			dl+=t-'0';
		}else if(t>='a'&&t<='f'){
			dl+=t-'a'+10;
		}else if(t>='A'&&t<='F'){
			dl+=t-'A'+10;
		}else{
			PMSG("\n\rMalformed command.\n\r");
			DMSG("f1");
			dl=0;
			return 1;
		}
	}
	if(dl==0||dl%4){
		PMSG("\n\rSet length failed. length should not be 0 and should be divisible by 4 \n\r");
		DMSG("f2");
		return 2;
	}
	PMSG("\n\rSet length ok. New value is 0x%08x.\n\r",dl);
	DMSG("o%08x",dl);
	return 0;
}
u8 set_start_point(){
	ds=0;
	PMSG("New start point: ");
	//start_point: u32 : 8digits
	for(i=0;i<8;i++){
		u8 t;
		t=sci_receive_byte();
		PMSG("%c",t);
		ds*=16;
		if(t>='0'&&t<='9'){
			ds+=t-'0';
		}else if(t>='a'&&t<='f'){
			ds+=t-'a'+10;
		}else if(t>='A'&&t<='F'){
			ds+=t-'A'+10;
		}else{
			PMSG("\n\rMalformed command. Reset start point.\n\r");
			DMSG("f1");
			ds=0x00420000;
			return 1;
		}
	}
	//check if ds is illegal
	if(ds<0x00420000||ds>0x004f0000||ds%4){
		PMSG("\n\rStart point should great than 0x00420000 and less than 0x004f0000, and divisble by 4. Start point is reset now.\n\r");
		DMSG("f2");
		ds=0x00420000;
		return 2;
	}
	PMSG("\n\rStart point = 0x%08x now.\n\r",ds);
	DMSG("o%08x",ds);
	return 0;
}
u8 direct_write(){
	//Init flash clock.
	u32 efm_clk;
	efm_clk = cpm_get_efmclk();
	eflash_init(efm_clk);

	if(dl==0){
		PMSG("Data length should be set first!\n\r");
		DMSG("f1");
		return 1;
	}
	//dl should not be illegal
	assert(dl&&!(dl%4));

	//malloc not working. Use sram addr directly.
	u32 *bin=(u32*)0x00820000;

	//erase flash from ds to ds+dl
	for(i = ds; i <= ds+dl; i += 512){
		ret_code = eflash_page_erase(i);
		if(ret_code == EFLASH_PROG_ERASE_FAIL){
			PMSG("Flash erase error!\n\r");
			DMSG("f2");
			return 2;
		}
	}
	//receive data
	for(i=0;i<dl/4;i++){
		u32 data=0;u8 a;
		a=sci_receive_byte();
		data|=a;
		a=sci_receive_byte();
		data|=a<<8;
		a=sci_receive_byte();
		data|=a<<16;
		a=sci_receive_byte();
		data|=a<<24;
		bin[i]=data;
	}
	//program at once
	ret_code = eflash_bulk_program(ds,dl/4,bin);
	if(ret_code == EFLASH_PROG_ERASE_FAIL){
		PMSG("Flash write error!\n\r");
		DMSG("f3");
		return 3;
	}
	PMSG("Flash write ok!\n\r");
	DMSG("o");
	return 0;
}
int main(void){
	cpm_init();
	sci_init(SCI_ID2, g_ips_clk, BAUDRATE_115200);
	wdt_disable();
	printf_version();
	u32 i,j;
	u8 ser;
	is_programmer=0;
	for(i=20;i>0;i--){
		MSG("\rSystem will boot in %ds...",i);
		for(j=0;j<1000;j++){
			ser=sci_read_notimeout();
			if(ser!=0xff){
				//receive cmd
				if(ser=='p'){
					//internal usage for programmers, will strip output msg.
					is_programmer=1;
					ser=sci_receive_byte();
				}
				PMSG("\n\r");
				goto prog;
			}
			//TODO: a more precise delay
			delay(10000);
		}
	}

	//time out. starts the program.
	//app_starts()
app_starts:
	PMSG("Starting app.\n\r");
	while(1);

	//receive cmd. Stop timing and proc.
prog:
	ds=0x00420000;
	dl=0;
	while(1){
		switch(ser){
		case 'h':
			//help cmd
			show_help();
			break;
		case 'b':
			goto app_starts;
			break;
		case 'i':
			PMSG(__VER__);
			break;
		case 's':
			set_start_point();
			break;
		case 'l':
			set_data_length();
			break;
		case 'w':
			direct_write();
			break;
		default:
			MSG("Unrecognized command - %c, Use 'h' to get help.\n\r",ser);
		}
		if(!is_programmer)MSG("\n\rbootloader> ");
		//will block
		ser=sci_receive_byte();
		if(!is_programmer)MSG("%c\n\r",ser);

	}
	return 0;
}
