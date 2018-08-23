// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usbdev_scsi.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "usb_reg.h"
#include "usb_const.h"



//add end
void USBDev_Data_BulkOut(void);
void USBDev_Data_BulkIn(void);
void UsbRead10(UINT8* tmpBuf);
//Vendor Command Definition

//Process the useful lba
void enum_realDisk(unsigned long lba,unsigned char* buffer);
void copy_data_to_buffer(void);
unsigned short make_len_alignTo512(unsigned long value);
void DMAWaitDone(void);
void DMAWaitDone_Tx(void);
void DMATransfer(UINT32 memaddr, UINT32 len, UINT16 dcr);
void ClearRx();
void SetTx();


void VendorWriteData(UINT8 *tmpBuf,UINT32 len);
extern void USBDev_Inquiry(void);
extern void USBDev_ReadCapacity(void);
extern void USBDev_RequestSense(void);
extern void USBDev_ModeSense(void);
extern unsigned long RWDataAddr;
UINT8 rev_buf[512];

void UsbSetTXsize(UINT16 size,UINT8 mode)
{
	UINT8 data8;


	if(size)
	{
//		STH(size,TXMAXP);
		gUSBC_IdxReg->TXMAXP_L = size;
		gUSBC_IdxReg->TXMAXP_H = (size>>8);
	}
	else
	{
		if(g_usbVer == 1)
		{
			gUSBC_IdxReg->TXMAXP_L = USB_MAX_PACKET_SIZE_LOW;
			gUSBC_IdxReg->TXMAXP_H = USB_MAX_PACKET_SIZE_HIGH;
		}
		else
		{
			gUSBC_IdxReg->TXMAXP_L = USB_MAX_PACKET_SIZE_LOW_V11;
			gUSBC_IdxReg->TXMAXP_H = USB_MAX_PACKET_SIZE_HIGH_V11;
		}
	}

	if(mode==1)		//double buffer mode
	{
		data8 = gUSBC_fifoReg->TXFIFOSZ;
		data8 |= 0x10;		//enable double buffer
		gUSBC_fifoReg->TXFIFOSZ = data8;
		//Enable DMA mode 1 and Double Buffer Related AutoSet function
		gUSBC_IdxReg->TXCSR_H = DEV_TXCSR_AUTO_SET|DEV_TXCSR_TXMODE|DEV_TXCSR_DMA_ENAB;
	}else{
		data8 = gUSBC_fifoReg->TXFIFOSZ;
		data8 &= 0xef;		//disable double buffer
		gUSBC_fifoReg->TXFIFOSZ = data8;
		gUSBC_IdxReg->TXCSR_H = 0;
	}


}

void UsbSetRXsize(UINT16 size,UINT8 mode)
{
	UINT8 data8;

	if(size)
	{
//		STH(size,RXMAXP);
		gUSBC_IdxReg->RXMAXP_L = size;
		gUSBC_IdxReg->RXMAXP_H = (size>>8);
	}
	else
	{
		if(g_usbVer == 1)
		{
			gUSBC_IdxReg->RXMAXP_L = USB_MAX_PACKET_SIZE_LOW;
			gUSBC_IdxReg->RXMAXP_H = USB_MAX_PACKET_SIZE_HIGH;
		}
		else
		{
			gUSBC_IdxReg->RXMAXP_L = USB_MAX_PACKET_SIZE_LOW_V11;
			gUSBC_IdxReg->RXMAXP_H = USB_MAX_PACKET_SIZE_HIGH_V11;
		}
	}

	if(mode==1)		//double buffer mode
	{
		data8 = gUSBC_fifoReg->RXFIFOSZ;
		data8 |= 0x10;		//enable double buffer
		gUSBC_fifoReg->RXFIFOSZ = data8;
		//Enable DMA mode 1 and Double Buffer Related AutoSet function
		gUSBC_IdxReg->RXCSR_H = DEV_RXCSR_AUTOCLEAR|DEV_RXCSR_DMA_ENAB|DEV_RXCSR_DMAMODE;
		//gUSBC_IdxReg->RXCSR_H = DEV_RXCSR_AUTOCLEAR|DEV_RXCSR_DMA_ENAB;
	}else{
		data8 = gUSBC_fifoReg->RXFIFOSZ;
		data8 &= 0xef;		//disable double buffer
		gUSBC_fifoReg->RXFIFOSZ = data8;
		gUSBC_IdxReg->RXCSR_H = 0;
	}
}

UINT16 UsbSetMaxPacketSize(UINT8 size,UINT8 TxRx)		//for Read10 and so on
{
	UINT16 tmp;

	if(g_transLens<size)
	{
		if(TxRx==0)
			gTxMaxPacket = 512*g_transLens;
		else
			gRxMaxPacket = 512*g_transLens;
		tmp = ((g_transLens-1)<<11)|0x200;	//TxMAXP or RxMAXP
	}else{
		if(TxRx==0)
			gTxMaxPacket = 512*size;
		else
			gRxMaxPacket = 512*size;
		tmp = ((size-1)<<11)|0x200;
	}

	return tmp;
}

