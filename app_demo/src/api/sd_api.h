/*
 * sd_api.h
 *
 *  Created on: 2017Äê5ÔÂ5ÈÕ
 *      Author: Administrator
 */

#ifndef SD_API_H_
#define SD_API_H_

//Vendor CMD definition
#define	SDVENCMD_ENABLE_READ					(0x6F706572)
#define	SDVENCMD_DISABLE_READ					(0x5F737464)
#define	SDVENCMD_WRITE							(0x6F6D4374)

#define	SDVENCMD_ENABLE_MULTI_WRITE				(0x2D3E00F1)
#define	SDVENCMD_DISABLE_MULTI_WRITE			(0x6177496E)
#define	SDVENCMD_ENABLE_MULTI_READ				(0x74616F72)
#define	SDVENCMD_DISABLE_MULTI_READ				(0x6C616C20)


extern void  sd_intmode(sd_speed_mode sd_mode);

extern UINT8 sd_vender_read_cmd_handler(UINT32 lba,
										UINT32 g_cmdbuf,
										UINT32 g_databuf,
										UINT32 multi_flag,
										UINT32 multi_rw_data_len);

extern UINT8 sd_vender_write_cmd_handler(UINT32 lba,
										 UINT32 g_cmdbuf,
										 UINT32 g_databuf,
										 UINT32 multi_flag,
										 UINT32 multi_rw_data_len);

#endif /* SD_API_H_ */
