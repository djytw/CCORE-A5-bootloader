// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usb_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __USBDEV_REG_H__
#define __USBDEV_REG_H__

#include "includes.h"
#include "memmap.h"

/* Data Definition */
/******************************
*Notice: USB register is little endian
*	      Access these register by byte
*******************************/
//Data Struct of Common USB Registers
typedef struct _sUSBCCommonReg{
	volatile unsigned char	FADDRR;	//Function address register
	volatile unsigned char	UCSR;		//USB control and status register
	
	volatile unsigned char	INTRTX_L;	//Low byte of Interrupt register for Endpoint0 and Tx Endpoint
	volatile unsigned char	INTRTX_H;	//High byte of Interrupt register for Endpoint0 and Tx Endpoint	
	
	volatile unsigned char	INTRRX_L;	//Low byte of Interrupt register for Rx Endpoint
	volatile unsigned char	INTRRX_H;	//High byte of Interrupt register for Rx Endpoint
	
	volatile unsigned char	INTRTXE_L;	//Low byte of Interrupt enable register for IntrTx
	volatile unsigned char	INTRTXE_H;	//High byte of Interrupt enable register for IntrTx
	
	volatile unsigned char	INTRRXE_L;	//Low byte of Interrupt enable register for IntrRx
	volatile unsigned char	INTRRXE_H;	//High byte of Interrupt enable register for IntrRx
	
	volatile unsigned char	INTRUSB;	//Interrupt register for common USB interrupts
	volatile unsigned char	INTRUSBE;	//Interrupt enable register for IntrUSB
	
	volatile unsigned char	FNUMR_L;	//Low byte of Frame number
	volatile unsigned char	FNUMR_H;	//High byte of Frame number
	
	volatile unsigned char	EINDEX;		//Index register for selecting the endpoint status and control register
	volatile unsigned char	TSTMODE;	//Enables the USB test modes
} sUSBCCommonReg;

//Data Struct of Indexed Registers
typedef struct _sUSBCIndexedReg{
	volatile unsigned char	TXMAXP_L;		//Low byte of Maximum packet size for peripheral Tx endpoint
	volatile unsigned char	TXMAXP_H;		//High byte of Maximum packet size for peripheral Tx endpoint
	union{
		  volatile unsigned char	E0CSR_L;	//Low byte of Control Status register for Endpoint0
		  volatile unsigned char	TXCSR_L;	//Low byte of Control Status register for peripheral Tx endpoint
		};
	union{
		  volatile unsigned char	E0CSR_H;	//High byte of Control Status register for Endpoint0
		  volatile unsigned char	TXCSR_H;	//High byte of Control Status register for peripheral Tx endpoint
		};
	volatile unsigned char	RXMAXP_L;			//Low byte of Maximum packet size for peripheral Rx endpoint
	volatile unsigned char	RXMAXP_H;			//High byte of Maximum packet size for peripheral Rx endpoint
	
	volatile unsigned char	RXCSR_L;			//Low byte of Control Status register for peripheral Rx endpoint
	volatile unsigned char	RXCSR_H;			//High byte of Control Status register for peripheral Rx endpoint
	union{
		  volatile unsigned char	E0COUNTR_L;	//Low byte of Number of received bytes in Endpoint0 FIFO
		  volatile unsigned char	RXCount_L;		//Low byte of Number of bytes in peripheral Rx endpoint FIFO
		};
	union{
		  volatile unsigned char	E0COUNTR_H;	//High byte of Number of received bytes in Endpoint0 FIFO
		  volatile unsigned char	RXCount_H;		//High byte of Number of bytes in peripheral Rx endpoint FIFO
		};
	volatile unsigned char	TXTYPE;
	union{
		  volatile unsigned char	NAKLIMIT0;
		  volatile unsigned char	TXINTERVAL;
		};
	volatile unsigned char RXTYPE;
	volatile unsigned char RXINTERVAL;
} sUSBCIndexedReg;

//Dynamic FIFO
typedef	struct	_sUSBCFIFO_Reg{
	volatile unsigned char	OTGCTRL;
	volatile unsigned char	RESERVED;
	volatile unsigned char	TXFIFOSZ;	//Tx Endpoint FIFO size,double buffer only set in one register(TX_fifosz/RX_fifosz)
	volatile unsigned char	RXFIFOSZ;	//Rx Endpoint FIFO size,MAX FIFO size is 1024byte
	volatile unsigned char	TX_fifoadd_L;	//Tx Endpoint FIFO address(Low 8bit)
	volatile unsigned char	TX_fifoadd_H;	//Tx Endpoint FIFO address(High 8bit)
	volatile unsigned char	RX_fifoadd_L;	//Rx Endpoint FIFO address(Low 8bit)
	volatile unsigned char	RX_fifoadd_H;	//Rx Endpoint FIFO address(High 8bit)
} sUSBCFIFO_Reg;
//Define the USB buffer start address
#define		USB_BUFFER_ADDR					(EVB_SRAM_ADDR+USB_FIFO_OFFSET)
//#define		USB_BUFFER_ADDR					(EVB_SRAM_ADDR+0x1000)
//Define the USB buffer size(unit:byte)used in USB Demo
//#define		USB_BUFFER_SIZE_H				0x40
//#define		USB_BUFFER_SIZE_L				0x00