UINT16 UsbSetDoubleFIFO(UINT8 size,UINT8 TxRx)		//for Vendor Read and Vendor Write
{
	UINT16 tmp;

	if(g_transLens<size)
	{
		if(TxRx==0)
			gTxMaxPacket = 512*g_transLens;
		else
			gRxMaxPacket = 512*g_transLens;
		tmp = ((g_transLens/2-1)<<11)|0x200;
	}else{
		if(TxRx==0)
			gTxMaxPacket = 512*size;
		else
			gRxMaxPacket = 512*size;
		tmp = ((size/2-1)<<11)|0x200;
	}

	return tmp;
}

/*
Description:Receive data from host.(BULK-OUT to host)
*/
void USBDev_Data_BulkOut(void)
{
//	unsigned char ucReg=1;
	unsigned short uiRxCount;
//	unsigned long i,tmp = 0;
//	unsigned long *ulPara = &g_cbwPacket_l[4];
//	unsigned long data[32];

	uiRxCount = gUSBC_IdxReg->RXCount_H;
	uiRxCount <<=8;
	uiRxCount += gUSBC_IdxReg->RXCount_L; 
	 		   
	if(uiRxCount==0)
		return;
 
	if(uiRxCount==31)
	{
	    read_ep_buf(g_cbwPacket,USB_ENDPOINT_FIFO_ADDR,31);
		// constructe a csw packet
		//dCSWTag,got from CBW
		g_cswPacket[4]=g_cbwPacket[4];
		g_cswPacket[5]=g_cbwPacket[5];
		g_cswPacket[6]=g_cbwPacket[6];
		g_cswPacket[7]=g_cbwPacket[7];
		//dCSWDataResidue
		g_cswPacket[8]=(0>>24) & 0xFF;
		g_cswPacket[9]=(0>>16) & 0xFF;
		g_cswPacket[10]=(0>>8) & 0xFF;
		g_cswPacket[11]=(0) & 0xFF;
		//bCSWStatus
		g_cswPacket[12]=0;
		//Command and Sub Command
		g_bulkPhase = g_cbwPacket[15];
		g_subCmd = g_cbwPacket[28];

		//process command
		switch(g_bulkPhase)
		{
			case 0x00:
			case 0x1e:
				ClearRx();	//clear RxPktRdy bit
				USBDev_Packet_BulkIn((unsigned char *)g_cswPacket,13,1);								
				break;
			case 0x12:
				ClearRx();	//clear RxPktRdy bit
				USBDev_Inquiry();
				break;
			case 0x23:
			case 0x25:
				ClearRx();	//clear RxPktRdy bit
				USBDev_ReadCapacity();
				break;
			case 0x1a:
				ClearRx();	//clear RxPktRdy bit
				USBDev_ModeSense();
				break;
			case 0x03:	
				ClearRx();	//clear RxPktRdy bit
				USBDev_RequestSense();
				break;
			case 0x28:		
				ClearRx();	//clear RxPktRdy bit
				//get LBA and sector number
				g_wrLBA = g_cbwPacket[17];//CBWCB[2]
				g_wrLBA <<=8;
				g_wrLBA += g_cbwPacket[18];
				g_wrLBA <<=8;
				g_wrLBA += g_cbwPacket[19];
				g_wrLBA <<=8;
				g_wrLBA += g_cbwPacket[20];
				g_transLens = ((g_cbwPacket[22]<<8)|g_cbwPacket[23]);//512 byte per sector	

				g_TxRxCounter=0;
				g_databuf = (USB_BUFFER_ADDR+0x200);
				enum_realDisk(g_wrLBA,(unsigned char*)g_databuf);
				UsbRead10((unsigned char*)g_databuf);		
				break;
			//Vendor Command
			case 0x2A:
				ClearRx();	//clear RxPktRdy bit
				g_transLens = ((g_cbwPacket[22]<<8)|g_cbwPacket[23]);//512 byte per sector
				break;
//////****************添加用户程序分支*************************************////////
			case 0xC0:  								 //用户定义程序 写命令


				g_transLens = 1;//((g_cbwPacket[22]<<8)|g_cbwPacket[23]);//512 byte per secto
				msg_printf("user write cmd 0xC0 \r\n");
				ClearRx();	//clear RxPktRdy bit
				break;

			case 0xC1:

				//用户定义程序 读命令
				ClearRx();	//clear RxPktRdy bit
				msg_printf("user read cmd 0xC1 \r\n");
				USBDev_Packet_BulkIn(rev_buf,USB_MAX_PACKET_SIZE,0);

				break;
///////////////////////////////////////////////////////////////////////////////////
			default:
				//reply error to all other command		
				g_cswPacket[12] = 1;
				USBDev_Packet_BulkIn((unsigned char *)g_cswPacket,13,1);					
				break;
			}
	}
	else
	{	
		VendorWriteData((UINT8*)RWDataAddr,USB_MAX_PACKET_SIZE);


 	}
}

