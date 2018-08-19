// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : tc_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __TC_DRV_H__
#define __TC_DRV_H__

#include "type.h"
#include "int_drv.h"

#define TC_INT_NUM        0x38


typedef enum
{
   TC_WDP_2048=0x00,
   TC_WDP_1024=0x01,
   TC_WDP_512=0x02,
   TC_WDP_256=0x03,
   TC_WDP_128=0x04,
   TC_WDP_64=0x05,
   TC_WDP_32=0x06,
   TC_WDP_16=0x07
}TC_TIMER_PRESCALER;

extern void tc_isr(void);
extern void tc_reset_init(TC_TIMER_PRESCALER tc_wdp, UINT16 tcmr);
extern void tc_int_init(TC_TIMER_PRESCALER wdp, UINT16 tcmr);
extern void tc_feed(void);
extern UINT32 tc_get_tick(void);
extern UINT16 tc_get_remainCount(void);

#endif /* __TC_DRV_H__ */