//usb FIFO register
#define		USB_FIFO_ENDPOINT_0				USBC_BASEADDR + 0x20
#define		USB_FIFO_ENDPOINT_1				USBC_BASEADDR + 0x24
#define		USB_FIFO_ENDPOINT_2				USBC_BASEADDR + 0x28
#define		USB_FIFO_ENDPOINT_3				USBC_BASEADDR + 0x2C
#define		USB_FIFO_ENDPOINT_4				USBC_BASEADDR + 0x30
#define		USB_FIFO_ENDPOINT_5				USBC_BASEADDR + 0x34
#define		USB_FIFO_ENDPOINT_6				USBC_BASEADDR + 0x38
#define		USB_FIFO_ENDPOINT_7				USBC_BASEADDR + 0x3C
//Half-Word Access
#define		USB_FIFO_EP1TX_PTR0				USBC_BASEADDR + 0x40
#define		USB_FIFO_EP1TX_PTR1				USBC_BASEADDR + 0x42
#define		USB_FIFO_EP2TX_PTR0				USBC_BASEADDR + 0x44
#define		USB_FIFO_EP2TX_PTR1				USBC_BASEADDR + 0x46
#define		USB_FIFO_EP3TX_PTR0				USBC_BASEADDR + 0x48
#define		USB_FIFO_EP3TX_PTR1				USBC_BASEADDR + 0x4A
#define		USB_FIFO_EP0_PTR0				USBC_BASEADDR + 0x58

//USB Internal DMA Register
//DMA configurable up to 8 channels
#define DMA_INTR							(USBC_BASEADDR +0x200) //8bit
//channel 1
#define DMA_CNTL1							(USBC_BASEADDR +0x204) //16bit
#define DMA_CNTL1_L							(USBC_BASEADDR +0x204)
#define DMA_CNTL1_H							(USBC_BASEADDR +0x205)
#define DMA_ADDR1							(USBC_BASEADDR +0x208) //32bit
#define DMA_COUNT1							(USBC_BASEADDR +0x20c) //32bit
//channel 2
#define DMA_CNTL2							(USBC_BASEADDR +0x214) //16bit
#define DMA_CNTL2_L							(USBC_BASEADDR +0x214)
#define DMA_CNTL2_H							(USBC_BASEADDR +0x215)
#define DMA_ADDR2							(USBC_BASEADDR +0x218) //32bit
#define DMA_COUNT2							(USBC_BASEADDR +0x21c) //32bit
//channel 3
#define DMA_CNTL3							(USBC_BASEADDR +0x224) //16bit
#define DMA_CNTL3_L							(USBC_BASEADDR +0x224)
#define DMA_CNTL3_H							(USBC_BASEADDR +0x225)
#define DMA_ADDR3							(USBC_BASEADDR +0x228) //32bit
#define DMA_COUNT3							(USBC_BASEADDR +0x22c) //32bit
//channel 4
#define DMA_CNTL4							(USBC_BASEADDR +0x234) //16bit
#define DMA_CNTL4_L							(USBC_BASEADDR +0x234)
#define DMA_CNTL4_H							(USBC_BASEADDR +0x235)
#define DMA_ADDR4							(USBC_BASEADDR +0x238) //32bit
#define DMA_COUNT4							(USBC_BASEADDR +0x23c) //32bit
//channel 5
#define DMA_CNTL5							(USBC_BASEADDR +0x244) //16bit
#define DMA_CNTL5_L							(USBC_BASEADDR +0x244)
#define DMA_CNTL5_H							(USBC_BASEADDR +0x245)
#define DMA_ADDR5							(USBC_BASEADDR +0x248) //32bit
#define DMA_COUNT5							(USBC_BASEADDR +0x24c) //32bit
//channel 6
#define DMA_CNTL6							(USBC_BASEADDR +0x254) //16bit
#define DMA_CNTL6_L							(USBC_BASEADDR +0x254)
#define DMA_CNTL6_H							(USBC_BASEADDR +0x255)
#define DMA_ADDR6							(USBC_BASEADDR +0x258) //32bit
#define DMA_COUNT6							(USBC_BASEADDR +0x25c) //32bit
//channel 7
#define DMA_CNTL7							(USBC_BASEADDR +0x264) //16bit
#define DMA_CNTL7_L							(USBC_BASEADDR +0x264)
#define DMA_CNTL7_H							(USBC_BASEADDR +0x265)
#define DMA_ADDR7							(USBC_BASEADDR +0x268) //32bit
#define DMA_COUNT7							(USBC_BASEADDR +0x26c) //32bit
//channel 8
#define DMA_CNTL8							(USBC_BASEADDR +0x274) //16bit
#define DMA_CNTL8_L							(USBC_BASEADDR +0x274)
#define DMA_CNTL8_H							(USBC_BASEADDR +0x275)
#define DMA_ADDR8							(USBC_BASEADDR +0x278) //32bit
#define DMA_COUNT8							(USBC_BASEADDR +0x27c) //32bit

