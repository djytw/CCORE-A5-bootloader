// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : spi_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __SPI_API_H__
#define __SPI_API_H__

#include "type.h"
#include "spi_drv.h"

//spi id
enum{
	SPI_ID1 = SPI1,
	SPI_ID2 = SPI2,
	SPI_ID3 = SPI3,
	SPI_ID4 = SPI4,
};

//spi ucframemode
enum{
    SPI_CPOL0CPHA0,
    SPI_CPOL0CPHA1,
    SPI_CPOL1CPHA0,
    SPI_CPOL1CPHA1,
    SPI_TIMODE,
};

//spi ucframesize
enum{
    SPI_FRAME8BIT = 8,
    SPI_FRAME9BIT,
    SPI_FRAME10BIT,
    SPI_FRAME11BIT,
    SPI_FRAME12BIT,
    SPI_FRAME13BIT,
    SPI_FRAME14BIT,
    SPI_FRAME15BIT,
    SPI_FRAME16BIT,
};

//spi bauddiv
enum{
    SPI_BDDIV2,
    SPI_BDDIV4,
    SPI_BDDIV8,
    SPI_BDDIV16,
    SPI_BDDIV32,
    SPI_BDDIV64,
    SPI_BDDIV128,
    SPI_BDDIV256,
};

//spi trsmode
enum{
    SPI_CPUTRANS,
    SPI_DMACTRANS,
    SPI_EDMACTRANS,
};

//spi pins
enum{
    SPI_MISO = 0,
    SPI_MOSI,
    SPI_SCK,
    SPI_SS
};

#define IS_SPI_PINx(pin) (((pin) == SPI_MISO) || \
                          ((pin) == SPI_MOSI) || \
                          ((pin) == SPI_SCK) || \
                          ((pin) == SPI_SS))

extern BOOL spi_master_init(UINT8 ucid, UINT8 ucframemode, UINT8 bauddiv, UINT8 ucssoe );
extern BOOL spi_slave_init(UINT8 ucid, UINT8 ucframemode );
extern BOOL spi_readwrite_byte(UINT8 ucid, UINT8 *pwrite, UINT8 *pread, UINT32 uldatalen,UINT8 uctrsmode);
extern BOOL spi_sspin_high(UINT8 ucid );
extern BOOL spi_sspin_low(UINT8 ucid );
extern BOOL spi_config_gpio(UINT8 ucid, UINT8 pin, UINT8 dir);
extern UINT8 spi_read_gpio(UINT8 ucid, UINT8 pin);
extern BOOL spi_write_gpio(UINT8 ucid, UINT8 pin, UINT8 val);
#endif /* __SPI_API_H__ */
