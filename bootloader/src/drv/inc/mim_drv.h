// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : mim_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __MIM_DRV_H__
#define __MIM_DRV_H__

//extern void mim_cfg_as_gpio(UINT32 dir_mask);
//extern void mim_gpio_output(UINT32 data);
//extern void mim_cs0_enable(UINT8 wats, UINT8 wnts, UINT8 rats, UINT8 ws);
//extern void mim_cs1_enable(UINT8 wats, UINT8 wnts, UINT8 rats, UINT8 ws, UINT8 ps);
//extern void mim_cfg_eport(void);
//extern void mim_init(void);
extern BOOL mim_pin_config(UINT8 pin, UINT8 dir);
extern UINT8 mim_pin_read(UINT8 pin);
extern BOOL mim_pin_write(UINT8 pin, UINT8 val);

#endif /* __MIM_DRV_H__ */
