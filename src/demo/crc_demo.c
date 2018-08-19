// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : cpm_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "crc_api.h"
#include "crc_demo.h"

UINT8 Table_CRC8[256];
UINT16 Table_CRC16[256];
UINT32 Table_CRC32[256];

UINT8 buf[] = {
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	0x12, 0x34, 0x56, 0x78
};


static void creat_crc8_table(void);
static void creat_crc16_table(void);
static void creat_crc32_table(void);
static UINT8 do_crc_08_add0(UINT8 *point, int aSize, UINT8 init_data);
static UINT16 do_crc_16_add0(UINT8 *point, int aSize, UINT16 init_data);
static UINT32 do_crc_32_add0(UINT8 *point, int aSize, UINT32 init_data);

static void creat_crc8_table(void)
{
	int i, j;
	UINT32 poly, c;

	/* x^8 + x^2 + x^1 + x^0 polynomial (0x07)  */
	static const char p[] = {0,  1,  2};

	poly = 0L;
	for (i = 0; i < sizeof(p) / sizeof(char); i++)
	{
		poly |= 1L << p[i];
	}

	for(i = 0; i < 256; i++)
	{
		c = i;
		for(j = 0; j < 8; j++)
		{
			c = (c & 0x80) ? poly ^ (c << 1) : (c << 1);
		}
		Table_CRC8[i] = (char)c;
	}
}

static void creat_crc16_table( void )
{
	int i,  j;
	UINT32 poly,  c;
	/* x^16 + x^12 + x^5 + x^0    polynomial (0x1021)       */
	static const char p[] = {0, 5, 12};

	poly = 0L;

	for(i = 0; i < sizeof(p) / sizeof(char); i++)
	{
		poly |= 1L << p[i];
	}

	for(i = 0; i < 256; i++)
	{
		c = i << 8;
		for(j = 0; j < 8; j++)
		{
			c = (c & 0x8000) ? poly ^ (c << 1) : (c << 1);
		}
		Table_CRC16[i] = (UINT16)c;
	}
}

static void creat_crc32_table( void )
{
	int i,  j;
	UINT32 c,  poly;
	/*
	x32 + x26 + x23 + x22 + x16 + x12 + x11 + x10 + x8 + x7 + x5 + x4 + x2 + x + 1
	polynomial (0x04C11DB7L)
	*/
	static const char p[] = {0, 1, 2, 4, 5, 7, 8, 10, 11, 12, 16, 22, 23, 26};

	poly = 0L;

	for(i = 0; i < sizeof(p) / sizeof(char); i++)
	{
		poly |= 1L<<p[i];
	}
	for(i = 0; i < 256; i++)
	{
		c = (UINT32)i << 24;
		for(j = 0; j < 8; j++)
		{
			c = (c & 0x80000000) ? poly ^ (c << 1) : (c << 1);
		}
		Table_CRC32[i] = c;
	}
}

static UINT8 do_crc_08_add0(UINT8 *point, int aSize, UINT8 init_data)
{
	int i;
	UINT8 CRC8_1;

	CRC8_1 = init_data;

	for(i = 0; i< aSize; i++)
	{
		CRC8_1 = Table_CRC8[(UINT8)((CRC8_1) ^ (*point++))];
	}

    return CRC8_1;
}

static UINT16 do_crc_16_add0(UINT8 *point, int aSize, UINT16 init_data)
{
	int i;
	UINT16 CRC16_1;

	CRC16_1 = init_data;

	if(0 == (aSize % 2))
	{
		for(i = 0; i < aSize; i++)
		{
			CRC16_1 = ((CRC16_1 << 8) ) ^ Table_CRC16[((CRC16_1 >> 8) ^ (*point++)) & 0xFF];
		}
	}
	else if(1 == (aSize % 2))
	{
		for(i = 0; i < aSize; i++)
		{
			CRC16_1 = ((CRC16_1 << 8) ) ^ Table_CRC16[((CRC16_1 >> 8) ^ (*point++)) & 0xFF];
		}

		CRC16_1 = ((CRC16_1 << 8) ) ^ Table_CRC16[((CRC16_1 >> 8) ^ (0x00)) & 0xFF];
	}

	return CRC16_1;
}

static UINT32 do_crc_32_add0(UINT8 *point, int aSize, UINT32 init_data)
{
	UINT32 CRC32_1;
	int i;

	CRC32_1 = init_data;
	if(0)
	{
		if(0 == (aSize % 4))
		{
			for(i = 0; i < aSize; i = i + 4)
			{
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point+i+3))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point+i+2))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point+i+1))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point+i+0))) & 0xFF];
			}
		}
		else if(1 == (aSize % 4))
		{
			for(i = 0; i < aSize-1; i = i + 4)
			{
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point+i + 3))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point+i + 2))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point+i + 1))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point+i + 0))) & 0xFF];
			}

			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 0))) & 0xFF];
		}
		else if(2 == (aSize % 4))
		{
			for(i = 0; i < aSize - 2; i = i + 4)
			{
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 3))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 2))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 1))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 0))) & 0xFF];
			}

			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 1))) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 0))) & 0xFF];
		}
		else
		{
			for(i = 0; i < aSize - 3; i = i + 4)
			{
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 3))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 2))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 1))) & 0xFF];
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 0))) & 0xFF];
			}

			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 2))) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 1))) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point + i + 0))) & 0xFF];
		}
	}
	else
	{
		if(0 == (aSize % 4))
		{
			for(i = 0; i < aSize; i++)
			{
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point++))) & 0xFF];
			}
		}
		else if(1 == (aSize % 4))
		{
			for(i = 0; i < aSize; i++)
			{
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point++))) & 0xFF];
			}
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
		}
		else if(2 == (aSize % 4))
		{
			for(i = 0; i < aSize; i++)
			{
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point++))) & 0xFF];
			}
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
		}
		else
		{
			for(i = 0; i < aSize; i++)
			{
				CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (*(point++))) & 0xFF];
			}
			CRC32_1 = (CRC32_1 << 8) ^ Table_CRC32[((CRC32_1 >> 24) ^ (0x00)) & 0xFF];
		}
	}

	return CRC32_1;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 crc_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Demo of crc.
//    Calculate CRC use in both software and hardware method;
//    Generate BKPT if result are not match
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void crc_demo(void)
{
	UINT32 crcrr1 = 0;
	UINT32 crcrr2 = 0;
	UINT32 i;

	creat_crc8_table();
	creat_crc16_table();
	creat_crc32_table();

	for (i = 0; i < 4; i++)
	{
		crcrr1  = crc_calc(buf, sizeof(buf)/sizeof(char) - i, 0xffffffff, CRC_32, 1);
		crcrr2  = do_crc_32_add0(buf, sizeof(buf)/sizeof(char) - i, 0xffffffff);

		if(crcrr1 !=crcrr2)
		{
			asm("bkpt");
		}
	}

	for (i = 0; i < 2; i++)
	{
		crcrr1 = crc_calc(buf, sizeof(buf)/sizeof(char) - i, 0xffffffff, CRC_16, 1);
		crcrr2 = do_crc_16_add0(buf, sizeof(buf) / sizeof(char) - i, 0xffff);

		if(crcrr1 != crcrr2)
		{
			asm("bkpt");
		}
	}

	crcrr1 = crc_calc(buf, sizeof(buf)/sizeof(char), 0xff, CRC_8, 1);
	crcrr2 = do_crc_08_add0(buf, sizeof(buf) / sizeof(char), 0xff);

	if(crcrr1 != crcrr2)
	{
		asm("bkpt");
	}
	MSG("CRC test success\r\n");
}
