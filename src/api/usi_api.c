// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usi_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "usi_api.h"

#define VERIFY_STRING			"7816 2017 01 18 00 00"
#define VERIFY_STRING_LEN		32

const UINT8 g_verify_string[VERIFY_STRING_LEN] = VERIFY_STRING;

/* internal variables */

/* internal functions */
static void ins_read_version(void);
static void process_apdu(void);
//static void apdu_get_data(void);
static void process_data(void);

/* global variables */


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 ins_read_version
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    APDU of read version.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void ins_read_version(void)
{
	usi_send_pb(apdu_cmdbuf[1]);
	__memcpy(apdu_buf, (void*)g_verify_string, 64);

	usi_send_le_data();
	result_code = SW_SUCCESS;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 process_apdu
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Status of APDU handler.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void process_apdu(void)
{
	if(CLA != 0xFE)
	{
		result_code = SW_CLA_NOT_SUPPORTED;
		adpu_status = APDU_STATE_IDLE;
		return;
	}

	switch (INS)
	{
		case 0x01:
			result_code = SW_SUCCESS;
			adpu_status = APDU_STATE_IDLE;
			break;
		case INS_READ_VERSION:
			ins_read_version();
			adpu_status = APDU_STATE_IDLE;
			break;
		default:
			result_code = SW_INS_NOT_SUPPORTED;
			adpu_status = APDU_STATE_IDLE;
			break;
	}
}

#if 0
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 apdu_get_data
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Get APDU data.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void apdu_get_data(void)
{
	if(apdu_cmdbuf[4] == 0){
		result_code = SW_WRONG_LENGTH;
		adpu_status = APDU_STATE_IDLE;
	}
	else{
		apdu_datalen = apdu_cmdbuf[4];
		result_code = SW_NULL;
		adpu_status = APDU_STATE_DATA;
	}

}

#endif
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 process_data
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    APDU data handler.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static void process_data(void)
{
	switch (INS)
	{
		default:
			result_code = SW_CLA_NOT_SUPPORTED;
			adpu_status = APDU_STATE_IDLE;
			break;
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_process
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Main process of USI.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void usi_process(void)
{
	if(adpu_status == APDU_STATE_CMD)
	{
		process_apdu();
		usi_send_status();
	}

	if(adpu_status == APDU_STATE_DATA_OK)
	{
		usi_dis_wto();
		process_data();
		usi_send_status();
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 usi_init
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    USI initialization.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void usi_init(void)
{
	usi_interrput_init();
	usi_apdu_init();
}

/*******************************************************************************
* Function Name  : usi_config_gpio
* Description    : USI配置成GPIO用途。
*
* Input          : - ucid: USI通道选择，取值 USI_ID1, USI_ID2, USI_ID3.
*                  - pin：USI对应的PIN脚，取值USI_RST、USI_CLK、USI_DAT.
*                  - dir：设置GPIO方向   GPIO_OUTPUT：输出    GPIO_INPUT：输入
*
* Output         : None
* Return         : TRUE or FALSE
* ******************************************************************************/
BOOL usi_config_gpio(UINT8 ucid, UINT8 pin, UINT8 dir)
{
	BOOL ret_val;

	/*invalid port number*/
	if((ucid < USI1) || (ucid > USI3))
	{
		return	FALSE;
	}

	if(!IS_USI_PINx(pin))
	{
		return	FALSE;
	}

	ret_val = usi_pin_config(ucid, pin, dir);

	return ret_val;
}

/*******************************************************************************
* Function Name  : usi_read_gpio
* Description    : 获取pin对应引脚的电平
* Input          : - ucid: USI通道选择，取值  USI_ID1, USI_ID2, USI_ID3.
*                  - pin：USI对应的PIN脚，取值USI_RST、USI_CLK、USI_DAT.
*
* Output         : None
* Return         : Bit_SET:高电平  Bit_RESET：低电平
******************************************************************************/
UINT8 usi_read_gpio(UINT8 ucid, UINT8 pin)
{
	UINT8 val = 0x00;

	/*invalid port number*/
	if((ucid < USI1) || (ucid > USI3))
	{
		return	FALSE;
	}

	if(!IS_USI_PINx(pin))
	{
		return	FALSE;
	}

	val = usi_pin_read(ucid, pin);

	return val;
}

/*******************************************************************************
* Function Name  : usi_write_gpio
* Description    : 设置USI_Pin对应引脚的电平
* Input          : - ucid: USI通道选择，取值  USI_ID1, USI_ID2, USI_ID3.
*                  - pin：USI对应的PIN脚，取值USI_RST、USI_CLK、USI_DAT.
*                  - val：设置的电平，Bit_SET：设置为高电平  Bit_RESET：设置为低电平
*
* Output         : None
* Return         : TRUE or FALSE
******************************************************************************/
BOOL usi_write_gpio(UINT8 ucid, UINT8 pin, UINT8 val)
{
	BOOL ret_val;

	/*invalid port number*/
	if((ucid < USI1) || (ucid > USI3))
	{
		return	FALSE;
	}

	if(!IS_USI_PINx(pin))
	{
		return	FALSE;
	}

	ret_val = usi_pin_write(ucid, pin, val);

	return ret_val;
}

