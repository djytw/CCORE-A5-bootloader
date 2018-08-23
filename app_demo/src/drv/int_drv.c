// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : int_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "int_reg.h"
#include "int_drv.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 interrupt_setup
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    ISR installation.
//
// Input:
//    int_num:   ISR num
//    priority:  0~3, 0 > 1 > 2 > 3 in priority.
//    int_fun:   isr entrance
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void interrupt_setup(UINT8 int_num, UINT8 priority, void (* int_fun ))
{
	volatile UINT32 ier_tmp,plsr_tmp,plsr_reg;

	ier_tmp = IO_READ32(EIC_IER);

	IO_WRITE32(EIC_IER,(ier_tmp & ~(1 << (int_num - 32))));

	plsr_reg = (PLSR + int_num - 32) &~ 0x03;
	plsr_tmp = IO_READ32(plsr_reg);
	((UINT8 *)&plsr_tmp)[(int_num & 0x03)] = priority<<6;
	IO_WRITE32(plsr_reg, plsr_tmp);

	//VecTable[int_num] = int_fun;

	IO_WRITE32(EIC_IER,(ier_tmp | (1 << (int_num - 32))));
}
/*
void interrupt_setup(UINT8 int_num, UINT8 priority, void (* int_fun ))
{
	volatile UINT32 ier_tmp;

	ier_tmp = IO_READ32(EIC_IER);

	IO_WRITE8((PLSR + int_num - 32),(priority<<6));

	IO_WRITE32(EIC_IER,(ier_tmp & ~(1 << (int_num - 32))));

	//VecTable[int_num] = int_fun;

	IO_WRITE32(EIC_IER,(ier_tmp | (1 << (int_num - 32))));
}*/



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 read_vec
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Read vector number.
//
// Input:
//    None.
//
// Output:
//    Vector number.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 read_vec(void)
{
	UINT8 vec_num;

	vec_num = (IO_READ32(EIC_ICSR) & 0x007f) - 32;

	return vec_num;
}
