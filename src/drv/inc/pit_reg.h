// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : pit_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __PIT_REG_H__
#define __PIT_REG_H__

/* macro definition */
#define PIT1_PCSR				(*(volatile UINT16*)(PIT1_BASE + 0x0))
#define PIT1_PCSR_H				(*(volatile UINT8*) (PIT1_BASE + 0x0))
#define PIT1_PCSR_L				(*(volatile UINT8*) (PIT1_BASE + 0x1))
#define PIT1_PMR				(*(volatile UINT16*)(PIT1_BASE + 0x2))
#define PIT1_PCNTR				(*(volatile UINT16*)(PIT1_BASE + 0x4))

#define PIT2_PCSR				(*(volatile UINT16*)(PIT2_BASE + 0x0))
#define PIT2_PCSR_H				(*(volatile UINT8*) (PIT2_BASE + 0x0))
#define PIT2_PCSR_L				(*(volatile UINT8*) (PIT2_BASE + 0x1))
#define PIT2_PMR				(*(volatile UINT16*)(PIT2_BASE + 0x2))
#define PIT2_PCNTR				(*(volatile UINT16*)(PIT2_BASE + 0x4))

/* PITx_PCSR */
#define PIT_EN					(1 << 0)
#define PIT_RLD					(1 << 1)
#define PIT_PIF					(1 << 2)
#define PIT_PIE					(1 << 3)
#define PIT_OVW					(1 << 4)
#define PIT_DOZE				(1 << 6)

#define PCSR_EN					0x01
#define PCSR_RLD				0x02
#define PCSR_PIF				0x04
#define PCSR_PIE				0x08
#define PCSR_OVW				0x10
#define PCSR_PDBG				0x20
#define PCSR_PDOZE				0x40
#define PCSR_PRE				0x0F

#endif /* __PIT_REG_H__ */