#define INTR_DMA1							(1<<0)
#define INTR_DMA2							(1<<1)
#define INTR_DMA3							(1<<2)
#define INTR_DMA4							(1<<3)
#define INTR_DMA5							(1<<4)
#define INTR_DMA6							(1<<5)
#define INTR_DMA7							(1<<6)
#define INTR_DMA8							(1<<7)

//dma cntl
#define CNTL_DMAEN(x)						((x)<<0)
#define CNTL_DIRECTION(x)					((x)<<1)
#define CNTL_DMAMODE(x)						((x)<<2)
#define CNTL_INTERE(x)						((x)<<3)
#define CNTL_EP(x)							((x)<<4)
#define CNTL_BUSERR(x)						((x)<<8)
#define CNTL_BURSTMODE(x)					((x)<<9)		
			
	//standard Device Descriptor
extern const unsigned char USB_Device_Descriptor[18];
	//Device Qualifier Descriptor
extern const unsigned char USB_Device_Qualifier_Descriptor[10];
	//configuration descriptor
extern const unsigned char USB_Configuration_Descriptor[];
	//standard string Descriptor,serial number
extern const unsigned char USB_String_Descriptor[];
	//MBR const data
extern const unsigned char MBR[];
	//DBR const data
extern const unsigned char DBR[];

/* Global USB Register */
extern sUSBCCommonReg* gUSBC_ComReg;
extern sUSBCIndexedReg* gUSBC_IdxReg;
extern sUSBCFIFO_Reg* gUSBC_fifoReg; 

//global message queue for USB loop tasks.
extern volatile unsigned char g_msgflags;
extern unsigned char g_msgflags1;

//USB version(1--USB2.0;0--USB1.1)
extern unsigned char g_usbVer;

//usb the max packet size
extern unsigned short gTxMaxPacket;
extern unsigned short gRxMaxPacket;

//Save USB Address
extern	volatile unsigned char g_USBAddrFlag;
extern	volatile unsigned char g_USBNewAddr;//indicate which command is processed currently
extern	volatile unsigned char g_bulkPhase;	

//indicate which sub command is processed currently
extern unsigned char g_subCmd;

extern unsigned char g_dev_std_req[];

//CBW packet
extern unsigned long g_cbwPacket_l[];
extern unsigned char* g_cbwPacket;
	
//CSW packet
extern unsigned char g_cswPacket[];

//USB data buffer1
extern volatile unsigned long g_databuf;

//indicate the start sector in reading device
extern unsigned long g_wrLBA;

//indicate the length in Once tranfer from PC to device
extern unsigned short g_transLens;

//indicate the transfer stage of USB1.1
extern unsigned char g_TxRxCounter;

//indicate the mode of reading device
extern unsigned char g_readMode; 

//ChipTest Status
extern unsigned short g_Chiptest_Status;	//1-Selftest is running;0-Selftest finished
extern unsigned short g_Chiptest_Result;	//0-Selftest pass;Other-Selftest fail
extern unsigned short g_Chiptest_FailtoDo;	//0-After Selftest fail,system halt,Other-After fail,system go-on
extern unsigned short g_Chiptest_Enable;	//0-ChipTest Enable,Other-ChipTest Disable
//ChipTest Parameters
//ChipTest Parameters
extern unsigned short g_trng_mode;
extern unsigned short g_sm4_protect;
extern unsigned short g_rsa_protect;

//Bootloader Enable Flag
extern unsigned short g_BL_Enable;

//Bootloader Password Success Flag
extern unsigned short g_PWD_Result;	

//Bootloader Pwd fail Counter
extern unsigned short g_BL_FailCounter;

//Bootloader Pwd Max fail time
extern unsigned short g_BL_MaxFail;

/* USB Function definition */
//Init USB registers
extern void USB_Init();

extern void USBDev_Polling(void);

//USB Interrrupt Function
extern void USBDev_ISR();

//USB Read data from Endpoint FIFO
extern void read_ep_buf(unsigned char *out_buf,unsigned long ep,unsigned short uiLens);

//USB write data to Endpoint FIFO
extern void write_ep_buf(unsigned long ep,unsigned char *out_buf,unsigned short uiLens);

//USB Suspend Interrupt
extern void USBDev_Suspend(void);

//USB Bus Reset Interrupt
extern void USBDev_BusReset(void);

//USB Endpoint0 Handler
extern void USBDev_Ep0Handler(void);

//Clear RxPktRdy
extern void ClearRx();

//Send packet to host.(BULK-IN to host)
//flag--0,normal,flag--1,CSW packet
extern void USBDev_Packet_BulkIn(unsigned char *pDataBuf,unsigned short uiLength,unsigned char flag);

//Dynamic function point
extern void (*dynamic)(void);

extern void USB_int_Service(void);

#endif
