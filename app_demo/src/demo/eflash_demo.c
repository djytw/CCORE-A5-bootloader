// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eflash_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



#include "type.h"
#include "eflash_api.h"
#include "cpm_api.h"
#include "eport_api.h"
#include "eflash_demo.h"


void eflash_demo()
{

	UINT32 i = 0, ret_code = 0;
	UINT32 efm_clk;
	UINT8 *p_data_buf = (UINT8 *)0x820000;

	for(i = 0; i < 0x200; i++)
	{
		p_data_buf[i] = i & 0xFF;
	}

	efm_clk = cpm_get_efmclk();
	eflash_init(efm_clk);
	PRINTF("-CASE1:eflash init success\r\n");

#ifdef EFM_DISABLE_BOOTLOADER_DEMO
	/* Disable rom boot */
	eflash_disable_bootloader();
	PRINTF("-CASE2:eflash disable bootload success\r\n");
#endif

#ifdef EFM_RECOVERY_TO_ROM_DEMO
	/* Recovery to rom mode */
	eflash_recovery_to_rom();
	PRINTF("-CASE3:eflash recovery to rom success\r\n");
#endif

	/* page erase. */
	for(i = EFM_BASE + 0x80000; i < EFM_END; i += 512)
	{
		/* MPU configure pages, can not be read. */
		if(i < 0x4fee00 || i >= 0x500000)
		{
			ret_code = eflash_page_erase(i);
			if(ret_code == EFLASH_PROG_ERASE_FAIL)
			{
				asm("bkpt");
			}
		}
	}
	PRINTF("-CASE4:eflash page erase success\r\n");
	/* page erase verify. */
	for(i = EFM_BASE + 0x80000; i < EFM_END; i += 4)
	{
		if(i < 0x4fee00 || i >= 0x500000)
		{
			if(eflash_word_read(i) != 0xFFFFFFFF)
			{
				asm("bkpt");
			}
		}
	}
	PRINTF("-CASE5:eflash page erase verify success\r\n");

	/* word program. */
	for(i = EFM_BASE + 0x80000; i < EFM_END; i += 4)
	{
		if(i < 0x4fee00 || i >= 0x500000)
		{
			ret_code = eflash_program(i, i);
			if(ret_code == EFLASH_PROG_ERASE_FAIL)
			{
				PRINTF("  addr = %08x program faile\r\n",i);
//				asm("bkpt");
				return;
			}
			PRINTF("  addr = %08x program success\r\n",i);
		}
	}
	PRINTF("-CASE6:eflash pword program success\r\n");
	/* word program verify. */
	for(i = EFM_BASE + 0x80000; i < EFM_END; i += 4)
	{
		if(i < 0x4fee00 || i >= 0x500000)
		{
			if(eflash_word_read(i) != i)
			{
				asm("bkpt");
			}
		}
	}
	PRINTF("-CASE7:eflash pword program verify success\r\n");
	/* page erase. */
	for(i = EFM_BASE + 0x80000; i < EFM_END; i += 512)
	{
		if(i < 0x4fee00 || i >= 0x500000)
		{
			eflash_page_erase(i);
			if(ret_code == EFLASH_PROG_ERASE_FAIL)
			{
				asm("bkpt");
			}
		}
	}

	/* page erase verify. */
	for(i = EFM_BASE + 0x80000; i < EFM_END; i += 4)
	{
		if(i < 0x4fee00 || i >= 0x500000)
		{
			if(eflash_word_read(i) != 0xFFFFFFFF)
			{
				asm("bkpt");
			}
		}
	}

	/* bulk program. */
	for(i = EFM_BASE + 0x80000; i < EFM_END; i += 512)
	{
		if(i < 0x4fee00 || i >= 0x500000)
		{
			ret_code = eflash_bulk_program(i, 0x200 / 4, (UINT32 *)p_data_buf);
			{
				if(ret_code == EFLASH_PROG_ERASE_FAIL)
				{
					asm("bkpt");
				}
			}
		}
	}
	PRINTF("-CASE8:eflash bulk program success\r\n");
	/* bulk program verify. */
	for(i = EFM_BASE + 0x80000; i < EFM_END; i++)
	{
		if(i < 0x4fee00 || i >= 0x500000)
		{
			if(eflash_byte_read(i) != p_data_buf[i & 0xFF])
			{
				asm("bkpt");
			}
		}
	}
	PRINTF("-CASE9:eflash bulk program verify success\r\n");
	/* page erase. */
	for(i = EFM_BASE + 0x80000; i < EFM_END; i += 512)
	{
		if(i < 0x4fee00 || i >= 0x500000)
		{
			eflash_page_erase(i);
			if(ret_code == EFLASH_PROG_ERASE_FAIL)
			{
				asm("bkpt");
			}
		}
	}

	/* page erase verify. */
	for(i = EFM_BASE + 0x80000; i < EFM_END; i += 4)
	{
		if(i < 0x4fee00 || i >= 0x500000)
		{
			if(eflash_halfword_read(i) != 0xFFFF)
			{
				asm("bkpt");
			}
		}
	}
}
