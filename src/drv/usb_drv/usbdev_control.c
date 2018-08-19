// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usbdev_control.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "usb_reg.h"
#include "usb_const.h"
#include "ccm_reg.h"
#include "cpm_reg.h"
#include "int_reg.h"
#include "memmap.h"
#include "includes.h"



/* Global USB Register */
sUSBCFIFO_Reg* gUSBC_fifoReg;
sUSBCCommonReg* gUSBC_ComReg;
sUSBCIndexedReg* gUSBC_IdxReg;

//USB version(1--USB2.0;0--USB1.1)
unsigned char g_usbVer;

//usb the max packet size
unsigned short gTxMaxPacket = 0;
unsigned short gRxMaxPacket = 0;

unsigned char g_dev_std_req[8];

//CBW packet
unsigned long g_cbwPacket_l[8];
unsigned char* g_cbwPacket=(unsigned char*)g_cbwPacket_l;
	
//CSW packet
unsigned char g_cswPacket[13];

//USB data buffer1
volatile unsigned long g_databuf = 0x820000;

//indicate the start sector in reading device
unsigned long g_wrLBA;

//Save USB Address
volatile unsigned char g_USBAddrFlag;

volatile unsigned char g_USBNewAddr;	
//indicate which command is processed currently
volatile unsigned char g_bulkPhase;	

//indicate which sub command is processed currently
unsigned char g_subCmd;

//indicate the length in Once tranfer from PC to device
unsigned short g_transLens;

//indicate the transfer stage of USB1.1
unsigned char g_TxRxCounter;

//indicate the mode of reading device
unsigned char g_readMode; 

//global message queue for USB loop tasks.
volatile unsigned char g_msgflags;

unsigned char g_msgflags1;

//Suspend Mode Enable Flag(0-disable;1-enable)
unsigned char g_suspendMode;

//ChipTest Status
unsigned short g_Chiptest_Status;	//1-Selftest is running;0-Selftest finished
unsigned short g_Chiptest_Result;	//0-Selftest pass;Other-Selftest fail
unsigned short g_Chiptest_FailtoDo;	//0-After Selftest fail,system halt,Other-After fail,system go-on
unsigned short g_Chiptest_Enable;	//0-ChipTest Enable,Other-ChipTest Disable
//ChipTest Parameters
unsigned short g_trng_mode;//0x5a80;
unsigned short g_sm1_protect;//0x5a0c;
unsigned short g_sm4_protect;//0x5a03;
unsigned short g_rsa_protect;
//Bootloader Enable Flag
unsigned short g_BL_Enable = FALSE;
//Bootloader Password Success Flag
unsigned short g_PWD_Result = FALSE;	
//Bootloader Pwd fail Counter
unsigned short g_BL_FailCounter = 0;
//Bootloader Pwd Max fail time
unsigned short g_BL_MaxFail = BL_VERIFY_MAXCOUNTER;


unsigned long VendorReadFlag = 0;	//∂¡øÿ÷∆±‰¡ø
unsigned long RWDataAddr = EVB_SRAM_ADDR;
unsigned long RWDataLength = 0;
unsigned long InitData = 0;
unsigned long LoadDataAddr = 0;
unsigned long LoadDatalength = 0;
void (*dynamic)(void);


void USBDev_GetStatus(void);
void USBDev_GetDescriptor(void);
void USBDev_EP0_SendStall(void);
void write_ep0_buf(unsigned char *in_buf,unsigned short uiLen);

//USB Inquiry
void USBDev_Inquiry(void);
//USB Mode Sense
void USBDev_ModeSense(void);
//USB Request Sense
void USBDev_RequestSense(void);
//USB Read Capacity
void USBDev_ReadCapacity(void);
//Vendor Command Definition

void SetFIFO_Addr(unsigned long bufferAddr,unsigned char mode);
void UsbSetTXsize(UINT16 size,UINT8 mode);
void USBDev_EP1_RX_ISR(void);
void USBDev_EP1_TX_ISR(void);
void USBDev_EP0_ISR(void);
//Dynamic function point
//void (*dynamic)(void);

