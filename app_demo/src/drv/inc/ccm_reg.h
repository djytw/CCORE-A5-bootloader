// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : ccm_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __CCM_REG_H__
#define __CCM_REG_H__

//------------------------------------------------------------------
//                        Headers
//------------------------------------------------------------------
#include "type.h"
//------------------------------------------------------------------




typedef struct{
	VUINT16 FDCR;           	//FD Configuration Register
	VUINT16 CCR;           	//Chip Configuration Register
	VUINT16 CIR;          		//Chip Identification Register
	VUINT16 PHYPA;          	//
	VUINT16 Reserved_08;		//
	VUINT16 CTR;				//Chip Test Register
	VUINT32 HSSPI1PADCTRL;		//
	VUINT32 PCFG12;			//PMU Configuration1/2 Register
	VUINT32 PCFG3;         	//PMU Configuration3 Register
	VUINT32 RTCFG12;			//RTC Configuration1/2 Register
	VUINT32 RTCFG3;			//RTC Configuration3 Register
	VUINT32 RTC_SR;         	//RTC Status Register
	VUINT32 Reserved_24;		//
	VUINT32 Reserved_28;		//
	VUINT32 HSSPI2PADCTRL;		//
	VUINT32 HSSPI3PADCTRL;		//
}CCM_REG;

//CCR Chip Configuration Register //offset at 0x00000002
#define	CCM_SPI4EN_MASK				(0x0080)

//HSSPIPADCTRL
#define CCM_SWAPSD_MASK				(0x80000000)
#define CCM_SWAPDBUS_MASK			(0x40000000)
#define CCM_SPIINTEN_MASK			(0x20000000)


#define PHYPA					(*(volatile UINT16 *)(CCM_BASE + 0x06))
#define PHYPA_LOW				(*(volatile UINT8 *) (CCM_BASE + 0x06))
#define PCFG12					(*(volatile UINT16 *)(CCM_BASE + 0x12))
#define PMU_RTC					(*(volatile UINT16 *)(CCM_BASE + 0x20))


#endif /* CCM_REG_H_ */
