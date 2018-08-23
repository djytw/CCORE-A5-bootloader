// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eflash_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "eflash_api.h"

static eflash_ops_func_t eflash_ops;

void eflash_init(UINT32 f_eflash_clk)
{
	eflash_enable_main_write_access();
	eflash_drv_init(&eflash_ops);
	eflash_ops.set_clkd(f_eflash_clk / 1000);
}

/* eflash byte read interface. */
UINT8 eflash_byte_read(UINT32 addr)
{
	return (*(volatile UINT8 *)(addr));
}

/* eflash halfword read interface. */
UINT16 eflash_halfword_read(UINT32 addr)
{
	return (*(volatile UINT16 *)(addr));
}

/* eflash word read interface. */
UINT32 eflash_word_read(UINT32 addr)
{
	return (*(volatile UINT32 *)(addr));
}

/* eflash word program interface. */
UINT8 eflash_program(UINT32 addr, UINT32 data)
{
	return eflash_ops.eflash_program(addr, data, 1);
}

/* eflash bulk program interface. */
UINT8 eflash_bulk_program(UINT32 addr, UINT32 num_words, UINT32 *data_buf)
{
	return eflash_ops.eflash_bulk_program(addr, num_words, data_buf, 1);
}


/* eflash page erase interface. */
UINT8 eflash_page_erase(UINT32 addr)
{
	UINT8 ret_value;
	ret_value = eflash_ops.eflash_page_erase(addr, 1);

//	//invalid this page in cache if it is cacheable
//	if(get_target_cache_attr(addr) == cache_through)
//	{
//		invalid_cache_by_addr_len(addr,EFLASH_PAGESIZE);
//	}

	return ret_value;
}


