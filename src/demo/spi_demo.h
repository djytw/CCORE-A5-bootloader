// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : spi_demo.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef __SPI_DEMO_H__
#define __SPI_DEMO_H__

#define SPI_DEMO_MS			(1)//1:MASTER	0:SLAVE

#if ( SPI_DEMO_MS	== 	(1) )
#define SPI_DEMO_SS			(1)//1:SSOE	0:SSOD
#endif

#define SPI_DEMO_DATALEN	(256)

extern BOOL spi_demo();

#endif /* __SPI_DEMO_H__ */
