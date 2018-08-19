// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usi_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __USI_REG_H__
#define __USI_REG_H__

#define MAX_DATABUF_LEN			256
#define MAX_HEADER_LEN			6

#define	ATR_LENGTH		0x14

#define	INS_PPS			0x10
//------------------------------------------------------------

typedef struct	_sUSIReg{
	volatile unsigned char	USIBDR;
	volatile unsigned char	USICR1;
	volatile unsigned char	USICR2;
	volatile unsigned char	USISR;

	volatile unsigned char	USIIER;

	union{
		volatile unsigned char	USIRDR;
		volatile unsigned char	USITDR;
	};

	volatile unsigned char	USIWTRH;
	volatile unsigned char	USIWTRM;
	volatile unsigned char	USIWTRL;

	volatile unsigned char	USIGTRH;
	volatile unsigned char	USIGTRL;

	volatile unsigned char	USICSR;
	volatile unsigned char	USIPCR;
	volatile unsigned char	USIPORT;
	volatile unsigned char	USIDDR;
	volatile unsigned char	USIFIFOINTCON;
	volatile unsigned short	USICRC;
}sUSIReg;


#define USI_BASE USI1_BASE

#define USI1_CR1				(*(volatile unsigned char *)(USI1_BASE + 0x01))
#define USI1_CR2				(*(volatile unsigned char *)(USI1_BASE + 0x02))
#define USI1_PCR				(*(volatile unsigned char *)(USI1_BASE + 0x0c))
#define USI1_PDR				(*(volatile unsigned char *)(USI1_BASE + 0x0d))
#define USI1_DDR				(*(volatile unsigned char *)(USI1_BASE + 0x0e))

/////////////////////////////////////////////////////////////
#define USISR_TDRE_MASK     0x80
#define USISR_TC_MASK       0x40
#define USISR_RDRF_MASK     0x20
#define USISR_OR_MASK       0x10
#define USISR_ERROR_MASK    0x08
#define USISR_ATR_MASK      0x04
#define USISR_WTO_MASK      0x02
#define USISR_SB_MASK       0x01


#endif /* __USI_REG_H__ */
