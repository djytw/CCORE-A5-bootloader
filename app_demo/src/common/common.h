// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : common.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __COMMON_H__
#define __COMMON_H__

#include "includes.h"

typedef union _ULINT {
//32bit
    struct  {                  // Big Endian
        unsigned char h8;
        unsigned char l8;
    } be;

    struct  {                  // Little Endian
    	unsigned char l8;
    	unsigned char h8;
    } le;

    unsigned short UI;

} ULINT;


/* define align */
#define ALIGNED(x)      __attribute__((aligned (x)))
#define BUFF_ALIGN      __attribute__((aligned (128)))
#define U32_ALIGN       __attribute__((aligned (4)))

/* define inline */
#define INLINE          __inline

extern void delay(volatile UINT32 val);
extern void dump_hex(UINT32 addr, UINT32 len);
extern BOOL check_data(UINT32 bar,  UINT32 par, UINT32 len);

#endif /* __COMMON_H__ */
