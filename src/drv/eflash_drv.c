// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eflash_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#include "type.h"
#include "eflash_drv.h"
#include "eflash_reg.h"


void eflash_drv_init(eflash_ops_func_t *eflash_ops)
{
	eflash_ops->set_clkd = *((void (*)(UINT32 f_eflash_khz))((UINT32 *)(0x00000202)));

	eflash_ops->eflash_program = (*(UINT8 (*)(UINT32, UINT32, UINT8))(((UINT32 *)( 0x00008000))));
	eflash_ops->eflash_page_erase = (*(UINT8 (*)(UINT32, UINT8)) (((UINT32 *)( 0x000081c0))));
	eflash_ops->eflash_mass_erase = (*(void (*)(UINT32, UINT8)) (((UINT32 *)( 0x000082c4))));

	eflash_ops->eflash_line_program = (*(UINT8 (*)(UINT32, UINT32, UINT32 *, UINT8))(((UINT32 *)( 0x000080b0))));
	eflash_ops->eflash_bulk_program = (*(UINT8 (*)(UINT32, UINT32, UINT32 *, UINT8))(((UINT32 *)( 0x00008398))));
}

void eflash_drv_clr_smw_err_flag()
{
	EFSTAT |= 0x02020002;
}

void eflash_drv_set_verify_cnt(UINT32 cnt)
{
	SMWOP2 &= ~0x01F00000;
	SMWOP2 |= ((cnt & 0x1F) << 20);
}

void eflash_drv_set_read_wait_cycle(UINT32 cycles)
{
	EFCR &= ~0x0000000F;
	EFCR |= cycles & 0xF;
}

UINT32 eflash_drv_get_main_access_permission()
{
	return EFAPR;
}

void eflash_drv_set_main_access_permission(UINT8 access_permission)
{
	EFAPR = 0xcdef9700 | (access_permission & 0x7F);
}


static UINT8 eflash_get_main_access_permission()
{
	return (eflash_drv_get_main_access_permission() & 0xFF);
}

/* eflash enable main block write permission. */
void eflash_enable_main_write_access()
{
	UINT8 main_access;

	main_access = eflash_get_main_access_permission();
	main_access |= 0x2A;
	eflash_drv_set_main_access_permission(main_access);
}

/* eflash disable main block write permission. */
void eflash_disable_main_write_access()
{
	UINT8 main_access;

	main_access = eflash_get_main_access_permission();
	main_access &= (~0x2A);
	eflash_drv_set_main_access_permission(main_access);
}


