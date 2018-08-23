// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : c0.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __C0_H__
#define __C0_H__

#include "int_reg.h"
//----------------------------------------------------------------------------
//                           Basic Operation
//----------------------------------------------------------------------------
#define bit_read(r,b) ((r>>b) & 0x1 )
#define bits_read(r,b,m) ((r >> b) & m)

#define bit_write(r,b) (r |= (0x1 << b)  )
#define bits_write(r,b,m,v) ( r = (( r & ~(m <<b)) | (v << b)) )

#define bit_clear(r,b) (r &= ~(1<<b))
#define bits_clear(r,b,m)  (r &= ~(m<<b))

#define SYS_PSR_read(psr)   __asm__ __volatile__("mfcr %0, psr":"=r"(psr))
#define SYS_PSR_write(psr)  __asm__ __volatile__("mtcr %0, psr"::"r"(psr))

#define SYS_VBR_read(vbr)   __asm__ __volatile__("mfcr %0, vbr":"=r"(vbr))
#define SYS_VBR_write(vbr)  __asm__ __volatile__("mtcr %0, vbr"::"r"(vbr))

#define SYS_RMD_read(rmd)   __asm__ __volatile__("mfcr %0, cr13":"=r"(rmd))

//----------------------------------------------------------------------------
//      General register read/write(read from a g_reg; write to a g_reg)
//----------------------------------------------------------------------------
// r0 r/w
#define G_R0_write(var)   __asm__  __volatile__("MOV r0, %[value]"::[value]"r"(var));
#define G_R0_read(var)    __asm__  __volatile__("MOV %[value],r0":[value]"=r"(var));
// r1 r/w
#define G_R1_write(var)   __asm__  __volatile__("MOV r1, %[value]"::[value]"r"(var));
#define G_R1_read(var)    __asm__  __volatile__("MOV %[value],r1":[value]"=r"(var));
// r2 r/w
#define G_R2_write(var)   __asm__  __volatile__("MOV r2, %[value]"::[value]"r"(var));
#define G_R2_read(var)    __asm__  __volatile__("MOV %[value],r2":[value]"=r"(var));
// r3 r/w
#define G_R3_write(var)   __asm__  __volatile__("MOV r3, %[value]"::[value]"r"(var));
#define G_R3_read(var)    __asm__  __volatile__("MOV %[value],r3":[value]"=r"(var));
// r4 r/w
#define G_R4_write(var)   __asm__  __volatile__("MOV r4, %[value]"::[value]"r"(var));
#define G_R4_read(var)    __asm__  __volatile__("MOV %[value],r4":[value]"=r"(var));
// r5 r/w
#define G_R5_write(var)   __asm__  __volatile__("MOV r5, %[value]"::[value]"r"(var));
#define G_R5_read(var)    __asm__  __volatile__("MOV %[value],r5":[value]"=r"(var));
// r6 r/w
#define G_R6_write(var)   __asm__  __volatile__("MOV r6, %[value]"::[value]"r"(var));
#define G_R6_read(var)    __asm__  __volatile__("MOV %[value],r6":[value]"=r"(var));
// r7 r/w
#define G_R7_write(var)   __asm__  __volatile__("MOV r7, %[value]"::[value]"r"(var));
#define G_R7_read(var)    __asm__  __volatile__("MOV %[value],r7":[value]"=r"(var));
// r8 r/w
#define G_R8_write(var)   __asm__  __volatile__("MOV r8, %[value]"::[value]"r"(var));
#define G_R8_read(var)    __asm__  __volatile__("MOV %[value],r8":[value]"=r"(var));
// r9 r/w
#define G_R9_write(var)   __asm__  __volatile__("MOV r9, %[value]"::[value]"r"(var));
#define G_R9_read(var)    __asm__  __volatile__("MOV %[value],r9":[value]"=r"(var));
// r10 r/w
#define G_R10_write(var)  __asm__  __volatile__("MOV r10, %[value]"::[value]"r"(var));
#define G_R10_read(var)   __asm__  __volatile__("MOV %[value],r10":[value]"=r"(var));
// r11 r/w
#define G_R11_write(var)  __asm__  __volatile__("MOV r11, %[value]"::[value]"r"(var));
#define G_R11_read(var)   __asm__  __volatile__("MOV %[value],r11":[value]"=r"(var));
// r12 r/w
#define G_R12_write(var)  __asm__  __volatile__("MOV r12, %[value]"::[value]"r"(var));
#define G_R12_read(var)   __asm__  __volatile__("MOV %[value],r12":[value]"=r"(var));
// r13 r/w
#define G_R13_write(var)  __asm__  __volatile__("MOV r13, %[value]"::[value]"r"(var));
#define G_R13_read(var)   __asm__  __volatile__("MOV %[value],r13":[value]"=r"(var));
// r14 r/w
#define G_R14_write(var)  __asm__  __volatile__("MOV r14, %[value]"::[value]"r"(var));
#define G_R14_read(var)   __asm__  __volatile__("MOV %[value],r14":[value]"=r"(var));
// r15 r/w
#define G_R15_write(var)  __asm__  __volatile__("MOV r15, %[value]"::[value]"r"(var));
#define G_R15_read(var)   __asm__  __volatile__("MOV %[value],r15":[value]"=r"(var));


//----------------------------------------------------------------------------
//                              Embedded EPT
//----------------------------------------------------------------------------
//#define EPT_CSR EIC_BASEADDR+0x1000+0x00    // ept control & status register
//#define EPT_RLD EIC_BASEADDR+0x1000+0x04    // ept reload value register
//#define EPT_CNT EIC_BASEADDR+0x1000+0x08    // ept current value register

#define EPT_CSR_WRITE(val) *(volatile UINT32 *) (EPT_CSR) = val
#define EPT_RLD_WRITE(val) *(volatile UINT32 *) (EPT_RLD) = val
#define EPT_CNT_WRITE(val) *(volatile UINT32 *) (EPT_CNT) = val

#define EPT_CSR_READ(val) val = *(volatile UINT32 *) (EPT_CSR)
#define EPT_RLD_READ(val) val = *(volatile UINT32 *) (EPT_RLD)
#define EPT_CNT_READ(val) val = *(volatile UINT32 *) (EPT_CNT)

#endif /* __C0_H__ */
