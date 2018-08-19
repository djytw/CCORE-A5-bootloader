// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usb_const.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef  __USBDEV_CONST__
#define	 __USBDEV_CONST__

#include "memmap.h"

#define BL_VERIFY					{0x55,0xaa,0x5a,0xa5,0x66,0x99,0x69,0x96,0x12,0x34,0x56,0x78}
#define BL_VERIFY_MAXCOUNTER	10

#define EVB_SRAM_ADDR			0x00800000
//#define USER_DATA_ADDR			0x00800200


#define USB_EP1_TEST

//#define USB_FIFO_OFFSET			0x1000
#define USB_FIFO_OFFSET			0

#define USBDMA_BURST_LEN		0
#define USBDMA_MODE1

//current endpoint MACRO
#ifdef USB_EP1_TEST
#define		USB_ENDPOINT_FIFO_ADDR			USB_FIFO_ENDPOINT_1
#define		USB_ENDPOINT_INDEX				INDEX_EP1
#endif
#ifdef USB_EP2_TEST
#define		USB_ENDPOINT_FIFO_ADDR			USB_FIFO_ENDPOINT_2
#define		USB_ENDPOINT_INDEX				INDEX_EP2
#endif
#ifdef USB_EP3_TEST
#define		USB_ENDPOINT_FIFO_ADDR			USB_FIFO_ENDPOINT_3
#define		USB_ENDPOINT_INDEX				INDEX_EP3
#endif
#ifdef USB_EP4_TEST
#define		USB_ENDPOINT_FIFO_ADDR			USB_FIFO_ENDPOINT_4
#define		USB_ENDPOINT_INDEX				INDEX_EP4
#endif
#ifdef USB_EP5_TEST
#define		USB_ENDPOINT_FIFO_ADDR			USB_FIFO_ENDPOINT_5
#define		USB_ENDPOINT_INDEX				INDEX_EP5
#endif
#ifdef USB_EP6_TEST
#define		USB_ENDPOINT_FIFO_ADDR			USB_FIFO_ENDPOINT_6
#define		USB_ENDPOINT_INDEX				INDEX_EP6
#endif
#ifdef USB_EP7_TEST
#define		USB_ENDPOINT_FIFO_ADDR			USB_FIFO_ENDPOINT_7
#define		USB_ENDPOINT_INDEX				INDEX_EP7
#endif


//endpoint define
#define		CONTROL_EP									0
#define		DATA_IN_EP                               	1
#define		DATA_OUT_EP                              	1
#define		INDEX_EP1									1
#define		INDEX_EP2									2
#define		INDEX_EP3									3
#define		INDEX_EP4									4
#define		INDEX_EP5									5
#define		INDEX_EP6									6
#define		INDEX_EP7									7

//usb power mode select
#define		USB_POWER_ENAB_SUSP							0x01
#define		USB_POWER_SUSP_MODE							0x02
#define		USB_POWER_RESUME	             			0x04
#define		USB_POWER_RESET								0x08
#define		USB_POWER_HS_MODE							0x10
#define		USB_POWER_HS_ENAB							0x20
#define		USB_POWER_SOFT_CONN							0x40
#define		USB_POWER_ISO_UPDATE				  	  	0x80

//usb common interrupt number	
#define		USB_INTERRUPT_SUSPEND						0x01
#define		USB_INTERRUPT_RESUME							0x02
#define		USB_INTERRUPT_RESET							0x04
#define		USB_INTERRUPT_SOF								0x08
#define		USB_INTERRUPT_CONNECT						0x10
#define		USB_INTERRUPT_DISCON							0x20
#define		USB_INTERRUPT_SESSREQ						0x40
#define		USB_INTERRUPT_VBUSERR						0x80

//bulk transfer packet size 
#define		USB_MAX_PACKET_SIZE							512
#define		USB_MAX_PACKET_SIZE_LOW						0x00
#define		USB_MAX_PACKET_SIZE_HIGH					0x02
#define		USB_MAX_PACKET_SIZE_V11						64
#define		USB_MAX_PACKET_SIZE_LOW_V11					0x40
#define		USB_MAX_PACKET_SIZE_HIGH_V11				0x00


//usb tx interrupt number
#define		USB_INTERRUPT_EP0							0x01
#define		USB_TX_INTERRUPT_EP1						0x02
#define		USB_TX_INTERRUPT_EP2						0x04
#define		USB_TX_INTERRUPT_EP3						0x08
#define		USB_TX_INTERRUPT_EP4						0x10
#define		USB_TX_INTERRUPT_EP5						0x20
#define		USB_TX_INTERRUPT_EP6						0x40
#define		USB_TX_INTERRUPT_EP7						0x80

//Usb Rx Interrupt Number
#define		USB_RX_INTERRUPT_EP0						0x01
#define		USB_RX_INTERRUPT_EP1						0x02
#define		USB_RX_INTERRUPT_EP2						0x04
#define		USB_RX_INTERRUPT_EP3						0x08
#define		USB_RX_INTERRUPT_EP4						0x10
#define		USB_RX_INTERRUPT_EP5						0x20
#define		USB_RX_INTERRUPT_EP6						0x40
#define		USB_RX_INTERRUPT_EP7						0x80

