// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : lowpower_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef LOWPOWER_DRV_H_
#define LOWPOWER_DRV_H_

extern void pad_wkp_isr(void);
extern void lp_drv_POFF1_cfg(void);
extern void lp_drv_POFF2_cfg(UINT8 mode);
extern void lp_drv_enable_wkppad(UINT8 pad_num, BOOL interrupt_en);
extern void lp_drv_disable_wkppad(UINT8 pad_num);
extern void lp_drv_change_VREF(UINT8 vref_val);
extern void lp_drv_enter_sleep(void);
extern UINT8 lp_drv_get_wkp_flag(void);
extern UINT8 lp_drv_get_wkppad_val(void);
extern void lp_drv_clr_wkp_flag(UINT8 pad_num);

#endif /* LOWPOWER_DRV_H_ */