/*
Description:USB Read data from Endpoint FIFO
Inputs:
	ep,endpoint number
	out_buf,points to memory data will be moved to.
	uiLens,data length
*/
void read_ep_buf(unsigned char *out_buf,unsigned long ep,unsigned short uiLens)
{
	unsigned short	i=0;

	for(i=0;i<uiLens;i++)
	{
		out_buf[i]=IO_READ8(ep);
	}

}

/*
Description:USB write data to Endpoint FIFO
Inputs:
	ep,endpoint number
	out_buf,points to memory data will be moved to.
	uiLens,data length
*/
void  write_ep_buf(unsigned long ep,unsigned char *out_buf,unsigned short uiLens)
{
	unsigned short	i;
	for(i=0;i<uiLens;i++)
		IO_WRITE8(ep,out_buf[i]);
}

/*
Description:Set ep0 enter idle,ClearFeature request will clear STALL condition.
*/
void USBDev_EP0_SendStall(void)
{
	unsigned char ucReg=gUSBC_IdxReg->E0CSR_L;

	ucReg |=DEV_CSR0_SENDSTALL;
	gUSBC_IdxReg->E0CSR_L = ucReg;
}

/**************************************************************************************
Description:USB Write data to Endpoint0  FIFO,after write over,will generate a interrupt.
Inputs:
	in_buf,data source 
	uiLen,data length
**************************************************************************************/
void write_ep0_buf(unsigned char *in_buf,unsigned short uiLen)
{
	unsigned char ucReg=gUSBC_IdxReg->E0CSR_L;
	
	write_ep_buf(USB_FIFO_ENDPOINT_0,in_buf,uiLen);

	//set TxPktRdy =1 and DataEnd =1
	ucReg |= DEV_CSR0_DATAEND|DEV_CSR0_TXPKTRDY;
	gUSBC_IdxReg->E0CSR_L=ucReg;
	//It will generate a TX interrupt.
}

void USB_Init()
{
	g_cbwPacket=(unsigned char*)g_cbwPacket_l;
	g_databuf=USB_BUFFER_ADDR;

	//USB Interrupt and register Init
	g_usbVer = 1;//USB2.0,

	//Enable PHY Power Switch
	BIT_SET(CPM_PWRCR, PWRCR_PHY_PSWEN_BIT);			//enable usbphy power switch
	//delay at least 10us, sys clk is 40MHz, in release obj, one clock_cycle is 6 clock
	//so (40 * 10 / 6) is about 10us, we use 15us here.
	delay(100);
	BIT_CLR(CPM_PWRCR, PWRCR_PHY_I_ISOEN_BIT);
	BIT_CLR(CPM_PWRCR, PWRCR_PHY_O_ISOEN_BIT);		//disable usbphy isolation
	delay(100);
	BIT_CLR(CPM_PWRCR, PWRCR_PHY_RSTMASK_BIT);		//diable usbphy reset mask, release the reset signal
	//Enable PHY Regulator
	PHYPA_LOW = 0x3C;

	//Config 12MHz Clk
	CPM_STABLE = 0x00000100;
	CPM_OCSR |= 0x10;		//Enable 12MHz Clock


	g_cswPacket[0]=0x55;
	g_cswPacket[1]=0x53;
	g_cswPacket[2]=0x42;
	g_cswPacket[3]=0x53;	

	/* Global USB Register */
	//gUSBC_fifoReg = (sUSBCFIFO_Reg*)(USBC_BASEADDR+0x1A);
	gUSBC_fifoReg = (sUSBCFIFO_Reg*)(USBC_BASEADDR+0x60);

	gUSBC_ComReg = (sUSBCCommonReg*)USBC_BASEADDR;
	gUSBC_IdxReg = (sUSBCIndexedReg*)(USBC_BASEADDR+0x10);
	//USB data buffer
	g_databuf = USB_BUFFER_ADDR;
	//The suspend mode is disable before BULK-Only tranfer start
	g_suspendMode = 0;
	/* Setup USB register */
	//enable usb common interrupt
	//0		1		2		3		4		5		6		7 (bit)
	//Susp	Resume	Reset	SOF		Conn	Discon	SessReq	VBusErr
	gUSBC_ComReg->INTRUSBE = USB_INTERRUPT_RESET
							|USB_INTERRUPT_CONNECT
							|USB_INTERRUPT_DISCON
							|USB_INTERRUPT_SUSPEND
							|USB_INTERRUPT_RESUME;
	//enable ep0 and ep1 tx interrupts,clear other tx interrupts
	gUSBC_ComReg->INTRTXE_L = USB_INTERRUPT_EP0|(1<<USB_ENDPOINT_INDEX);
	//enable ep1 rx interrupt,clear other rx interrupts
	gUSBC_ComReg->INTRRXE_L = (1<<USB_ENDPOINT_INDEX);
	//ensure ep0 control/status regesters appeare in the memory map.
	gUSBC_ComReg->EINDEX = CONTROL_EP;

	//Enable Soft connection	
	if(g_usbVer == 1)
		gUSBC_ComReg->UCSR  = USB_POWER_SOFT_CONN|USB_POWER_HS_ENAB;
	else
		gUSBC_ComReg->UCSR  = USB_POWER_SOFT_CONN;	

	g_USBAddrFlag = 0;
	g_USBNewAddr = 0;

	BIT_SET(IO_READ32(EIC_IER), INTERRUPT_SOURCE_USB);
}

