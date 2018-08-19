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
* Description    : MIM���ó�GPIO��;��
*
* Input          : - pin��MIM��Ӧ��PIN�ţ�ȡֵMIM_D0 ~ MIM_D31.
*                  - dir������GPIO����   GPIO_OUTPUT�����    GPIO_INPUT������
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
* Description    : ��ȡpin��Ӧ���ŵĵ�ƽ
* Input          : - pin��MIM��Ӧ��PIN�ţ�ȡֵMIM_D0 ~ MIM_D31.
*
* Output         : None
* Return         : Bit_SET:�ߵ�ƽ  Bit_RESET���͵�ƽ
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
* Description    : ����pin��Ӧ���ŵĵ�ƽ
* Input          : - pin��MIM��Ӧ��PIN�ţ�ȡֵMIM_D0 ~ MIM_D31.
*                  - val�����õĵ�ƽ��Bit_SET������Ϊ�ߵ�ƽ  Bit_RESET������Ϊ�͵�ƽ
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

