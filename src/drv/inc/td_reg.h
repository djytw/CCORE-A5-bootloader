// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : td_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __TD_REG_H__
#define __TD_REG_H__

#include "type.h"
#include "memmap.h"

#define TD_CR_1				(*(volatile UINT32*)(SEC_DET_BASE + 0x0000))
#define TD_CR_2				(*(volatile UINT32*)(SEC_DET_BASE + 0x0004))


/* TD_CR */
#define TD_HT_RST_MASK		(0x1<<8)
#define TD_HT_INT_MASK		(0x1<<9)
#define TD_LT_RST_MASK		(0x1<<11)
#define TD_LT_INT_MASK		(0x1<<12)
#define TD_SEL_MASK			(0x1<<14)

#define TD_LAT_CLR_MASK		(0x1<<0)
#define TD_LT_ST_MASK		(0x1<<1)
#define TD_HT_ST_MASK		(0x1<<2)
#define TD_LT_ST_LAT_MASK	(0x1<<3)
#define TD_HT_ST_LAT_MASK	(0x1<<4)

#define TD_HT_EN			1
#define TD_HT_DIS			0

#define TD_LT_EN			1
#define TD_LT_DIS			0

#define TD_RST_MODE			2
#define TD_INT_MODE			1

#define TD_CHANNEL_1		0
#define TD_CHANNEL_2		1

#define TD_HT_SET			0x19  //test 69.3
#define TD_LT_SET			0x09  //test -8.5


#endif /* __TD_REG_H__ */
