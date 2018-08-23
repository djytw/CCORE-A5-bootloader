// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usb_cdc_control.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "usb_reg.h"
#include "usb_const.h"
#include "int_reg.h"
#include "cpm_reg.h"
#include "ccm_reg.h"


#define STATUS_NULL			0x00
#define RCV_COMPLETE		0x01 //接收完成
#define SEND_START			0x02 //开始发送
#define SEND_COMPLETE		0x03 //发送完成
#define PROCESS_COMPLETE 	0x04 //处理完成

#define		USB_ENDPOINT_FIFO_ADDR			USB_FIFO_ENDPOINT_1
#define		USB_ENDPOINT_INDEX		       INDEX_EP1
#define 	USB_MAX_PACKET_SIZE_EP0                     64

/* Global USB Register */
extern sUSBCFIFO_Reg* gUSBC_fifoReg;
extern sUSBCCommonReg* gUSBC_ComReg;
extern sUSBCIndexedReg* gUSBC_IdxReg;


//usb the max packet size
extern unsigned short gTxMaxPacket ;
extern unsigned short gRxMaxPacket ;

//USB version(1--USB2.0;0--USB1.1)
extern unsigned char g_usbVer;
//Suspend Mode Enable Flag(0-disable;1-enable)
extern unsigned char g_suspendMode;
//Save USB Address
extern volatile unsigned char g_USBNewAddr;
//indicate which command is processed currently
extern volatile unsigned char g_bulkPhase;

extern unsigned char g_dev_std_req[8];
extern volatile unsigned char g_msgflags;
extern  unsigned char g_msgflags1;

#define USB_CDC_EN  1
UINT8  g_uchUSBStatus;
UINT8 *g_EP1BufAddr;
UINT8 *g_EP2BufAddr;
UINT8 *g_EP3BufAddr;

// 0 is Ep0 发送第一包数据
// 1 is EP0 发送从第二包开始的数据
UINT8 g_Ep0Data_Stage;
UINT8* gp_Ep0_Descriptor;

UINT8 LineCoding[7]={0x80,0x25,0x00,0x00,0x00,0x00,0x08};		//9600,无校验,8bit

extern const UINT8 USB_cdc_Device_Descriptor[18];

	//Device Qualifier Descriptor
extern const unsigned char USB_cdc_Device_Qualifier_Descriptor[10];

extern const UINT8 USB_cdc_Configuration_Descriptor[] ;



extern const unsigned char USB_cdc_String_Descriptor[];

//USB Language ID
extern const UINT8 UsbLanguageID[4] ;


//Manufacturer String
extern const UINT8 UsbStrDescManufacturer[12];


//Product String
extern const UINT8 UsbStrDescProduct[30];



//Serial Number
extern const UINT8 UsbStrDescSerialNumber[34] ;


/*
Description:USB Read data from Endpoint FIFO
Inputs:
	ep,endpoint number
	out_buf,points to memory data will be moved to.
	uiLens,data length
*/
extern void read_ep_buf(unsigned char *out_buf, unsigned long ep, unsigned short uiLens);


/*
Description:USB write data to Endpoint FIFO
Inputs:
	ep,endpoint number
	out_buf,points to memory data will be moved to.
	uiLens,data length
*/
extern void  write_ep_buf(unsigned long ep, unsigned char *out_buf, unsigned short uiLens);

/*
Description:Set ep0 enter idle,ClearFeature request will clear STALL condition.
*/
extern void USBDev_EP0_SendStall(void);

/**************************************************************************************
Description:USB Write data to Endpoint0  FIFO,after write over,will generate a interrupt.
Inputs:
	in_buf,data source
	uiLen,data length
**************************************************************************************/
extern void write_ep0_buf(unsigned char *in_buf,unsigned short uiLen);


