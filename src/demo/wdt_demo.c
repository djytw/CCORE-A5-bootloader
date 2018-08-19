// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : wdt_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "wdt_demo.h"
#include "wdt_api.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 wdt_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    watch dog timer demo func.
//
// Input:
//    None.
//
// Output:
//    None.
//
// Note:
//    After sys-boot, WDT is running by default. WDT can't be configured twice.
//    To use this demo, WDT must not be configure before, for example in crt0.s
//	            lrw		r3,0x0e
//	            lrw		r2,0x70090000
//	            st.h	r3,(r2,0)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void wdt_demo()
{
	int i;

	MSG("\r\n\r\n%s entered!\r\n", __func__);

    set_WDT_span(0x6f00);
    if(get_WDT_state()==WDT_STOPPED)
    {
    	MSG("Oops, WDT was configured somewhere before!\r\n");
    	return;
    }
    else
    {
       start_WDT();
    }
    for(i=0x5000; i>0; i--)
    {
    	if( (i%0x400)==0x00 )
    	{
    		feed_WDT();
    		MSG("-1- WDT count: 0x%04x\r\n", check_WDT_life());
    	}
    	else
    	{
    		if( (i%150) == 0x00 )
    		{
    			MSG("-2- WDT count: 0x%04x\r\n", check_WDT_life());
    		}
    	}

    }

    MSG("NO feed ...\r\n");
    while(1)
    {
    	i++;
    	if( (i%0x1000) == 0x00 )
    	{
    		MSG("WDT count: 0x%04x\r\n", check_WDT_life());
    	}
    }
}
