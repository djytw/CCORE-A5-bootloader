// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : tc_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "debug.h"
#include "tc_demo.h"
#include "tc_api.h"


#define TC_INT_DEMO

void TC_demo()
{
	int i;

	MSG("\r\n\r\n%s entered!\r\n", __func__);


#ifdef 	TC_INT_DEMO
	TC_init(TC_WDP_16, 0x8f00, TC_INT_enable);
#else
	TC_init(TC_WDP_16, 0x8f00, TC_INT_disable);
#endif

    for(i=0x6000; i>0; i--)
    {
    	if( (i%0x400)==0x00 )
    	{
    		feed_TC();
    		MSG("-1- TC count: 0x%04x\r\n", get_TC_count());
    	}
    	else
    	{
    		if( (i%250) == 0x00 )
    		{
    			MSG("-2- TC count: 0x%04x\r\n", get_TC_count());
    		}
    	}

    }

    MSG("NO feed ...\r\n");
    while(1)
    {
    	i++;
    	if( (i%0x1000) == 0x00 )
    	{
    		MSG("TC count: 0x%04x\r\n", get_TC_count());
    	}
    }

}
