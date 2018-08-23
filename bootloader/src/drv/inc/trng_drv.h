// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : trng_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __TRNG_DRV_H__
#define __TRNG_DRV_H__

extern void trng_init(void);
extern void trng_close(void);
extern UINT32 trng_get_random_word(void);

#endif /* __TRNG_DRV_H__ */
