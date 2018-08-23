// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : edmac_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//------------------------------------------------------------------
//                        Headers
//------------------------------------------------------------------
#include "memmap.h"
#include "edmac_reg.h"
#include "edmac_drv.h"
#include "spi_drv.h"
#include "type.h"
#include "crc_drv.h"
#include "usi_drv.h"
#include "int_drv.h"
//------------------------------------------------------------------

/*EDMAC global status*/
VINT8 g_edmac_minordone[EDMAC_HWNUM][EDMAC_CHNUM];

/*EDMAC base address*/
const UINT32 g_edmac_baseaddr[EDMAC_HWNUM][EDMAC_CHNUM] = {
		{EDMAC0CH0_BASE, EDMAC0CH1_BASE}, {EDMAC1CH0_BASE, EDMAC1CH1_BASE}
		};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edamc interrupt service program,clear done or error states
//
// Input:
//
// Output:
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void edmac_isr()
{
	/*EDMAC registers pointer*/
	EDMAC_REG* pregspointer = 0;

	pregspointer = (EDMAC_REG *)(g_edmac_baseaddr[0][0]);
	if( (pregspointer->CSR)&(EDMAC_MINORDONE_MASK) )
	{
		g_edmac_minordone[0][0] = 0x01;
		pregspointer->CSR |= EDMAC_MINORDONE_MASK;
	}

	pregspointer = (EDMAC_REG *)(g_edmac_baseaddr[0][1]);
	if( (pregspointer->CSR)&(EDMAC_MINORDONE_MASK) )
	{
		g_edmac_minordone[0][1] = 0x01;
		pregspointer->CSR |= EDMAC_MINORDONE_MASK;
	}

	pregspointer = (EDMAC_REG *)(g_edmac_baseaddr[1][0]);
	if( (pregspointer->CSR)&(EDMAC_MINORDONE_MASK) )
	{
		g_edmac_minordone[1][0] = 0x01;
		pregspointer->CSR |= EDMAC_MINORDONE_MASK;
	}

	pregspointer = (EDMAC_REG *)(g_edmac_baseaddr[1][1]);
	if( (pregspointer->CSR)&(EDMAC_MINORDONE_MASK) )
	{
		g_edmac_minordone[1][1] = 0x01;
		pregspointer->CSR |= EDMAC_MINORDONE_MASK;
	}

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_inten
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edmac interrupt enable or disable
//
// Input:
//		ucid
//		ben
//
// Output:
//		true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL edmac_inten(UINT8 ucid, BOOL ben)
{
	EIC_REG *peicregspointer;

	if ( ucid > EDMAC1 )
	{
		return FALSE;
	}

	peicregspointer = (EIC_REG *)EIC_BASE;

	if( ucid == EDMAC0 )
	{
		if(ben)
		{
			peicregspointer->IER |= IER_EDMAC0INT_MASK;
		}
		else
		{
			peicregspointer->IER &= ~IER_EDMAC0INT_MASK;
		}
	}
	if( ucid == EDMAC1 )
	{
		if(ben)
		{
			peicregspointer->IER |= IER_EDMAC1SCI2INT_MASK;
		}
		else
		{
			peicregspointer->IER &= ~IER_EDMAC1SCI2INT_MASK;
		}
	}

	return TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_sramtrans
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edmac sram transfer program
//
// Input:
//		ucid
//		ucch
//		psrc
//		pdst
//		ulbytelen
//		binten
//
// Output:
//		true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL edmac_sramtrans(UINT8 ucid, UINT8 ucch, UINT8* psrc, UINT8* pdst, UINT32 ulbytelen, BOOL binten)
{
	/*EDMAC registers pointer*/
	EDMAC_REG* pregspointer = 0;

	/*invalid parameters*/
	if ( (ucid > EDMAC1)||(ucch > EDMACCH1) )
	{
		return	FALSE;
	}

	pregspointer = (EDMAC_REG *)(g_edmac_baseaddr[ucid][ucch]);

	if ( binten )
	{
		g_edmac_minordone[ucid][ucch] = 0;
		pregspointer->CCR = 0;
		pregspointer->CCR = EDMAC_MINDONEIE_MASK|EDMAC_TTYPE0_MASK|EDMAC_CHVALID_MASK;
		pregspointer->RBAR = (UINT32)(psrc);
		pregspointer->WBAR = (UINT32)(pdst);
		pregspointer->MINISUMR = ulbytelen;
		pregspointer->MAJSUMR = 0;
		pregspointer->CSR |= EDMAC_EDMAEN_MASK;
		while(1)
		{
		   if( g_edmac_minordone[ucid][ucch] ==  0x01 )
		   {
			   g_edmac_minordone[ucid][ucch] = 0;
			   break;
		   }
		}
	}
	else
	{
		pregspointer->CCR = 0;
		pregspointer->CCR = EDMAC_TTYPE0_MASK|EDMAC_CHVALID_MASK;
		pregspointer->RBAR = (UINT32)(psrc);
		pregspointer->WBAR = (UINT32)(pdst);
		pregspointer->MINISUMR = ulbytelen;
		pregspointer->MAJSUMR = 0;
		pregspointer->CSR |= EDMAC_EDMAEN_MASK;
		while(((pregspointer->CSR)&(EDMAC_MINORDONE_MASK))==0); // channel done
		pregspointer->CSR |= (EDMAC_MINORDONE_MASK|EDMAC_MAJORDONE_MASK); // clear done
	}

	pregspointer->CSR &= ~EDMAC_EDMAEN_MASK;
	return	TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_spitrans
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edmac spi transfer program
//
// Input:
//		ucch
//		ucch
//		psend
//		precv
//		ulbytelen
//		binten
//
// Output:
//		true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL edmac_spitrans(UINT8 ucch, UINT8 ucspiid, UINT8* psend, UINT8* precv, UINT32 ulbytelen, BOOL binten)
{
	/*EDMAC registers pointer*/
	EDMAC_REG* pregspointer = 0;

	/*invalid parameters*/
	if ( (ucch > EDMACCH1)||(ucspiid >SPI3) )
	{
		return	FALSE;
	}

	pregspointer = (EDMAC_REG *)(g_edmac_baseaddr[EDMAC1][ucch]);

	pregspointer->CCR = 0;

	if( SPI1 == ucspiid )//SPI1
	{
		pregspointer->CCR = EDMAC_TTYPE3_MASK|EDMAC_PN0SPI1_MASK|EDMAC_CHVALID_MASK;
	}
	else if( SPI2 == ucspiid )//SPI2
	{
		pregspointer->CCR = EDMAC_TTYPE3_MASK|EDMAC_PN1SPI2_MASK|EDMAC_CHVALID_MASK;
	}
	else if( SPI3 == ucspiid )//SPI3
	{
		pregspointer->CCR = EDMAC_TTYPE3_MASK|EDMAC_PN14SPI3_MASK|EDMAC_CHVALID_MASK;
	}

	pregspointer->RBAR = (UINT32)(psend);
	pregspointer->WBAR = (UINT32)(precv);
	pregspointer->MINISUMR = ulbytelen;
	pregspointer->MAJSUMR = 0;

	if ( binten )
	{
		g_edmac_minordone[1][ucch] = 0;
		pregspointer->CCR |= EDMAC_MINDONEIE_MASK;
		pregspointer->CSR |= EDMAC_EDMAEN_MASK;
		while(1)
		{
		   if( g_edmac_minordone[1][ucch] ==  0x01 )
		   {
			   g_edmac_minordone[1][ucch] = 0;
			   break;
		   }
		}
	}
	else
	{
		pregspointer->CSR |= EDMAC_EDMAEN_MASK;
		while(((pregspointer->CSR)&(EDMAC_MINORDONE_MASK))==0); // channel done
		pregspointer->CSR |= (EDMAC_MINORDONE_MASK|EDMAC_MAJORDONE_MASK); // clear done
	}
	pregspointer->CSR &= ~EDMAC_EDMAEN_MASK;
	return	TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_busy
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edmac busy
//
// Input:
//		none
//
// Output:
//		none
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void edmac_busy()
{
	usi_gpiovalu(0x04,1);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_idle
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edmac idle
//
// Input:
//		none
//
// Output:
//		none
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline void edmac_idle()
{
	usi_gpiovalu(0x04,0);
}

/*
 * edmac_piplinecrypt: edmac spi transfer program
 * input:
 * output:
 * description:
 */
VUINT32 g_edmaccryptbuf[2][2][EDMAC_CRYPTBLOCK_LEN/4];


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_idle
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edmac spi pipline transfer program
//
// Input:
//		ucspiid
//		majorch0
//		majorch1
//		frame
//		len
//		type
//		crc
//
// Output:
//		true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL edmac_piplinecrypt(UINT8 ucspiid, INT32 majorch0, INT32 majorch1, INT32 frame, INT32 len, INT32 type, UINT8 crc)
{
	/*EDMAC registers pointer*/
	EDMAC_REG* pedmac0ch0regs = 0;
	EDMAC_REG* pedmac0ch1regs = 0;
	EDMAC_REG* pedmac1ch0regs = 0;
	EDMAC_REG* pedmac1ch1regs = 0;
	UINT32 spipnmask;

	if ( ucspiid > SPI3 )
	{
		return	FALSE;
	}

	if( SPI1 == ucspiid )//SPI1
	{
		spipnmask = EDMAC_PN0SPI1_MASK;
	}
	else if( SPI2 == ucspiid )//SPI2
	{
		spipnmask = EDMAC_PN1SPI2_MASK;
	}
	else if( SPI3 == ucspiid )//SPI3
	{
		spipnmask = EDMAC_PN14SPI3_MASK;
	}

	pedmac0ch0regs = (EDMAC_REG *)(g_edmac_baseaddr[EDMAC0][0]);
	pedmac0ch1regs = (EDMAC_REG *)(g_edmac_baseaddr[EDMAC0][1]);
	pedmac1ch0regs = (EDMAC_REG *)(g_edmac_baseaddr[EDMAC1][0]);
	pedmac1ch1regs = (EDMAC_REG *)(g_edmac_baseaddr[EDMAC1][1]);
	
	pedmac0ch0regs->CSR &= ~EDMAC_EDMAEN_MASK;
	pedmac0ch1regs->CSR &= ~EDMAC_EDMAEN_MASK;
	pedmac1ch0regs->CSR &= ~EDMAC_EDMAEN_MASK;
	pedmac1ch1regs->CSR &= ~EDMAC_EDMAEN_MASK;

	if(crc)//CRC32
	{
		crc0_init(0xffffffff);
		crc1_init(0xffffffff);
		crc0_crconfig(CRC32|EDMAC_SEL|CRC_DECODE|CODE_WR_EN|EDMA_UPDATA|EDMA_LATCH);
		crc1_crconfig(CRC32|EDMAC_SEL|EDMA_UPDATA|CODE_SEND_EN);
	}

	if(type != EDMAC_PN10SHA_MASK)//AES/SM4
	{
		pedmac0ch0regs->CCR = LINK_SRC_SEL_2|LINK|EDMAC_TTYPE3_MASK|type;
		pedmac0ch0regs->RBAR = (UINT32)&g_edmaccryptbuf[0][0];
		pedmac0ch0regs->WBAR = (UINT32)&g_edmaccryptbuf[0][1];
		pedmac0ch0regs->MINISUMR = EDMAC_CRYPTBLOCK_LEN;
		pedmac0ch0regs->MAJSUMR = majorch0;

		pedmac0ch1regs->CCR = LINK_SRC_SEL_3|LINK|EDMAC_TTYPE3_MASK|type;
		pedmac0ch1regs->RBAR = (UINT32)&g_edmaccryptbuf[1][0];
		pedmac0ch1regs->WBAR = (UINT32)&g_edmaccryptbuf[1][1];
		pedmac0ch1regs->MINISUMR = EDMAC_CRYPTBLOCK_LEN;
		pedmac0ch1regs->MAJSUMR = majorch1;

		pedmac1ch0regs->CCR = LINK_SRC_SEL_0|LINK|EDMAC_TTYPE3_MASK|spipnmask|PRELOAD_6|EDMAC_CHVALID_MASK;
		pedmac1ch0regs->RBAR = (UINT32)&g_edmaccryptbuf[0][1];
		pedmac1ch0regs->WBAR = (UINT32)&g_edmaccryptbuf[0][0];
		pedmac1ch0regs->MINISUMR = EDMAC_CRYPTBLOCK_LEN;
		pedmac1ch0regs->MAJSUMR = majorch0;

		pedmac1ch1regs->CCR = LINK_SRC_SEL_1|LINK|EDMAC_TTYPE3_MASK|spipnmask|PRELOAD_6|EDMAC_CHVALID_MASK;
		pedmac1ch1regs->RBAR = (UINT32)&g_edmaccryptbuf[1][1];
		pedmac1ch1regs->WBAR = (UINT32)&g_edmaccryptbuf[1][0];
		pedmac1ch1regs->MINISUMR = EDMAC_CRYPTBLOCK_LEN;
		pedmac1ch1regs->MAJSUMR = majorch1;

		if (len > 0)
		{
			if(majorch1 >= majorch0)
			{
				pedmac1ch0regs->MAJSUMR = majorch0+1;
				pedmac1ch0regs->LASTMINSUMR =(LAST_MINOR_EN) |len;
				majorch0++;
			}
			else
			{
				pedmac1ch1regs->MAJSUMR = majorch1+1;
				pedmac1ch1regs->LASTMINSUMR =(LAST_MINOR_EN) |len;
				majorch1++;
			}
		}
	}
	else//SM3
	{
		pedmac0ch0regs->CCR = LINK_SRC_SEL_2|LINK|EDMAC_TTYPE2_MASK|type;
		pedmac0ch0regs->RBAR = (UINT32)&g_edmaccryptbuf[0][0];
		pedmac0ch0regs->WBAR = (UINT32)&g_edmaccryptbuf[0][1];
		pedmac0ch0regs->MINISUMR = EDMAC_CRYPTBLOCK_LEN;
		pedmac0ch0regs->MAJSUMR = majorch0;

		pedmac0ch1regs->CCR = LINK_SRC_SEL_3|LINK|EDMAC_TTYPE2_MASK|type;
		pedmac0ch1regs->RBAR = (UINT32)&g_edmaccryptbuf[1][0];
		pedmac0ch1regs->WBAR = (UINT32)&g_edmaccryptbuf[1][1];
		pedmac0ch1regs->MINISUMR = EDMAC_CRYPTBLOCK_LEN;
		pedmac0ch1regs->MAJSUMR = majorch1;

		pedmac1ch0regs->CCR = LINK_SRC_SEL_0|LINK|EDMAC_TTYPE3_MASK|spipnmask|PRELOAD_6|EDMAC_CHVALID_MASK;
		pedmac1ch0regs->RBAR = (UINT32)&g_edmaccryptbuf[0][1];
		pedmac1ch0regs->WBAR = (UINT32)&g_edmaccryptbuf[0][0];
		pedmac1ch0regs->MINISUMR = EDMAC_CRYPTBLOCK_LEN;
		pedmac1ch0regs->MAJSUMR = majorch0;

		pedmac1ch1regs->CCR = LINK_SRC_SEL_1|LINK|EDMAC_TTYPE3_MASK|spipnmask|PRELOAD_6|EDMAC_CHVALID_MASK;
		pedmac1ch1regs->RBAR = (UINT32)&g_edmaccryptbuf[1][1];
		pedmac1ch1regs->WBAR = (UINT32)&g_edmaccryptbuf[1][0];
		pedmac1ch1regs->MINISUMR = EDMAC_CRYPTBLOCK_LEN;
		pedmac1ch1regs->MAJSUMR = majorch1;

		if (len > 0)
		{
			if(majorch1 >= majorch0)
			{
				pedmac1ch0regs->MAJSUMR = majorch0+1;
				pedmac1ch0regs->LASTMINSUMR =(LAST_MINOR_EN) |len;

				pedmac0ch0regs->MAJSUMR = majorch0+1;
				pedmac0ch0regs->LASTMINSUMR = (LAST_MINOR_EN) |len;

				majorch0++;
			}
			else
			{
				pedmac1ch1regs->MAJSUMR = majorch1+1;
				pedmac1ch1regs->LASTMINSUMR =(LAST_MINOR_EN) |len;

				pedmac0ch1regs->MAJSUMR = majorch1+1;
				pedmac0ch1regs->LASTMINSUMR = (LAST_MINOR_EN) |len;

				majorch1++;
			}
		}
	}

	pedmac1ch0regs->CCR |= (PIPELINEd|SPI_WROPT|PRIOR_CHG);
	pedmac1ch0regs->CCR &= ~(PRIOR_CHG);
	pedmac1ch1regs->CCR |= (PIPELINEd|SPI_WROPT);

	if(crc)
	{
		//MINOR CRC
		pedmac1ch1regs->CCR |= CRC_CHEN|SEND_CRC_CHEN;/*WRITE_CRC_CHEN;*/
		pedmac1ch1regs->CCR &= ~(MAJOR_CAR_SEL);
		pedmac1ch0regs->CCR |= CRC_CHEN|SEND_CRC_CHEN;/*WRITE_CRC_CHEN;*/
		pedmac1ch0regs->CCR &= ~(MAJOR_CAR_SEL);
	}

	pedmac0ch0regs->CSR |= EDMAC_EDMAEN_MASK;
	pedmac0ch1regs->CSR |= EDMAC_EDMAEN_MASK;
	pedmac1ch0regs->CSR |= EDMAC_EDMAEN_MASK;
	pedmac1ch1regs->CSR |= EDMAC_EDMAEN_MASK;

	edmac_idle();
	if((majorch0 > 0) && (majorch1 >= majorch0))
	{
		while ((pedmac1ch1regs->CSR & EDMAC_MAJORDONE_MASK) == 0);
	}
	else
	{
		while ((pedmac1ch0regs->CSR & EDMAC_MAJORDONE_MASK) == 0);
	}
	edmac_busy();

	while ((pedmac1ch1regs->CSR & EDMAC_MAJORDONE_MASK) == 0);
	while ((pedmac1ch0regs->CSR & EDMAC_MAJORDONE_MASK) == 0);
	while ((pedmac0ch1regs->CSR & EDMAC_MAJORDONE_MASK) == 0);
	while ((pedmac0ch0regs->CSR & EDMAC_MAJORDONE_MASK) == 0);

	pedmac1ch0regs->CSR |= (EDMAC_MAJORDONE_MASK|EDMAC_MINORDONE_MASK);
	pedmac1ch1regs->CSR |= (EDMAC_MAJORDONE_MASK|EDMAC_MINORDONE_MASK);
	pedmac0ch0regs->CSR |= (EDMAC_MAJORDONE_MASK|EDMAC_MINORDONE_MASK);
	pedmac0ch1regs->CSR |= (EDMAC_MAJORDONE_MASK|EDMAC_MINORDONE_MASK);

	pedmac1ch0regs->LASTMINSUMR = 0;
	pedmac1ch1regs->LASTMINSUMR = 0;

	if(crc)
	{
		if( FALSE == crc0_get_lasterr() )
		{
			return FALSE;
		}
	}

	return TRUE;
}


//spi master

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_spimincrc
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edmac spi minor crc transfer program
//
// Input:
//		ucspiid
//		psendbuf
//		precvbuf
//		datalen
//		crc
//
// Output:
//		true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL edmac_spimincrc(UINT8 ucspiid, UINT8 *psendbuf, UINT8 *precvbuf, UINT32 datalen, UINT8 crc)
{
	/*EDMAC registers pointer*/
	EDMAC_REG* pedmac1ch0regs = 0;
	UINT32 spipnmask;
	UINT32 block,len;

	if ( ucspiid > SPI3 )
	{
		return	FALSE;
	}

	block = (datalen / EDMAC_CRYPTBLOCK_LEN)-1;
	len = datalen % EDMAC_CRYPTBLOCK_LEN;

	if( SPI1 == ucspiid )//SPI1
	{
		spipnmask = EDMAC_PN0SPI1_MASK;
	}
	else if( SPI2 == ucspiid )//SPI2
	{
		spipnmask = EDMAC_PN1SPI2_MASK;
	}
	else if( SPI3 == ucspiid )//SPI3
	{
		spipnmask = EDMAC_PN14SPI3_MASK;
	}

	pedmac1ch0regs = (EDMAC_REG *)(g_edmac_baseaddr[EDMAC1][0]);
	pedmac1ch0regs->CSR &= ~EDMAC_EDMAEN_MASK;

	if(crc)//CRC32
	{
		crc0_init(0xffffffff);
		crc1_init(0xffffffff);
		crc0_crconfig(CRC32|EDMAC_SEL|CRC_DECODE|EDMA_UPDATA|EDMA_LATCH);
		crc1_crconfig(CRC32|EDMAC_SEL|EDMA_UPDATA|CODE_SEND_EN);
	}

	pedmac1ch0regs->CCR = LINK_SRC_SEL_0|LINK|EDMAC_TTYPE3_MASK|spipnmask|PRELOAD_6|EDMAC_CHVALID_MASK;
	pedmac1ch0regs->RBAR = (UINT32)psendbuf;
	pedmac1ch0regs->WBAR = (UINT32)precvbuf;
	pedmac1ch0regs->MINISUMR = EDMAC_CRYPTBLOCK_LEN;
	//pedmac1ch0regs->RBARSTEP = RBAR_STEP_EN|EDMAC_CRYPTBLOCK_LEN;
	//pedmac1ch0regs->WBARSTEP = WBAR_STEP_EN|EDMAC_CRYPTBLOCK_LEN;
	pedmac1ch0regs->MAJSUMR = block;

	if (len > 0)
	{
		pedmac1ch0regs->MAJSUMR = block+1;
		pedmac1ch0regs->LASTMINSUMR =(LAST_MINOR_EN) |len;
	}

	if(crc)
	{
		//MINOR CRC
		pedmac1ch0regs->CCR |= CRC_CHEN|SEND_CRC_CHEN|WRITE_CRC_CHEN;
		pedmac1ch0regs->CCR &= ~(MAJOR_CAR_SEL);
	}

	pedmac1ch0regs->CSR |= EDMAC_EDMAEN_MASK;

	edmac_idle();
	while ((pedmac1ch0regs->CSR & EDMAC_MAJORDONE_MASK) == 0);
	edmac_busy();

	pedmac1ch0regs->CSR |= (EDMAC_MAJORDONE_MASK|EDMAC_MINORDONE_MASK);

	pedmac1ch0regs->LASTMINSUMR = 0;
	pedmac1ch0regs->RBARSTEP = 0;
	pedmac1ch0regs->WBARSTEP = 0;

	if(crc)
	{
		if( FALSE == crc0_get_lasterr() )
		{
			return FALSE;
		}
	}

	return TRUE;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_waitspicomd
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edmac spi wait comd program
//
// Input:
//		ucid
//		pspicmd
//
// Output:
//		true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL edmac_waitspicomd(UINT8 ucid, UINT8 *pspicmd)
{
	EDMAC_REG* pedmac1ch0regs = 0;
	UINT8 spicos_tmpbuf[16];
	UINT32 spipnmask=0;

	pedmac1ch0regs = (EDMAC_REG *)(g_edmac_baseaddr[EDMAC1][0]);

	if( ucid > SPI4 )
	{
		return FALSE;
	}

	crc0_init(0xffffffff);
	crc0_crconfig( CRC8|EDMAC_SEL|CRC_DECODE);

	pedmac1ch0regs->CSR &= ~EDMAC_EDMAEN_MASK;
	spi_enable(ucid, 0);
	spi_clrfifo(ucid);
	spi_enable(ucid, 1);

	if( SPI1 == ucid )//SPI1
	{
		spipnmask = EDMAC_PN0SPI1_MASK;
	}
	else if( SPI2 == ucid )//SPI2
	{
		spipnmask = EDMAC_PN1SPI2_MASK;
	}
	else if( SPI3 == ucid )//SPI3
	{
		spipnmask = EDMAC_PN14SPI3_MASK;
	}

	pedmac1ch0regs->CCR = EDMAC_TTYPE3_MASK|spipnmask|PRELOAD_6|EDMAC_CHVALID_MASK;
	pedmac1ch0regs->RBAR = (UINT32)spicos_tmpbuf;
	pedmac1ch0regs->WBAR = (UINT32)pspicmd;
	pedmac1ch0regs->MINISUMR = 15;
	pedmac1ch0regs->MAJSUMR = 0;
	pedmac1ch0regs->CCR |= (PIPELINEd|SPI_WROPT|PRIOR_CHG);
	pedmac1ch0regs->CCR &= ~(PRIOR_1);
	pedmac1ch0regs->CCR |= MAJOR_CAR_SEL|CRC_CHEN|WRITE_CRC_CHEN;

	edmac_busy();
	pedmac1ch0regs->CSR |= EDMAC_EDMAEN_MASK;
	edmac_idle();
	while ((pedmac1ch0regs->CSR & EDMAC_MAJORDONE_MASK) == 0);
	edmac_busy();

	pedmac1ch0regs->CSR |= EDMAC_MAJORDONE_MASK|EDMAC_MINORDONE_MASK;
	pedmac1ch0regs->CSR = 0;
	pedmac1ch0regs->CCR = 0;

	return TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_spislavecrc
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edmac spi slave crc trans program
//
// Input:
//		ucid
//		psend
//		precv
//		len
//		crcen
//
// Output:
//		true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL edmac_spislavecrc(UINT8 ucid, UINT8 *psend, UINT8 *precv, UINT32 len, UINT8 crcen)
{
	EDMAC_REG* pedmac1ch0regs = 0;
	UINT32 spipnmask=0;

	if( ucid > SPI4 )
	{
		return FALSE;
	}

	pedmac1ch0regs = (EDMAC_REG *)(g_edmac_baseaddr[EDMAC1][0]);

	pedmac1ch0regs->CSR &= ~EDMAC_EDMAEN_MASK;
	spi_enable(ucid, 0);
	spi_clrfifo(ucid);
	spi_enable(ucid, 1);

	if( SPI1 == ucid )//SPI1
	{
		spipnmask = EDMAC_PN0SPI1_MASK;
	}
	else if( SPI2 == ucid )//SPI2
	{
		spipnmask = EDMAC_PN1SPI2_MASK;
	}
	else if( SPI3 == ucid )//SPI3
	{
		spipnmask = EDMAC_PN14SPI3_MASK;
	}

	if( crcen )
	{
		crc0_init(0xffffffff);
		crc1_init(0xffffffff);
		crc0_crconfig(CRC32|EDMAC_SEL|CRC_DECODE);
		crc1_crconfig(CRC32|EDMAC_SEL|CODE_SEND_EN);
	}

	if( len > 7 )
	{
		pedmac1ch0regs->CCR = EDMAC_TTYPE3_MASK|spipnmask|PRELOAD_6|EDMAC_CHVALID_MASK;
		pedmac1ch0regs->RBAR = (UINT32)psend;
		pedmac1ch0regs->WBAR = (UINT32)precv;
		pedmac1ch0regs->MINISUMR = len;
		pedmac1ch0regs->MAJSUMR = 0;
	}
	else
	{
		pedmac1ch0regs->CCR = EDMAC_TTYPE3_MASK|spipnmask|((len-1)<<2)|EDMAC_CHVALID_MASK;
		pedmac1ch0regs->RBAR = (UINT32)psend;
		pedmac1ch0regs->WBAR = (UINT32)precv;
		pedmac1ch0regs->MINISUMR = len;
		pedmac1ch0regs->MAJSUMR = 0;
	}
	pedmac1ch0regs->CCR |= (PIPELINEd |SPI_WROPT| PRIOR_CHG);
	pedmac1ch0regs->CCR &= ~(PRIOR_1);

	if( crcen )
	{
		pedmac1ch0regs->CCR |= MAJOR_CAR_SEL|CRC_CHEN|SEND_CRC_CHEN/*|WRITE_CRC_CHEN*/;
	}

	pedmac1ch0regs->CSR |= EDMAC_EDMAEN_MASK;

	edmac_idle();
	while ((pedmac1ch0regs->CSR & EDMAC_MAJORDONE_MASK) == 0);
	edmac_busy();

	pedmac1ch0regs->CSR |= EDMAC_MAJORDONE_MASK|EDMAC_MINORDONE_MASK;
	pedmac1ch0regs->CSR = 0;
	pedmac1ch0regs->CCR = 0;

	if( crcen )
	{
		if( FALSE == crc0_get_status() )
		{
			return FALSE;
		}
	}

	return TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_spimastercrc
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edmac spi master crc trans program
//
// Input:
//		ucch
//		ucspiid
//		psend
//		precv
//		ulbytelen
//		crctype
//
// Output:
//		true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL edmac_spimastercrc(UINT8 ucch, UINT8 ucspiid, UINT8* psend, UINT8* precv, UINT32 ulbytelen, UINT8 crctype)
{
	/*EDMAC registers pointer*/
	EDMAC_REG* pregspointer = 0;

	/*invalid parameters*/
	if ( (ucch > EDMACCH1)||(ucspiid >SPI3) )
	{
		return	FALSE;
	}

	pregspointer = (EDMAC_REG *)(g_edmac_baseaddr[EDMAC1][ucch]);

	pregspointer->CCR = 0;

	if( crctype != 0 )
	{
		crc0_init(0xffffffff);
		crc1_init(0xffffffff);
	}

	if( crctype == 8 )
	{
		crc0_crconfig(CRC8|EDMAC_SEL|CRC_DECODE);
		crc1_crconfig(CRC8|EDMAC_SEL|CODE_SEND_EN);
	}
	else if( crctype == 16)
	{
		crc0_crconfig(CRC16|EDMAC_SEL|CRC_DECODE);
		crc1_crconfig(CRC16|EDMAC_SEL|CODE_SEND_EN);
	}
	else if( crctype == 32 )
	{
		crc0_crconfig(CRC32|EDMAC_SEL|CRC_DECODE);
		crc1_crconfig(CRC32|EDMAC_SEL|CODE_SEND_EN);
	}

	if( SPI1 == ucspiid )//SPI1
	{
		pregspointer->CCR = EDMAC_TTYPE3_MASK|EDMAC_PN0SPI1_MASK|EDMAC_CHVALID_MASK;
	}
	else if( SPI2 == ucspiid )//SPI2
	{
		pregspointer->CCR = EDMAC_TTYPE3_MASK|EDMAC_PN1SPI2_MASK|EDMAC_CHVALID_MASK;
	}
	else if( SPI3 == ucspiid )//SPI3
	{
		pregspointer->CCR = EDMAC_TTYPE3_MASK|EDMAC_PN14SPI3_MASK|EDMAC_CHVALID_MASK;
	}

	pregspointer->RBAR = (UINT32)(psend);
	pregspointer->WBAR = (UINT32)(precv);
	pregspointer->MINISUMR = ulbytelen;
	pregspointer->MAJSUMR = 0;


	if( crctype != 0 )
	{
		pregspointer->CCR |= MAJOR_CAR_SEL|CRC_CHEN|SEND_CRC_CHEN;/*WRITE_CRC_CHEN;*/
	}

	pregspointer->CSR |= EDMAC_EDMAEN_MASK;
	while(((pregspointer->CSR)&(EDMAC_MINORDONE_MASK))==0); // channel done
	pregspointer->CSR |= (EDMAC_MINORDONE_MASK|EDMAC_MAJORDONE_MASK); // clear done

	pregspointer->CSR &= ~EDMAC_EDMAEN_MASK;

	pregspointer->CSR = 0;
	pregspointer->CCR = 0;

	if( crctype == 32 )
	{
		if( FALSE == crc0_get_status() )
		{
			return FALSE;
		}
	}

	return	TRUE;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 edmac_crypttrans
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    edmac crypt trans program
//
// Input:
//		ucch
//		crypttype
//		psend
//		precv
//		ulbytelen
//
// Output:
//		true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL edmac_crypttrans(UINT8 ucch, UINT32 crypttype, UINT8* psend, UINT8* precv, UINT32 ulbytelen)
{
	/*EDMAC registers pointer*/
	EDMAC_REG* pregspointer = 0;

	/*invalid parameters*/
	if ( ucch > EDMACCH1 )
	{
		return	FALSE;
	}

	pregspointer = (EDMAC_REG *)(g_edmac_baseaddr[EDMAC0][ucch]);

	pregspointer->CCR = 0;

	if(EDMAC_PN10SHA_MASK == crypttype)
	{
		pregspointer->CCR = EDMAC_TTYPE2_MASK|crypttype|EDMAC_CHVALID_MASK;
	}
	else
	{
		pregspointer->CCR = EDMAC_TTYPE3_MASK|crypttype|EDMAC_CHVALID_MASK;
	}

	pregspointer->RBAR = (UINT32)(psend);
	pregspointer->WBAR = (UINT32)(precv);
	pregspointer->MINISUMR = ulbytelen;
	pregspointer->MAJSUMR = 0;

	pregspointer->CSR |= EDMAC_EDMAEN_MASK;
	while(((pregspointer->CSR)&(EDMAC_MINORDONE_MASK))==0); // channel done
	pregspointer->CSR |= (EDMAC_MINORDONE_MASK|EDMAC_MAJORDONE_MASK); // clear done

	pregspointer->CSR &= ~EDMAC_EDMAEN_MASK;
	pregspointer->CSR = 0;
	pregspointer->CCR = 0;
	return	TRUE;
}




