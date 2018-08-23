// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : cpm_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __CPM_H__
#define __CPM_H__

#include "includes.h"
#include "cpm_drv.h"

/* data structure */


/* global variables declaration */
extern UINT32 g_sys_clk;
extern UINT32 g_ips_clk;
extern UINT32 g_efm_clk;

/* functions declaration */
extern UINT32 cpm_get_sysclk(void);
extern UINT32 cpm_get_ipsclk(void);
extern UINT32 cpm_get_efmclk(void);

extern BOOL cpm_set_sysclk(UINT32 sys_clk);

extern void cpm_init(void);

#endif /* __CPM_H__ */
