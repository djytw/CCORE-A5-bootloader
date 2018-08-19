// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : dmac_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __DMAC_DRV_H__
#define __DMAC_DRV_H__

#include "type.h"

#define DMAC_HWNUM				(1)
#define DMAC_CHNUM				(8)

#define DMACCH0					(0)
#define DMACCH1					(1)
#define DMACCH2					(2)
#define DMACCH3					(3)
#define DMACCH4					(4)
#define DMACCH5					(5)
#define DMACCH6					(6)
#define DMACCH7					(7)

extern void dmac_inten(BOOL ben);
extern BOOL dmac_transword(UINT8 ucch, UINT8* psrc, UINT8* pdst, UINT32 ulwordlen, BOOL binten);
extern BOOL dmac_transhalfword(UINT8 ucch, UINT8* psrc, UINT8* pdst, UINT32 ulhwordlen, BOOL binten);
extern BOOL dmac_transbyte(UINT8 ucch, UINT8* psrc, UINT8* pdst, UINT32 ulbytelen, BOOL binten);
extern BOOL dmac_spitrans(UINT8 ucspiid, UINT8* psend, UINT8* precv, UINT32 uldatalen, BOOL binten);

#endif /* __DMAC_DRV_H__ */