/*
Description:support usb high speed test mode
//\\add by ctzhu at 2008-04-08
*/
void USBDev_TestMode(void)
{
	unsigned char test_packet[53] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 
		0xAA, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 
		0xEE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xBF, 0xDF, 
		0xEF, 0xF7, 0xFB, 0xFD, 0xFC, 0x7E, 0xBF, 0xDF, 
		0xEF, 0xF7, 0xFB, 0xFD, 0x7E};
	
	switch(g_dev_std_req[5])
	{
		case 1:		//Test_J
			gUSBC_ComReg->TSTMODE = 0x02;
//			asm{wait}
			break;
		case 2:		//Test_K
			gUSBC_ComReg->TSTMODE = 0x04;
//			asm{wait}
			break;
		case 3:		//Test_SE0_NAK
			gUSBC_ComReg->TSTMODE = 0x01;
//			asm{wait}
			break;
		case 4:		//Test_Packet
			write_ep_buf(USB_FIFO_ENDPOINT_0,test_packet,53);
			gUSBC_IdxReg->E0CSR_L = 0x02;
			gUSBC_ComReg->TSTMODE = 0x08;
//			asm{wait}
			break;
		default:
			break;			
	}
}

/*
Description: Set the size of send data from FIFO
	Size = 0; Set the MAX vaule of data size(USB1.1/2.0)
	Size != 0; Set the request value of data size
*/
/*
void USBDev_SetTxSize(unsigned short Size)
{
	if(Size){
		//Set Tx Transfer Data size
		gUSBC_IdxReg->TXPSZR_L = Size;
		gUSBC_IdxReg->TXPSZR_H = (Size>>8);
	}else{
		//Set MAX Tx Transfer size
		if(g_usbVer == 1){
			gUSBC_IdxReg->TXPSZR_L = USB_MAX_PACKET_SIZE_LOW;
			gUSBC_IdxReg->TXPSZR_H = USB_MAX_PACKET_SIZE_HIGH;
		}else{
			gUSBC_IdxReg->TXPSZR_L = USB_MAX_PACKET_SIZE_LOW_V11;
			gUSBC_IdxReg->TXPSZR_H = USB_MAX_PACKET_SIZE_HIGH_V11;
		}	
	}
}*/

#define USB_SUSPEND_MODE1
//#define USB_SUSPEND_MODE2

