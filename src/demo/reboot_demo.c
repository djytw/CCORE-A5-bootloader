/*
 * reboot_demo.c
 *
 *  Created on: 2017Äê11ÔÂ29ÈÕ
 *      Author: YangWenfeng
 */

#include "reboot_api.h"
#include "cpm_api.h"
#include "eflash_api.h"

void reboot_demo(void)
{
	eflash_init(g_efm_clk);
	reboot();
}
