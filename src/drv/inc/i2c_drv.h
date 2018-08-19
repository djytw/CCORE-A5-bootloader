// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : i2c_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __I2C_DRV_H__
#define __I2C_DRV_H__

#include "type.h"
#include "memmap.h"

extern BOOL i2c_config(UINT8 pre, UINT8 addr, UINT8 device_mode);
extern void i2c_interrupt_enable();
extern void i2c_m_writedata(UINT8 slave_addr,UINT8* buf,UINT16 len);
extern void i2c_m_writedata_int(UINT8 slave_addr,UINT8* buf,UINT16 len);
extern void i2c_m_readdata(UINT8 slave_addr,UINT8* buf,UINT16 len);
extern void i2c_m_readdata_int(UINT8 slave_addr,UINT8* buf,UINT16 len);
extern void i2c_s_trans_data(UINT8* r_buf,UINT16 r_len,UINT8* s_buf,UINT16 s_len);
extern void i2c_s_trans_data_int(UINT8* r_buf,UINT16 r_len,UINT8* s_buf,UINT16 s_len);
extern BOOL i2c_pin_config(UINT8 pin, UINT8 dir);
extern UINT8 i2c_pin_read(UINT8 pin);
extern BOOL i2c_pin_write(UINT8 pin, UINT8 val);

#endif /* __I2C_DRV_H__ */