//Device CSR0 Bit Define
#define    	DEV_CSR0_RXPKTRDY                           0x01
#define    	DEV_CSR0_TXPKTRDY                           0x02
#define    	DEV_CSR0_SENTSTALL                          0x04
#define    	DEV_CSR0_DATAEND                            0x08
#define    	DEV_CSR0_SETUPEND                           0x10
#define    	DEV_CSR0_SENDSTALL                          0x20
#define    	DEV_CSR0_SERVICE_RXPKTRDY					0x40
#define    	DEV_CSR0_SERVICE_SETUPEND					0x80

//TX Register Bit Low as Device
#define		DEV_TXCSR_TXPKTRDY							0x01
#define		DEV_TXCSR_FIFO_NOT_EMPTY					0x02
#define		DEV_TXCSR_UNDER_RUN							0x04
#define		DEV_TXCSR_FLUSH_FIFO						0x08
#define		DEV_TXCSR_SEND_STALL						0x10
#define		DEV_TXCSR_SENT_SATLL						0x20
#define		DEV_TXCSR_CLR_DATA_TOG						0x40
#define		DEV_TXCSR_INCOMP_TX							0x80

//TX Register Bit High as Device
#define		DEV_TXCSR_DMAMODE							0x04
#define		DEV_TXCSR_FRC_DATA_TOG						0x08
#define		DEV_TXCSR_DMA_ENAB							0x10
#define		DEV_TXCSR_TXMODE							0x20
#define		DEV_TXCSR_ISO								0x40
#define		DEV_TXCSR_AUTO_SET							0x80

//RX Register Bit Low as Device
#define		DEV_RXCSR_RXPKTRDY							0x01
#define		DEV_RXCSR_FIFOFULL							0x02
#define		DEV_RXCSR_OVERRUN							0x04
#define		DEV_RXCSR_DATA_ERROR						0x08
#define		DEV_RXCSR_FLUSH_FIFO						0x10
#define		DEV_RXCSR_SENDSTALL							0x20
#define		DEV_RXCSR_SENTSTALL							0x40
#define		DEV_RXCSR_CLR_DATA_TOG						0x80

//RX Register Bit High as Device
#define		DEV_RXCSR_INCOMP_RX							0x01
#define		DEV_RXCSR_DMAMODE							0x08
#define		DEV_RXCSR_DISNYET							0x10
#define		DEV_RXCSR_DMA_ENAB							0x20
#define		DEV_RXCSR_ISO								0x40
#define		DEV_RXCSR_AUTOCLEAR							0x80


//Transmit direct	
#define		TX											1
#define		RX											0

//scsi command
#define 	SCSICMD_TEST_UNIT_READY						0x00
#define 	SCSICMD_REQUEST_SENSE                   	0x03
#define 	SCSICMD_INQUIRY                        		0x12
#define 	SCSICMD_MODE_SENSE_06                   	0x1a
#define 	SCSICMD_READ_FORMAT_CAPACITIES          	0x23
#define 	SCSICMD_READ_CAPACITY                   	0x25
#define 	SCSICMD_READ_10                         	0x28

//vendor command
#define		VENDOR_BL_VERIFY							0xD0
#define		VENDOR_IDENTIFY_CMD							0xD1
#define		VENDOR_R_W_CMD								0xD2
//vendor sub command
#define		VENDOR_IDENTIFY_SUBCMD						0x01
#define		VENDOR_READ_SUBCMD							0x01
#define		VENDOR_DISABLEREAD_SUBCMD					0x02
#define		VENDOR_WRITE_SUBCMD							0x03

#define		VENDOR_MASSERASE_SUBCMD						0x08
#define		VENDOR_PAGEERASE_SUBCMD						0x09
#define 	VENDOR_PROGRAM_SUBCMD						0x0a
#define		VENDOR_CHANGEPOWMODE_SUBCMD					0x0b
#define		VENDOR_RUNDYACODE_SUBCMD					0xcc

#define 	VENDOR_SM4ENCODE_SUBCMD						0x1a
#define		VENDOR_SM4DISENCODE_SUBCMD					0x1b
#define		VENDOR_READRUESLT_SUBCMD					0x1c




#define DT_DEVICE                     1
#define DT_CONFIGURATION    	      2
#define DT_STRING                     3
#define DT_INTERFACE                  4
#define DT_ENDPOINT                   5
#define DT_DEVICE_QUALIFIER           6
#define DT_OTHER_SPEED_CONDIGURATION  7
#define DT_INTERFACE_POWER            8

#define TRANS_ISO			    0x01
#define TRANS_BULK             	0x02
#define TRANS_INT			    0x03

#define 	DEVICE_TYPE                                   		0x1
#define 	CONFIG_TYPE                                   		0x2
#define 	STRING_TYPE                                   		0x3
#define 	INTERFACE_TYPE                                		0x4
#define 	ENDPOINT_TYPE                                 		0x5
#define		DEVICE_QUALIFIER                              		0x6
#define 	OTHER_SPEED                                   		0x7
#define 	INTERFACE_POWER                               		0x8
#define 	REPORT_TYPE                                   		0x22
#endif