void USBDev_Suspend(void)
{
//	unsigned int tmp;
//	int i;
	unsigned char ucMode;

	if(g_suspendMode == 1)
	{
		//Disable USB FILE Clock
		ucMode= gUSBC_ComReg->UCSR;
		ucMode |= USB_POWER_ENAB_SUSP;
		gUSBC_ComReg->UCSR = ucMode;


		//Enable USB FILE Clock
		ucMode= gUSBC_ComReg->UCSR;
		ucMode &= ~USB_POWER_ENAB_SUSP;	
		//ucMode |= USB_POWER_SOFT_CONN;	
		gUSBC_ComReg->UCSR = ucMode;
	}
}

/*
Description:USB Bus Reset Interrupt
*/
void USBDev_BusReset(void)
{
	unsigned char ucMode;
	unsigned char tempL, tempH;	
//    unsigned long i=0;
/*    
    while(i!=0x3ffff)
	{
		i++;
	}	 
*/	
	//write FAddr 0
	gUSBC_ComReg->FADDRR = 0;
	//access DATA_OUT_EP register map
	gUSBC_ComReg->EINDEX = USB_ENDPOINT_INDEX;
	//device into idle state
	//check whether device works on HS.
	ucMode = gUSBC_ComReg->UCSR; //need clear suspend flag?
	if(ucMode & 0x10)
		g_usbVer = 1;//USB2.0
	else
		g_usbVer = 0;
		
	//set FIFO size
	if(g_usbVer == 1)
	{
		gTxMaxPacket = USB_MAX_PACKET_SIZE;
		gRxMaxPacket = USB_MAX_PACKET_SIZE;
		gUSBC_fifoReg->TXFIFOSZ = 0x06;
		gUSBC_fifoReg->RXFIFOSZ = 0x06; 
	}else{
		gTxMaxPacket = USB_MAX_PACKET_SIZE_V11;
		gRxMaxPacket = USB_MAX_PACKET_SIZE_V11;	
		gUSBC_fifoReg->TXFIFOSZ = 0x03;
		gUSBC_fifoReg->RXFIFOSZ = 0x03;	
	}

	//set fifo offset address
	//gUSBC_fifoReg->TX_fifoadd_L = ((USB_FIFO_OFFSET>>3)&0x00FF);
	//gUSBC_fifoReg->TX_fifoadd_H = ((USB_FIFO_OFFSET>>11)&0x00FF);
	//gUSBC_fifoReg->RX_fifoadd_L = ((USB_FIFO_OFFSET>>3)&0x00FF);
	//gUSBC_fifoReg->RX_fifoadd_H = ((USB_FIFO_OFFSET>>11)&0x00FF);
	SetFIFO_Addr(0,0);		//default FIFO address
	
	if(g_usbVer == 1)
	{
	   tempL = USB_MAX_PACKET_SIZE_LOW;
	   tempH = USB_MAX_PACKET_SIZE_HIGH;		   
	}
	else
	{
	   tempL = USB_MAX_PACKET_SIZE_LOW_V11;
	   tempH = USB_MAX_PACKET_SIZE_HIGH_V11;			
	}

	gUSBC_IdxReg->TXCSR_L = DEV_TXCSR_CLR_DATA_TOG;
	gUSBC_IdxReg->TXCSR_H = 0;

	gUSBC_IdxReg->TXMAXP_L = tempL;
	gUSBC_IdxReg->TXMAXP_H = tempH;

 	gUSBC_IdxReg->RXCSR_L = 0x80;
 	gUSBC_IdxReg->RXCSR_H = 0x0;
 
	gUSBC_IdxReg->RXMAXP_L = tempL;
	gUSBC_IdxReg->RXMAXP_H = tempH;
	//=================================
    
	//Flush Tx Ep FIFO
	gUSBC_IdxReg->TXCSR_L = DEV_TXCSR_FLUSH_FIFO;
	
	//Flush Rx Ep FIFO
	gUSBC_IdxReg->RXCSR_L = DEV_RXCSR_FLUSH_FIFO;
	
}

