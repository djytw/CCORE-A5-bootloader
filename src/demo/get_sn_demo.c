/*
 * get_sn_demo.c
 *
 *  Created on: 2017Äê10ÔÂ24ÈÕ
 *      Author: fjzhang
 */
#include "type.h"
#include "debug.h"
#include "get_sn_api.h"


void get_sn_demo(void)
{
	UINT8 i;
	UINT8 databuf[8];

	msg_printf("get sn demo\r\n");

	get_sn(databuf);
	msg_printf("sn:");
	for(i = 0; i < 8; i ++)
	{
		msg_printf("%02x ",databuf[i]);
	}
	msg_printf("\r\n");

	while(1);

}

