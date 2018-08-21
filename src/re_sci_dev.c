
#include "includes.h"
#include "memmap.h"
#include "sci_reg.h"
#include "sci_drv.h"


extern volatile SCI_REG* pregspointer;
u8 sci_read_notimeout(){
	u8 tmp;
	SCI_ENABLE_RECEIVER;
	if(0 == (pregspointer->SR1 & RDRF_MASK))return 0xff;
	tmp = pregspointer->DRL;
	return tmp;
}
