// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eflash_demo.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __EFLASH_DEMO_H__
#define __EFLASH_DEMO_H__

#include "includes.h"
#include "eflash_drv.h"
#include "eport_drv.h"

#define EFM_DISABLE_BOOTLOADER_DEMO
#define EFM_RECOVERY_TO_ROM_DEMO

/*
 * Description:
 *     eflash progrm/erase demo.
 *
 * Input:
 *     none
 *
 * Output:
 *    none
 */
extern void eflash_demo();

#endif /* __EFLASH_DEMO_H__ */
