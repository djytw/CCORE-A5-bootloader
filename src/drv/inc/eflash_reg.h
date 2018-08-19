// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eflash_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __EFLASH_REG__
#define __EFLASH_REG__

///////////////////////regs///////////////////////////////////////

#define EFCR			(*(volatile UINT32 *)(0x63f80000))
#define EFAPR			(*(volatile UINT32 *)(0x63f80004))
#define EFSTAT			(*(volatile UINT32 *)(0x63f80008))
#define EFINTM			(*(volatile UINT32 *)(0x63f8000c))
#define EFCMD			(*(volatile UINT32 *)(0x63f80010))
#define EECCECNT		(*(volatile UINT32 *)(0x63f80014))
#define ETIMBASE		(*(volatile UINT32 *)(0x63f80018))
#define ETIMCFG			(*(volatile UINT32 *)(0x63f8001c))
#define EFPETIMER		(*(volatile UINT32 *)(0x63f80020))
#define SMWOP0       	(*(volatile UINT32 *)(0x63f80024))
#define SMWOP1       	(*(volatile UINT32 *)(0x63f80028))
#define SMWOP2       	(*(volatile UINT32 *)(0x63f8002C))
#define SMWOP3       	(*(volatile UINT32 *)(0x63f80030))
#define EFCMD1			(*(volatile UINT32 *)(0x63f800c8))


/* CMD IDX */
#define EFLASH_MASS_ERASE_CMD				(0x01)
#define EFLASH_PAGE_ERASE_CMD				(0x02)
#define EFLASH_NORMAL_PROG_CMD				(0x03)
#define EFLASH_SMART_PROG_CMD				(0x04)
#define EFLASH_SMART_MASS_ERASE_CMD			(0x05)
#define EFLASH_ONE_SHOT_MASS_ERASE_CMD		(0x06)
#define EFLASH_SMART_PAGE_ERASE_CMD			(0x07)
#define EFLASH_SMART_SECTOR_ERASE_CMD		(0x08)
#define EFLASH_ENTER_SLEEP_CMD				(0x0F)
#define EFLASH_BIASINI_TEST_CMD				(0x10)
#define EFLASH_EXTC_TEST_CMD				(0x11)
#define EFLASH_REF_CELL_TEST_CMD			(0x12)
#define EFLASH_VTON_TEST_CMD				(0x13)
#define EFLASH_IFREN_TEST_CMD				(0x14)
#define EFLASH_EXIT_SLEEP_CMD				(0x1F)

#define SMWOP0_200NS_CLK_NUM		(0x1F00)
#define SMWOP0_1US_CLK_NUM			(0x00FF)

#define ETIMBASE_1US_CLK_NUM		(0x00FF)
#define ETIMBASE_20NS_CLK_CNT		(0x0700)

#endif // end of #ifndef __EFLASH__

