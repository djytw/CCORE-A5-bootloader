/*
 * reboot_api.c
 *
 *  Created on: 2017��11��29��
 *      Author: YangWenfeng
 */

#include "eflash_drv.h"


void reboot(void)
{
	eflash_recovery_to_rom();
}