void USBDev_TestMode(void);
/*************************************************
Function: write_ep0_buf_notEnd
Description: 通过端点0发送数据，不是最后一包
Calls:
Called By:
Input:
    INT8U* in_buf:要发送的数据的起始地址
    INT16U uiLens:要发送的数据长度
Output: 无
Return: 无
Others: 无
*************************************************/
void write_ep0_buf_notEnd(UINT8 *in_buf, UINT16 uiLen)
{
	UINT8  ucReg  = gUSBC_IdxReg->E0CSR_L;
//	unsigned short i = 0;

	write_ep_buf(USB_FIFO_ENDPOINT_0,in_buf,uiLen);
	ucReg  |=  DEV_CSR0_TXPKTRDY;    // buffer填满后，告诉USB开始发送，不是最后一包
	gUSBC_IdxReg->E0CSR_L  =  ucReg;
}


//set fifo offset address(0~0x2000,only 8k SRAM can set to be FIFO)
extern void SetFIFO_Addr(unsigned long bufferAddr,unsigned char mode);


extern void ClearRx(void);

extern void SetTx(void);




/*
Description: Set the size of send data from FIFO
	Size = 0; Set the MAX vaule of data size(USB1.1/2.0)
	Size != 0; Set the request value of data size
*/
void USBDev_SetTxSize(unsigned short Size)
{
	if(Size)
	{
		//Set Tx Transfer Data size
		gUSBC_IdxReg->TXMAXP_L = Size;
		gUSBC_IdxReg->TXMAXP_H = (Size>>8);
	}
	else
	{
		//Set MAX Tx Transfer size
		if(g_usbVer == 1)
		{
			gUSBC_IdxReg->TXMAXP_L = USB_MAX_PACKET_SIZE_LOW;
			gUSBC_IdxReg->TXMAXP_H = USB_MAX_PACKET_SIZE_HIGH;
		}else{
			gUSBC_IdxReg->TXMAXP_L = USB_MAX_PACKET_SIZE_LOW_V11;
			gUSBC_IdxReg->TXMAXP_H = USB_MAX_PACKET_SIZE_HIGH_V11;
		}
	}
}


/*
Description:USB Bus Reset Interrupt
*/
void USB_CDC_BusReset(void)
{
//	unsigned char ucMode;
	unsigned char tempL, tempH;
	unsigned char i = 0;;
	//unsigned short EPxBufAddr;

	msg_printf("USBDev_BusReset\r\n");
	//g_EP1BufAddr = (UINT8*)USBEP1_BUF_ADDR;
	//g_EP2BufAddr = (UINT8*)USBEP2_BUF_ADDR;
	//g_EP3BufAddr = (UINT8*)USBEP3_BUF_ADDR;
	gUSBC_ComReg->FADDRR = 0;

	//write FAddr 0
	for (i=0; i<3; i++)
	{
		//access DATA_OUT_EP register map
		gUSBC_ComReg->EINDEX =  INDEX_EP1+i;
		//device into idle state
		//check whether device works on HS.
		//ucMode = gUSBC_ComReg->UCSR; //need clear suspend flag?
		//if(ucMode & 0x10)
			//g_usbVer = 1;//USB2.0
		//else
			//g_usbVer = 0;

		//set FIFO size
		if(g_usbVer == 1)
		{
			gTxMaxPacket = USB_MAX_PACKET_SIZE;
			gRxMaxPacket = USB_MAX_PACKET_SIZE;
			gUSBC_fifoReg->TXFIFOSZ = 0x06;
			gUSBC_fifoReg->RXFIFOSZ = 0x06;
		}
		else
		{
			gTxMaxPacket = USB_MAX_PACKET_SIZE_V11;
			gRxMaxPacket = USB_MAX_PACKET_SIZE_V11;
			gUSBC_fifoReg->TXFIFOSZ = 0x03;
			gUSBC_fifoReg->RXFIFOSZ = 0x03;
		}

		//set fifo offset address
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

	 	gUSBC_IdxReg->RXCSR_L = DEV_RXCSR_CLR_DATA_TOG;
	 	gUSBC_IdxReg->RXCSR_H = 0x0;

		gUSBC_IdxReg->RXMAXP_L = tempL;
		gUSBC_IdxReg->RXMAXP_H = tempH;
		//=================================

		//Flush Tx Ep FIFO
		gUSBC_IdxReg->TXCSR_L = DEV_TXCSR_FLUSH_FIFO;

		//Flush Rx Ep FIFO
		gUSBC_IdxReg->RXCSR_L = DEV_RXCSR_FLUSH_FIFO;
	}

}