void USBDev_Ep0Handler(void)
{
	unsigned char ucReq=0;
//    volatile unsigned short wValue=0;

	//read stand request from USBC FIFO to g_dev_std_req
	read_ep_buf(g_dev_std_req,USB_FIFO_ENDPOINT_0,8);
	
	ucReq=g_dev_std_req[1];//dev_std_req->bRequest;
	
	switch(ucReq)
	{
		case 0://Get Status
			USBDev_GetStatus();
			break;
		case 1:
			//ClearFeature
			//set ServiceRxPktRdy to clear RxPktRdy and set DataEnd
			gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY|DEV_CSR0_DATAEND;
			break;
		case 3:
			//SetFeature
			//set ServiceRxPktRdy to clear RxPktRdy and set DataEnd
			gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY|DEV_CSR0_DATAEND;
			if(g_dev_std_req[0]==0x0)	//test mode
				USBDev_TestMode();
			break;
		case 5:
			//SetAddress
            ucReq = g_dev_std_req[2];// & 0x7f;dev_std_req->wValue>>8
			//set ServiceRxPktRdy to clear RxPktRdy and set DataEnd
			gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY|DEV_CSR0_DATAEND;
			
			g_USBNewAddr = ucReq;
			g_USBAddrFlag = 1;
			break;
		case 6://Get Descriptor
			USBDev_GetDescriptor();
			break;
		case 8:
			//GetConfiguration
			//set ServiceRxPktRdy to clear RxPktRdy
			gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY|DEV_CSR0_DATAEND;
				
			write_ep0_buf(&ucReq,1);			
			break;
		case 9:
			//SetConfiguration
			//set ServiceRxPktRdy to clear RxPktRdy and set DataEnd
			gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY|DEV_CSR0_DATAEND;
			break;
		case 10:
			//GetInterface		
			gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY;
			write_ep0_buf(&ucReq,1);
			break;		
		case 11:
			//SetInterface
			gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY|DEV_CSR0_DATAEND;			
			break;
		case 0xFE://0xa1
			//GetMaxLUN
			ucReq=0;
			//set ServiceRxPktRdy to clear RxPktRdy
			gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY;
			write_ep0_buf(&ucReq,1);			
			break;				
		case 0xFF://0x21:
			//ClassReset
			//write FAddr 0
			gUSBC_ComReg->FADDRR = 0;
			//write	Index 1
			gUSBC_ComReg->EINDEX = DATA_IN_EP;
			//Flush Tx Ep FIFO
			gUSBC_IdxReg->TXCSR_L = DEV_TXCSR_FLUSH_FIFO;
			//Flush Rx Ep FIFO
			gUSBC_IdxReg->RXCSR_L = DEV_RXCSR_FLUSH_FIFO;
			//write	Index 0
			gUSBC_ComReg->EINDEX = CONTROL_EP;
			//set ServiceRxPktRdy to clear RxPktRdy and set DataEnd
			gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY|DEV_CSR0_DATAEND;			
			break;
		default:
			USBDev_EP0_SendStall();
			break;	
	}
}


