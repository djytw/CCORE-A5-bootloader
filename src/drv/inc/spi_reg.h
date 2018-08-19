// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : spi_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __SPI_REG_H__
#define __SPI_REG_H__

//------------------------------------------------------------------
//                        Headers
//------------------------------------------------------------------
#include "type.h"
//------------------------------------------------------------------

typedef struct
{
	VUINT8  BR;            //SPI Baud Rate Register
    VUINT8  FR;            //SPI Frame Register
    VUINT8  CR1;           //SPI Control Register 1
    VUINT8  CR2;           //SPI Control Register 2
    VUINT8  RXFTOCTR;      //SPI RX FIFO Timeout Counter Register
    VUINT8  TXFTOCTR;      //SPI TX FIFO Timeout Counter Register
    VUINT8  RXFCR;         //SPI RX FIFO Control Register
    VUINT8  TXFCR;         //SPI TX FIFO Control Register
    VUINT8  ASCDR;         //SPI After SCK Delay Register
    VUINT8  BSCDR;         //SPI Before SCK Delay Register
    VUINT8  DDR;           //SPI Port Data Direction Register
    VUINT8  PURD;          //SPI Pullup and Reduced Drive Register
    VUINT8  TCNT_M;        //SPI Transmit Counter Register Mid
    VUINT8  TCNT_H;        //SPI Transmit Counter Register High
    VUINT8  PORT;          //SPI Port Data Register
    VUINT8  TCNT_L;        //SPI Transmit Counter Register Low
    VUINT8  IRSP;          //Interrupt Register of SS Pin
    VUINT8  Reserved_11;	//Reserved at 0x00000011
    union
    {
    	VUINT16 DR16;      //SPI Data Register
    	struct		//zfj20171214
    	{
    		VUINT8  DR_L;      //SPI Data Register Low
    		VUINT8  DR_H;      //SPI Data Register High
    	}DRHL;
    };
    VUINT8  RXFSR;         //SPI RX FIFO Status Register
    VUINT8  TXFSR;         //SPI TX FIFO Status Register
    VUINT16 SR16;      	//SPI Status Register
    VUINT8  FDCR;          //SPI FIFO Debug Control Register
    VUINT8  ICR;           //SPI Interrupt Control Register
    VUINT8  DMACR;         //SPI DMA Control Register
    VUINT8  DMATHR;        //SPI DMA Threshold Register
    VUINT8  RXFDBGR;       //SPI RX FIFO Debug Register
    VUINT8  Reserved_1D;	//Reserved at 0x0000001D
    VUINT8  TXFDBGR;       //SPI TX FIFO Debug Register
}SPI_REG;


//SPI FIFO size
#define SPI_FIFO_SIZE	(8)

//SPIBR(SPI Baud Rate divisor Register macros)//offset at 0x00000000
#define SPI_BR_2					(0x00)
#define SPI_BR_4					(0x01)
#define SPI_BR_6					(0x20)
#define SPI_BR_8					(0x02)
#define SPI_BR_10					(0x40)
#define SPI_BR_20					(0x41)
#define SPI_BR_40					(0x42)
#define SPI_BR_64					(0x05)

//SPIFR(SPI Frame Register macros)//offset at 0x00000001
#define SPIFR_CONT_MASK				(0x80)
#define SPIFR_GTE_MASK				(0x40)
#define SPIFR_LBM_MASK				(0x20)
#define SPIFR_FFSEL_MASK			(0x10)
#define SPIFR_FMSZ_MASK				(0x0f)
#define FMSZ4_16(len)				(len-1)

//SPICR1(SPI Control Register1 macros)//offset at 0x00000002
#define SPICR1_SPIE_MASK			(0x80)
#define SPICR1_SPE_MASK				(0x40)
#define SPICR1_SWOM_MASK			(0x20)
#define SPICR1_MSTR_MASK			(0x10)
#define SPICR1_CPOL_MASK			(0x08)
#define SPICR1_CPHA_MASK			(0x04)
#define SPICR1_SSOE_MASK			(0x02)
#define SPICR1_LSBFE_MASK			(0x01)

//SPICR2(SPI Control Register1 macros)//offset at 0x00000003
#define SPICR2_GT_MASK				(0xfc)
#define SPICR2_SPISDOZ_MASK			(0x02)
#define SPICR2_SPC0_MASK			(0x01)

//SPIRXFTOCTR(SPI RX FIFO TimeOut Counter Register macros)//offset at 0x00000004
#define SPIRXFTOCTR_RXFTOIE_MASK	(0x80)
#define SPIRXFTOCTR_RXFTOE_MASK		(0x40)

//SPITXFTOCTR(SPI TX FIFO TimeOut Counter Register macros)//offset at 0x00000005
#define SPITXFTOCTR_TXFTOIE_MASK	(0x80)
#define SPITXFTOCTR_TXFTOE_MASK		(0x40)

//SPIRXFCR(SPI RX FIFO Control Register macros)//offset at 0x00000006
#define SPIRXFCR_RXFCLR_MASK        (0x80)
#define SPIRXFCR_RXFOVIE_MASK       (0x40)
#define SPIRXFCR_RXFUDIE_MASK       (0x20)
#define SPIRXFCR_RXFSTHIE_MASK      (0x10)
#define SPIRXFCR_RXFSTH_MASK		(0x0f)