/*
Description:USB standard command GetStatus
*/
void USB_CDC_GetStatus(void)
{
	unsigned char txdat[2]={0,0};

	//set ServiceRxPktRdy to clear RxPktRdy and set DataEnd
	gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY|DEV_CSR0_DATAEND;

    switch(g_dev_std_req[0])//dev_std_req->bmRequestType
	{
		case 0x80:
		case 0x81:
		case 0x82:
			write_ep0_buf(txdat,2);
			break;
		default:
	        USBDev_EP0_SendStall();
			break;
	}

}

void write_ep0_buf_long(UINT16 requstLen, UINT8 *databuf, UINT16 dataLen)
{
	UINT16 sentLen = 0;

	if (requstLen > dataLen)
		requstLen = dataLen;

	if (dataLen > USB_MAX_PACKET_SIZE_EP0)		//描述符大小超过一个包大小，需分包发送
	{
		if (requstLen > USB_MAX_PACKET_SIZE_EP0)
		{
#ifndef USB_USEINT
			gUSBC_ComReg->INTRTXE_L &=0xfe;		//关闭EP0中断
#endif
			while ((requstLen-sentLen) > USB_MAX_PACKET_SIZE_EP0)
			{
				write_ep0_buf_notEnd(databuf+sentLen,USB_MAX_PACKET_SIZE_EP0);
				while((gUSBC_ComReg->INTRTX_L &0x01)==0x00);
				sentLen += USB_MAX_PACKET_SIZE_EP0;
			}
			write_ep0_buf(databuf+sentLen,requstLen-sentLen);
#ifndef USB_USEINT
			gUSBC_ComReg->INTRTXE_L |=0x01;		//打开EP0中断
#endif
		}
		else
		{
			write_ep0_buf(databuf,requstLen);
		}
	}
	else	//一包就可发送完成
	{
		requstLen = (requstLen>dataLen)?dataLen:requstLen;		//host可能会发送长度字节为FF的请求
		write_ep0_buf(databuf,requstLen);
	}
}
unsigned char control_transfer_end_flag =0;
/*
Description:USB standard command GetDescriptor
*/
void USB_CDC_GetDescriptor(void)
{
	unsigned char i;
	unsigned char USBDEV_Descriptor[18];
	unsigned short Configuration_Descriptor_Len;
	unsigned char USBDEV_Configuration_Descriptor[0x56];
	unsigned char ucReg = g_dev_std_req[6];//dev_std_req->wCount>>8;
	unsigned char ucReg2 = g_dev_std_req[7];
	unsigned char reqIndex = g_dev_std_req[3]; //=dev_std_req->wValue & 0x0F;
	unsigned char ucIndex = g_dev_std_req[2];//=dev_std_req->wValue>>8;
	unsigned short ucRegLen;

	//set ServiceRxPktRdy to clear RxPktRdy
	gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY;
	ucRegLen = ((UINT16)ucReg2<<8)+ucReg;
	//Init all Descriptors
	for(i=0; i<18; i++)
	{
		USBDEV_Descriptor[i] = USB_cdc_Device_Descriptor[i];//ok
	}

	Configuration_Descriptor_Len = (USB_cdc_Configuration_Descriptor[3]<<8)+USB_cdc_Configuration_Descriptor[2];
	for(i = 0; i < Configuration_Descriptor_Len; i++)
	{
		USBDEV_Configuration_Descriptor[i] = USB_cdc_Configuration_Descriptor[i];//
	}

	msg_printf("reqIndex = %x Configuration_Descriptor_Len = %x\r\n",reqIndex,Configuration_Descriptor_Len);
	switch(reqIndex)
	{
		//get device descriptor request
		case DEVICE_TYPE://device descriptor
		{
			if(ucReg <= USB_cdc_Device_Descriptor[0])
			{
				write_ep0_buf((unsigned char*)USBDEV_Descriptor, ucReg);
			}
			else
			{
				write_ep0_buf((unsigned char*)USBDEV_Descriptor, 8);
			}
			break;
		}
		//get configuration descriptor request
		case CONFIG_TYPE:
		{

			write_ep0_buf_long(ucRegLen, (UINT8*)USB_cdc_Configuration_Descriptor, Configuration_Descriptor_Len);
			control_transfer_end_flag =1;

			break;
		}
		//get string descriptor request
		case STRING_TYPE:
		{
			if (ucIndex==0)
			{
				//USBDEV_String_Descriptor[0]=0x04;
				write_ep0_buf((UINT8*)UsbLanguageID, 4);
			}
			else if(ucIndex==1)
			{
				//USBDEV_String_Descriptor[0]=18;
				ucReg = (ucReg>UsbStrDescManufacturer[0])?UsbStrDescManufacturer[0]:ucReg;
				write_ep0_buf((UINT8*)UsbStrDescManufacturer, ucReg);
			}
			else if(ucIndex==2)
			{
				//USBDEV_String_Descriptor[0]=26;
				ucReg = (ucReg>UsbStrDescProduct[0])?UsbStrDescProduct[0]:ucReg;
				write_ep0_buf((UINT8*)UsbStrDescProduct,ucReg);
			}
			else if(ucIndex==3)//serial code
			{
				//USBDEV_String_Descriptor[0]=0x1A;
				ucReg = (ucReg>UsbStrDescSerialNumber[0])?UsbStrDescSerialNumber[0]:ucReg;
				write_ep0_buf((UINT8*)UsbStrDescSerialNumber,ucReg);
			}
			break;
		}
		case DEVICE_QUALIFIER:
		{
			if(ucReg <= USB_cdc_Device_Qualifier_Descriptor[0])
			{
				write_ep0_buf((unsigned char*)USB_cdc_Device_Qualifier_Descriptor, ucReg);
			}
			else
			{
				write_ep0_buf((unsigned char*)USB_cdc_Device_Qualifier_Descriptor, 8);
			}
			break;
		}
		//get other_speed_configuration descriptor
		case OTHER_SPEED:
		{
			USBDEV_Configuration_Descriptor[1]=0x07;//other_speed_configuration
			if(ucReg < 10)
			{
				//in normal,first getting configuration descriptor only is to get
				//configuration size
				write_ep0_buf((unsigned char*)USBDEV_Configuration_Descriptor,ucReg);
			}
			else
			{
				//USBDEV_Configuration_Descriptor[22]=0x40;
				//USBDEV_Configuration_Descriptor[23]=0x00;
				//USBDEV_Configuration_Descriptor[29]=0x40;
				//USBDEV_Configuration_Descriptor[30]=0x00;
				//write_ep0_buf((unsigned char*)USBDEV_Configuration_Descriptor,0x20);
			}
			break;
		}
		case REPORT_TYPE:                 //HID协议里规定的报告描述符
		{
			ucReg = 0x34;

			break;
		}
		default:
		{
			USBDev_EP0_SendStall();
			break;
		}
	}
}

