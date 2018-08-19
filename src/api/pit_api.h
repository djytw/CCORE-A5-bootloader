// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : pit_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __PIT_H__
#define __PIT_H__


/* macro definition */
#define PIT_1				1
#define PIT_2				2

#define MS(m)				(1000 / m)
#define US(m)				(1000000 / m)
#define NS(m)				(1000000000 / m)

/* data structure */
typedef enum _PIT_CLKDIV_ {
	PIT_CLK_DIV_1,//1��Ƶ
	PIT_CLK_DIV_2,//2��Ƶ
	PIT_CLK_DIV_4,//4��Ƶ
	PIT_CLK_DIV_8,//8��Ƶ
	PIT_CLK_DIV_16,//16��Ƶ
	PIT_CLK_DIV_32,//32��Ƶ
	PIT_CLK_DIV_64,//64��Ƶ
	PIT_CLK_DIV_128,//128��Ƶ
	PIT_CLK_DIV_256,//256��Ƶ
	PIT_CLK_DIV_512,//512��Ƶ
	PIT_CLK_DIV_1024,//1024��Ƶ
	PIT_CLK_DIV_2048,//2048��Ƶ
	PIT_CLK_DIV_4096,//4096��Ƶ
	PIT_CLK_DIV_8192,//8192��Ƶ
	PIT_CLK_DIV_16384,//16384��Ƶ
	PIT_CLK_DIV_32768,//32768��Ƶ
} PIT_CLKDIV, *P_PIT_CLKDIV;


/* functions declaration */
extern void pit_init(UINT8 pit_no, UINT32 pit_clk, PIT_CLKDIV div, UINT16 val);
extern void pit_disable(UINT8 pit_no);
extern void pit_time_start(UINT8 pit_no);
extern FP32 pit_get_past_time(UINT8 pit_no);

#endif /* __PIT_H__ */
