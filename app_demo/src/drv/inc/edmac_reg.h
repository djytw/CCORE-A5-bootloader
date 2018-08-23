// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : edmac_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __EDMAC_REG_H__
#define __EDMAC_REG_H__

//------------------------------------------------------------------
//                        Headers
//------------------------------------------------------------------
#include "type.h"
//------------------------------------------------------------------

typedef struct{
	VUINT32 CCR;           //EDMAC Control Register of CHannel 0
	VUINT32 CSR;           //EDMAC Control State Register
	VUINT32 RBAR;          //EDMAC Read Buff Address Register of Channel 0
	VUINT32 WBAR;          //EDMAC Write Buffer Address Register of Channel 0
	VUINT32 MINISUMR;		//EDMAC MINOR SUM Counter Register of Channel 0
	VUINT32 MINICNTR;		//EDMAC MINOR Counter Register of Channel 0
	VUINT32 MAJSUMR;		//EDMAC MAJOR SUM Counter Register of Channel 0
	VUINT32 MAJCNTR;		//EDMAC MAJOR Counter Register of Channel 0
	VUINT32 SPAR0;         //EDMAC Special Peripheral Address Register of Channel 0
	VUINT32 RBARSTEP;
	VUINT32 WBARSTEP;
	VUINT32 LASTMINSUMR;
}EDMAC_REG;

//EDMAC Control Register of Channel  (EDMACCR)//offset at 0x00000000
#define EDMAC_TTYPE0_MASK				(0x00000000)	//sram to sram
#define EDMAC_TTYPE1_MASK				(0x00000020)	//peripheral to sram
#define EDMAC_TTYPE2_MASK				(0x00000040)	//sram to peripheral
#define EDMAC_TTYPE3_MASK				(0x00000060)	//sram to peripheral then peripheral to sram

//EDMAC0 PN MASK
#define EDMAC_PN5AES_MASK				(0x00000500)	//AES
#define EDMAC_PN6DES_MASK				(0x00000600)	//DES
#define EDMAC_PN7SCB2_MASK				(0x00000700)	//SCB2
#define EDMAC_PN9SM4_MASK				(0x00000900)	//SM4
#define EDMAC_PN10SHA_MASK				(0x00000a00)	//SHA
#define EDMAC_PN11SSF33_MASK			(0x00000b00)  	//SSF33
#define EDMAC_PN12RSA_MASK				(0x00000c00)  	//RSA

//EDMAC1 PN MASK
#define EDMAC_PN0SPI1_MASK				(0x00000000)	//SPI1
#define EDMAC_PN1SPI2_MASK				(0x00000100)	//SPI2
#define EDMAC_PN2USI1_MASK				(0x00000200)	//USI1
#define EDMAC_PN3USI2_MASK				(0x00000300)	//USI2
#define EDMAC_PN4USI3_MASK				(0x00000400)	//USI3
#define EDMAC_PN8SCI1_MASK				(0x00000800)  	//SCI1
#define EDMAC_PN13SCI2_MASK				(0x00000d00)  	//SCI2
#define EDMAC_PN14SPI3_MASK				(0x00000e00)	//SPI3

#define EDMAC_CHVALID_MASK				(0x00000002)
#define EDMAC_MINDONEIE_MASK			(0x00000001)

//EDMAC Control State Register (EDMACCSR)//offset at 0x00000004
#define EDMAC_MINORDONE_MASK			(0x00000002)	//MINOR DONE
#define EDMAC_EDMAEN_MASK				(0x00010000)	//EDMAEN
#define EDMAC_MAJORDONE_MASK			(0x00000008)	//MAJOR DONE




#define LINK 						0x00010000
#define LINK_SRC_SEL_0 				0x00000000
#define LINK_SRC_SEL_1 				0x00020000
#define LINK_SRC_SEL_2				0x00040000
#define LINK_SRC_SEL_3 				0x00060000
#define LINK_SRC_SEL_4 				0x00080000

#define PRELOAD_SPI_FIFO_0			0x00000000
#define PRELOAD_SPI_FIFO_2	 		0x00000004
#define PRELOAD_SPI_FIFO_4 	 		0x00000008
#define PRELOAD_SPI_FIFO_8 	 		0x0000000c

#define MINOR_CAR_SEL				0x00000000
#define MAJOR_CAR_SEL				0x00800000
#define MAJOR_CRC_SEL				0x00800000
#define MINOR_CRC_SEL 				0x00000000
#define CRC_CHEN 					0x00400000
#define SEND_CRC_CHEN				0x00200000
#define WRITE_CRC_CHEN 				0x00100000
#define MAJOR_DONEIE 				0x01000000

#define PIPELINEd			(0x80000000)
#define PIP_SPI_HW			(0x40000000)
#define PIP_SPI_HW			(0x40000000)
#define SPI_WROPT			(0x08000000)
#define PRIOR_CHG			(0x20000000)
#define PRIOR_1				(0x10000000)

#define PRELOAD_6		(6<<2)
#define EW_VALID  0x00000002
#define EW_EN  0x00010000
#define	EDMA_IE			0x01

#define	LAST_MINOR_EN 			0x80000000

#define RBAR_STEP_EN			(0x80000000)
#define RBAR_STEP_DIR			(0x40000000)

#define WBAR_STEP_EN			(0x80000000)
#define WBAR_STEP_DIR			(0x40000000)

#endif /* EDMAC_REG_H_ */
