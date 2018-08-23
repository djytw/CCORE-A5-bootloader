// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eflash_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __EFLASH_DRV_H__
#define __EFLASH_DRV_H__
#include "type.h"
typedef struct
{
	/* set eflash clock divider, configure the eflash timings. */
	void (*set_clkd)(UINT32 f_eflash_khz);

	/* eflash word program interface. */
	UINT8 (*eflash_program)(UINT32 addr, UINT32 data, UINT8 intr_dis);
	/* eflash page erase interface. */
	UINT8 (*eflash_page_erase)(UINT32 addr, UINT8 intr_dis);
	/* eflash mass erase interface. */
	void (*eflash_mass_erase)(UINT32 addr, UINT8 intr_dis);

	/* eflash line program interface. */
	UINT8 (*eflash_line_program)(UINT32 addr, UINT32 num_words, UINT32 *data_buf, UINT8 intr_dis);
	/* eflash bulk program interface. */
	UINT8 (*eflash_bulk_program)(UINT32 addr, UINT32 num_words, UINT32 *data_buf, UINT8 intr_dis);

}eflash_ops_func_t;

extern void eflash_drv_init(eflash_ops_func_t *eflash_ops);

extern void eflash_drv_clr_smw_err_flag();
extern void eflash_drv_set_verify_cnt(UINT32 cnt);
extern void eflash_drv_set_read_wait_cycle(UINT32 cycles);

UINT32 eflash_drv_get_main_access_permission();
extern void eflash_drv_set_main_access_permission(UINT8 access_permission);

extern void eflash_disable_bootloader(void);
extern void eflash_recovery_to_rom(void);
#endif /* __EFLASH_DRV_H__ */
