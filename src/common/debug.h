// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : debug.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "includes.h"
#include "sci_api.h"
#include "sci_drv.h"

/*-------------------------------------------------------------------*/
#define MSG_STR_BUF_LEN_MAX             256
#define MSG_STR_BUF_LEN_GUARD           4

#define MSG_BUF_OVF_STR                 "-E-: Msg Buffer Overflow!\r\n"

/*-------------------------------------------------------------------*/
enum
{
    MSG_LVL_NONE,
    MSG_LVL_ERR,
    MSG_LVL_WARN,
    MSG_LVL_INFO,
    MSG_LVL_DBG,
};

//#define MSG_LVL MSG_LVL_WARN	//default
#define MSG_LVL MSG_LVL_DBG

#define SYS_ERR "-E-: "
#define SYS_WARN "-W-: "
#define SYS_INFO "-I-: "
#define SYS_DBG "-D-: "


#define PRINTF(...) msg_printf(__VA_ARGS__)
#define MSG(...) msg_printf(__VA_ARGS__)
#define MSG_WARN(...) (MSG_LVL < MSG_LVL_WARN) ? (void)0 : msg_printf(SYS_WARN __VA_ARGS__)
#define MSG_INFO(...) (MSG_LVL < MSG_LVL_INFO) ? (void)0 : msg_printf(SYS_INFO __VA_ARGS__)
#define MSG_DBG(...) (MSG_LVL < MSG_LVL_DBG) ? (void)0 : msg_printf(SYS_DBG __VA_ARGS__)
#define MSG_ERR(...) (MSG_LVL < MSG_LVL_DBG) ? (void)0 : msg_printf(SYS_ERR __VA_ARGS__)


/*-------------------------------------------------------------------*/

void msg_printf(char *fmt, ...);
void assert(BOOL val);

#endif /* __DEBUG_H__ */

