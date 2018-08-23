// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : scu_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __SCU_REG_H__
#define __SCU_REG_H__

#define SCU_PWR_CTR							(*(volatile UINT32*)(SCU_BASE + 0x10))
#define SCU_ASSERT_BUSY_CNT_CFG				(*(volatile UINT32*)(SCU_BASE + 0x14))
#define SCU_FW_STAT							(*(volatile UINT32*)(SCU_BASE + 0x28))
#define SCU_MMC_CTR							(*(volatile UINT32*)(SCU_BASE + 0x2C))
#define SCU_MMC_STAT						(*(volatile UINT32*)(SCU_BASE + 0x30))
#define SCU_MEM_DS							(*(volatile UINT32*)(SCU_BASE + 0x34))
#define SCU_MEM_SD							(*(volatile UINT32*)(SCU_BASE + 0x38))
#define SCU_CMD_IDX							(*(volatile UINT32*)(SCU_BASE + 0x5C))
#define SCU_CMD_ARG							(*(volatile UINT32*)(SCU_BASE + 0x60))
#define SCU_CMD_TIMESTAMP					(*(volatile UINT32*)(SCU_BASE + 0x64))
#define SCU_TIMESTAMP						(*(volatile UINT32*)(SCU_BASE + 0x68))
#define SCU_BASE_TIMER						(*(volatile UINT32*)(SCU_BASE + 0x6C))

/* SCU_PWR_CTR */
#define EMMC_DATA							(1<<8)
#define EMMC_CMDQ							(1<<12)

/* SCU_FW_STAT */
#define FW_STAT								(1<<0)

/* SCU_MMC_CTR */
#define PORT_TO_FIX_PSWD_LOCK				(1<<0)
#define VOLT_REG_1_8V						(1<<1)
#define CMD61_ENABLE						(1<<2)
#define RAM2_POWER_OFF						(1<<3)
#define EMMC_EVT_LOG_EN						(1<<4)
#define EMMC_CMD_LOG_EN						(1<<5)
#define ASSER_BUSY							(1<<6)
#define CMD7_SWIDTH_DISABLE					(1<<7)
#define ACMD6_SWIDTH_DISABLE				(1<<8)
#define SOFTWARE_SWIDTH						(1<<9)

/* SCU_MMC_STAT */
#define EXIT_LOW_POWER						(1<<0)
#define STOP_INER_TO_STOP					(1<<1)
#define CMD_RECEIVED						(1<<2)
#define CMD_ARG_FIFO_EMPTY					(1<<8)
#define CMD_IDX_FIFO_EMPTY					(1<<9)
#define CMD_ARG_FIFO_FULL					(1<<10)
#define CMD_IDX_FIFO_FULL					(1<<11)

/* SCU_MEM_DS */
#define AHBRAM0								(1<<0)
#define AHBRAM1								(1<<1)
#define AHBRAM2								(1<<2)
#define AHBRAM3								(1<<3)
#define AHBRAM4								(1<<4)
#define AHBRAM5								(1<<5)
#define AHBRAM6								(1<<6)
#define AHBRAM7								(1<<7)
#define CACHE_TAG0							(1<<8)
#define CACHE_TAG1							(1<<9)
#define USB									(1<<16)
#define AES_BIST_CON0						(1<<17)
#define AES_BIST_CON1						(1<<18)
#define AES_BIST_CON2						(1<<19)
#define AES_BIST_CON3						(1<<20)
#define CRY_SHA_BIST_CON8					(1<<21)

/* SCU_MEM_SD */
#define AHBRAM0								(1<<0)
#define AHBRAM1								(1<<1)
#define AHBRAM2								(1<<2)
#define AHBRAM3								(1<<3)
#define AHBRAM4								(1<<4)
#define AHBRAM5								(1<<5)
#define AHBRAM6								(1<<6)
#define AHBRAM7								(1<<7)
#define CACHE_DATA0							(1<<8)
#define CACHE_DATA1							(1<<9)
#define ROM_DATA							(1<<10)
#define ROM_CODE							(1<<11)
#define NFC_DP_SRAM0						(1<<22)
#define NFC_DP_SRAM1						(1<<23)
#define NFC_DP_SRAM2						(1<<24)
#define NFC_CDMA							(1<<25)

#endif /* __SCU_REG_H__ */
