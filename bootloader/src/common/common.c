// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : common.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "common.h"
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 delay
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    System delay function.
//
// Input:
//    val: delay time.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void delay(volatile UINT32 val)
{
	while(val--);
}

BOOL check_data(UINT32 bar,  UINT32 par, UINT32 len)
{
	UINT32 i;
	UINT8 *pSrc = (UINT8 *)bar;
	UINT8 *pDst = (UINT8 *)par;

	for(i=0;i<len;i++)
	{
		if((*pSrc++)!=(*pDst++))
		{
			return FALSE;
		}
	}
	return TRUE;
}

void cc_memcpy(unsigned int *output, unsigned int *input, unsigned int len)
{
	if (len != 0) {

		do {
			*output++ = *input++;
		}while (--len != 0);
	}
}

void cc_memset(unsigned int *output, int value, unsigned int len)
{
	if(len != 0) {
		do {
			*output++ = value;
		}while(--len != 0);
	}
}

void dump_hex(UINT32 addr, UINT32 len)
{
	int i,j;
	UINT8 *p_buf;

	j = 0;
	p_buf =(UINT8*)addr;
	for(i = 0; i < len; i++)
	{
		PRINTF("%02x", *p_buf);
		p_buf++;
		j++;
		if(j%32 == 0)
		{
			PRINTF("\n");
		}
		else
		{
			if(j%8 == 0)
			{
				PRINTF(" ");
			}
		}
	}

	if(j%32 != 0)
	{
		PRINTF("\n");
	}

}

UINT32 change_endian(UINT32 data)
{
	UINT32 res;

	res = (data<<24) | ((data<<8)&0x00FF0000) | ((data>>8)&0x0000FF00) | (data>>24);
	return res;
}

void change_endian_mem(UINT32* pStart, UINT32 len_word)
{
	UINT32* p32 = pStart;	//start address
	UINT32 num = len_word;	//word count (byte length/4)
	int i;

	for(i = 0; i < num; i++)
	{
		*p32 = change_endian(*p32);
		p32++;
	}
}
