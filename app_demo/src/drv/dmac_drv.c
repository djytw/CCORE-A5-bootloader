// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : dmac_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



//------------------------------------------------------------------
//                        Headers
//------------------------------------------------------------------
#include "memmap.h"
#include "dmac_reg.h"
#include "dmac_drv.h"
#include "spi_reg.h"
#include "spi_drv.h"
#include "int_drv.h"
#include "type.h"
//------------------------------------------------------------------

/*DMAC global interrupt status*/
static VUINT8 g_dmaisr_flag = 0;//DMA isr done flag
/*DMAC global error status*/
static VUINT8 g_dmasr_errflag = 0;//DMA isr error flag

/*DMAC channel base address*/
UINT32 const g_dmacch_baseaddr[DMAC_CHNUM] = {(DMAC_BASE+0x100),(DMAC_BASE+0x120),\
												(DMAC_BASE+0x140),(DMAC_BASE+0x160),\
												(DMAC_BASE+0x180),(DMAC_BASE+0x1a0),\
												(DMAC_BASE+0x1c0),(DMAC_BASE+0x1e0),};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 dmac_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    damc interrupt service program.
//    clear done or error states.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void dmac_isr(void)
{
	/*DMAC registers pointer*/
	DMAC_CONTROL_REG* pctrregspointer = 0;

	pctrregspointer = (DMAC_CONTROL_REG*)(DMAC_BASE);

	if( (pctrregspointer->DMACINTCS) & (0xff) )//dma done
	{
		g_dmaisr_flag = (pctrregspointer->DMACINTCS) & (0xff);
		pctrregspointer->DMACINTCC = g_dmaisr_flag;
		//PRINTF("DMA 0x%x ISR\n", dma_isr_flag);
	}

	if( (pctrregspointer->DMACINTES) & (0xff) )//dma error
	{
		g_dmasr_errflag = (pctrregspointer->DMACINTES) & (0xff);
		pctrregspointer->DMACINTEC = g_dmasr_errflag;
		//PRINTF("=================DMA 0x%x ERROR ISR=============\r\n\r\n", dma_isr_flag);
	}

}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 damc_inten
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    dmac interrupt enable or disable.
//
// Input:
//    ben: 0, disable; 1, enable.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void dmac_inten(BOOL ben)
{
	EIC_REG *peicregspointer;

	peicregspointer = (EIC_REG *)EIC_BASE;

	if(ben)
	{
		peicregspointer->IER |= IER_DMACINT_MASK;
	}
	else
	{
		peicregspointer->IER &= ~IER_DMACINT_MASK;
	}

}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 damc_transword
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    dmac sram transfer word program.
//
// Input:
//    ucch: which channel.
//    psrc: source address.
//    pdst: destination address.
//    ulwordlen: length in word
//    binten: enable interrupt or not.
//
// Output:
//
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL dmac_transword(UINT8 ucch, UINT8* psrc, UINT8* pdst, UINT32 ulwordlen, BOOL binten)
{
	/*DMAC registers pointer*/
	DMAC_CONTROL_REG* pctrregspointer = 0;
	DMAC_CHANNEL_REG* pchregspointer;
	UINT32 damctr;
	UINT8 errflag;

	/*invalid parameters*/
	if ( ucch >= DMAC_CHNUM )
	{
		return	FALSE;
	}

	if( ulwordlen > (2047)||( ulwordlen%4 != 0 ) )//max word trans datalen == (2^11 - 1)*4
	{
		return	FALSE;
	}
	else
	{
		damctr = DMA_IE|DI|SI|D_M2|DWIDTH_W|SWIDTH_W|DBSIZE_4|SBSIZE_4|(ulwordlen);
	}

	pctrregspointer = (DMAC_CONTROL_REG*)(DMAC_BASE);
	pchregspointer = (DMAC_CHANNEL_REG*)g_dmacch_baseaddr[ucch];

	g_dmaisr_flag = 0;
	g_dmasr_errflag = 0;

	pctrregspointer->DMACCONFIG |= DMACEN;
	pchregspointer->DMACC0SADDR = (UINT32)psrc;
	pchregspointer->DMACC0DADDR = (UINT32)pdst;
	pchregspointer->DMACC0CTRL = damctr;

	if ( binten )
	{
		g_dmaisr_flag = 0;
		g_dmasr_errflag = 0;
		pchregspointer->DMACC0CONFIG = ITC|INTErr|CHEN;
		while(1)
		{
		   if( g_dmaisr_flag ==  (0x01<<ucch) )
		   {
			   errflag = 0;
			   g_dmaisr_flag = 0;
			   break;
		   }
		   else if( (g_dmasr_errflag&(0x01<<ucch)) != 0 )
		   {
			   errflag = 1;
			   break;
		   }

		}
	    if( 1 == errflag )
	    {
		   g_dmasr_errflag = 0;
		   return FALSE;
	    }
	}
	else
	{
		pchregspointer->DMACC0CONFIG = CHEN;
		while(1)
		{
			if( (pctrregspointer->DMACRINTCS) == (0x01<<(ucch)) )//trans done
			{
				errflag = 0;
				break;
			}
			if( ((pctrregspointer->DMACRINTES)&(0x01<<(ucch))) != 0)//trans err
			{
				errflag = 1;
				break;
			}
		}
		if( 1 == errflag )//trans err
		{
			pctrregspointer->DMACRINTES = (0x01<<ucch); //clear error flag
			return	FALSE;
		}
		else//trans done
		{
			pctrregspointer->DMACINTCC = (0x01<<ucch);
		}
	}

   pctrregspointer->DMACCONFIG &= ~DMACEN;

   return	TRUE;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 damc_transhalfword
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    dmac sram transfer halfword program.
//
// Input:
//    ucch: wchich channel.
//    pscr: source address.
//    pdst: destination address.
//    ulhwordlen: length in half-word.
//    binten: enable interrupt or not.
//
// Output:
//
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL dmac_transhalfword(UINT8 ucch, UINT8* psrc, UINT8* pdst, UINT32 ulhwordlen, BOOL binten)
{
	/*DMAC registers pointer*/
	DMAC_CONTROL_REG* pctrregspointer = 0;
	DMAC_CHANNEL_REG* pchregspointer;
	UINT32 damctr;
	UINT8 errflag;

	/*invalid parameters*/
	if ( ucch >= DMAC_CHNUM )
	{
		return	FALSE;
	}

	if( ( ulhwordlen > (2047) )||( ulhwordlen%2 != 0 ) )//max word trans datalen == (2^11 - 1)*2
	{
		return	FALSE;
	}
	else
	{
		damctr = DMA_IE|DI|SI|D_M2|DWIDTH_HW|SWIDTH_HW|(ulhwordlen);
	}

	pctrregspointer = (DMAC_CONTROL_REG*)(DMAC_BASE);
	pchregspointer = (DMAC_CHANNEL_REG*)g_dmacch_baseaddr[ucch];

	g_dmaisr_flag = 0;
	g_dmasr_errflag = 0;

	pctrregspointer->DMACCONFIG |= DMACEN;
	pchregspointer->DMACC0SADDR = (UINT32)psrc;
	pchregspointer->DMACC0DADDR = (UINT32)pdst;
	pchregspointer->DMACC0CTRL = damctr;

	if ( binten )
	{
		g_dmaisr_flag = 0;
		g_dmasr_errflag = 0;
		pchregspointer->DMACC0CONFIG = ITC|INTErr|CHEN;
		while(1)
		{
		   if( g_dmaisr_flag ==  (0x01<<ucch) )
		   {
			   errflag = 0;
			   g_dmaisr_flag = 0;
			   break;
		   }
		   else if( (g_dmasr_errflag&(0x01<<ucch)) != 0 )
		   {
			   errflag = 1;
			   break;
		   }

		}
	    if( 1 == errflag )
	    {
		   g_dmasr_errflag = 0;
		   return FALSE;
	    }
	}
	else
	{
		pchregspointer->DMACC0CONFIG = CHEN;
		while(1)
		{
			if( (pctrregspointer->DMACRINTCS) == (0x01<<(ucch)) )//trans done
			{
				errflag = 0;
				break;
			}
			if( ((pctrregspointer->DMACRINTES)&(0x01<<(ucch))) != 0)//trans err
			{
				errflag = 1;
				break;
			}
		}
		if( 1 == errflag )//trans err
		{
			pctrregspointer->DMACRINTES = (0x01<<ucch); //clear error flag
			return	FALSE;
		}
		else//trans done
		{
			pctrregspointer->DMACINTCC = (0x01<<ucch);
		}
	}

   pctrregspointer->DMACCONFIG &= ~DMACEN;

   return	TRUE;
}





// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 damc_transbyte
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    dmac sram transfer byte program.
//
// Input:
//    ucch: which channel.
//    psrc: source address.
//    pdst: destination address.
//    ulbytelen: length in byte
//    binten: enable interrupt or not.
//
// Output:
//
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL dmac_transbyte(UINT8 ucch, UINT8* psrc, UINT8* pdst, UINT32 ulbytelen, BOOL binten)
{
	/*DMAC registers pointer*/
	DMAC_CONTROL_REG* pctrregspointer = 0;
	DMAC_CHANNEL_REG* pchregspointer;
	UINT32 damctr;
	UINT8 errflag;

	/*invalid parameters*/
	if ( ucch >= DMAC_CHNUM )
	{
		return	FALSE;
	}

	if( ( ulbytelen > (2047) ) )//max word trans datalen == (2^11 - 1)
	{
		return	FALSE;
	}
	else
	{
		damctr = DMA_IE|DI|SI|D_M2|(ulbytelen);
	}

	pctrregspointer = (DMAC_CONTROL_REG*)(DMAC_BASE);
	pchregspointer = (DMAC_CHANNEL_REG*)g_dmacch_baseaddr[ucch];

	g_dmaisr_flag = 0;
	g_dmasr_errflag = 0;

	pctrregspointer->DMACCONFIG |= DMACEN;
	pchregspointer->DMACC0SADDR = (UINT32)psrc;
	pchregspointer->DMACC0DADDR = (UINT32)pdst;
	pchregspointer->DMACC0CTRL = damctr;

	if ( binten )
	{
		g_dmaisr_flag = 0;
		g_dmasr_errflag = 0;
		pchregspointer->DMACC0CONFIG = ITC|INTErr|CHEN;
		while(1)
		{
		   if( g_dmaisr_flag ==  (0x01<<ucch) )
		   {
			   errflag = 0;
			   g_dmaisr_flag = 0;
			   break;
		   }
		   else if( (g_dmasr_errflag&(0x01<<ucch)) != 0 )
		   {
			   errflag = 1;
			   break;
		   }

		}
	    if( 1 == errflag )
	    {
		   g_dmasr_errflag = 0;
		   return FALSE;
	    }
	}
	else
	{
		pchregspointer->DMACC0CONFIG = CHEN;
		while(1)
		{
			if( (pctrregspointer->DMACRINTCS) == (0x01<<(ucch)) )//trans done
			{
				errflag = 0;
				break;
			}
			if( ((pctrregspointer->DMACRINTES)&(0x01<<(ucch))) != 0)//trans err
			{
				errflag = 1;
				break;
			}
		}
		if( 1 == errflag )//trans err
		{
			pctrregspointer->DMACRINTES = (0x01<<ucch); //clear error flag
			return	FALSE;
		}
		else//trans done
		{
			pctrregspointer->DMACINTCC = (0x01<<ucch);
		}
	}

   pctrregspointer->DMACCONFIG &= ~DMACEN;

   return	TRUE;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 damc_spitrans
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    DMAC SPI transfer program.
//
// Input:
//    ucspiid: spi id number.
//    psend: spi send buffer
//    precv: spi receive buffer
//    uldatalen: spi transfer length
//    binten: interrupt enable flag.
//
// Output:
//
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL dmac_spitrans(UINT8 ucspiid, UINT8* psend, UINT8* precv, UINT32 uldatalen, BOOL binten)
{
	/*DMAC registers pointer*/
	DMAC_CONTROL_REG* pctrregspointer = 0;
	DMAC_CHANNEL_REG* pchregspointer[2];
	/*SPI registers pointer*/
	SPI_REG* pspiregspointer = 0;
	UINT8 errflag = 0;

	/*invalid parameters*/
	if ( ucspiid >SPI4 )
	{
		return	FALSE;
	}

	pctrregspointer = (DMAC_CONTROL_REG*)(DMAC_BASE);
	pspiregspointer = (SPI_REG *)(g_spi_baseaddr[ucspiid]);

	if(ucspiid == SPI4)
	{
		pchregspointer[0] = (DMAC_CHANNEL_REG*)g_dmacch_baseaddr[6];
		pchregspointer[1] = (DMAC_CHANNEL_REG*)g_dmacch_baseaddr[7];

		pctrregspointer->DMACCONFIG |= DMACEN;
		//TX
		pchregspointer[0]->DMACC0SADDR = (UINT32)psend;
		pchregspointer[0]->DMACC0DADDR = (UINT32)(&(pspiregspointer->DRHL.DR_L));
		pchregspointer[0]->DMACC0CTRL = DMA_IE|SI|(uldatalen);
		//RX
		pchregspointer[1]->DMACC0SADDR = (UINT32)(&(pspiregspointer->DRHL.DR_L));
		pchregspointer[1]->DMACC0DADDR = (UINT32)precv;
		pchregspointer[1]->DMACC0CTRL = DMA_IE|DI|(uldatalen);

		//wait for dmac done
		if( binten )//interrupt
		{
			g_dmaisr_flag = 0;
			g_dmasr_errflag = 0;
			pchregspointer[0]->DMACC0CONFIG = ITC|M2P_DMA|CHEN|((6)<<6);
			pchregspointer[1]->DMACC0CONFIG = ITC|P2M_DMA|CHEN|((7)<<1);
			while(1)
			{
				if( g_dmaisr_flag == ((0x01<<(7))|(0x01<<(6))) )//dmac trans done
				{
					g_dmaisr_flag = 0;
					errflag = 0;
					break;
				}
				else if( ((g_dmasr_errflag)&(((0x01<<(7))|(0x01<<(6))))) != 0 )//dmac trans err
				{
					errflag = 1;
					break;
				}
			}
			if( 1 == errflag )//err
			{
				g_dmasr_errflag = 0;
				return	FALSE;
			}
		}
		else
		{
			pchregspointer[0]->DMACC0CONFIG = M2P_DMA|CHEN|((6)<<6);
			pchregspointer[1]->DMACC0CONFIG = P2M_DMA|CHEN|((7)<<1);
			while(1)
			{
				if( (pctrregspointer->DMACRINTCS) == ((0x01<<(6))|(0x01<<(7))) )//trans done
				{
					errflag = 0;
					break;
				}
				if( ((pctrregspointer->DMACRINTES)&((0x01<<(6))|(0x01<<(7)))) != 0)//trans err
				{
					errflag = 1;
					break;
				}
			}
			if( 1 == errflag )//trans err
			{
				pctrregspointer->DMACRINTES = 0xff; //clear error flag
				return	FALSE;
			}
			else//trans done
			{
				pctrregspointer->DMACINTCC = 0xff;
			}
		}
	}
	else
	{
		pchregspointer[0] = (DMAC_CHANNEL_REG*)g_dmacch_baseaddr[0+ucspiid];
		pchregspointer[1] = (DMAC_CHANNEL_REG*)g_dmacch_baseaddr[3+ucspiid];

		pctrregspointer->DMACCONFIG |= DMACEN;
		//TX
		pchregspointer[0]->DMACC0SADDR = (UINT32)psend;
		pchregspointer[0]->DMACC0DADDR = (UINT32)(&(pspiregspointer->DRHL.DR_L));
		pchregspointer[0]->DMACC0CTRL = DMA_IE|SI|(uldatalen);
		//RX
		pchregspointer[1]->DMACC0SADDR = (UINT32)(&(pspiregspointer->DRHL.DR_L));
		pchregspointer[1]->DMACC0DADDR = (UINT32)precv;
		pchregspointer[1]->DMACC0CTRL = DMA_IE|DI|(uldatalen);

		//wait for dmac done
		if( binten )//interrupt
		{
			g_dmaisr_flag = 0;
			g_dmasr_errflag = 0;
			pchregspointer[0]->DMACC0CONFIG = ITC| M2P_DMA|CHEN|((0+ucspiid)<<6);
			pchregspointer[1]->DMACC0CONFIG = ITC|P2M_DMA|CHEN|((3+ucspiid)<<1);
			while(1)
			{
				if( g_dmaisr_flag == ((0x01<<(3+ucspiid))|(0x01<<(ucspiid))) )//dmac trans done
				{
					g_dmaisr_flag = 0;
					errflag = 0;
					break;
				}
				else if( ((g_dmasr_errflag)&((0x01<<(3+ucspiid))|(0x01<<(ucspiid)))) != 0 )//dmac trans err
				{
					errflag = 1;
					break;
				}
			}
			if( 1 == errflag )//err
			{
				g_dmasr_errflag = 0;
				return	FALSE;
			}
		}
		else
		{
			pchregspointer[0]->DMACC0CONFIG = M2P_DMA|CHEN|((0+ucspiid)<<6);
			pchregspointer[1]->DMACC0CONFIG = P2M_DMA|CHEN|((3+ucspiid)<<1);
			while(1)
			{
				if( (pctrregspointer->DMACRINTCS) == ((0x01<<(3+ucspiid))|(0x01<<(ucspiid))) )//trans done
				{
					errflag = 0;
					break;
				}
				if( ((pctrregspointer->DMACRINTES)&((0x01<<(3+ucspiid))|(0x01<<(ucspiid)))) != 0)//trans err
				{
					errflag = 1;
					break;
				}
			}
			if( 1 == errflag )//trans err
			{
				pctrregspointer->DMACRINTES = 0xff; //clear error flag
				return	FALSE;
			}
			else//trans done
			{
				pctrregspointer->DMACINTCC = 0xff;
			}
		}
	}

	pctrregspointer->DMACCONFIG &= ~DMACEN;//disable dmac
	return	TRUE;
}

