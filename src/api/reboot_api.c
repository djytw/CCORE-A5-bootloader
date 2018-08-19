/*
 * reboot_api.c
 *
 *  Created on: 2017Äê11ÔÂ29ÈÕ
 *      Author: YangWenfeng
 */

#include "eflash_drv.h"


void reboot(void)
{
	eflash_recovery_to_rom();
}
