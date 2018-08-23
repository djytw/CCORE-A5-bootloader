// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : pit_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __PIT_DRV_H__
#define __PIT_DRV_H__

#include "type.h"

/* macro definition */
#define PIT_INT
#define PIT_INT_NUM        0x22

/* data structure */
typedef enum _PIT_NUM_ {
    PIT1 = 1,
    PIT2,
} PIT_NUM, *P_PIT_NUM;


/* functions declaration */
extern void pit_isr(void);
extern BOOL pit_config(UINT8 pit_no, UINT32 clk, UINT32 div, UINT16 val);
extern void pit_start(PIT_NUM pit_no);
extern void pit_stop(PIT_NUM pit_no);
extern void pit_time_count_init(PIT_NUM pit_no);
extern FP32 pit_past_time(PIT_NUM pit_no);
extern void pit_restart(PIT_NUM pit_no);

#endif /* PIT_DRV_H_ */
