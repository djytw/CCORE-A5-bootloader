// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usi_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __USI_API_H__
#define __USI_API_H__

#include "includes.h"
#include "usi_drv.h"
#include "int_drv.h"

#define USI1		1
#define USI2		2
#define USI3		3

//usi id
enum{
	USI_ID1 = USI1,
	USI_ID2 = USI2,
	USI_ID3 = USI3
};

typedef enum
{
    USI_RST = 0,
    USI_CLK,
    USI_DAT,
}USI_PIN;

#define IS_USI_PINx(pin) (((pin) == USI_RST) || \
                          ((pin) == USI_CLK) ||\
                         ((pin) == USI_DAT) )

#define CLA				apdu_cmdbuf[0]
#define INS				apdu_cmdbuf[1]
#define P1				apdu_cmdbuf[2]
#define P2				apdu_cmdbuf[3]
#define P1P2			(P1*256|P2)
#define P3				apdu_cmdbuf[4]

#define INS_READ_VERSION			0xE2//??：：?：：：a?to：a：?2?t????┐?o?
#define INS_GET_RESPONSE			0xC0//GET RESPONSE

extern void usi_init(void);
extern void usi_process(void);

extern BOOL usi_config_gpio(UINT8 ucid, UINT8 pin, UINT8 dir);
extern UINT8 usi_read_gpio(UINT8 ucid, UINT8 pin);
extern BOOL usi_write_gpio(UINT8 ucid, UINT8 pin, UINT8 val);

#endif /* __USI_API_H__ */
