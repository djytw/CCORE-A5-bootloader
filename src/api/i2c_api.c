// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : i2c_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "type.h"
#include "i2c_drv.h"
#include "i2c_reg.h"
#include "i2c_api.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_master_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c master inits.
//
// Input:
//    	pre
//		trans_mode
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL i2c_master_init(UINT8 pre, UINT8 trans_mode)
{
	UINT8 ret_val = 0;

	if((pre > 0x3f)||(pre < 0))
	{
		return FALSE;
	}

	ret_val = i2c_config(pre, 0x0, I2C_MASTER_MODE);
	if(ret_val == FALSE)
	{
		return FALSE;
	}

	if(trans_mode == I2C_INT_MODE)
	{
		i2c_interrupt_enable();
	}

	return TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_slave_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c slave inits.
//
// Input:
//    	addr
//		trans_mode
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL i2c_slave_init(UINT8 addr, UINT8 trans_mode)
{
	UINT8 ret_val = 0;

	ret_val = i2c_config(0x0, addr, I2C_SLAVE_MODE);
	if(ret_val == FALSE)
	{
		return FALSE;
	}

	if(trans_mode == I2C_INT_MODE)
	{
		i2c_interrupt_enable();
	}

	return TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_master_write
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c master writes data.
//
// Input:
//    	slave_addr
//		buf
//		len
//		trans_mode
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_master_write(UINT8 slave_addr, UINT8* buf, UINT16 len, UINT8 trans_mode)
{
	if(trans_mode == I2C_INT_MODE)
	{
		i2c_m_writedata_int(slave_addr, buf, len);
	}
	else
	{
		i2c_m_writedata(slave_addr, buf, len);
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_master_read
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c master reads data.
//
// Input:
//    	slave_addr
//		buf
//		len
//		trans_mode
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_master_read(UINT8 slave_addr, UINT8* buf, UINT16 len, UINT8 trans_mode)
{
	if(trans_mode == I2C_INT_MODE)
	{
		i2c_m_readdata_int(slave_addr, buf, len);
	}
	else
	{
		i2c_m_readdata(slave_addr, buf, len);
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_slave_trans
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c slave trans data.
//
// Input:
//    	r_buf
//		r_len
//		s_buf
//		s_len
//		trans_mode
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_slave_trans(UINT8* r_buf,UINT16 r_len,UINT8* s_buf,UINT16 s_len, UINT8 trans_mode)
{
	if(trans_mode == I2C_INT_MODE)
	{
		i2c_s_trans_data_int(r_buf, r_len, s_buf, s_len);
	}
	else
	{
		i2c_s_trans_data(r_buf, r_len, s_buf, s_len);
	}
}

/*******************************************************************************
* Function Name  : i2c_config_gpio
* Description    : I2C配置成GPIO用途。
*
* Input          : - pin：I2C对应的PIN脚，取值I2C_SCL、I2C_SDA.
*                  - dir：设置GPIO方向   GPIO_OUTPUT：输出    GPIO_INPUT：输入
*
* Output         : None
* Return         : TRUE or FALSE
* ******************************************************************************/
BOOL i2c_config_gpio(UINT8 pin, UINT8 dir)
{
	BOOL ret_val;

	if(!IS_I2C_PINx(pin))
	{
		return	FALSE;
	}

	ret_val = i2c_pin_config(pin, dir);

	return ret_val;
}

/*******************************************************************************
* Function Name  : i2c_read_gpio
* Description    : 获取pin对应引脚的电平
* Input          : - pin：I2C对应的PIN脚，取值I2C_SCL、I2C_SDA.
*
* Output         : None
* Return         : Bit_SET:高电平  Bit_RESET：低电平
******************************************************************************/
UINT8 i2c_read_gpio(UINT8 pin)
{
	UINT8 val = 0x00;

	if(!IS_I2C_PINx(pin))
	{
		return	FALSE;
	}

	val = i2c_pin_read(pin);

	return val;
}

/*******************************************************************************
* Function Name  : i2c_write_gpio
* Description    : 设置pin对应引脚的电平
* Input          : - pin：I2C对应的PIN脚，取值I2C_SCL、I2C_SDA.
*                  - val：设置的电平，Bit_SET：设置为高电平  Bit_RESET：设置为低电平
*
* Output         : None
* Return         : TRUE or FALSE
******************************************************************************/
BOOL i2c_write_gpio(UINT8 pin, UINT8 val)
{
	BOOL ret_val;

	if(!IS_I2C_PINx(pin))
	{
		return	FALSE;
	}

	ret_val = i2c_pin_write(pin, val);

	return ret_val;
}

