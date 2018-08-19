// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : sys_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __SYS_API_H__
#define __SYS_API_H__

#include "type.h"
#include "debug.h"
#include "cpm_drv.h"
#include "sci_drv.h"
#include "pit_drv.h"
#include "ccm_drv.h"
#include "cpm_api.h"
#include "reboot_demo.h"
#include "i2c_api.h"
#include "wdt_api.h"

void printf_version(void);
void sys_init(void);

#endif /* __SYS_API_H__ */
