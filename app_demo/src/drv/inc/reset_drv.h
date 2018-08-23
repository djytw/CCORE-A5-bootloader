// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : rst_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __RST_DRV_H__
#define __RST_DRV_H__

extern void rst_force_softrst(void);
extern void rst_force_porrst(void);
extern UINT8 rst_status(void);

extern void reset_dis_simcard_rst(void);
extern void reset_dis_hfd_rst(void);
extern void reset_dis_lfd_rst(void);
extern void reset_dis_hvd_rst(void);
extern void reset_dis_lvd_rst(void);

#endif /* __RST_DRV_H__ */
