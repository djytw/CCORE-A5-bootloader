
/*
 * sd_api.c
 *
 *  Created on: 2017Äê4ÔÂ12ÈÕ
 *      Author: ccore-1
 */

#include "type.h"
#include "iomacros.h"
#include "sd_drv.h"
#include "sd_api.h"
#include "debug.h"

UINT32 SD_VendorCMD = 0;
extern UINT32 VendorReadFlag;
static UINT32 RWDataAddr;
static UINT32 RWDataLength;

UINT8 sd_vender_read_cmd_handler(UINT32 lba,
									UINT32 g_cmdbuf,
									UINT32 g_databuf,
									UINT32 multi_flag,
									UINT32 multi_rw_data_len)
{
	UINT16 i;

	if(multi_flag == 0)
	{
		if(lba != 1)
			return VENDOR_HANDLER_FAILED;

		if(VendorReadFlag == 1)
		{
			MSG("read addr = 0x%08x, len = %d\n", RWDataAddr, RWDataLength);
			for(i = 0; i < RWDataLength; i++)
			{
				*((UINT8*)(g_cmdbuf + i)) = *((UINT8*)(RWDataAddr + i));
			}
			if(RWDataLength < 512)
			{
				for(; i < 512; i++)
				{
					*((UINT8*)(g_cmdbuf + i)) = 0;
				}
			}
		}
		else if(VendorReadFlag == 2)//multi read
		{

		}
		else
		{
			VendorReadFlag = 0;
		}
	}
	else
	{
		///TODO: Multi Read Data Process
		MSG("lba = %d, multi_flag = %d, multi_rw_data_len = 0x%x\n", lba, multi_flag, multi_rw_data_len);
	}

	return VENDOR_HANLDER_SUCCESS;
}

UINT8 sd_vender_write_cmd_handler(UINT32 lba,
									UINT32 g_cmdbuf,
									UINT32 g_databuf,
									UINT32 multi_flag,
									UINT32 multi_rw_data_len)
{
	UINT32 tmp, len;
	UINT16 i;
	UINT32 *para;

	if(lba == 1)
	{
		para = (UINT32 *)(g_cmdbuf);
		SD_VendorCMD = para[0];

		switch(SD_VendorCMD)
		{
			case SDVENCMD_ENABLE_READ:		//Enable Read Func
				RWDataAddr = para[1];
				RWDataLength = para[2];
				VendorReadFlag = para[3];
				MSG("normal read addr = 0x%x len = %d, read_flag = %d.\n", RWDataAddr, RWDataLength, VendorReadFlag);
				break;

			case SDVENCMD_DISABLE_READ:
				/* disable read function. */
				VendorReadFlag = 0;
				MSG("disable normal read.\n");
				break;

			case SDVENCMD_WRITE:
				/* write data to sram. */
				tmp = para[1];		/* the addr to be written into. */
				len = para[2];		/* the len of the written data. */
				for(i = 0; i < len; i++)
				{
					*(unsigned char *)(tmp + i) = (*(unsigned char*)(g_cmdbuf + 0x10 + i));
				}

				MSG("write addr = 0x%08x, len = %d:\n", tmp, len);
				MSG("Write Data:\n");
				for(i = 0; i < len; i++)
				{
					MSG("0x%02x, ", *((UINT8 *)(g_cmdbuf + 0x10 + i)));
					if(((i + 1) % 16) == 0)
						MSG("\n");
				}
				MSG("\n");
				break;

			case SDVENCMD_ENABLE_MULTI_WRITE:
				tmp = para[1];
				len = para[2];
				MSG("multi write addr = 0x%x len = %d.\n", tmp, len);
				set_multi_rw_para(tmp, len, 1);
				break;

			case SDVENCMD_ENABLE_MULTI_READ:
				tmp = para[1];
				len = para[2];
				MSG("multi read addr = 0x%x len = %d.\n", tmp, len);
				set_multi_rw_para(tmp, len, 0);
				break;

			case SDVENCMD_DISABLE_MULTI_WRITE:
			case SDVENCMD_DISABLE_MULTI_READ:
				clr_multi_rw_para();
				MSG("Disable multi operation. \n");
				break;

			default: ;
		}
	}
	else if(multi_flag)
	{
		///TODO: Multi Write Data Process
		MSG("lba = %d, multi_flag = %d, multi_rw_data_len = 0x%x\n", lba, multi_flag, multi_rw_data_len);
	}
	else
		return VENDOR_HANDLER_FAILED;

	return VENDOR_HANLDER_SUCCESS;
}

//void sd_ISR(void)
//{
//	sd_mem_handler();
//}

UINT32 g_sd_databuf[SD_GALDATABUF_LEN/4];

void sd_intmode(sd_speed_mode sd_mode)
{
	sddc_init(sd_mode,
			(UINT32 *)g_sd_databuf,
			&sd_vender_read_cmd_handler,
			&sd_vender_write_cmd_handler);
}
