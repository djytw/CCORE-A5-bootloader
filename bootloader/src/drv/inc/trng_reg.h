// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : trng_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __TRNG_REG_H__
#define __TRNG_REG_H__

#define TRNG_CR					*(volatile UINT32*)(TRNG_BASE + 0x0)
#define TRNG_DR					*(volatile UINT32*)(TRNG_BASE + 0x4)

#define TRNG_CR_H               *(volatile UINT16*)(TRNG_BASE + 0x2)
#define TRNG_CR_L               *(volatile UINT16*)(TRNG_BASE + 0x0)

#endif /* __TRNG_REG_H__ */