/*
Description:USB standard command GetDescriptor
*/
void USBDev_GetDescriptor(void)
{
	unsigned char i;
	unsigned char USBDEV_Descriptor[18];
	unsigned char USBDEV_Configuration_Descriptor[32];
	unsigned char USBDEV_String_Descriptor[26];
	unsigned char ucReg=g_dev_std_req[6];//dev_std_req->wCount>>8;
	unsigned char reqIndex=g_dev_std_req[3]; //=dev_std_req->wValue & 0x0F;
	unsigned char ucIndex=g_dev_std_req[2];//=dev_std_req->wValue>>8;
	//set ServiceRxPktRdy to clear RxPktRdy
	gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY;

	//Init all Descriptors
	for(i=0;i<18;i++)
	{
		USBDEV_Descriptor[i] = USB_Device_Descriptor[i];
	}
	for(i=0;i<32;i++)
	{
		USBDEV_Configuration_Descriptor[i] = USB_Configuration_Descriptor[i];
	}
	for(i=0;i<26;i++)
	{
		USBDEV_String_Descriptor[i] = USB_String_Descriptor[i];
	}
	
	switch(reqIndex)
	{
		//get device descriptor request
		case 1:
		{
			if(ucReg<19)
			{
				write_ep0_buf((unsigned char*)USBDEV_Descriptor,ucReg);
			}
			else
			{
				write_ep0_buf((unsigned char*)USBDEV_Descriptor,8);
			}
			break;
		}
		//get configuration descriptor request
		case 2:
		{						
			if(ucReg<10)
			{
				//in normal,first getting configuration descriptor only is to get 
				//configuration size
				write_ep0_buf((unsigned char*)USBDEV_Configuration_Descriptor,ucReg);
			}
			else
			{
				if(g_usbVer==0)
				{
					//USB1.1,change packet size
					USBDEV_Configuration_Descriptor[22]=0x40;
					USBDEV_Configuration_Descriptor[23]=0x00;
					USBDEV_Configuration_Descriptor[29]=0x40;
					USBDEV_Configuration_Descriptor[30]=0x00;
				}
				write_ep0_buf((unsigned char*)USBDEV_Configuration_Descriptor,0x20);
			}
			break;
		}
		//get string descriptor request
		case 3:
		{
			if(ucReg<3 )
			{
				USBDEV_String_Descriptor[1]=0x03;
				if (ucIndex==0)
				{
					USBDEV_String_Descriptor[0]=0x04;
				}
				else
				{
					if(ucIndex==3)//serial code
					{
						USBDEV_String_Descriptor[0]=0x1A;
					}
					else if(ucIndex==1)
					{
						USBDEV_String_Descriptor[0]=18;
					}
					else if(ucIndex==2)
					{
						USBDEV_String_Descriptor[0]=26;
					}
				}
				//in normal,first getting configuration descriptor only is to get
				//configuration size
				write_ep0_buf((unsigned char*)USBDEV_String_Descriptor,ucReg);
			}
			else
			{
				if(ucIndex==0)
				{
					USBDEV_String_Descriptor[0]=0x04;
					USBDEV_String_Descriptor[1]=0x03;
					USBDEV_String_Descriptor[2]=0x09;
					USBDEV_String_Descriptor[3]=0x04;
					write_ep0_buf((unsigned char*)USBDEV_String_Descriptor,4);
				}
				else
				{	//read manufacturer and product string
					if(ucIndex==3)
					{	//serial code
						ucReg=0x1A;
					}
					else if(ucIndex==1)
					{	//manufacturer string
						USBDEV_String_Descriptor[0]=18;
						ucReg=8;
					}
					else if(ucIndex==2)
					{	//product string
						USBDEV_String_Descriptor[0]=26;
						ucReg=12;
					}
					write_ep0_buf((unsigned char*)USBDEV_String_Descriptor,ucReg);
				}
			}
			break;
		}
		case 6://DEVICE_QUALIFIER
		{
			if(ucReg<19)
			{
				write_ep0_buf((unsigned char*)USB_Device_Qualifier_Descriptor,ucReg);
			}
			else
			{
				write_ep0_buf((unsigned char*)USB_Device_Qualifier_Descriptor,8);
			}
			break;
		}
		//get other_speed_configuration descriptor
		case 7:
		{
			USBDEV_Configuration_Descriptor[1]=0x07;//other_speed_configuration
			if(ucReg<10)
			{
				//in normal,first getting configuration descriptor only is to get 
				//configuration size
				write_ep0_buf((unsigned char*)USBDEV_Configuration_Descriptor,ucReg);
			}
			else
			{		
				USBDEV_Configuration_Descriptor[22]=0x40;
				USBDEV_Configuration_Descriptor[23]=0x00;
				USBDEV_Configuration_Descriptor[29]=0x40;
				USBDEV_Configuration_Descriptor[30]=0x00;
				write_ep0_buf((unsigned char*)USBDEV_Configuration_Descriptor,0x20);
			}
			break;
		}
		default:
		{
			USBDev_EP0_SendStall();
			break;	
		}
	}
}

