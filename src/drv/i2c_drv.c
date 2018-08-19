// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : i2c_drv.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "includes.h"
#include "i2c_reg.h"
#include "i2c_drv.h"
#include "int_drv.h"
#include "cpm_reg.h"


static VUINT32 g_len_send = 0;
static VUINT32 g_len_receive = 0;
static VUINT8 g_complete = 0;
static VUINT8 i2c_status;
static VUINT8 i2c_hs_status=0xff;

UINT8 *g_data_send;
UINT8 *g_data_receive;
UINT16 g_data_len = 0;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_m_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c master interrupt handle.
//
// Input:
//    	None.
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_m_isr(void)
{
	VUINT8 tmp=0;
	i2c_status = I2C_CSR;
	i2c_hs_status =I2C_SHSIR;

	if((i2c_hs_status & SLV_HS) != SLV_HS)
	{
		if((i2c_status & SR_AASLV) != SR_AASLV)		//The current slave device is addressed by master
		{
			if((i2c_status & SR_ARBL)==SR_ARBL)
			{
				I2C_CR &= ~CR_MSMOD;		//clear MSMOD to send STOP
			}
			else
			{
				if((i2c_status & SR_AACK)==SR_AACK)
				{
					I2C_CR &= ~CR_MSMOD;
				}
				else
				{
					if((i2c_status & SR_RC)!=SR_RC) // RECEIVER interrupt
					{
						if((i2c_status & SR_DACK)==SR_DACK)
						{
							if(g_len_send == g_data_len)
							{
								g_complete =0xff;
								I2C_CR &= ~CR_MSMOD;
							}
							else
							{
								I2C_CDR =g_data_send[g_len_send];
								g_len_send++;
							}
						}
						else
						{
							I2C_CR &= ~CR_MSMOD;
						}
					}
					else
					{
						if((i2c_status & SR_DACK)==SR_DACK)
						{
							if((i2c_status & SR_TF)==SR_TF)
							{
								g_data_receive[g_len_receive] = I2C_CDR;

								if(g_len_receive<(g_data_len-2))
								{
									I2C_CR |= CR_ACKEN;		//write ACKEN to clear RC status and enable next byte from Slave
								}
								else
								{
									I2C_CR &= ~CR_ACKEN;
								}

								g_len_receive++;
							}
							else
							{
								tmp = I2C_CDR;
								tmp ++;//add for warning
								I2C_CR |= CR_ACKEN;
							}
						}
						else
						{
							g_data_receive[g_len_receive] = I2C_CDR;
							g_complete =0xff;
							I2C_CR &= ~CR_MSMOD;
						}
					}
				}
			}
		}
	}
	else
	{
		I2C_SSHTR |=0x1;
		I2C_SHSIR |=SLV_HS;
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_s_isr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c slave interrupt handle.
//
// Input:
//    	None.
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_s_isr(void)
{
	VUINT8 tmp =0;
	i2c_status = I2C_CSR;
	i2c_hs_status = I2C_SHSIR;

	if((i2c_hs_status & SLV_HS) != SLV_HS )
	{
		if((i2c_status & SR_AASLV) == SR_AASLV )		//The current slave device is addressed by master
		{
			if((i2c_status & SR_RC) == SR_RC) // RECEIVER interrupt
			{
				if((I2C_CSR & SR_TF) == SR_TF) // transfer complete
				{
					g_data_receive[g_len_receive] = I2C_CDR;
					g_len_receive++;

					I2C_CR |= CR_ACKEN;
				}
				else
				{
					I2C_CR &= ~CR_AMIE;
				}
			}
			else // RECEIVER interrupt
			{
				if((i2c_status & SR_TF) == SR_TF) // transfer complete
				{
					if((i2c_status & SR_DACK)==SR_DACK)
					{
						I2C_CDR =g_data_send[g_len_send];
						g_len_send++;
						I2C_CR &= ~CR_AMIE;
					}
					else
					{
						tmp = I2C_CDR;
						tmp ++;//add for warning
					}
				}
				else
				{
					I2C_CR &= ~CR_AMIE;
				}
			}
		}
		else
		{
			asm("bkpt");
		}
	}
	else
	{
		I2C_SSHTR =(I2C_SSHTR&0xc0)|0x1;
		I2C_SSHTR =I2C_SSHTR|0x1;

		I2C_SHSIR |=SLV_HS;
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_config
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c module configs.
//
// Input:
//    	pre
//		addr
//		device_mode
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL i2c_config(UINT8 pre, UINT8 addr, UINT8 device_mode)
{
	I2C_CR = 0x0;
	I2C_CR |= CR_EN;

	delay(100);

	I2C_CR |= CR_ACKEN;

	if(device_mode == I2C_MASTER_DEVICE)
	{
		I2C_CPR =pre;
	}
	else if(device_mode == I2C_SLAVE_DEVICE)
	{
		I2C_SAR = addr;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_interrupt_enable
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c interrupt enables.
//
// Input:
//    	None.
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_interrupt_enable()
{
	EIC_REG *peicregspointer;
	peicregspointer = (EIC_REG *)EIC_BASE;

	I2C_CR |=CR_IEN;
	peicregspointer->IER |= IER_I2CINT_MASK;

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_master_send
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c master sends data.
//
// Input:
//    	data
//
// Output:
//      reg
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 i2c_master_send(UINT8 data)
{
	UINT8 reg;

	I2C_CDR = data;
	while((I2C_CSR&SR_TF)!=SR_TF);
	while((I2C_CSR&SR_DACK)!=SR_DACK);
	reg = I2C_CSR;

	return reg;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_master_rec
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c master receives data.
//
// Input:
//    	i
//		len
//
// Output:
//      data
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 i2c_master_rec(UINT32 i,UINT16 len)
{
	UINT8 data;

	while((I2C_CSR & SR_TF)!=SR_TF);

	data =I2C_CDR;

	if(i!=(len-2))
		I2C_CR |= CR_ACKEN;		//write ACKEN to clear RC status and enable next byte from Slave
	else
		I2C_CR &= ~CR_ACKEN;	//no write ACKEN to stop next byte from Slave

	return data;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_m_writedata
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c master writes data in polling mode.
//
// Input:
//    	slave_addr
//		buf
//		len
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_m_writedata(UINT8 slave_addr,UINT8* buf,UINT16 len)
{
	UINT16 i;
	volatile UINT8 status=0xff;

	//send slave addr;
	I2C_CDR =slave_addr&0xfe;
	while((I2C_CSR&SR_BBUSY)==SR_BBUSY);
	I2C_CR |= CR_MSMOD;
	while((I2C_CSR&SR_TF)!=SR_TF);

	//send Data
	while((I2C_CSR&SR_DACK)!=SR_DACK);

	status = I2C_CSR;

	if((status & SR_ARBL)==SR_ARBL)
	{
		I2C_CR &= ~CR_MSMOD;
		MSG("I2C Master arbitration lost occur!\n");
	}
	else
	{
		if((status & SR_AACK)!=SR_AACK)
		{
			for(i=0;i<len;i++)
			{
				i2c_master_send(*(buf+i));
			}
		}
	}

	I2C_CR &= ~CR_MSMOD;
	while(I2C_CSR&SR_BBUSY);		//busy bit clear indicate STOP finish

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_m_writedata_int
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c master writes data in interrupt mode.
//
// Input:
//    	slave_addr
//		buf
//		len
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_m_writedata_int(UINT8 slave_addr,UINT8* buf,UINT16 len)
{

	g_data_send = buf;
	g_data_len = len;

	//send slave addr
	I2C_CDR = slave_addr&0xfe;
	I2C_CR |= CR_MSMOD;
	delay(10);
	while((I2C_CSR&SR_TF)!=SR_TF);

	//send Data
	while(1)
	{
		if(g_complete == 0xff)
		{
			g_len_send =0;
			g_complete =0;

			break;
		}
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_m_readdata
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c master reads data in polling mode.
//
// Input:
//    	slave_addr
//		buf
//		len
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_m_readdata(UINT8 slave_addr,UINT8* buf,UINT16 len)
{
	UINT32 i;
	volatile UINT8 status;

	//send slave addr;
	I2C_CDR = slave_addr|0x01;
	while((I2C_CSR&SR_BBUSY)==SR_BBUSY);
	I2C_CR |= CR_MSMOD;
	while((I2C_CSR&SR_RC)!=SR_RC);
	I2C_CR |=CR_ACKEN;
	while((I2C_CSR&SR_DACK)!=SR_DACK);

	//receive data
	while((I2C_CSR & SR_RC) != SR_RC);

	status = I2C_CSR;

	if((status & SR_ARBL)==SR_ARBL)
	{
		I2C_CR &= ~CR_MSMOD;		//clear MSMOD to send STOP
		MSG("I2C Master arbitration lost occur!\n");
	}
	else
	{
		if((status & SR_AACK)==SR_AACK)
		{
			I2C_CR &= ~CR_MSMOD;		//clear MSMOD to send STOP
			MSG("I2C Master aack error!\n");
		}
		else
		{
			for(i=0;i<len;i++)
			{
				*(buf+i) = i2c_master_rec(i,len);
			}
		}
	}

	I2C_CR &= ~CR_MSMOD;
	while(I2C_CSR&SR_BBUSY);		//busy bit clear indicate STOP finish
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_m_readdata_int
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c master reads data in interrupt mode.
//
// Input:
//    	slave_addr
//		buf
//		len
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_m_readdata_int(UINT8 slave_addr,UINT8* buf,UINT16 len)
{

	g_data_receive = buf;
	g_data_len = len;

	//send slave addr
	I2C_CDR = slave_addr|0x01;
	I2C_CR |= CR_MSMOD;
	while((I2C_CSR&SR_RC) == 0);

	while(1)
	{
		if(g_complete == 0xff)
		{
			g_len_receive =0;
			g_complete =0;
			break;
		}
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_s_trans_data
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c slave sends or receives data in polling mode.
//
// Input:
//    	r_buf
//		r_len
//		s_buf
//		s_len
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_s_trans_data(UINT8* r_buf,UINT16 r_len,UINT8* s_buf,UINT16 s_len)
{
	UINT32 i=0;
	VUINT8 status =0xff;

	while((I2C_CSR & SR_AASLV) != SR_AASLV){i2c_status =0xff;}

	if((I2C_SHSIR&SLV_HS) ==SLV_HS)
	{
		I2C_SSHTR =0x00;
		I2C_SHSIR |=SLV_HS;
	}
	else
	{
		status =I2C_CSR;

		if((status & SR_AASLV) == SR_AASLV)		//从模式
		{
			if((status & SR_RXTX) != SR_RXTX)  //接收模式
			{
				for(i=0;i<r_len;)
				{
					while((I2C_CSR & SR_RC) != SR_RC);

					if((I2C_CSR & SR_TF) == SR_TF) // data complete
					{
						*(r_buf+i) = I2C_CDR;
						I2C_CR |= CR_ACKEN;

						i++;
					}
					else //address complete
					{
						I2C_CR |= CR_ACKEN;
					}
				}
			}
			else //发送模式
			{
				while((I2C_CSR & SR_TF) != SR_TF);

				for(i=0;i<s_len;i++)
				{
					if(i!=(s_len-1))
					{
						I2C_CDR =*(s_buf+i);
						while((I2C_CSR & SR_TF) != SR_TF);
					}
					else
					{
						I2C_CDR =*(s_buf+i);
					}
				}
			}
		}
	}

	i2c_status =0xff;

	while(I2C_CSR&SR_BBUSY);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_s_trans_data_int
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    i2c slave sends or receives data in interrupt mode.
//
// Input:
//    	r_buf
//		r_len
//		s_buf
//		s_len
//
// Output:
//      None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void i2c_s_trans_data_int(UINT8* r_buf,UINT16 r_len,UINT8* s_buf,UINT16 s_len)
{

	g_data_send = s_buf;
	g_data_receive = r_buf;

	while(1)
	{
		if(r_len==g_len_receive)
		{
			g_len_receive=0x0;

			break;
		}

		if(s_len==g_len_send)
		{
			g_len_send=0x0;

			break;
		}

	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_pin_config
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    config i2c pins as gpio.
//
// Input:
//		pin
//		dir
//
// Output:
//      true or false
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL i2c_pin_config(UINT8 pin, UINT8 dir)
{
	I2C_PCR |= 0xc0;//config gpio

	if (dir == GPIO_OUTPUT)
	{
		I2C_DDR |= (1<<pin);//output
	}
	else if (dir == GPIO_INPUT)
	{
		I2C_DDR &= (~(1<<pin));//input
	}
	else
	{
		return FALSE;
	}

	return	TRUE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_pin_read
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    read i2c pins status as gpio.
//
// Input:
//		pin
//
// Output:
//      Bit_SET or Bit_RESET
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UINT8 i2c_pin_read(UINT8 pin)
{
	UINT8 bitstatus = 0x00;

	bitstatus = I2C_PDR;
	if (bitstatus &(Bit_SET<<pin))
		bitstatus = Bit_SET;
	else
		bitstatus = Bit_RESET;

	return bitstatus;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 i2c_pin_write
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    read i2c pins status as gpio.
//
// Input:
//		pin
//		val
//
// Output:
//      TRUE or FALSE
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL i2c_pin_write(UINT8 pin, UINT8 val)
{
	if (val == Bit_SET)
		I2C_PDR |= (Bit_SET<<pin);
	else
		I2C_PDR &= (~(Bit_SET<<pin));

	return TRUE;
}
