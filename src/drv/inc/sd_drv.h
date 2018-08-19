#ifndef __SDDC_DRV_H__
#define __SDDC_DRV_H__

//Macro Definition
#define MULTI_READ_CMD_END				(0)
#define MULTI_READ_CMD_START			(1)
#define MULTI_WRITE_CMD_END				(2)
#define MULTI_WRITE_CMD_START			(3)
#define MULTI_CMD_NULL					(4)

#define MULTI_RW_NULL_FLAG				(0)
#define MULTI_READ_FLAG					(1)
#define MULTI_WRITE_FLAG				(2)

#define MULT_RW_CMD_LBA					(0x237)
#define MULT_RW_DATA_LEN				(0x10000/4)//64KB

#define SD_GALDATABUF_LEN				(0x200)

typedef enum
{
	HS_MODE,
	SDR50_MODE,
	SDR104_MODE,
}sd_speed_mode;

typedef void (*SD_EMMC_ISR_ROUTINE)(void);
typedef UINT8 (*SD_EMMC_RW_ROUTINE)(UINT32 lba,
									UINT32 g_sd_cmdbuf,
									UINT32 g_sd_databuf,
									UINT32 multi_flag,
									UINT32 multi_rw_data_len);

// vender handler return state
#define VENDOR_HANLDER_SUCCESS			(0)
#define VENDOR_HANDLER_FAILED			(1)

extern void sd_mem_handler(void);
extern void sddc_init(sd_speed_mode sd_mode,
						UINT32 *data_buf,
						SD_EMMC_RW_ROUTINE read_cmd_handler,
						SD_EMMC_RW_ROUTINE write_cmd_handler);
extern void set_multi_rw_para(UINT32 addr, UINT32 len, UINT32 is_write);
extern void clr_multi_rw_para();

#endif