/*
Description:USB standard command GetStatus
*/
void USBDev_GetStatus(void)
{
	unsigned char txdat[2]={0,0};
	
	//set ServiceRxPktRdy to clear RxPktRdy and set DataEnd
	gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY|DEV_CSR0_DATAEND;

    switch(g_dev_std_req[0])//dev_std_req->bmRequestType
	{
		case 0x80:
		case 0x81:
			write_ep0_buf(txdat,2);
			break;
		default:
	        USBDev_EP0_SendStall();
			break;
	}	
	
}

/*
Description:Inquiry
*/
void USBDev_Inquiry(void)
{
	//response inquiry command data
	unsigned char SCSI_Inquiry[36]=
	{
	 	0x00,
	 	0x80,	//removal disk,if hard disk the value is 0
		0x04,
		0x02,
		
		0x1f,	//Additional Length		
		0x00, 	//reserved
		0x00, 	//reserved
		0x00,	//reserved
		
		'G',	//Vendor Identification string,default is "Generic"
		'e',
		'n',
		'e',
		'r',
		'i',
		'c',
		0x20,
		
		'F', 	//Product Identification string,default is "Flash Disk"
		'l',
		'a', 	
		's',
		'h',
		0x20,
		'D',
		'i',
		's',
		'k',
		0x20,
		0x20,
		0x20,
		0x20,
		0x20,
		0x20,
		
		0x31, 	//Product Revision,1.0
		0x2e,
		0x30,
		0x30,
	 };
	//Set Suspend enable flag
	g_suspendMode = 1;
	 	
	//response inquiry command data packet  to host
	USBDev_Packet_BulkIn((unsigned char *)SCSI_Inquiry,36,0);
}

/*
Description:Command 1a
*/
void USBDev_ModeSense(void)
{
	unsigned char SCSIDATA_Mode_Sense_1a[4]={0x03,0x00,0x80,0x00};		//Write protect

	//Send Mode Sense data packet to host
	USBDev_Packet_BulkIn((unsigned char *)SCSIDATA_Mode_Sense_1a,4,0);
}

/*
Description:SCSICMD Request Sense
*/
void USBDev_RequestSense(void)
{
	//scsi command request sense data,18B
	unsigned char SCSIDATA_RequestSense[18]=
	{
			/*
	        0x70,
	        0x00,
	        0x02,		//no media

	        0x00,		        
	        0x00,
	        0x00,
	        0x00,
	        0x06,
	        0x00,
	        0x00,
	        0x00,
	        0x00,

	        0x3a,
	        0x00,		        
	        0x00,
	        0x00,
	        0x00,
	        0x00,
	        */
	       	0x70,0x00,0x05,0x00,		//Unsupport CDB command	        
	        0x00,0x00,0x00,0x0a,
	        0x00,0x00,0x00,0x00,
	        0x24,0x00,0x00,0x00,
	        0x00,0x00
	} ;

	//response request sense command data packet to host
	USBDev_Packet_BulkIn(SCSIDATA_RequestSense,18,0);
}

void USBDev_ReadCapacity()
{	
	//response read capacities command data 
	unsigned char SCSIDATA_ReadCapacities[]=
	{
		 0x00,//reserved
		 0x00,//reserved
		 0x00,//reserved
		 0x08,//Capacity List Length
		 
		 0xff, //number of block   MSB
		 0xff, //number of block    |
		 0xff, //number of block    |
		 0xfe, //number of block   LSB
		 
		 0x00,
		 0x00,  // length of block
		 0x02,
		 0x00
	};

	if(g_bulkPhase == 0x23)
		//response read capacity command data packet to host
		USBDev_Packet_BulkIn(SCSIDATA_ReadCapacities,12,0);
	else
		//response read capacity command data packet to host
		USBDev_Packet_BulkIn(SCSIDATA_ReadCapacities+4,8,0);	
}

void ClearRx()
{
    unsigned char ucReg = 0;
	//clear Rx
	ucReg = gUSBC_IdxReg->RXCSR_L;
	ucReg &=0xFE;	//Clear RxPktRdy
	gUSBC_IdxReg->RXCSR_L = ucReg;	
}

