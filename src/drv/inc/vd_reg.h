// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : vd_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef __VD_REG_H__
#define __VD_REG_H__

#define LVD_EN			1
#define LVD_DIS			0

#define HVD_EN			1
#define HVD_DIS			0

#define LVD_RST_MODE	2
#define LVD_INT_MODE	1

#define HVD_RST_MODE	2
#define HVD_INT_MODE	1

#define VD_POWER_1V8	0
#define VD_POWER_3V3	1

#define HVD_3V90		0x0
#define HVD_3V81		0x04
#define HVD_3V72		0x08
#define HVD_3V63		0x0c

#define HVD_2V22		0x0
#define HVD_2V16		0x10
#define HVD_2V10		0x20
#define HVD_2V05		0x30

#define LVD_2V67		0x0
#define LVD_2V76		0x04
#define LVD_2V86		0x08
#define LVD_2V97		0x0c

#define LVD_1V43		0x0
#define LVD_1V48		0x10
#define LVD_1V54		0x20
#define LVD_1V60		0x30

#endif /* __VD_REG_H__ */
