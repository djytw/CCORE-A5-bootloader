// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : alg_demo.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __ALG_DEMO_H__
#define __ALG_DEMO_H__

#include "includes.h"
#include "alg_api.h"
#include "alg_drv.h"
#include "trng_api.h"

#define BUF_BASE_ADDR                (UINT32)(0x00820000)

typedef enum{
	MEM_SEQUENCE,
	MEM_RANDOM,
	MEM_FIX
}MEM_INIT_TYPE;

extern void buffer_init(UINT32 addr, UINT32 len, MEM_INIT_TYPE type, UINT8 pattern);

void des_demo(void);
void aes_demo(void);
void sm4_demo(void);
void sm3_demo(void);

void alg_demo(void);

#endif /* __ALG_DEMO_H__ */