void SetTx()
{
	unsigned char ucReg = 0;
	ucReg = gUSBC_IdxReg->TXCSR_L;
	ucReg |= 0x01;	//Set TxPktRdy
	gUSBC_IdxReg->TXCSR_L = ucReg;	
}

void ClearUnderRun()
{
	unsigned char ucReg = 0;
	ucReg = gUSBC_IdxReg->TXCSR_L;
	ucReg &= 0xFB;
	gUSBC_IdxReg->TXCSR_L = ucReg;
}

//set fifo offset address(0~0x2000,only 8k SRAM can set to be FIFO)
void SetFIFO_Addr(unsigned long bufferAddr,unsigned char mode)
{
	//gUSBC_ComReg->EINDEX = USB_ENDPOINT_INDEX;
	
	if(mode==0)
	{	
		//reset to default fifo address
		gUSBC_fifoReg->TX_fifoadd_L = ((USB_FIFO_OFFSET>>3)&0x00FF);
		gUSBC_fifoReg->TX_fifoadd_H = ((USB_FIFO_OFFSET>>11)&0x00FF);
		gUSBC_fifoReg->RX_fifoadd_L = ((USB_FIFO_OFFSET>>3)&0x00FF);
		gUSBC_fifoReg->RX_fifoadd_H = ((USB_FIFO_OFFSET>>11)&0x00FF);
	}
	else if(mode==1)
	{
		//Set Tx fifo Address
		gUSBC_fifoReg->TX_fifoadd_L = ((bufferAddr>>3)&0x00FF);
		gUSBC_fifoReg->TX_fifoadd_H = ((bufferAddr>>11)&0x00FF);	
	}
	else if(mode==2)
	{
		//Set Rx fifo Address
		gUSBC_fifoReg->RX_fifoadd_L = ((bufferAddr>>3)&0x00FF);
		gUSBC_fifoReg->RX_fifoadd_H = ((bufferAddr>>11)&0x00FF);
	
	}
}

/*
Description: Send packet to host,don't use DMA.(BULK-IN to host)
flag--0,normal,flag--1,CSW packet
*/
void USBDev_Packet_BulkIn(unsigned char *pDataBuf,unsigned short uiLength,unsigned char flag)
{
//	unsigned char ucReg;

 	UsbSetTXsize(uiLength,0);

	//write data into TX FIFO and wait for send
	gUSBC_ComReg->EINDEX = USB_ENDPOINT_INDEX;
	write_ep_buf(USB_ENDPOINT_FIFO_ADDR,pDataBuf,uiLength);

	SetTx();		//set TxPktRdy=1

	if(flag)
	{
		g_bulkPhase =0xFF;
		g_subCmd = 0xFF;
	}
}

void USBDev_Polling(void)
{
	//Endpoint1 RX handler
	if(g_msgflags&0x10)
	{
		g_msgflags &=0xEF;	//Clear RX Interrupt Bit
		USBDev_EP1_RX_ISR();
	}

	//device send data to host
	if(g_msgflags1 & (1<<USB_ENDPOINT_INDEX))    //OK
	{
		g_msgflags1 &=(~(1<<USB_ENDPOINT_INDEX));
		USBDev_EP1_TX_ISR();
	}

	// if bus reset
	if(g_msgflags & 0x04)   //OK
	{
		g_msgflags &=0xFB;
		USBDev_BusReset();
	}

	//to process setup packet   //OK
	if(g_msgflags1 & 0x1)
	{
		if(g_USBAddrFlag == 1){
			gUSBC_ComReg->FADDRR = g_USBNewAddr;
			g_USBAddrFlag = 0;
		}
		g_msgflags1 &=0xFE;
		USBDev_EP0_ISR();
	}

	// if suspend change
 	if(g_msgflags & 0x1)      //OK
	{
		g_msgflags &=0xFE;
#ifdef __USB_SUSPEND_EN__
		USBDev_Suspend();
#endif
	}
}
