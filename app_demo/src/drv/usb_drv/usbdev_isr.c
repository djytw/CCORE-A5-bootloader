// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usbdev_isr.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "usb_reg.h"
#include "usb_const.h"


//add end
void USB_MS_ISR(void);
void USBDev_EP1_TX_ISR(void);
void USBDev_EP1_TX_ISR(void);
void USBDev_Data_BulkOut(void);
void USBDev_Data_BulkIn(void);
//Vendor Command Definition



/*
Description:USB interrupt service routine
*/
volatile unsigned int g_Dma_Done;  //Dma complete flag
void USB_MS_ISR(void)
{
	//DMA
	g_Dma_Done = IO_READ8(DMA_INTR);
	//check common interrupt
	g_msgflags |= gUSBC_ComReg->INTRUSB;
		
	//check TX interrupt
	g_msgflags1 |=gUSBC_ComReg->INTRTX_L;

	//Check RX interrupt
	if((gUSBC_ComReg->INTRRX_L)&(1<<USB_ENDPOINT_INDEX))
 		g_msgflags |= 0x10;

	//Flush USB FIFO

	if((g_usbVer == 1))
		gUSBC_IdxReg->TXCSR_L = DEV_TXCSR_FLUSH_FIFO;
		
	//Clear Last Completed Command		
	if(g_bulkPhase == 0xFF)
		g_msgflags1 &= (~(1<<USB_ENDPOINT_INDEX));
}


/*
Description: USB Endpoint0 Interrupt Service Routine,respond control transfer
*/
void USBDev_EP0_ISR(void)
{
	unsigned char ucReg=0;

	//enable ep0 register map to be accessed
	gUSBC_ComReg->EINDEX = CONTROL_EP;

	ucReg=gUSBC_IdxReg->E0CSR_L;	
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
	if(ucReg & 0x01)
	{
		USBDev_Ep0Handler();
	}

}

/*
Description:Receive data sent from host.(BULK-OUT)
*/
void USBDev_EP1_RX_ISR(void)
{
	unsigned char ucRegLow;
	
	//access DATA_OUT_EP register map
	gUSBC_ComReg->EINDEX = USB_ENDPOINT_INDEX;
	ucRegLow = gUSBC_IdxReg->RXCSR_L;
	//Clear sentstall and restart data toggle.
	if(ucRegLow & DEV_RXCSR_SENTSTALL)
	{
		ucRegLow &=0xBF;//clear SendStall bit
		ucRegLow |=DEV_RXCSR_CLR_DATA_TOG;//set ClrDataTog
		gUSBC_IdxReg->RXCSR_L = ucRegLow;
	}

	//Start receive data packet
	if(ucRegLow & DEV_RXCSR_RXPKTRDY)	 //RxPktRdy=1
	{
		USBDev_Data_BulkOut();
	}
	
}

/*
Description:Send data to host.(BULK-IN)
*/
void USBDev_EP1_TX_ISR(void)
{
	//access DATA_OUT_EP register map
	gUSBC_ComReg->EINDEX = USB_ENDPOINT_INDEX;
	USBDev_Data_BulkIn();
}
