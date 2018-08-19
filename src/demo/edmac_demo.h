// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : edmac_demo.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef _EDMAC_DEMO_H_
#define _EDMAC_DEMO_H_

enum{
	EDMAC0_ID = 0,
	EDMAC1_ID,
};

enum{
	EDMAC_CH0_ID = 0,
	EDMAC_CH1_ID,
};

#define EDMAC_MAXLEN_TEST		(1024)//dmac sram test len

#define EDMAC_INTEN_TEST		(1)//dmac interrupt test	0:int_dis 1:int_en

extern BOOL edmac_demo();

#endif /* EDMA_DEMO_H_ */