/*
Description:Device sends data to host(BULK-IN to host)
*/
void USBDev_Data_BulkIn(void)
{
//	unsigned char ucReg;

	switch(g_bulkPhase)
	{
		case 0x28:
			if(g_TxRxCounter==0)
			{
				g_databuf = (USB_BUFFER_ADDR+0x200);
				enum_realDisk(g_wrLBA,(unsigned char*)g_databuf);
			}
			UsbRead10((unsigned char*)g_databuf);	
			break;					

		default:
			if(g_bulkPhase == 0x1a)
				g_cswPacket[12] = 1;
			USBDev_Packet_BulkIn((unsigned char *)g_cswPacket,13,1);					
			break;			
	}
}

void UsbRead10(UINT8* tmpBuf)
{
//	UINT8 i;
	UINT16 DmaCtl = 0;

	//write data from buffer to TX
	if(g_transLens)
	{
		UsbSetTXsize(USB_MAX_PACKET_SIZE,0);
		DmaCtl = CNTL_DMAEN(1) | CNTL_DIRECTION(1) | CNTL_DMAMODE(0)
				| CNTL_INTERE(1) | CNTL_EP(USB_ENDPOINT_INDEX) | CNTL_BUSERR(0) | CNTL_BURSTMODE(USBDMA_BURST_LEN);
		DMATransfer((UINT32)tmpBuf, USB_MAX_PACKET_SIZE, DmaCtl);
		DMAWaitDone();
		SetTx();
		g_wrLBA++;
		g_transLens--;
	}
	else
	{
		 USBDev_Packet_BulkIn((unsigned char *)g_cswPacket,13,1);	//write csw response
	}
}






void VendorWriteData(UINT8 *tmpBuf,UINT32 len)
{
//	UINT16 DmaCtl = 0;
	UINT32 i;


	if(g_usbVer==1)
	{

		read_ep_buf(rev_buf,USB_ENDPOINT_FIFO_ADDR,USB_MAX_PACKET_SIZE);
		ClearRx();
		g_transLens--;
	}
	msg_printf("rec data:\r\n");

	for(i=0;i<64;i++)
	{
		if(i%16 ==0) msg_printf("\r\n");
		msg_printf("%02x ",rev_buf[i]);

	}

	if(g_transLens == 0)
	{
		msg_printf("return csw packet:\r\n");
		USBDev_Packet_BulkIn((unsigned char *)g_cswPacket,13,1);			//send csw packetb
	}
}


void enum_realDisk(unsigned long lba,unsigned char* buffer)
{
	unsigned long fat_sum;
	unsigned char* addr;
	unsigned short reserve,i;
	unsigned long dbr_offset;
	
	addr = (unsigned char*)&DBR[0];
	reserve = *(addr+0x0e);
	fat_sum = *(addr+0x17);
	fat_sum = (fat_sum<<8) + *(addr+0x16);
	addr = (unsigned char*)buffer;
	
	dbr_offset = MBR[454];
	
	if(lba == 0){
	   memcpy(buffer,(unsigned long*)MBR,512);
	}
	else if(lba == dbr_offset){
	   memcpy(buffer,(unsigned long*)DBR,512);
	}
	else if(lba == (reserve+dbr_offset)){
		for(i=0; i<512; i++)
			*(addr+i) = 0;
		*addr = 0xf8;
		*(addr+1) = 0xff;
		*(addr+2) = 0xff;
		*(addr+3) = 0xff;
		return;
	}
	else if(lba == (fat_sum+reserve+dbr_offset)){
		for(i=0; i<512; i++)
			*(addr+i) = 0;	
		*addr = 0xf8;
		*(addr+1) = 0xff;
		*(addr+2) = 0xff;
		*(addr+3) = 0xff;
		return;
	}
	else{
		for(i=0; i<512; i++)
			*(addr+i) = 0;	
		return;
	}
	return;
}

void copy_data_to_buffer(void)
{
//	unsigned long i;

	;
}

unsigned short make_len_alignTo512(unsigned long value)
{
	unsigned short ret_value;
	
	ret_value = value>>9;
	if(value&0x1ff)
		ret_value++;
		
	return ret_value;
}
extern volatile unsigned int g_Dma_Done;
void DMAWaitDone(void)
{
//	UINT8 DmaStatus = 0;
	//wait DMA complete
	do
	{

	}while((g_Dma_Done & INTR_DMA1) != 0x01);		//INTR status is delay a long time after DMA done

}

void DMAWaitDone_Tx(void)
{
	UINT16 txcsr;

	//Wait TxpktRdy is Clear
	do{
		txcsr = gUSBC_IdxReg->TXCSR_L;
		
	}while((txcsr&DEV_TXCSR_FIFO_NOT_EMPTY)==DEV_TXCSR_FIFO_NOT_EMPTY);
}

void DMATransfer(UINT32 memaddr, UINT32 len, UINT16 dcr)
{
	IO_WRITE32(DMA_ADDR1,memaddr);

	IO_WRITE32(DMA_COUNT1,len);

	IO_WRITE16(DMA_CNTL1,dcr);
}
