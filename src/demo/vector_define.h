// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : vector_define.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __VECTOR_DEFINE_H__
#define __VECTOR_DEFINE_H__
#include "demo.h"

#ifdef USB_MS_DEMO_EN
	#define USB_MS
#endif
#ifdef USB_CDC_DEMO_EN
	#define USB_CDC
#endif

#define I2C_MASTER_DEMO

#define CPM_EN
#endif /* __VECTOR_DEFINE_H__ */
