/*
 * gpio_led_demo.c
 *
 *  Created on: 2017骞�鏈�7鏃�
 *      Author: ccore
 */
#include "gpio_led_demo.h"
#include "mim_api.h"
#include "spi_api.h"
#include "i2c_api.h"
#include "sci_api.h"
#include "usi_api.h"
#include "cpm_api.h"

static void Led_delay(volatile int n)
{
	while(n--);
}

INT8 gpio_led_demo()
{
	INT8 tmp;

#ifdef MIM_GPIO_LED_TEST

#ifdef LED_TEST
	//output test
	mim_config_gpio(MIM_D16, GPIO_OUTPUT);

	while(1)
	{
		mim_write_gpio(MIM_D16, Bit_SET);
		Led_delay(550000);//100ms
		mim_write_gpio(MIM_D16, Bit_RESET);
		Led_delay(550000);
	}
#else
	//input test
	mim_config_gpio(MIM_D17, GPIO_INPUT);
	//while(1)
	{
		tmp = mim_read_gpio(MIM_D17);

		if ( tmp == 1)
		{
			MSG("MIM PORT is H\r\n");
		}
		else if (tmp == 0)
		{
			MSG("MIM PORT is L\r\n");
		}
		else
		{
			MSG("error\r\n");
		}
		Led_delay(2750000);//500ms
	}
#endif

#endif  //MIM_GPIO_LED_TEST

#ifdef SPI_GPIO_LED_TEST
#ifdef LED_TEST
	//output test
	spi_config_gpio(SPI_ID2, SPI_MOSI, GPIO_OUTPUT);

	while(1)
	{
		spi_write_gpio(SPI_ID2, SPI_MOSI, Bit_SET);
		Led_delay(550000);//100ms
		spi_write_gpio(SPI_ID2, SPI_MOSI, Bit_RESET);
		Led_delay(550000);

}
#else
	//input test
	spi_config_gpio(SPI_ID2, SPI_MOSI, GPIO_INPUT);
	while(1)
	{
		tmp = spi_read_gpio(SPI_ID2, SPI_MOSI);

		if ( tmp == 1)
		{
			MSG("SPI PORT is H\r\n");
		}
		else if (tmp == 0)
		{
			MSG("SPI PORT is L\r\n");
		}
		else
		{
			MSG("error\r\n");
		}
		Led_delay(2750000);//500ms
	}
#endif
#endif  //SPI_GPIO_LED_TEST

#ifdef I2C_GPIO_LED_TEST
#ifdef LED_TEST
	//output test
	i2c_config_gpio(I2C_SCL, GPIO_OUTPUT);
	while(1)
	{
		i2c_write_gpio(I2C_SCL, Bit_SET);
		Led_delay(550000);//100ms
		i2c_write_gpio(I2C_SCL, Bit_RESET);
		Led_delay(550000);
	}
#else
	//input test
	i2c_config_gpio(I2C_SCL, GPIO_INPUT);
	while(1)
	{
		tmp = i2c_read_gpio(I2C_SCL);

		if ( tmp == 1)
		{
			MSG("I2C PORT is H\r\n");
		}
		else if (tmp == 0)
		{
			MSG("I2C PORT is L\r\n");
		}
		else
		{
			MSG("error\r\n");
		}
		Led_delay(2750000);//500ms
	}
#endif
#endif  //I2C_GPIO_LED_TEST

#ifdef SCI_GPIO_LED_TEST
#ifdef LED_TEST
	//output test
	sci_config_gpio(SCI_ID2,SCI_TX, GPIO_OUTPUT);

	while(1)
	{
		sci_write_gpio(SCI_TX, Bit_SET);
		Led_delay(550000);//100ms
		sci_write_gpio(SCI_TX, Bit_RESET);
		Led_delay(550000);
	}
#else
	//input test
	sci_config_gpio(SCI_ID2,SCI_RX, GPIO_INPUT);
	while(1)
	{
		sci_set_ucid(SCI_ID2);
		tmp = sci_read_gpio(SCI_RX);

		if ( tmp == 1)
		{
			sci_set_ucid(SCI_ID1);
			MSG("UART PORT is H\r\n");
		}
		else if (tmp == 0)
		{
			sci_set_ucid(SCI_ID1);
			MSG("UART PORT is L\r\n");
		}
		else
		{
			sci_set_ucid(SCI_ID1);
			MSG("error\r\n");
		}
		Led_delay(2750000);//500ms
	}
#endif
#endif  //SCI_GPIO_LED_TEST

#ifdef USI_GPIO_LED_TEST
#ifdef LED_TEST
	//output test
	//Card3_Power_Switch(card_3v3);
	usi_config_gpio(USI_ID1, USI_RST, GPIO_OUTPUT);

	while(1)
	{
		usi_write_gpio(USI_ID1, USI_RST, Bit_SET);
		Led_delay(550000);//100ms
		usi_write_gpio(USI_ID1, USI_RST, Bit_RESET);
		Led_delay(550000);
	}
#else
	//input test
	usi_config_gpio(USI_ID1, USI_RST, GPIO_INPUT);
	while(1)
	{
		tmp = usi_read_gpio(USI_ID1, USI_RST);

		if ( tmp == 1)
		{
			MSG("USI PORT is H\r\n");
		}
		else if (tmp == 0)
		{
			MSG("USI PORT is L\r\n");
		}
		else
		{
			MSG("error\r\n");
		}
		Led_delay(2750000);//500ms
	}
#endif
#endif  //USI_GPIO_LED_TEST

	//2.2s
	//Delay(0xB1D800);
	return tmp;
}