void USB_CDC_ClearRx0(void)
{
	//set ServiceRxPktRdy to clear RxPktRdy
	gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY;
}


void USB_CDC_Ep0Handler(void)
{
	unsigned char ucReq=0;
//	unsigned char i;
	int loop;
	//read stand request from USBC FIFO to g_dev_std_req


	if(gUSBC_IdxReg->E0COUNTR_L != 8)		//设置串口属性，非setup包，而是out包
	{
		read_ep_buf(LineCoding, USB_FIFO_ENDPOINT_0, 7);
		gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY;
		return;
	}

	read_ep_buf(g_dev_std_req, USB_FIFO_ENDPOINT_0, 8);


	ucReq = g_dev_std_req[1];//dev_std_req->bRequest;
	#if 1
	msg_printf("std req:");
	for(loop=0;loop<8;loop++)
		msg_printf("%02x ",g_dev_std_req[loop]);
	msg_printf("\r\n");

	#endif
	if(1 == ((g_dev_std_req[0]>>5) & 0x3))//类请求
	{

		gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY;

		switch(ucReq)
		{
			case 0x20:		//CDC协议，SET_LINE_CODING
			{
				//直接返回，等待接收数据过程的OUT包

				break;
			}
			case 0x21:	//CDC协议，GET_LINE_CODING
			{

				write_ep0_buf((unsigned char *)LineCoding, 7);

				break;
			}
			case 0x22:					//SET_CONTROL_LINR_STATE
			{
				break;
			}
			case 0x23:
			{
				break;
			}
			default:
			{
				USBDev_EP0_SendStall();
				break;
			}
		}
	}
	else
	{
		switch(ucReq)
		{
			case 0:
				USB_CDC_GetStatus();
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
				//gpram_USBAddrFlag = 1;
				g_USBNewAddr = ucReq;
				break;
			case 6:
				USB_CDC_GetDescriptor();
				break;
			case 8:
				//GetConfiguration
				//set ServiceRxPktRdy to clear RxPktRdy
				gUSBC_IdxReg->E0CSR_L = DEV_CSR0_SERVICE_RXPKTRDY|DEV_CSR0_DATAEND;

				write_ep0_buf(&ucReq, 1);
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

			default:
				USBDev_EP0_SendStall();
				break;
		}
	}
}


