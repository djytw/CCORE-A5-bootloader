// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : crc_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __CRC_API_H__
#define __CRC_API_H__

#include "includes.h"
#include "crc_drv.h"

#define CRC_8			0
#define CRC_16			1
#define CRC_32			2

extern UINT32 crc_calc(
	UINT8 *p_crc_data,
	UINT32 crc_data_length,
	UINT32 crc_init_data,
	UINT8 crc_mode,
	UINT8 swap_mode
);

#endif /* __CRC_API_H__ */
