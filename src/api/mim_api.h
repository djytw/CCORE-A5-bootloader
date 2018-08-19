// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : mim_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef MIM_API_H_
#define MIM_API_H_

#include "type.h"

typedef enum
{
    MIM_D0 = 0,
    MIM_D1,
    MIM_D2,
    MIM_D3,
    MIM_D4,
    MIM_D5,
    MIM_D6,
    MIM_D7,
    MIM_D8,
    MIM_D9,
    MIM_D10,
    MIM_D11,
    MIM_D12,
    MIM_D13,
    MIM_D14,
    MIM_D15,
    MIM_D16,
    MIM_D17,
	MIM_D18,
	MIM_D19,
	MIM_D20,
	MIM_D21,
	MIM_D22,
	MIM_D23,
	MIM_D24,
	MIM_D25,
	MIM_D26,
	MIM_D27,
	MIM_D28,
	MIM_D29,
	MIM_D30,
	MIM_D31
}MIM_PIN;

#define IS_MIM_PINx(pin) (((pin) >= MIM_D0) && \
                          ((pin) <= MIM_D31))

extern BOOL mim_config_gpio(UINT8 pin, UINT8 dir);
extern UINT8 mim_read_gpio(UINT8 pin);
extern BOOL mim_write_gpio(UINT8 pin, UINT8 val);

#endif /* MIM_API_H_ */