/*
Description: USB Endpoint0 Interrupt Service Routine,respond control transfer
*/
void USB_CDC_EP0_ISR(void)
{
	unsigned char ucReg=0;

	//enable ep0 register map to be accessed
	gUSBC_ComReg->EINDEX = CONTROL_EP;

	ucReg = gUSBC_IdxReg->E0CSR_L;

	//clear SentStall bit
	if(ucReg &0x04)
	{
		ucReg &=0xFB;
	}
	//clear SetupEnd bit
	if(ucReg & 0x10)
	{
		//set ServiceSetupEnd = 1;
		ucReg |=0x80;
	}
	gUSBC_IdxReg->E0CSR_L = ucReg;

	//if RxPktRdy=1,Data come into ep0 buf
	if((ucReg & DEV_CSR0_RXPKTRDY) || g_Ep0Data_Stage)
	{
		USB_CDC_Ep0Handler();
	}
}

void USB_CDC_ISR(void)
{
	
	UINT8  ucISR;
	UINT8  index;

	index = gUSBC_ComReg->EINDEX;	//解决USB中断模式的问题。先保存端点，执行完后恢复端点。

	//check common interrupt
	g_msgflags |= gUSBC_ComReg->INTRUSB;
	//check TX interrupt
	g_msgflags1 |=gUSBC_ComReg->INTRTX_L;
	//Check RX interrupt
	ucISR = gUSBC_ComReg->INTRRX_L;


	if(ucISR & (1<<USB_ENDPOINT_INDEX))
 		g_msgflags |= 0x10;

	//to process setup packet   //OK
	if(g_msgflags1 & 0x1)
	{
		if(g_USBNewAddr)
		{
			gUSBC_ComReg->FADDRR = g_USBNewAddr;
			g_USBNewAddr = 0;	//set usb address once
		}
		g_msgflags1 &= 0xFE;
		USB_CDC_EP0_ISR();
	}
	//Endpoint1 RX handler
	if(g_msgflags&0x10)
	//if (ucISR & (1<<USB_ENDPOINT_INDEX))
	{
		g_msgflags &= 0xEF;	//Clear RX Interrupt Bit
		g_uchUSBStatus |= BIT0;
	}
#if(USB_CDC_EN)
	if ((ucISR & (1<<INDEX_EP2)))
	{
		g_uchUSBStatus |= BIT1;
	}
#endif
	//device send data to host
	if(g_msgflags1 & (1<<USB_ENDPOINT_INDEX))    //OK
	{
		g_msgflags1 &=(~(1<<USB_ENDPOINT_INDEX));
		g_uchUSBStatus |= BIT4;
	}


	// if bus reset
	if(g_msgflags & 0x04)   //OK
	{
		g_msgflags &= 0xFB;
		USB_CDC_BusReset();

	}
	if(g_msgflags & 0x1)      //OK
	{
		g_msgflags &=0xFE;
		//USBDev_Suspend();
	}
	//Clear Last Completed Command
	if(g_bulkPhase == 0xFF)
		g_msgflags1 &= (~(1<<USB_ENDPOINT_INDEX));

	gUSBC_ComReg->EINDEX = index; 	//恢复端点
}

