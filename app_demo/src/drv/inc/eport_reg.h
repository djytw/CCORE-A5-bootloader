// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eport_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __EPORT_REG_H__
#define __EPORT_REG_H__

#include "memmap.h"

/* macro definition */
#define EPORT_EPPAR					(*(volatile UINT16*)(EPORT1_BASE))
#define EPORT_EPIER					(*(volatile UINT8 *)(EPORT1_BASE + 0x02))
#define EPORT_EPDDR					(*(volatile UINT8 *)(EPORT1_BASE + 0x03))
#define EPORT_EPPDR					(*(volatile UINT8 *)(EPORT1_BASE + 0x04))
#define EPORT_EPDR					(*(volatile UINT8 *)(EPORT1_BASE + 0x05))
#define EPORT_EPPUER				(*(volatile UINT8 *)(EPORT1_BASE + 0x06))
#define EPORT_EPFR					(*(volatile UINT8 *)(EPORT1_BASE + 0x07))
#define EPORT_EPODER				(*(volatile UINT8 *)(EPORT1_BASE + 0x08))
#define EPORT_EPLPR					(*(volatile UINT8 *)(EPORT1_BASE + 0x09))

#define LEVEL_H						1
#define LEVEL_L						0

/* internal data structure */
typedef struct _EPORT_ISR_SET_
{
	UINT8 eport_isr_num;
	UINT8 eport_int_priority;
	void (*eport_isr_entr)(void);
}EPORT_ISR_SET, *P_EPORT_ISR_SET;

#endif /* __EPORT_REG_H__ */
