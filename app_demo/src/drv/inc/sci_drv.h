// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : sci_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __SCI_DRV_H__
#define __SCI_DRV_H__

/* macro definition */
#define BAUDRATE_9600					(9600)
#define BAUDRATE_115200					(115200)

#define SCI_HWNUM				(2)
#define SCI1					(0)
#define SCI2					(1)


/* data structure */


/* global variables declaration */


/* function declaration */
extern void sci_puts_dev(volatile const UINT8 *s);
extern BOOL sci_init(UINT8 ucid, UINT32 sci_clk, UINT32 baudrate);

extern void sci_send_byte(UINT8 outbyte);
extern UINT8 sci_receive_byte(void);

extern BOOL sci_set_id(UINT8 ucid);
extern BOOL sci_pin_config(UINT8 ucid, UINT8 pin, UINT8 dir);
extern UINT8 sci_pin_read(UINT8 pin);
extern BOOL sci_pin_write(UINT8 pin, UINT8 val);

#endif	/* __SCI_DRV_H__ */


