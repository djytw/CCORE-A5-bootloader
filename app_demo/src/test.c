/*
 * test.c
 *
 *  Created on: 2018Äê8ÔÂ12ÈÕ
 *      Author: SYSTEM
 */

#include "includes.h"
#include "wdt_api.h"
#include "cpm_api.h"
#include "eport_api.h"
#include "eflash_api.h"
void test(){
	int i,k;
	u8 lst[]={0,5,2,7,6,3,4,1};
	while(1)
	for(i=0;i<8;i++){
		eport_write_data(0xff, 0xff);
		k=1<<lst[i];
		eport_write_data(k, 0);
		delay(550000);
	}
}
