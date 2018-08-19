// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usi_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "includes.h"
#include "memmap.h"
#include "int_drv.h"
#include "int_reg.h"
#include "usi_drv.h"
#include "usi_reg.h"


/* internal variables */
static const UINT8 atr_string[ATR_LENGTH] = {
		0x3b,0x9d,0x96,0x80,0x1f,0xc6,0x43,0x43,0x20,0x42,
		0x6F,0x6F,0x74,0x6C,0x6F,0x61,0x64,0x65,0x72,0x55
};

static const UINT16 fi_di_table[15] = {
		0x31DE, 0x11FE, 0x12FD, 0x13FC, 0x14FB,
		0x15FA, 0x16F9, 0x18F7, 0x917E, 0x927D,
		0x937C, 0x947B, 0x957A, 0x9679, 0x9778
};

static const UINT8 fd_cycle[15] = {
		0x01, 0x02, 0x03, 0x04, 0x05,
		0x06, 0x07, 0x08, 0x09, 0x0a,
		0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};

static sUSIReg* gusi_reg;

/*USI base address*/
UINT32 const g_usi_baseaddr[4] = {0, USI1_BASE, USI2_BASE, USI3_BASE};

//Function Definition


/* internal functions */
static void init_apdu(UINT32 usi_base_addr);
static void trans_byte(UINT8 data);
static void send_atr(void);
static void send_pts_ack(void);
static void send_default_ack(void);
static void pps_manager(void);
static void atr_handler(void);

/* global variables */
UINT8 adpu_status = APDU_STATE_IDLE;
UINT8 *apdu_buf = (UINT8 *)USI_DATA_BUF_ADDR;		// this addr is used only for USI data-exchange which is defined in memmap.h
													// If you want to use this address for other application, modify it first.
UINT8 *apdu_data = (UINT8 *)(USI_DATA_BUF_ADDR+0x40);

