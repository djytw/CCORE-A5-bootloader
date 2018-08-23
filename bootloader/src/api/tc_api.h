// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : tc_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _TC_API_H_
#define _TC_API_H_
#include "type.h"
#include "tc_drv.h"

typedef enum {TC_INT_enable, TC_INT_disable} TC_INT;

void TC_init(TC_TIMER_PRESCALER tc_wdp, UINT16 tcmr, TC_INT tcInt);
void feed_TC();
UINT16 get_TC_count();
UINT32 get_TC_tick();

#endif /* _TC_API_H_ */
