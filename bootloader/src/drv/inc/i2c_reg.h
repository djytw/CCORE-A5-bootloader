// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : i2c_reg.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __I2C_REG_H__
#define __I2C_REG_H__

#define I2C_SAR		    (*(volatile UINT8 *)(I2C_BASE+0x0))
#define I2C_CR		    (*(volatile UINT8 *)(I2C_BASE+0x1))
#define I2C_CPR		    (*(volatile UINT8 *)(I2C_BASE+0x2))
#define I2C_CSR		    (*(volatile UINT8 *)(I2C_BASE+0x3))
#define I2C_CDR		    (*(volatile UINT8 *)(I2C_BASE+0x4))
#define I2C_SSHTR	    (*(volatile UINT8 *)(I2C_BASE+0x5))
#define I2C_SHSIR	    (*(volatile UINT8 *)(I2C_BASE+0x6))

#define I2C_PCR		    (*(volatile UINT8 *)(I2C_BASE+0x7))
#define I2C_PDR		    (*(volatile UINT8 *)(I2C_BASE+0x8))
#define I2C_DDR		    (*(volatile UINT8 *)(I2C_BASE+0x9))
#define I2C_FCTR		(*(volatile UINT8 *)(I2C_BASE+0xa))
#define I2C_10NSFTVR	(*(volatile UINT8 *)(I2C_BASE+0xb))
#define I2C_50NSFTVR	(*(volatile UINT8 *)(I2C_BASE+0xc))

#define CR_EN		0x01
#define CR_IEN		0x02
#define CR_MSMOD	0x04
#define CR_ACKEN	0x08
#define CR_REPSTA	0x10
#define CR_AMIE		0x20
#define CR_HMSEN	0x20

#define SR_TF		0x01
#define SR_RC		0x02
#define SR_AASLV	0x04
#define SR_BBUSY	0x08
#define SR_ARBL		0x10
#define SR_RXTX		0x20
#define SR_DACK		0x40
#define SR_AACK		0x80

#define SLV_HS      0x01

#define I2C_SLAVE_ADDR 	        0x30
#define I2C_MASTER_ADDR 		0x02

#define SDA_OPEN_DRAIN_OUTPUT  do{I2C_PCR |= 0x40;}while(0)
#define SDA_COMOS_OUTPUT       do{I2C_PCR &= 0xBF;}while(0)
#define SDA_PULLUP_EN          do{I2C_PCR |= 0x02;}while(0)
#define SDA_PULLUP_DIS         do{I2C_PCR &= 0xFD;}while(0)
#define SDA_PULLDOWN_EN        do{;}while(0)
#define SDA_PULLDOWN_DIS       do{;}while(0)

#define SCL_OPEN_DRAIN_OUTPUT  do{I2C_PCR |= 0x10;}while(0)
#define SCL_COMOS_OUTPUT       do{I2C_PCR &= 0xEF;}while(0)
#define SCL_PULLUP_EN          do{I2C_PCR |= 0x01;}while(0)
#define SCL_PULLUP_DIS         do{I2C_PCR &= 0xFE;}while(0)
#define SCL_PULLDOWN_EN        do{;}while(0)
#define SCL_PULLDOWN_DIS       do{;}while(0)


//I2C device Status
#define I2C_OK					0
#define I2C_ENODEV				2

#define I2C_INPUT    0
#define I2C_OUTPUT   1

#define I2C_MASTER_MODE		1
#define I2C_SLAVE_MODE		0

#define I2C_INT_MODE		1
#define I2C_POLL_MODE		0

#define I2C_MASTER_DEVICE	1
#define I2C_SLAVE_DEVICE	0

/*
typedef enum
{
    I2C_SCL,
    I2C_SDA,
}I2C_NO;
*/

#endif /* __I2C_REG_H__ */
