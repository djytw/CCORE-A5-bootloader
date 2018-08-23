// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eflash_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __EFLASH_H__
#define __EFLASH_H__

#include "includes.h"
#include "eflash_drv.h"

#define EFM0_MAIN_BASEADDR		(0x00400000)
#define EFM1_MAIN_BASEADDR		(0x00480000)
#define EFM2_MAIN_BASEADDR		(0x00500000)

#define EFM_MAIN_LEN			(0x00140000)

#define EFM_BASE				(0x00400000)
#define EFM_END					(EFM_BASE + 0x140000)

/* EFlash Prog/Erase Result. */
#define EFLASH_PROG_ERASE_PASS			(0)
#define EFLASH_PROG_ERASE_FAIL			(1)
#define EFLASH_OUT_OF_RANGE				(2)

/* eflash page size. */
#define EFLASH_PAGESIZE					(0x200)

/*
 * Description:
 *     init eflash related functions and timings.
 *
 * Input:
 *     @f_eflash_khz: eflash modules clock
 *
 * Output:
 *     none
 */
extern void eflash_init(UINT32 f_eflash_clk);

/*
 * Description:
 *     eflash program function.
 *
 * Input:
 *     @addr: eflash addr
 *     @data: programmed word
 *
 * Output:
 *     @0: EFLASH_PROG_ERASE_PASS
 *     @1: EFLASH_PROG_ERASE_FAIL
 */
extern UINT8 eflash_program(UINT32 addr, UINT32 data);

/*
 * Description:
 *     eflash bulk program function.
 *
 * Input:
 *     @addr: eflash addr
 *     @num_words: number of words to be programmed
 *     @data_buf: data buffer to be programmed
 *
 * Output:
 *     @0: EFLASH_PROG_ERASE_PASS
 *     @1: EFLASH_PROG_ERASE_FAIL
 */
extern UINT8 eflash_bulk_program(UINT32 addr, UINT32 num_words, UINT32 *data_buf);

/*
 * Description:
 *     eflash line program function.
 *     one line is 64 words, and the function only can program on line.
 *     so max num_words must be little than 64, and
 *     the eflash addr must be 64-words aligned or
 *     the words to be programed must be in 64-words boundary.
 *
 * Input:
 *     @addr: eflash addr
 *     @num_words: number of words to be programmed(must < 64)
 *     @data: data buffer to be programed
 *
 * Output:
 *     @0: EFLASH_PROG_ERASE_PASS
 *     @1: EFLASH_PROG_ERASE_FAIL
 */
extern UINT8 eflash_line_program(UINT32 addr, UINT32 num_words, UINT32 *data_buf);

/*
 * Description:
 *     eflash page program function.
 *     flash page size is 512 byte.
 *
 * Input:
 *     @addr: eflash addr
 *
 * Output:
 *     @0: EFLASH_PROG_ERASE_PASS
 *     @1: EFLASH_PROG_ERASE_FAIL
 */
extern UINT8 eflash_page_erase(UINT32 addr);

/*
 * Description:
 *     eflash byte read interface.
 *
 * Input:
 *     none
 *
 * Output:
 *     none
 */
extern UINT8 eflash_byte_read(UINT32 addr);

/*
 * Description:
 *     eflash halfword read interface.
 *
 * Input:
 *     none
 *
 * Output:
 *     none
 */
extern UINT16 eflash_halfword_read(UINT32 addr);

/*
 * Description:
 *     eflash word read interface.
 *
 * Input:
 *     none
 *
 * Output:
 *     none
 */
extern UINT32 eflash_word_read(UINT32 addr);


/*
 * Description:
 *     clear smart operation error flag.
 *
 * Input:
 *     none
 *
 * Output:
 *     none
 */
extern void eflash_clr_smw_err_flag();

/*
 * Description:
 *     set max verify count.
 *
 * Input:
 *     none
 *
 * Output:
 *     none
 */
extern void eflash_set_verify_cnt(UINT32 cnt);

/*
 * Description:
 *     set eflash read wait cycle.
 *
 * Input:
 *     none
 *
 * Output:
 *     none
 */
extern void eflash_set_read_wait_cycle(UINT32 cycles);

/*
 * Description:
 *     enable main write access.
 *
 * Input:
 *     none
 *
 * Output:
 *     none
 */
extern void eflash_enable_main_write_access();

/*
 * Description:
 *     enable disable write access.
 *
 * Input:
 *     none
 *
 * Output:
 *     none
 */
extern void eflash_disable_main_write_access();

#endif /* __EFLASH_H__ */
