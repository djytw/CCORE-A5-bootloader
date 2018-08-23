// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : i2c_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __I2C_API_H__
#define __I2C_API_H__

#include "type.h"

typedef enum
{
    I2C_SCL = 0,
    I2C_SDA,

}I2C_PIN;

#define IS_I2C_PINx(pin) (((pin) == I2C_SCL) || \
                          ((pin) == I2C_SDA))

extern BOOL i2c_master_init(UINT8 pre, UINT8 trans_mode);
extern BOOL i2c_slave_init(UINT8 addr, UINT8 trans_mode);
extern void i2c_master_write(UINT8 slave_addr, UINT8* buf, UINT16 len, UINT8 trans_mode);
extern void i2c_master_read(UINT8 slave_addr, UINT8* buf, UINT16 len, UINT8 trans_mode);
extern void i2c_slave_trans(UINT8* r_buf,UINT16 r_len,UINT8* s_buf,UINT16 s_len, UINT8 trans_mode);
extern BOOL i2c_config_gpio(UINT8 pin, UINT8 dir);
extern UINT8 i2c_read_gpio(UINT8 pin);
extern BOOL i2c_write_gpio(UINT8 pin, UINT8 val);

#endif /* __I2C_API_H__ */