//SPITXFCR(SPI TX FIFO Control Register macros)//offset at 0x00000007
#define SPITXFCR_TXFCLR_MASK        (0x80)
#define SPITXFCR_TXFOVIE_MASK       (0x40)
#define SPITXFCR_TXFUDIE_MASK       (0x20)
#define SPITXFCR_TXFSTHIE_MASK      (0x10)
#define SPITXFCR_TXFSTH_MASK		(0x0f)

//SPIASDR(SPI After SCK Delay Register macros)//offset at 0x00000008
#define SPIASDR_ASCDE_MASK			(0x80)
#define SPIASDR_PASCD_MASK			(0x70)
#define SPIASDR_ASCD_MASK			(0x07)

//SPIBSDR(SPI Before SCK Delay Register)//offset at 0x00000009
#define SPIASDR_BSCDE_MASK			(0x80)
#define SPIASDR_PBSCD_MASK			(0x70)
#define SPIASDR_BSCD_MASK			(0x07)

//SPIDDR(SPI Port Data Direction Register macros)//offset at 0x0000000a
#define SPIDDR_SS_MASK				(0x08)
#define SPIDDR_SCK_MASK				(0x04)
#define SPIDDR_MOSI_MASK			(0x02)
#define SPIDDR_MISO_MASK			(0x01)

//SPIPURD(SPI Pullup and Reduced Drive Register macros)//offset at 0x0000000b
#define SPIPURD_HS_MASK 			(0x80)
#define SPIPURD_PSW_MASK 			(0x40)
#define SPIPURD_DBLTXDR_MASK 		(0x20)
#define SPIPURD_RDPSP_MASK 			(0x10)
#define SPIPURD_PDPSP_MASK 			(0x02)
#define SPIPURD_PUPSP_MASK 			(0x01)

//SPIPORT(SPI Port Data Register macros)//offset at 0x0000000e
#define SPIPORT_SS_MASK				(0x08)
#define SPIPORT_SCK_MASK			(0x04)
#define SPIPORT_MOSI_MASK			(0x02)
#define SPIPORT_MISO_MASK			(0x01)

//SPIISP( Interrupt Register of SS Pin macros)//offset at 0x00000010
#define SPIPORT_SSIE_MASK			(0x80)
#define SPIPORT_SSF_MASK			(0x10)
#define SPIPORT_SSLPR_MASK			(0x08)
#define SPIPORT_SSD_MASK			(0x04)
#define SPIPORT_SSPA_MASK			(0x03)

//SPIRXFSR(SPI RX FIFO Status Register macros)//offset at 0x00000014
#define SPIRXFSR_RXNXTP_MASK		(0x70)
#define SPIRXFSR_RXFCTR_MASK		(0x0f)

//SPITXFSR(SPI TX FIFO Status Register macros)//offset at 0x000000015
#define SPITXFSR_TXNXTP_MASK		(0x70)
#define SPITXFSR_TXFCTR_MASK		(0x0f)

//SPISRL(SPI Status Register macros)//offset at 0x00000016
#define SPISR_TXFTO_MASK	        (0x8000)
#define SPISR_TXFOVF_MASK			(0x4000)
#define SPISR_TXFUDF_MASK			(0x2000)
#define SPISR_TXFSER_MASK	       	(0x1000)
#define SPISR_RXFTO_MASK			(0x0800)
#define SPISR_RXFOVF_MASK			(0x0400)
#define SPISR_RXFUDF_MASK			(0x0200)
#define SPISR_RXFSER_MASK			(0x0100)
#define SPISR_SPIF_MASK				(0x0080)
#define SPISR_FLOST_MASK			(0x0040)
#define SPISR_EOTF_MASK				(0x0020)
#define SPISR_MODF_MASK				(0x0010)
#define SPISR_TXFFULL_MASK			(0x0008)
#define SPISR_TXFEMP_MASK			(0x0004)
#define SPISR_RXFFULL_MASK			(0x0002)
#define SPISR_RXFEMP_MASK			(0x0001)

//SPIFDCR(SPI FIFO Debug Control Register macros)//offset at 0x000000018
#define SPISR_TXFIDX_MASK	        (0x70)
#define SPISR_RXFIDX_MASK			(0x07)

//SPIICR(SPI Interrupt Control Register macros)//offset at 0x000000019
#define SPISR_FLOSTIE_MASK	        (0x40)
#define SPISR_MODFIE_MASK			(0x10)

//SPIDCR(SPI DMA Control Register macros)//offset at 0x00000001a
#define SPISR_TXDMAE_MASK	        (0x02)
#define SPISR_RXDMAE_MASK			(0x01)

//SPIDTR( SPI DMA Threshold Register macros)//offset at 0x00000001b
#define SPISR_TXDMATH_MASK	        (0x70)
#define SPISR_RXDMATH_MASK			(0x07)

extern UINT32 const g_spi_baseaddr[];

#endif /* __SPI_REG_H__ */
