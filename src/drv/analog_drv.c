// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : analog_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "reset_reg.h"
#include "vd_reg.h"
#include "fd_reg.h"
//#include "ld_reg.h"
#include "td_reg.h"
//#include "pgd_reg.h"
#include "vector_table.h"

#include "eport_demo.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 analog_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    analog module interrupt handle.
//
// Input:
//    	None.
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void analog_isr()
{
	if((RST_RCR & HVDF) == HVDF)
	{
		RST_RCR &= ~HVDE;
		MSG("The interrupt of HVD happens.\n");
	}

	if((RST_RCR & LVDF) == LVDF)
	{
		RST_RCR &= ~LVDE;
		MSG("The interrupt of LVD happens.\n");
	}

	if((RST_RCR & HFDF) == HFDF)
	{
		RST_RCR &= ~HFDE;
		MSG("The interrupt of HFD happens.\n");
	}

	if((RST_RCR & LFDF) == LFDF)
	{
		RST_RCR &= ~LFDE;
		MSG("The interrupt of LFD happens.\n");

	}

//	if(((LD_SR & LDOUT_MASK) == LDOUT_MASK) || ((LD_SR & LDDET_MASK) == LDDET_MASK))
//	{
//		MSG("The interrupt of LD happens.\n");
//	}

	if((TD_CR_1 & (TD_HT_ST_MASK | TD_HT_ST_LAT_MASK)) == (TD_HT_ST_MASK | TD_HT_ST_LAT_MASK))
	{
		TD_CR_1 &= ~TD_HT_INT_MASK;
		TD_CR_1 |= TD_LAT_CLR_MASK;
		MSG("The interrupt of TD_SENSOR_1 high temperature happens.\n");
	}

	if((TD_CR_1 & (TD_LT_ST_MASK | TD_LT_ST_LAT_MASK)) == (TD_LT_ST_MASK | TD_LT_ST_LAT_MASK))
	{
		TD_CR_1 &= ~TD_LT_INT_MASK;
		TD_CR_1 |= TD_LAT_CLR_MASK;
		MSG("The interrupt of TD_SENSOR_1 low temperature happens.\n");
	}

	if((TD_CR_2 & (TD_HT_ST_MASK | TD_HT_ST_LAT_MASK)) == (TD_HT_ST_MASK | TD_HT_ST_LAT_MASK))
	{
		TD_CR_2 &= ~TD_HT_INT_MASK;
		TD_CR_2 |= TD_LAT_CLR_MASK;
		MSG("The interrupt of TD_SENSOR_2 high temperature happens.\n");
	}

	if((TD_CR_2 & (TD_LT_ST_MASK | TD_LT_ST_LAT_MASK)) == (TD_LT_ST_MASK | TD_LT_ST_LAT_MASK))
	{
		TD_CR_2 &= ~TD_LT_INT_MASK;
		TD_CR_2 |= TD_LAT_CLR_MASK;
		MSG("The interrupt of TD_SENSOR_2 low temperature happens.\n");
	}

//	if((PGD_SR & PGDOUT_MASK) == PGDOUT_MASK)
//	{
//		MSG("The interrupt of PGDOUT happens.\n");
//	}
//
//	if((PGD_SR & PGDDET_MASK) == PGDDET_MASK)
//	{
//		MSG("The interrupt of PGDDET happens.\n");
//	}
//
}
