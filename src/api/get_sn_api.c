/*
 * get_sn_api.c
 *
 *  Created on: 2017Äê10ÔÂ24ÈÕ
 *      Author: fjzhang
 */

#include "get_serial_sn_drv.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 get_sn
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//		get serial number.
//		serial number length is 8 bytes.
//		so the buff must be 8 bytes at least.
// Input:
//		@buff: serial number buf, must be 8 bytes at least.
// Output:
//      @buff: 8 bytes length sn.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void get_sn(unsigned char *databuf)
{
	get_serial_number(databuf);
}
