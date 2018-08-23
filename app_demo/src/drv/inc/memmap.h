// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : memmap.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __MEMMAP_H__
#define __MEMMAP_H__

#define DES_BASE				(0x00C90000)
#define AES_BASE				(0x00CF0000)
#define SMS4_BASE				(0x00DE0000)

#define USBC_BASE				(0x01000000)
//#define DMAC_BASE				(0x03000000)
#define SCU_BASE				(0x04000000)
#define EMMC_SD_BASE			(0x06000000)

#define MIM_BASE				(0x63F00000)
#define CCM_BASE				(0x63F04000)
#define RESET_BASE				(0x63F08000)
#define SCB2_BASE				(0x63F1C000)
#define CRYPTO_BASE				(0x63F20000)
#define EDMAC_BASE				(0x63F24000)
#define LD_BASE					(0x63F38000)
#define TRNG_BASE				(0x63F40000)
#define CRC_BASE				(0x63F58000)
#define PGD_BASE				(0x63F5C000)
#define SEC_DET_BASE			(0x63F60000)
#define SHA1_BASE				(0x63F64000)
#define LED_BASE				(0x63F70000)
#define SSF33_BASE				(0x63F78000)
#define EFLASH_BASE				(0x63F80000)
#define IOMUX_BASE				(0x63F84000)
#define CPM_BASE				(0x63F88000)

#define SPI1_BASE				(0x70000000)
#define SPI2_BASE				(0x70010000)
#define SPI3_BASE				(0x70020000)
#define SCI1_BASE				(0x70030000)
#define SCI2_BASE				(0x70040000)
#define PIT1_BASE				(0x70050000)
#define PIT2_BASE				(0x70060000)
#define TC_BASE					(0x70070000)
#define EPORT1_BASE				(0x70080000)
#define WDT_BASE				(0x70090000)
#define SWP_BASE				(0x700A0000)
#define I2C_BASE				(0x700B0000)
#define USI1_BASE				(0x700C0000)
#define USI2_BASE				(0x700D0000)
#define USI3_BASE				(0x700E0000)
#define ENCR1_BASE				(0x700F0000)
#define EPORT2_BAEE				(0x70100000)
#define SPI4_BASE				(0x70110000)

#define CACHE_CONFIG_BASE		(0xFFF00000)


//TBD...
//to be checked

//EIC
#define EIC_BASE   				(0xe0000000)

//EDMAC
#define EDMAC0CH0_BASE   		(0x63f24000)
#define EDMAC0CH1_BASE   		(0x63f24040)
#define EDMAC1CH0_BASE   		(0x700f0000)
#define EDMAC1CH1_BASE   		(0x700f0040)
//DMAC
#define DMAC_BASE   			(0x03000000)

#define USI_DATA_BUF_ADDR		(0x00810000)

//USB
#define USBC_BASEADDR			(0x01000000)


//CRC
#define AHB_CRC_BASE 			(0x78000000)
#define AHB_CRC1_BASE 			(0x7c000000)


#endif /* __MEMMAP_H__ */
