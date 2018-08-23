/*
 * drv.c
 *
 *  Created on: 2017年11月15日
 *      Author: YangWenfeng
 */
#include "alg_drv.h"


SM2_STU_PRAMS    stu_sm2_prams;
SM2_STU_PUBKEY   stu_sm2_pubkey;
SM2_STU_PRVKEY   stu_sm2_prikey;
ECC_STU_BIGINT32 stu_sm2_signature_r;
ECC_STU_BIGINT32 stu_sm2_signature_s;

STU_RSA_PUBKEY  stu_rsa_pubkey;
STU_RSA_PRIVKEY stu_rsa_prikey;

const UINT8 charGx[]           = "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7";
const UINT8 charGy[]           = "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0";
const UINT8 charPrimeN[]       = "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123";
const UINT8 charPrimeP[]       = "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF";
const UINT8 charCoefficientA[] = "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC";
const UINT8 charCoefficientB[] = "28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93";

void arith_edma_enable(void)
{
	cpm_arith_enable(ARITH_ENCR_A);
}


void arith_edma_disable(void)
{
	;
}

//小端(以字为单位)转大端模式,u32 转  u8
unsigned int u32_2_u8(unsigned int *src,unsigned int inlen,unsigned char *dest)
{
	unsigned short j;
	unsigned char *p = (unsigned char*)src;

	if(!inlen) return 0;

	for(j = 0x0;j < inlen;j++)
	{
		dest[j*4]   = p[(inlen-j)*4-1];
		dest[j*4+1] = p[(inlen-j)*4-2];
		dest[j*4+2] = p[(inlen-j)*4-3];
		dest[j*4+3] = p[(inlen-j)*4-4];
	}
	return (inlen<<2);
}

//大端转小端(以字为单位)模式,u8 转  u32
unsigned int u8_2_u32(unsigned char *src,unsigned int inlen,unsigned int *dest)
{
	unsigned int end_index,i;
	unsigned int temp;

	if(inlen < 4) return 0;
	//计算末尾位置
	end_index = inlen>>2;
	if(inlen & 3)
	{
		end_index++;
	}

	for(i = 0x0;i < end_index;i++)
	{
		temp = ((unsigned int)src[i*4]<<24)|((unsigned int)src[i*4+1]<<16)|((unsigned int)src[i*4+2]<<8)|(unsigned int)src[i*4+3];
		dest[end_index-1-i] = temp;
	}
	return end_index;
}

//len为字长度，以字为单位整体翻转，字内不变
void swap_word(unsigned int *dest, unsigned int *src, unsigned int wordLen)
{
	unsigned int i;
	unsigned int temp;

	//输入输出使用同一个BUF
	if (src == dest)
	{
		for (i=0; i<wordLen/2; i++)
		{
			temp = dest[i];
			dest[i] = src[wordLen-1-i];
			dest[wordLen-1-i] = temp;
		}
	}
	else
	{
		for (i=0; i<wordLen; i++)
		{
			dest[i] = src[wordLen-1-i];
		}
	}
}