/*************************************************
Function: usb_cdc_send
Description: USB端点1发送一包数据
Calls:
Called By:
Input:
    INT8U *buf:发送数据的起始地址
    INT16U len:发送数据的长度
Output: 无
Return: 无
Others: 无
*************************************************/
void usb_cdc_send(UINT8 usb_ep, UINT8 *buf, UINT16 len)
{
	if ((usb_ep == CONTROL_EP)||(usb_ep > INDEX_EP7))
		return ;
	//access DATA_OUT_EP register map
    msg_printf("usb_cdc_send begin\r\n");
	gUSBC_ComReg->EINDEX = INDEX_EP1;//DEV_TXCSR_TXPKTRDY

	while((gUSBC_IdxReg->TXCSR_L & DEV_TXCSR_TXPKTRDY) == DEV_TXCSR_TXPKTRDY);//检查发送缓冲是否有数据，等待为空；
	USBDev_SetTxSize(len);

	//write data into TX FIFO and wait for send
	write_ep_buf(USB_ENDPOINT_FIFO_ADDR+(usb_ep-1)*0x04, buf, len);

	SetTx();		//set TxPktRdy=1
	msg_printf("usb_cdc_send end\r\n");
	gUSBC_ComReg->EINDEX = INDEX_EP2;//
}

/*************************************************
Function: usb_cdc_receive
Description: USB端点1接收一包数据
Calls:
Called By:
Input:
    INT8U *buf:接收数据的起始地址
Output: 无
Return: 接收数据的长度
Others: 无
*************************************************/
UINT16 usb_cdc_receive(UINT8 usb_ep, UINT8 *buf)
{
	UINT16   uiRxCount = 0;
	UINT8    ucRegLow;

	if ((usb_ep == CONTROL_EP)||(usb_ep > INDEX_EP7))
		return uiRxCount;

	//access DATA_OUT_EP register map
	gUSBC_ComReg->EINDEX = usb_ep;
	ucRegLow = gUSBC_IdxReg->RXCSR_L;
	//Clear sentstall and restart data toggle.
	if(ucRegLow & DEV_RXCSR_SENTSTALL)
	{
		ucRegLow &= 0xBF;//clear SendStall bit
		ucRegLow |= DEV_RXCSR_CLR_DATA_TOG;//set ClrDataTog
		gUSBC_IdxReg->RXCSR_L = ucRegLow;
	}

	//Start receive data packet
	if(ucRegLow & DEV_RXCSR_RXPKTRDY)	 //RxPktRdy=1
	{
		uiRxCount = gUSBC_IdxReg->RXCount_H;
		uiRxCount <<= 8;
		uiRxCount += gUSBC_IdxReg->RXCount_L;

		read_ep_buf(buf, USB_ENDPOINT_FIFO_ADDR+((usb_ep-1)<<2), uiRxCount);
		ClearRx();
	}
	return uiRxCount;
}

void USB_CDC_Init(void)
{
	g_cbwPacket=(unsigned char*)g_cbwPacket_l;
	g_databuf=USB_BUFFER_ADDR;

	//USB Interrupt and register Init
	g_usbVer = 0;//USB2.0,

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
	gUSBC_ComReg->INTRUSBE = USB_INTERRUPT_RESET|USB_INTERRUPT_CONNECT|USB_INTERRUPT_DISCON|USB_INTERRUPT_SUSPEND|USB_INTERRUPT_RESUME;
	//enable ep0 and ep1 tx interrupts,clear other tx interrupts

	gUSBC_ComReg->INTRTXE_L = USB_INTERRUPT_EP0|(1<<INDEX_EP1)|(1<<INDEX_EP3);
	gUSBC_ComReg->INTRRXE_L = (1<<INDEX_EP2);

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


