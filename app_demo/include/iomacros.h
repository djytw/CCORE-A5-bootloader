// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : iomacros.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __IOMACROS_H__
#define __IOMACROS_H__
#include "type.h"
/****************************************************************************
						Constants Definitions
****************************************************************************/
#define IO_READ8(p)            (*(volatile UINT8 *)(p))
#define IO_WRITE8(p,v)         (*((volatile UINT8 *)(p)) = ((UINT8)(v)))

#define IO_READ16(p)           (*(volatile UINT16 *)(p))
#define IO_WRITE16(p,v)        (*((volatile UINT16 *)(p)) = (UINT16)(v))

#define IO_READ32(p)           (*(volatile UINT32 *)(p))
#define IO_WRITE32(p,v)        (*((volatile UINT32 *)(p)) = (UINT32)(v))

#define W32(addr,value)		   IO_WRITE32(addr,value)
#define R32(addr)			   IO_READ32(addr)
#define REG32(addr)			   (*(volatile unsigned long *)(addr))
//bit operation
#define BSET32(reg, bit)		((reg) |= (bit))
#define BCLR32(reg, bit)		((reg) &= ~(bit))

/* Bit minipulation */
#define BIT(x)  ((UINT32)1 << (x))
#define BIT_SET(value,bit) (value |= (1 << bit))
#define BIT_CLR(value,bit) (value &= ~(1 << bit))
#define CHKBIT(val, bit) ((val)&(bit))

/* ALIGN UP*/
#define ALIGN(x, a)	(((x) + (a) - 1) & ~((a) - 1))
/* ALIGN DOWN*/
#define ALIGN_DOWN(x, a)	((x) & ~((a) - 1))


#define write_port_byte(port,adata) (*(volatile unsigned char *)(port))=((unsigned char)(adata))
#define read_port_byte(port)        (*(volatile unsigned char *)(port))

#define write_port_halfword(port,adata) (*(volatile unsigned short *)(port))=((unsigned short)(adata))
#define read_port_halfword(port)		(*(volatile unsigned short *)(port))

#define write_port_word(port,adata) (*(volatile unsigned long *)(port))=((unsigned long)(adata))
#define read_port_word(port)		(*(volatile unsigned long *)(port))


#endif /* __IOMACROS_H__ */
