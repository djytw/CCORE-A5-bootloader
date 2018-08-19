// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : dma_demo.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


extern BOOL dmac_demo(void);
#ifndef DMAC_DEMO_H_
#define DMAC_DEMO_H_

enum{
	DMAC_CH0_ID = 0,
	DMAC_CH1_ID,
	DMAC_CH2_ID,
	DMAC_CH3_ID,
	DMAC_CH4_ID,
	DMAC_CH5_ID,
	DMAC_CH6_ID,
	DMAC_CH7_ID,
};


enum{
	DMAC_BYTE_TEST,
	DMAC_HWORD_TEST,
	DMAC_WORD_TEST,
};

#define DMAC_MAXLEN_TEST	(1024)//dmac sram test len

#define DMAC_INTEN_TEST		(1)//dmac interrupt test	0:int_dis 1:int_en





#endif /* __DMA_DEMO_H__ */
