// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : mim_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "type.h"
#include "mim_drv.h"
#include "mim_reg.h"
#include "mim_api.h"

/*******************************************************************************
* Function Name  : mim_config_gpio
* Description    : MIM配置成GPIO用途。
*
* Input          : - pin：MIM对应的PIN脚，取值MIM_D0 ~ MIM_D31.
*                  - dir：设置GPIO方向   GPIO_OUTPUT：输出    GPIO_INPUT：输入
*
* Output         : None
* Return         : TRUE or FALSE
* ******************************************************************************/
BOOL mim_config_gpio(UINT8 pin, UINT8 dir)
{
	BOOL ret_val;

	if(!IS_MIM_PINx(pin))
	{
		return	FALSE;
	}

	ret_val = mim_pin_config(pin, dir);

	return ret_val;
}

/*******************************************************************************
* Function Name  : mim_read_gpio
* Description    : 获取pin对应引脚的电平
* Input          : - pin：MIM对应的PIN脚，取值MIM_D0 ~ MIM_D31.
*
* Output         : None
* Return         : Bit_SET:高电平  Bit_RESET：低电平
******************************************************************************/
UINT8 mim_read_gpio(UINT8 pin)
{
	UINT8 val = 0x00;

	if(!IS_MIM_PINx(pin))
	{
		return	FALSE;
	}

	val = mim_pin_read(pin);

	return val;
}

/*******************************************************************************
* Function Name  : mim_write_gpio
* Description    : 设置pin对应引脚的电平
* Input          : - pin：MIM对应的PIN脚，取值MIM_D0 ~ MIM_D31.
*                  - val：设置的电平，Bit_SET：设置为高电平  Bit_RESET：设置为低电平
*
* Output         : None
* Return         : TRUE or FALSE
******************************************************************************/
BOOL mim_write_gpio(UINT8 pin, UINT8 val)
{
	BOOL ret_val;

	if(!IS_MIM_PINx(pin))
	{
		return	FALSE;
	}

	ret_val = mim_pin_write(pin, val);

	return ret_val;
}