UINT8 apdu_cmdbuf[8];
UINT8 apdu_cnt = 0;
UINT16 apdu_datalen = 0;
UINT16 result_code = 0;
UINT32 apdu_addr = 0;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 init_apdu
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Init HW of USI.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void init_apdu(UINT32 usi_base_addr)
 {
 	UINT8 ret;
 	sUSIReg* usi_reg = (sUSIReg*)usi_base_addr;

 	usi_reg = (sUSIReg*)usi_base_addr;

 	// set USI control register1
 	usi_reg->USICR1 = 0x00; // DREN(Enable Delay Request), UART enable, WTEN enable

	// set USI control register2
 	usi_reg->USICR2 = 0xFF;

	//set WTR
	//USIWTRM = 0x12;

 	usi_reg->USIGTRL = 20;

	// Fsys=32MHz Fclk=2MHz F=372 D=1
 	usi_reg->USIBDR = 0x02;

	// set USI port control register
	//USIreg->USIPCR |= 0x20;	//open-drain mode isodata

 	usi_reg->USIFIFOINTCON = 0x00;

	//Clear USISR,USIRDR
	ret = usi_reg->USISR;
	if(ret & USISR_ATR_MASK)
	{
		usi_reg->USISR |= USISR_ATR_MASK; //clear ATR
		adpu_status = APDU_STATE_ATR;
		gusi_reg = usi_reg;		//ATR request on current USI port
     	//ATR Handler in Normal
		atr_handler();
	}
	ret = usi_reg->USIRDR;

	usi_reg->USIIER = 0x24; //enalbe recv interrupt(RDIE and ATR), 0x24;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 trans_byte
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Transmit a single byte.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void trans_byte(UINT8 data)
{
	while((gusi_reg->USISR & USISR_TDRE_MASK)==0)
	{
		;
	}

	gusi_reg->USITDR = data;

	// check runbit
	while((gusi_reg->USISR & USISR_TC_MASK)==0)
	{
		;
	}

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 send_atr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Send ATR string.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void send_atr(void)
{
	UINT8 i = 0;

	for ( i = 0 ; i < ATR_LENGTH; i++ )
	{
		trans_byte(atr_string[i]);
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_process
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Main process of USI.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void send_pts_ack(void)
{
	trans_byte(apdu_cmdbuf[0]);
	trans_byte(apdu_cmdbuf[1]);
	trans_byte(apdu_cmdbuf[2]);
	trans_byte(apdu_cmdbuf[3]);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_process
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Main process of USI.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void send_default_ack(void)
{
	trans_byte(0xFF);
	trans_byte(0x00);
	trans_byte(0xFF);
	gusi_reg->USIBDR = 0x02;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 pps_manager
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Manager of PPS.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void pps_manager(void)
{
	UINT8  i = 0;
	UINT16 temp = 0;

	if( apdu_cmdbuf[1] != INS_PPS ){//pps cmd error
		send_default_ack();
		return;
	}

	if((apdu_cmdbuf[0]^apdu_cmdbuf[1]^apdu_cmdbuf[2]) != apdu_cmdbuf[3]){//pps check byte error
		return;
	}

	temp = (((UINT16)apdu_cmdbuf[2] & 0x00ff) << 8);
	temp |= ((UINT16)apdu_cmdbuf[3] & 0x00ff);

	for ( i = 0; i < sizeof(fi_di_table)/2;i++ )
	{
		if ( temp == (UINT16)fi_di_table[i] )
		{
			send_pts_ack();

			gusi_reg->USIBDR = fd_cycle[i];

			return;
		}
	}
	if(i == sizeof(fi_di_table)/2)
	{
		send_default_ack();
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 atr_handler
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Handler of ATR.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void atr_handler(void)
{
	if(((gusi_reg->USICR1) & 0x10) == 0)
	{
		gusi_reg->USICR1 = 0x50;
		//USICR1 = 0x54;
		while(((gusi_reg->USISR) & USISR_TC_MASK) == USISR_TC_MASK);
		while(((gusi_reg->USISR) & USISR_TC_MASK) == 0);
	}
	//IO_WRITE8(0x00c30002,0x00);   //16MHz  Clock Divisor = 2
	delay(50);

    send_atr();			// 400-40000 cycle OK
    adpu_status = APDU_STATE_IDLE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_process
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Main process of USI.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void usi_en_wto(void)
{
	(gusi_reg->USICR1) |= USISR_WTO_MASK;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_process
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Main process of USI.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void usi_dis_wto(void)
{
	(gusi_reg->USICR1) &= ~USISR_WTO_MASK;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_interrput_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Init USI interrupt.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void usi_interrput_init(void)
{
	interrupt_setup(USI1_INT_NUM, 0, usi_isr);
	interrupt_setup(USI2_INT_NUM, 0, usi_isr);
	interrupt_setup(USI3_INT_NUM, 0, usi_isr);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_apdu_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Init APDU.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void usi_apdu_init(void)
{
	init_apdu(USI1_BASE);	  //USI1
	init_apdu(USI2_BASE);	  //USI2
	init_apdu(USI3_BASE);	  //USI3
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    ISR of USI.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void usi_isr(void)
{
	UINT8 usi_status;

	//indicate interrupt come from which USI
	switch(read_vec())
	{
		case INTERRUPT_SOURCE_USI1:
			gusi_reg = (sUSIReg*)USI1_BASE;
			break;
		case INTERRUPT_SOURCE_USI2:
			gusi_reg = (sUSIReg*)USI2_BASE;
			break;
		case INTERRUPT_SOURCE_USI3:
			gusi_reg = (sUSIReg*)USI3_BASE;
			break;
	}

	usi_status = gusi_reg->USISR;

	if(usi_status & USISR_ATR_MASK)//answer to reset
	{
		gusi_reg->USIBDR = 0x02;
        gusi_reg->USISR |= USISR_ATR_MASK; //clear ATR
        adpu_status = APDU_STATE_ATR;
     	//ATR Handler in ISR
		atr_handler();
        return;
    }

	//RDRF Receive Data Register Full Flag
	if(usi_status & USISR_RDRF_MASK)
	{
		while((usi_status & USISR_RDRF_MASK) == USISR_RDRF_MASK)
		{
			apdu_buf[apdu_cnt] = gusi_reg->USIRDR;
			apdu_cnt++;
			usi_status = gusi_reg->USISR;
		}

		if(adpu_status == APDU_STATE_IDLE)
		{
			if((apdu_buf[0] == 0xFF) && (apdu_cnt == 4)){//pps cmd
				__memcpy((unsigned char *)apdu_cmdbuf, (unsigned char *)apdu_buf, 4);
				adpu_status = APDU_STATE_PPS;
				apdu_cnt = 0;
			}
			else if((apdu_buf[0] == 0xFF) && (apdu_buf[1] == 0x00) && (apdu_cnt == 3)){//pps cmd
				__memcpy((unsigned char *)apdu_cmdbuf, (unsigned char *)apdu_buf, 3);
				adpu_status = APDU_STATE_PPS;
				apdu_cnt = 0;
			}
			else if(apdu_cnt == 5){//apdu cmd
				__memcpy((unsigned char *)apdu_cmdbuf, (unsigned char *)apdu_buf, 5);
				adpu_status = APDU_STATE_CMD;
				apdu_cnt = 0;

			}
		}
		else if((adpu_status == APDU_STATE_DATA) && (apdu_cnt == apdu_datalen)){
			adpu_status = APDU_STATE_DATA_OK;
			apdu_cnt = 0;
		}
		//PPS command Hander on ISR
		if(adpu_status == APDU_STATE_PPS)
		{
			//result_code = SW_NULL;
			usi_en_wto();
			pps_manager();
			usi_dis_wto();  //clear WTO by clear WTEN
			adpu_status = APDU_STATE_IDLE;
		}

		return;
	}

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_process
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Send PB byte if necessary.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void usi_send_pb (UINT8 val)
{
	/* this is for keep 12 etu */
	delay(0x10);
	trans_byte(val);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_send_status
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Send status of 16bits.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void usi_send_status(void)
{
	UINT8 sw1 = 0;
	UINT8 sw2 = 0;

	sw1 = (UINT8)(result_code >> 8);
	sw2 = (UINT8)result_code;

	if(result_code == SW_NULL)
	{
		usi_send_pb(apdu_cmdbuf[1]);
		result_code = 0;

		usi_en_wto();//¡¤¨¤?1¦Ì¨¨¡äy¨ºy?Y3?¨º¡À

	}
	else
	{
		trans_byte(sw1);
		trans_byte(sw2);
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_send_le_data
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Send LE data.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void usi_send_le_data(void)
{
	UINT16 i = 0,len = 0;

	if (apdu_cmdbuf[4] == 0)
	{
		len = 256;
	}
	else
	{
		len = apdu_cmdbuf[4];
	}

	for ( i = 0; i < len; i++ )
	{
		trans_byte(apdu_buf[i]);
	}
}


void usi_gpioconfig(UINT8 pcr,UINT8 ddr)
{
	USI1_CR1 = 0;
	USI1_CR2 = 0;
	USI1_PCR = pcr;	//ISODAT1 as GPIO
	USI1_DDR = ddr;	//ISODAT1 as output
	USI1_PDR = ddr;
}



void usi_gpiovalu(UINT8 ucval,BOOL ben)
{
	if( ben )
	{
		USI1_PDR |= ucval;
	}
	else
	{
		USI1_PDR &= ~ucval;
	}
}


#define USI_FILTER_CNT (0x80)
BOOL usi_readiodata()
{
	VUINT32 i;
	VUINT8 ret;
	VUINT8 reg;
	BOOL ret_val;

	ret_val = 0;
	ret = 0;
	for(i = 0; i < USI_FILTER_CNT; i++)
	{
		reg = ((USI1_PDR)&(0x04));
		if( ret != reg )
		{
			ret_val = 1;
			break;
		}
	}

	return ret_val;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_pin_config
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    config usi pins as gpio.
//
// Input:
//    	ucid
//		pin
//		dir
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL usi_pin_config(UINT8 ucid, UINT8 pin, UINT8 dir)
{
	sUSIReg* usi_reg = 0;

	usi_reg = (sUSIReg *)(g_usi_baseaddr[ucid]);

	/*enable/disable USI*/
	usi_reg->USIPCR |= 0xC0;	//config gpio

	if (dir == GPIO_OUTPUT)
	{
		usi_reg->USIDDR |= (1<<pin);//output
	}
	else if (dir == GPIO_INPUT)
	{
		usi_reg->USIDDR &= (~(1<<pin));//input
	}
	else
	{
		return FALSE;
	}

	return	TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_pin_read
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    read usi pins status as gpio.
//
// Input:
//    	ucid
//		pin
//
// Output:
//      Bit_SET or Bit_RESET
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 usi_pin_read(UINT8 ucid, UINT8 pin)
{
	sUSIReg* usi_reg = 0;
	UINT8 bitstatus = 0x00;

	usi_reg = (sUSIReg *)(g_usi_baseaddr[ucid]);

	bitstatus = usi_reg->USIPORT;
	if (bitstatus &(Bit_SET<<pin))
		bitstatus = Bit_SET;
	else
		bitstatus = Bit_RESET;

	return bitstatus;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_pin_write
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    read usi pins status as gpio.
//
// Input:
//    	ucid
//		pin
//		val
//
// Output:
//      TRUE or FALSE
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL usi_pin_write(UINT8 ucid, UINT8 pin, UINT8 val)
{
	sUSIReg* usi_reg = 0;

	usi_reg = (sUSIReg *)(g_usi_baseaddr[ucid]);

	if (val == Bit_SET)
		usi_reg->USIPORT |= (Bit_SET<<pin);
	else
		usi_reg->USIPORT &= (~(Bit_SET<<pin));

	return TRUE;
}

