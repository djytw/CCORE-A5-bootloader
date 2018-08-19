// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usb_ms_demo.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __USB_MS_DEMO_H__
#define __USB_MS_DEMO_H__

#include "includes.h"
#include "int_reg.h"
#include "int_drv.h"

extern void USB_Init();
extern void USBDev_Polling(void);
extern void usb_ms_demo(void);
extern void USB_MS_ISR(void);
#endif /* __USB_MS_DEMO_H__ */
