#include "includes.h"
#include "wdt_api.h"
#include "cpm_api.h"
#include "eport_api.h"
#include "eflash_api.h"
#include "eflash_demo.h"
#include "alg_api.h"
#include "alg_drv.h"

#define __VER__  "1.0 RC-3"
#define DEBUG_BREAK asm("bkpt")
#define PMSG(...) {if(!is_programmer)MSG(__VA_ARGS__);}
#define DMSG(...) {if(is_programmer)MSG(__VA_ARGS__);}
#define assert(a) {if(!(a))asm("bkpt");}



// is_programmer: 0: command user interface/ 1:programmer interface
u8 is_programmer=0;

// ds = download start point;  dl=data_length
u32 ds,dl;

void show_help(){
	//show help msg. only in cui mode
	PMSG(__VER__
			"\n\rUsage:\n\r"
			"\ti  -  View chip info\n\r"
			"\th  -  Show this help\n\r"
			"\ts  -  Set writing start point. \n\r");
	PMSG("\t\tFollowed by address which will be changed. 8 digits exactly, without '0x'. The default value is 00420000.\n\r"
			"\t\teg. s00420000\n\r"
			"\tl  -  Set writing length.\n\r");
	PMSG("\t\tFollowed by data length (or file size of the bin file), 4 digits exactly. Default: 0200\n\r"
			"\tw  -  Direct writing to flash. \n\r");
	PMSG("\t\tNeed to specify data length with 'l' command. Following LENGTH bytes will be write to flash. After writing, SHA-256 will be calculated and returned.\n\r"
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
	u8 i;
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
	PMSG("\n\rSet length ok. New value is 0x%04x.\n\r",dl);
	DMSG("o%04x",dl);
	return 0;
}
u8 set_start_point(){
	ds=0;
	PMSG("New start point: ");
	//start_point: u32 : 8digits
	u8 i;
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
	if(dl==0){
		PMSG("Data length should be set first!\n\r");
		DMSG("f1");
		return 1;
	}
	//dl should not be illegal
	assert(dl>0);
	assert(dl%4==0);

	//malloc not working. Use sram addr directly.
	u32 *bin=(u32*)0x00820000;

	u32 i,ret_code;
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

	//calculate SHA256
	u8* sha256=(u8*)0x00830000;
	hash_init(MODE_SHA256);
	sha_update(ds,dl);
	hash_dofinal(MODE_SHA256,sha256);
	u8 shaans[65];
	for(i=0;i<32;i++){
		u8 hi=sha256[i]>>4;
		u8 lo=sha256[i]&0xf;
		if(hi<10)shaans[i*2]=hi+'0';
		else shaans[i*2]=hi+'A'-10;
		if(lo<10)shaans[i*2+1]=lo+'0';
		else shaans[i*2+1]=lo+'A'-10;
	}
	shaans[64]=0;

	// rewrite interrupt table
	u8* vector = (u8*) 0x00820000;
	for(i=0;i<4;i++)
		vector[i] = eflash_byte_read(0x00400000+i);
	for(i=0x100;i<0x200;i++)
		vector[i] = eflash_byte_read(0x00400000+i);
	ret_code = eflash_page_erase(0x00400000);
	if(ret_code == EFLASH_PROG_ERASE_FAIL){
		PMSG("Flash write error!\n\r");
		DMSG("f4");
		return 4;
	}
	ret_code = eflash_bulk_program(0x00400000,128,(u32*)vector);
	if(ret_code == EFLASH_PROG_ERASE_FAIL){
		PMSG("Flash write error!\n\r");
		DMSG("f5");
		return 5;
	}

	PMSG("Flash write ok! SHA256=%s\n\r",shaans);
	DMSG("o%s",shaans);
	return 0;
}
int main(void){
	cpm_init();
	sci_init(SCI_ID2, g_ips_clk, 500000);
	wdt_disable();
	printf_version();

	//Init flash clock.
	u32 efm_clk;
	efm_clk = cpm_get_efmclk();
	eflash_init(efm_clk);
#ifdef CONF_DEBUG
	eflash_recovery_to_rom();
#endif

	u32 i,j;
	u8 ser;
	is_programmer=0;
	for(i=9;i>0;i--){
		MSG("\rSystem will boot in 0.%ds...",i);
		for(j=0;j<1000;j++){
			ser=sci_read_notimeout();
			if(ser!=0xff){
				//receive cmd
				if(ser=='p'){
					//internal usage for programmers, will strip output msg.
					is_programmer=1;
					DMSG("o");
					ser=sci_receive_byte();
				}
				PMSG("\n\r");
				goto prog;
			}
			//TODO: a more precise delay
			delay(120);
		}
	}

	//time out. starts the program.
	//app_starts()
app_starts:
	PMSG("Starting app.\n\r");
	u32 start_point=eflash_word_read(0x00420000);
	PMSG("position=0x%08x\n\r",start_point);
	void (*app_start)(void);
	app_start = (void (*) (void))(UINT32*)start_point;
	app_start();
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
			PMSG("\033[33mdjytw C*Core bootloader.\n\rVersion: "__VER__"\n\r\n\r\033[0m");
			DMSG("CCBOOT");
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
		case 'p':
			is_programmer=1;
			DMSG("o");
			break;
		default:
			PMSG("Unrecognized command - %c, Use 'h' to get help.\n\r",ser);
			DMSG("f");
		}
		if(!is_programmer)MSG("\n\rbootloader> ");
		//will block
		ser=sci_receive_byte();
		if(!is_programmer)MSG("%c\n\r",ser);

	}
	return 0;
}
