// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : spi_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __SPI_DRV_H__
#define __SPI_DRV_H__

#include "type.h"

#define SPI_HWNUM				(4)
#define SPI1					(0)
#define SPI2					(1)
#define SPI3					(2)
#define SPI4					(3)

//SPI default guard time
#define SPI_GT_03		(0x43)
#define SPI_DFT_GT		(0x00)

//macro to enable FIFO time-out
#define SPI_TIMEOUT_EN	(0)

//SPI mode
#define SPI_FSL_MODE0		(0x00) //CPOL:0 CPHA:0
#define SPI_FSL_MODE1		(0x04) //CPOL:0 CPHA:1
#define SPI_FSL_MODE2		(0x08) //CPOL:1 CPHA:0
#define SPI_FSL_MODE3		(0x0c) //CPOL:1 CPHA:1

#define SPI_TI_MODE			(0x5a) //TI mode//?

//SPI master/slave mode macros
#define SPI_MASTER		(0x10)
#define SPI_SLAVE		(0x00)

#define SPI_SSOE		(0x02)
#define SPI_LSBFE		(0x01)

#define SPI_GTE			(0x40)
#define SPI_BR2			(0)

#define SPI_FMSZ8		(7)

//Data regiter access mode macros
#define SPI_BYTE				(0x01)
#define SPI_HALFWORD			(0x00)

extern BOOL spi_hsenable(UINT8 ucid, BOOL ben);
extern BOOL spi_clrfifo(UINT8 ucid);
extern BOOL spi_dbltxdr(UINT8 ucid, BOOL ben);
extern BOOL spi_config(UINT8 ucid, UINT8 ucms, UINT8 ucbauddivisor, UINT8 ucframesize, UINT8 ucframemode, UINT8 ucgtime);
extern BOOL spi_dmacen(UINT8 ucid, BOOL ben);
extern BOOL spi_ssout(UINT8 ucid, BOOL bval);
extern BOOL spi_enable(UINT8 ucid, BOOL ben);
extern BOOL spi_trans8bit(UINT8 ucid, UINT8 *psend, UINT8 *precv, UINT32 uldatalen);
extern BOOL spi_trans16bit(UINT8 ucid, UINT16 *psend, UINT16 *precv, UINT32 uldatalen);
extern BOOL spi_pin_config(UINT8 ucid, UINT8 pin, UINT8 dir);
extern UINT8 spi_pin_read(UINT8 ucid, UINT8 pin);
extern BOOL spi_pin_write(UINT8 ucid, UINT8 pin, UINT8 val);

#endif /* __SPI_DRV_H__ */
