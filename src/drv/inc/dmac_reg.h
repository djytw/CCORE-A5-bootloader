// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : dmac_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __DMAC_REG_H__
#define __DMAC_REG_H__

//------------------------------------------------------------------
//                        Headers
//------------------------------------------------------------------
#include "type.h"
//------------------------------------------------------------------

/****************DMA CONTROL Register define *************************/

typedef struct _DMA_CONTROL_REG
{
	VUINT32 DMACINTS;
	VUINT32 DMACINTCS;
	VUINT32 DMACINTCC;
	VUINT32 DMACINTES;
	VUINT32 DMACINTEC;
	VUINT32 DMACRINTCS;
	VUINT32 DMACRINTES;
	VUINT32 DMACENDCH;
	VUINT32 DMACSOFTBR;
	VUINT32 DMACSOFTSR;
	VUINT32 DMACSOFTLBR;
	VUINT32 DMACSOFTLSR;
	VUINT32 DMACCONFIG;
	VUINT32 DMACSYNC;
}DMAC_CONTROL_REG;

typedef struct _DMA_CHANNEL_REG
{
	VUINT32 DMACC0SADDR;
	VUINT32 DMACC0DADDR;
	VUINT32 DMACC0LLI;
	VUINT32 DMACC0CTRL;
	VUINT32 DMACC0CONFIG;
}DMAC_CHANNEL_REG;


//config data for DMACCONFIG
#define M2_BIGEND		 	(0x4)
#define M1_BIGEND 			(0x2)
#define DMACEN 				(0x1)

//config data for DMACCxCTRL
#define DMA_IE 				(0x80000000)
#define DI 					(0x08000000)
#define SI 					(0x04000000)
#define D_M2 				(0x02000000)
#define S_M2 				(0x01000000)

#define DWIDTH_HW 			(0x00200000)
#define DWIDTH_W 			(0x00400000)
#define SWIDTH_HW 			(0x00040000)
#define SWIDTH_W 			(0x00080000)

#define DBSIZE_4 			(0x00008000)
#define DBSIZE_8 			(0x00010000)
#define DBSIZE_16 			(0x00018000)
#define DBSIZE_32 			(0x00020000)
#define DBSIZE_64 			(0x00028000)
#define DBSIZE_128 			(0x00030000)
#define DBSIZE_256 			(0x00038000)

#define SBSIZE_4 			(0x00001000)
#define SBSIZE_8 			(0x00002000)
#define SBSIZE_16 			(0x00003000)
#define SBSIZE_32 			(0x00004000)
#define SBSIZE_64 			(0x00005000)
#define SBSIZE_128 			(0x00006000)
#define SBSIZE_256 			(0x00007000)

//config data for DMACCxCONFIG
#define HALT 				(0x00040000)
#define ACTIVE 				(0x00020000)
#define ITC 				(0x00008000)
#define INTErr 				(0x00004000)
#define M2P_DMA 			(0x00000800)
#define P2M_DMA 			(0x00001000)
#define P2P_DMA 			(0x00001800)
#define P2P_DST 			(0x00002000)
#define M2P_DST 			(0x00002800)
#define P2M_SRC 			(0x00003000)
#define P2P_SRC 			(0x00003800)
#define CHEN 				(0x00000001)




#endif /* __DMAC_REG_H__ */
