// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : sci_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __SCI_API_H__
#define __SCI_API_H__

#include "includes.h"
#include "sci_drv.h"

//sci id
enum{
	SCI_ID1 = SCI1,
	SCI_ID2 = SCI2
};

typedef enum
{
    SCI_RX = 0,
    SCI_TX,

}SCI_PIN;

#define IS_SCI_PINx(pin) (((pin) == SCI_RX) || \
                          ((pin) == SCI_TX))

BOOL sci_set_ucid(UINT8 ucid);
extern BOOL sci_set_ucid(UINT8 ucid);
extern void sci_receive_data(UINT8 *rec_buf, UINT32 length);
extern void sci_send_data(const UINT8 *trans_buf, UINT32 length);
extern BOOL sci_config_gpio(UINT8 ucid, UINT8 pin, UINT8 dir);
extern UINT8 sci_read_gpio(UINT8 pin);
extern BOOL sci_write_gpio(UINT8 pin, UINT8 val);

#endif /* __SCI_H__ */
