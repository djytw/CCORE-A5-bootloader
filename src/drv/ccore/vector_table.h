// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : vector_table.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __VECTOR_TABLE_H__
#define __VECTOR_TABLE_H__

#include "vector_define.h"

#define ISR01 Misaligned_Access        // Misaligned Access
#define ISR02 Access_Error             // Access Error
#define ISR03 DummyHandler             // Dummy
#define ISR04 Illegal_Instrn           // Illegal Instruction
#define ISR05 DummyHandler             // Dummy
#define ISR06 DummyHandler             // Dummy
#define ISR07 Breakpoint_Exception     // BreakPoint
#define ISR08 Unrecoverable_Error      // Unrecoverable exception
#define ISR09 DummyHandler             // Dummy
#define ISR0a DummyHandler             // Dummy
#define ISR0b DummyHandler             // Dummy
#define ISR0c DummyHandler             // Dummy
#define ISR0d DummyHandler             // Dummy
#define ISR0e DummyHandler             // Dummy
#define ISR0f DummyHandler             // Dummy
#define ISR10 DummyHandler             // Trap 0
#define ISR11 DummyHandler             // Trap 1
#define ISR12 DummyHandler             // Trap 2
#define ISR13 DummyHandler             // Trap 3
#define ISR14 DummyHandler             // Dummy
#define ISR15 DummyHandler             // Dummy
#define ISR16 DummyHandler             // Dummy
#define ISR17 DummyHandler             // Dummy
#define ISR18 ept_isr             // timer
#define ISR19 DummyHandler		       // pend_trap
#define ISR1a DummyHandler             // Dummy
#define ISR1b DummyHandler             // Dummy
#define ISR1c DummyHandler             // Dummy
#define ISR1d DummyHandler             // Dummy
#define ISR1e DummyHandler             // Dummy
#define ISR1f DummyHandler             // Dummy
#define ISR20 pad_wkp_isr              // IRQ0
#ifdef CPM_EN
#define ISR21 cpm_isr                  // IRQ1
#else
#define ISR21  analog_isr
#endif
#define ISR22 pit_isr                  // IRQ2
#define ISR23 DummyHandler             // IRQ3
#define ISR24 dmac_isr                 // IRQ4
#define ISR25 eport0_isr               // IRQ5
#define ISR26 eport1_isr               // IRQ6
#define ISR27 eport2_isr               // IRQ7
#define ISR28 eport3_isr               // IRQ8
#define ISR29 eport4_isr               // IRQ9
#define ISR2a eport5_isr               // IRQ10
#define ISR2b eport6_isr               // IRQ11
#define ISR2c eport7_isr               // IRQ12
#define ISR2d DummyHandler             // IRQ13
#define ISR2e DummyHandler             // IRQ14
#define ISR2f DummyHandler             // IRQ15
#define ISR30 edmac_isr				   // IRQ16
#define ISR31 DummyHandler             // IRQ17
#define ISR32 DummyHandler             // IRQ18
#define ISR33 DummyHandler             // IRQ19
#define ISR34 edmac_isr     		   // IRQ20
#ifdef I2C_MASTER_DEMO
	#define ISR35 i2c_m_isr             // IRQ21
#else
	#define ISR35 i2c_s_isr             // IRQ21
#endif

#define ISR36 DummyHandler             // IRQ22
#define ISR37 DummyHandler             // IRQ23
#define ISR38 tc_isr                   // IRQ24

#ifdef USB_MS
	#define ISR39 USB_MS_ISR           // IRQ25
#else
	#ifdef USB_CDC
		#define ISR39 USB_CDC_ISR
	#else
		#define ISR39 DummyHandler
	#endif
#endif
#define ISR3a usi_isr                  // IRQ26
#define ISR3b sd_mem_handler            // IRQ27
#define ISR3c DummyHandler             // IRQ28
#define ISR3d DummyHandler             // IRQ29
#define ISR3e DummyHandler             // IRQ30
#define ISR3f DummyHandler             // IRQ31

extern void __start(void);
extern void Misaligned_Access( void );
extern void Access_Error( void );
extern void Illegal_Instrn( void );
extern void Breakpoint_Exception( void );
extern void Unrecoverable_Error( void );


extern void dmac_isr(void);
extern void edmac_isr(void);
extern void pit_isr(void);
extern void USB_MS_ISR();
extern void eport0_isr(void);
extern void eport1_isr(void);
extern void eport2_isr(void);
extern void eport3_isr(void);
extern void eport4_isr(void);
extern void eport5_isr(void);
extern void eport6_isr(void);
extern void eport7_isr(void);
extern void cpm_isr(void);
extern void usi_isr(void);
extern void DummyHandler(void);
extern void tc_isr(void);
extern void ept_isr(void);
extern void i2c_m_isr(void);
extern void i2c_s_isr(void);
extern void pad_wkp_isr(void);
extern void sd_mem_handler(void);
extern void analog_isr(void);
extern void USB_CDC_ISR(void);
#endif /* __VECTOR_TABLE_H__ */

