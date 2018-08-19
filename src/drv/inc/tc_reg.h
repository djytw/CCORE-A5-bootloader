// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : tc_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef __TC_REG_H__
#define __TC_REG_H__

#define TC_BASE					(0x70070000)
#define TCCR	    *(volatile unsigned short *)(TC_BASE+0x00)
#define TCMR	    *(volatile unsigned short *)(TC_BASE+0x02)
#define TCCNTR	    *(volatile unsigned short *)(TC_BASE+0x04)
#define TCSR	    *(volatile unsigned short *)(TC_BASE+0x06)

#define TC_WAIT				(1<<11)
#define TC_DOZE				(1<<10)
#define TC_STOP		    	(1<<9)
#define TC_DBG				(1<<8)
#define TC_IS				(1<<7)
#define TC_WDP_SHIFT        (4)
#define TC_IF				(1<<3)
#define TC_IE				(1<<2)
#define TC_CU				(1<<1)
#define TC_RN				(1<<0)

#endif /* __TC_REG_H__ */
