// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : edmac_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __EDMAC_DRV_H__
#define __EDMAC_DRV_H__

#include "type.h"

#define EDMAC_HWNUM					(2)
#define EDMAC_CHNUM					(2)
#define EDMAC0						(0)
#define EDMAC1						(1)
#define EDMACCH0					(0)
#define EDMACCH1					(1)



#define EDMAC_PN5AES				(0x00000500)	//AES
#define EDMAC_PN6DES				(0x00000600)	//DES
#define EDMAC_PN7SCB2				(0x00000700)	//SCB2
#define EDMAC_PN9SM4				(0x00000900)	//SM4
#define EDMAC_PN10SHA				(0x00000a00)	//SHA
#define EDMAC_PN11SSF33				(0x00000b00)  	//SSF33
#define EDMAC_PN12RSA				(0x00000c00)  	//RSA


#define EDMAC_CRYPTBLOCK_LEN	(0x400)
extern VUINT32 g_edmaccryptbuf[2][2][EDMAC_CRYPTBLOCK_LEN/4];

//#define APDU_SLEN			    (12)
#define APDU_DATALEN			(0x400)

extern BOOL edmac_waitspicomd(UINT8 ucid, UINT8 *pspicmd);
extern BOOL edmac_spislavecrc(UINT8 ucid, UINT8 *psend, UINT8 *precv, UINT32 len, UINT8 crcen);
extern BOOL edmac_inten(UINT8 ucid, BOOL ben);
extern BOOL edmac_sramtrans(UINT8 ucid, UINT8 ucch, UINT8* psrc, UINT8* pdst, UINT32 ulbytelen, BOOL binten);
extern BOOL edmac_spitrans(UINT8 ucch, UINT8 ucspiid, UINT8* psend, UINT8* precv, UINT32 uldatalen, BOOL binten);

extern BOOL edmac_piplinecrypt(UINT8 ucspiid, INT32 majorch0, INT32 majorch1, INT32 frame, INT32 len, INT32 type, UINT8 crc);
extern BOOL edmac_crypttrans(UINT8 ucch, UINT32 crypttype, UINT8* psend, UINT8* precv, UINT32 ulbytelen);
extern BOOL edmac_spimastercrc(UINT8 ucch, UINT8 ucspiid, UINT8* psend, UINT8* precv, UINT32 ulbytelen, UINT8 crctype);

#endif /* __EDMAC_DRV_H__ */
