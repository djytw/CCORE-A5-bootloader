// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : cache_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "debug.h"
#include "ept_demo.h"
#include "ept_api.h"

void ept_demo()
{
	int i=0;

	MSG("\r\n\r\n%s entered!\r\n", __func__);


	init_EPT(EPT_EXT_CLK, EPT_INT_EN, 0xa00000);

    while(1)
    {
    	i++;
    	if( (i%0x1000) == 0x00 )
    	{
    		MSG("EPT count: 0x%06x\r\n", get_EPT_count());
    	}
    }

}
