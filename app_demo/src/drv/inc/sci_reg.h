// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : sci_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __SCI_REG_H__
#define __SCI_REG_H__

#include "sci_drv.h"

/* macro definition */
/*
#define SCI_BD					(*(volatile UINT16*)(SCI_BASE + 0x0000))	// SCI baud register
#define SCI_BDH					(*(volatile UINT8 *)(SCI_BASE + 0x0001))	// SCI baud register high
#define SCI_BDL					(*(volatile UINT8 *)(SCI_BASE + 0x0000))	// SCI baud register low
#define SCI_CR1					(*(volatile UINT8 *)(SCI_BASE + 0x0003))	// SCI control register1
#define SCI_CR2					(*(volatile UINT8 *)(SCI_BASE + 0x0002))	// SCI control register2
#define SCI_SR1					(*(volatile UINT8 *)(SCI_BASE + 0x0005))	// SCI status register1
#define SCI_SR2					(*(volatile UINT8 *)(SCI_BASE + 0x0004))	// SCI status register2
#define SCI_DRH					(*(volatile UINT8 *)(SCI_BASE + 0x0007))	// SCI data register high
#define SCI_DRL					(*(volatile UINT8 *)(SCI_BASE + 0x0006))	// SCI data register low
#define SCI_PURD				(*(volatile UINT8 *)(SCI_BASE + 0x0009))	// SCI pullup and reduced drive register
#define SCI_PORT				(*(volatile UINT8 *)(SCI_BASE + 0x0008))	// SCI port data register
#define SCI_DDR					(*(volatile UINT8 *)(SCI_BASE + 0x000b))	// SCI data direction register
#define SCI_BRDF				(*(volatile UINT8 *)(SCI_BASE + 0x000a))	// SCI fractional baudrate divisor register
#define SCI_TR					(*(volatile UINT8 *)(SCI_BASE + 0x000d))	// SCI test register
#define SCI_IRCR				(*(volatile UINT8 *)(SCI_BASE + 0x000c))	// SCI infrared control register
#define SCI_IRDR				(*(volatile UINT8 *)(SCI_BASE + 0x000f))	// SCI infrared divisor register
#define SCI_FCR					(*(volatile UINT8 *)(SCI_BASE + 0x000e))	// SCI fifo contral register
#define SCI_FSR					(*(volatile UINT8 *)(SCI_BASE + 0x0011))	// SCI fifo status register
*/

typedef struct
{
	union
	{
		VUINT16 BD;		//0x0000 SCI baud register
		struct		//zfj20171214
		{
			VUINT8  BDL;	//0x0000 SCI baud register low
			VUINT8  BDH;	//0x0001 SCI baud register high
		}BDHL;
	};
	VUINT8 CR2;				//0x0002 SCI control register2
	VUINT8 CR1;				//0x0003 SCI control register1
	VUINT8 SR2;				//0x0004 SCI status register2
	VUINT8 SR1;				//0x0005 SCI status register1
	VUINT8 DRL;				//0x0006 SCI data register low
	VUINT8 DRH;				//0x0007 SCI data register high
	VUINT8 PORT;			//0x0008 SCI port data register
	VUINT8 PURD;			//0x0009 SCI pullup and reduced drive register
	VUINT8 BRDF;			//0x000a SCI fractional baudrate divisor register
	VUINT8 DDR;				//0x000b SCI data direction register
	VUINT8 IRCR;			//0x000c SCI infrared control register
	VUINT8 TR;				//0x000d SCI test register
	VUINT8 FCR;				//0x000e SCI fifo contral register
	VUINT8 IRDR;			//0x000f SCI infrared divisor register
	VUINT8 Reserved_10;;	//0x0010 Reserved at 0x00000010
	VUINT8 FSR;				//0x0011 SCI fifo status register
}SCI_REG;

//volatile SCI_REG* pregspointer = 0;		//SCI registers pointer

/* SCI_CR1 */
#define LOOPS_MASK				0x80
#define WOMS_MASK				0x40
#define RSRC_MASK				0x20
#define M_MASK					0x10
#define WAKE_MASK				0x08
#define ILT_MASK				0x04
#define PE_MASK					0x02
#define PT_MASK 				0x01

/* SCI_CR2 */
#define TIE_MASK				0x80
#define TCIE_MASK				0x40
#define RIE_MASK				0x20
#define ILIE_MASK				0x10
#define TE_MASK					0x08
#define RE_MASK					0x04
#define RWU_MASK				0x02
#define SBK_MASK				0x01

/* SCI_SR1 */
#define TDRE_MASK				0x80
#define TC_MASK		    		0x40
#define RDRF_MASK				0x20
#define IDLE_MASK				0x10
#define OR_MASK					0x08
#define NF_MASK					0x04
#define FE_MASK					0x02
#define PF_MASK					0x01

/* SCI_SR2 */
#define RAF_MASK				0x01

/* SCI_DRH */
#define R8_MASK		    		0x80
#define T8_MASK					0x40

/* SCI_PURD */
#define SCISDOZ_MASK			0x80
#define RDPSCI_MASK				0x10
#define PUPSCI_MASK				0x01

/* SCI_PORT */
#define SC1_MASK				0x02
#define SC0_MASK				0x01

/* SCI_DDR */
#define DDRSC1_MASK				0x02
#define DDRSC0_MASK				0x01

/* SCI_FSR */
#define TFTS_MASK				0x80
#define FTC_MASK			    0x40
#define RFTS_MASK				0x20
#define RTOS_MASK				0x10
#define TFULL_MASK				0x08
#define TEMPTY_MASK				0x04
#define RFULL_MASK				0x02
#define REMPTY_MASK				0x01

/* SCI_IRCR */
#define IRCR_IREN_MASK			0x01
#define IRCR_IRSC_MASK			0x02
#define IRCR_RINV_MASK			0x04
#define IRCR_TINV_MASK			0x08

#define SCI_ENABLE_TRANSMITTER  	(pregspointer->CR2 |= TE_MASK)
#define SCI_DISABLE_TRANSMITTER 	(pregspointer->CR2 &= ~TE_MASK)

#define SCI_ENABLE_RECEIVER			(pregspointer->CR2 |= RE_MASK)
#define SCI_DISABLE_RECEIVER		(pregspointer->CR2 &= ~RE_MASK)

/* internal data structure */

#endif /* SCI_REG_H_ */
