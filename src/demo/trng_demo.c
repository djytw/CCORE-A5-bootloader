// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : trng_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "trng_demo.h"
#include "includes.h"
#include "trng_api.h"

void trng_get_random_data(UINT8 *pdata, UINT16 len)
{
	UINT16 i;
	
	for(i=0; i<len; i+=4)
	{
		*(UINT32 *)(pdata+i) = trng_rand();
	}
}

void byte2bit(UINT8 data, UINT8 *result)
{
	unsigned char i;
	
	for(i=0; i<8; i++)
	{
		result[i] = (data>>i)&0x01;
	}
}

UINT8 rand_test(UINT8 *pdata, UINT16 len)
{
	unsigned char data[8];
	int i,j;
	int va0_count=0, va1_count=0;
	volatile int va0, va1;
	
	//count 0 & 1 in all 1KB data
	for(i=0; i<len; i++)
	{
		byte2bit(pdata[i], data);
		for(j=0; j<8; j++)
		{
			if(data[j] == 0)
			{
				va0_count++;
			}
			else if(data[j] == 1)
			{
				va1_count++;
			}
		}
	}
	
	va0 = 500 - va0_count*1000/(len*8);
	va1 = 500 - va1_count*1000/(len*8);
	if((va0 >= 50) || (va1 >= 50))
	{
		return FALSE;
	}

	//count 0 & 1 by 256 byte one block, 4 blocks totally 
	va0_count = 0;
	va1_count = 0;
	for(i=0; i<len; i++)
	{
		byte2bit(pdata[i], data);
		for(j=0; j<8; j++)
		{
			if(data[j] == 0)
			{
				va0_count++;
			}
			else if(data[j] == 1)
			{
				va1_count++;
			}
		}
		if((i+1)%256 == 0)
		{
			va0 = 500 - va0_count*1000/(256*8);
			va1 = 500 - va1_count*1000/(256*8);
			if((va0 >= 50) || (va1 >= 50))
			{
				return FALSE;
			}
			va0_count = 0;
			va1_count = 0;
		}
	}
	
	return TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 trng_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    demo of trng
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void trng_demo(void)
{
	volatile UINT8 ret, *pdata;

	pdata = (UINT8*)(0x00801000);

	trng_enable();
	
	//random data check  1KB
	trng_get_random_data((UINT8*)pdata, 0x400);
	ret = rand_test((UINT8 *)pdata, 0x400);
	if(ret == 0)
	{
		MSG("trng test failed!!\n");
	}
	else
	{
		MSG("trng test passed!!\n");
	}
	
	trng_close();

}



