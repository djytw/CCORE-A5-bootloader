// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usb_cdc_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "usb_cdc_demo.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usb_hid_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Demo of usb cdc dev.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern void USB_CDC_Init(void);

extern void usb_cdc_send(UINT8 usb_ep, UINT8 *buf, UINT16 len);

extern UINT16 usb_cdc_receive(UINT8 usb_ep, UINT8 *buf);
UINT8  cdc_ctl_buf[512];
extern UINT8  g_uchUSBStatus;
/*************************************************
Function: USBDev_DoCDCCmd
Description: CCID类的处理
Calls:
Called By:
Input: 无
Output: 无
Return: 无
Others: 无
*************************************************/
void USBDev_DoCDCCmd(void)
{
	UINT16 recvLen = 0;
	//UINT16 i = 0;

	memset(cdc_ctl_buf, 0x00, sizeof(cdc_ctl_buf));
	recvLen = usb_cdc_receive(INDEX_EP2, (UINT8 *)cdc_ctl_buf);
	if (recvLen == 0)
		return;
	msg_printf("USB Recv Len = 0x%04x:\r\n", recvLen);
	//for(; i < recvLen; i++)
	msg_printf("%s ", cdc_ctl_buf);
	msg_printf("\r\n");
	usb_cdc_send(INDEX_EP1, (UINT8*)cdc_ctl_buf, recvLen);
}



void usb_cdc_poll(void)
{
	if( (g_uchUSBStatus & BIT1) == BIT1 )     //接收到一包数据
	{
		g_uchUSBStatus &= ~BIT1;
		msg_printf("USBDev_DoCDCCmd\r\n");
		USBDev_DoCDCCmd();
	}
}


void usb_cdc_demo(void)
{
//	unsigned char ucMode;
//	unsigned int loop = 0;
//	unsigned int rx_num;

	msg_printf("usb_cdc_demo \r\n");
    Disable_Interrupts;
    USB_CDC_Init();
	Enable_Interrupts;

	while(1)
	{
		usb_cdc_poll();
	}
}
