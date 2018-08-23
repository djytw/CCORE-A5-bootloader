// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : crc_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __CRC_DRV_H__
#define __CRC_DRV_H__

#include "type.h"

#define CRC32 			0x80000000
#define CRC16 			0x40000000
#define CRC8 			0x20000000
#define CLEAR 			0x10000000
#define UPDATA			0x10000000
#define DMA_SEL			0x08000000
#define BYTESWAP		0x02000000
#define EDMAC_SEL 		0x01000000
#define BIGEND 			0x04000000
#define CODE_WR_EN 		0x00010000
#define CRC_DECODE		0x00040000
#define CODE_SEND_EN 	0x00020000
#define CRC_OK		 	0x00000001
#define CRC_LATERR		0x00000002

#define EDMA_UPDATA		0x00100000
#define EDMA_LATCH		0x00080000

extern BOOL crc0_get_lasterr();
extern BOOL crc1_get_lasterr();
extern BOOL crc0_get_status();
extern BOOL crc1_get_status();
extern void crc0_init(UINT32 ulval);
extern void crc1_init(UINT32 ulval);
extern void crc0_crconfig(UINT32 ulcrreg);
extern void crc1_crconfig(UINT32 ulcrreg);
extern void crc_mode_config(UINT8 crc_mode);
extern void crc_swap_config(BOOL byte_swap);
extern void crc_init_update(UINT32 init_data);
extern void crc_input(UINT32 data);
extern UINT32 crc_get_result(void);

#endif   /* __CRC_DRV_H__ */
