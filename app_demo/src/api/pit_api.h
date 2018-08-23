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
	PIT_CLK_DIV_1,//1分频
	PIT_CLK_DIV_2,//2分频
	PIT_CLK_DIV_4,//4分频
	PIT_CLK_DIV_8,//8分频
	PIT_CLK_DIV_16,//16分频
	PIT_CLK_DIV_32,//32分频
	PIT_CLK_DIV_64,//64分频
	PIT_CLK_DIV_128,//128分频
	PIT_CLK_DIV_256,//256分频
	PIT_CLK_DIV_512,//512分频
	PIT_CLK_DIV_1024,//1024分频
	PIT_CLK_DIV_2048,//2048分频
	PIT_CLK_DIV_4096,//4096分频
	PIT_CLK_DIV_8192,//8192分频
	PIT_CLK_DIV_16384,//16384分频
	PIT_CLK_DIV_32768,//32768分频
} PIT_CLKDIV, *P_PIT_CLKDIV;


/* functions declaration */
extern void pit_init(UINT8 pit_no, UINT32 pit_clk, PIT_CLKDIV div, UINT16 val);
extern void pit_disable(UINT8 pit_no);
extern void pit_time_start(UINT8 pit_no);
extern FP32 pit_get_past_time(UINT8 pit_no);

#endif /* __PIT_H__ */
