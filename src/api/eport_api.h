// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eport_spi.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __EPORT_API_H__
#define __EPORT_API_H__

#include "includes.h"
#include "eport_drv.h"
#include "mim_drv.h"

#define EPORT_PORT0				0
#define EPORT_PORT1				1
#define EPORT_PORT2				2
#define EPORT_PORT3				3
#define EPORT_PORT4				4
#define EPORT_PORT5				5
#define EPORT_PORT6				6
#define EPORT_PORT7				7

#define EPORT_PORT_LOW			0
#define EPORT_PORT_HIGH			1

#define EPORT_PORT_INPUT		0
#define EPORT_PORT_OUTPUT		1

extern void eport_config(UINT8 eport_num, UINT8 direction, BOOL interrupt, EPORT_INT_MODE int_mode);
extern void eport_write_port_data(UINT8 eport_num, UINT8 data);
extern UINT8 eport_read_port_data(UINT8 eport_num);
extern void eport_write_data(UINT8 eport_mask, UINT8 data);
extern UINT8 eport_read_data(UINT8 eport_mask);

#endif /* __EPORT_API_H__ */
