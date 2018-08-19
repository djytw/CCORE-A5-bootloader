// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : i2c_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "includes.h"
#include "i2c_api.h"
#include "i2c_demo.h"
#include "i2c_reg.h"
#include "vector_define.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Demo of i2c.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_demo()
{
#ifdef I2C_MASTER_DEMO

	UINT8 ret_val = 0;
	UINT8 i2c_write_buf[256];
	UINT8 i2c_read_buf[256];
	UINT32 i;

	for(i=0;i<0xc0;i++)
	{
		i2c_write_buf[i] = (i+1);
		i2c_read_buf[i] = 0;
	}

	ret_val = i2c_master_init(0x0, I2C_POLL_MODE);

	if(ret_val == FALSE)
	{
		MSG("The input arguments have errors\n");
	}

	i2c_master_write(0x30, i2c_write_buf, 0xc0, I2C_POLL_MODE);

	delay(1000);

	i2c_master_read(0x30, i2c_read_buf, 0xc0, I2C_POLL_MODE);

	for(i=0;i<0xc0;i++)
	{
		if(i2c_read_buf[i] != i2c_write_buf[i])
		{
			MSG("The i2c driver fails\n");
			asm("bkpt");
		}
	}

	MSG("The i2c driver succeeds\n");

#else
	UINT8 ret_val = 0;
	UINT8 i2c_receive_buf[256];

	UINT32 i;

	for(i=0;i<0xc0;i++)
	{
		i2c_receive_buf[i] = 0;
	}

	ret_val = i2c_slave_init(0x30, I2C_INT_MODE);

	if(ret_val == FALSE)
	{
		MSG("The input arguments have errors\n");
	}

	while(1)
	{
		i2c_slave_trans(i2c_receive_buf, 0xc0, i2c_receive_buf, 0xc0, I2C_INT_MODE);
	}

#endif
}

