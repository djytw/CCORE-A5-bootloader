// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : int_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __INTERRUPT_DRV_H__
#define __INTERRUPT_DRV_H__

#include "type.h"
#include "c0.h"


//----------------------------------------------------------------------------
//                      Embedded Interrupt Controller
//----------------------------------------------------------------------------

typedef struct {
  union {
    volatile UINT32 WORD;
  } ICSR;
  UINT32 RESERVED0[3];
  union {
    volatile UINT32 WORD;
  } IER;
  UINT32 RESERVED1[1];
  union {
    volatile UINT32 WORD;
  } IPSR;
  union {
    volatile UINT32 WORD;
  } IPCR;
  UINT32 RESERVED2[8];
  union {
    volatile UINT32 WORD;
  } PLSGR[8];
  union {
    volatile UINT32 WORD;
  } SYSPLSR;
} eic;

typedef struct {
  union {
    volatile UINT32 WORD;
  } CSR;
  union {
    volatile UINT32 WORD;
  } RLD;
  union {
    volatile UINT32 WORD;
  } CNT;
} ept;


typedef struct{
	VUINT32 ICSR;						//
	VUINT32 Reserved_04;				//
	VUINT32 Reserved_08;				//
	VUINT32 Reserved_0c;				//
	VUINT32 IER;						//
	VUINT32 Reserved_14;				//
	VUINT32 PISR;						//
	VUINT32 IPCR;						//
	VUINT32 Reserved_20;				//
	VUINT32 Reserved_24;				//
	VUINT32 Reserved_28;				//
	VUINT32 Reserved_2c;				//
	VUINT32 Reserved_30;				//
	VUINT32 Reserved_34;				//
	VUINT32 Reserved_38;				//
	VUINT32 Reserved_3c;				//
	VUINT32 PLSR00_03;					//
	VUINT32 PLSR04_07;					//
	VUINT32 PLSR08_11;					//
	VUINT32 PLSR12_15;					//
	VUINT32 PLSR16_19;					//
	VUINT32 PLSR20_23;					//
	VUINT32 PLSR24_27;					//
	VUINT32 PLSR28_31;					//
	VUINT32 SYSPLSR;					//
}EIC_REG;


//IER Interrupt Enable Register

#define IER_ANALOG_MASK				(0x00000002)
#define IER_SPI23INT_MASK			(0x00000008)
#define IER_DMACINT_MASK			(0x00000010)
#define IER_SPI14INT_MASK			(0x00004000)
#define IER_EDMAC0INT_MASK			(0x00010000)
#define IER_EDMAC1SCI2INT_MASK		(0x00100000)
#define IER_I2CINT_MASK				(0x00200000)


extern void interrupt_setup(UINT8 int_num, UINT8 priority, void (* int_fun ));

//Macros and functions for controlling interrupts
extern void Write_PSR(unsigned long);
extern unsigned long Read_PSR(void);
extern void Write_VBR(unsigned long);
extern unsigned long Read_VBR(void);
extern UINT8 read_vec(void);
extern void __memcpy(void*, void*, int);

#endif  /* __INTERRUPT_DRV_H__ */
