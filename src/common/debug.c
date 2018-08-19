// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : debug.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "debug.h"

static char msg_str_buf[MSG_STR_BUF_LEN_MAX + MSG_STR_BUF_LEN_GUARD];

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 __msg_outputs
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Send the string to SCI.
//
// Input:
//    strs: string to be send
//    len:  length of the string.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static INLINE void __msg_outputs(char *strs, UINT32 len)
{
    sci_puts_dev((UINT8*)strs);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 msg_printf
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Print through SCI.
//
// Input:
//    Standard input of print function.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void msg_printf(char *fmt, ...)
{
    va_list args;
    UINT32 len;

    va_start(args, fmt);
    vsprintf(msg_str_buf, fmt, args);
    len = strlen(msg_str_buf);
    if(len > MSG_STR_BUF_LEN_MAX)
    {
        __msg_outputs(MSG_BUF_OVF_STR,strlen(MSG_BUF_OVF_STR));
        while(1);
    }

    __msg_outputs(msg_str_buf, len);

    va_end(args);
}

void assert(BOOL val)
{
	if( val == FALSE )
	{
		asm("bkpt");
	}
}
