// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : trng_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __TRNG_API_H__
#define __TRNG_API_H__

#include "includes.h"
#include "trng_drv.h"

void trng_enable(void);
void trng_disable(void);
UINT32 trng_rand(void);

#endif /* __TRNG_API_H__ */
