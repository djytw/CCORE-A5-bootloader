// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : alg_api.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "alg_api.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sm4_ecb_encrypt_decrypt
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    sm4 ecb encrypt or decrypt
//
// Input:
//    en_de_mode, EncryptDecrypt mode, should be ALG_ENCRYPT or ALG_DECRYPT
//    key, KEY address
//    iv, IV(Initial Vector) address
//    data_in, input data address
//    data_out, output data buffer address
//    datalen, data length
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ALG_STATUS sm4_ecb_encrypt_decrypt(ALG_EN_DE_MODE en_de_mode,UINT8 *key,UINT8 *src,UINT8 *dest,UINT32 datalen)
{
	UINT32 key_buf[4];

	if((en_de_mode != ALG_ENCRYPT)
	 &&(en_de_mode != ALG_DECRYPT))
	{
		return ERROR_ENDE_MODE;
	}

	if((datalen&0x0F)||(datalen == 0))     //不是16的整数倍
	{
		return ERROR_DATA_LENGTH;
	}

	if((key == NULL)||(src == NULL)||(dest == NULL))
	{
		return ERROR_DATA_BUF;
	}
	memcpy((UINT8 *)key_buf,key,16);
	//module enable
	cpm_arith_enable(ARITH_SMS4);

	sm4_en_de_crypt(en_de_mode,
					ALG_ECB,
					ALG_COFBIT_DUMMY,
					(UINT32 *)src,
					(UINT32 *)dest,
					datalen,
					key_buf,
					NULL,
					0,     //false
					0,     //false
					1      //true
					);

	cpm_arith_disable(ARITH_SMS4);
	return SUCCESS_ALG;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sm4_cbc_encrypt_decrypt
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    sm4 cbc encrypt or decrypt
//
// Input:
//    en_de_mode, EncryptDecrypt mode, should be ALG_ENCRYPT or ALG_DECRYPT
//    key, KEY address
//    iv, IV(Initial Vector) address
//    data_in, input data address
//    data_out, output data buffer address
//    datalen, data length
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ALG_STATUS sm4_cbc_encrypt_decrypt(ALG_EN_DE_MODE en_de_mode,UINT8 *key,UINT8 *iv,UINT8 *src,UINT8 *dest,UINT32 datalen)
{
	UINT32 key_buf[4],iv_buf[4];

	if((en_de_mode != ALG_ENCRYPT)
	 &&(en_de_mode != ALG_DECRYPT))
	{
		return ERROR_ENDE_MODE;
	}

	if((datalen&0x0F)||(datalen == 0))     //不是16的整数倍
	{
		return ERROR_DATA_LENGTH;
	}

	if((key == NULL)||(src == NULL)||(dest == NULL)||(iv == NULL))
	{
		return ERROR_DATA_BUF;
	}

	memcpy((UINT8 *)key_buf,key,16);
	memcpy((UINT8 *)iv_buf,iv,16);
	//module enable
	cpm_arith_enable(ARITH_SMS4 );

	sm4_en_de_crypt(en_de_mode,
					ALG_CBC,
					ALG_COFBIT_DUMMY,
					(UINT32 *)src,
					(UINT32 *)dest,
					datalen,
					key_buf,
					iv_buf,
					0,   //false
					0,   //false
					1    //true
					);

	cpm_arith_disable(ARITH_SMS4 );
	return SUCCESS_ALG;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 des_ecb_encrypt_decrypt
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    des ecb encrypt or decrypt
//
// Input:
//    en_de_mode, EncryptDecrypt mode, should be ALG_ENCRYPT or ALG_DECRYPT
//    key_mode, key bits width, should be ALG_KEY64, ALG_KEY128 or ALG_KEY192
//    key, KEY address
//    src, input data address
//    dest, output data buffer address
//    datalen, data length
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ALG_STATUS des_ecb_encrypt_decrypt(ALG_EN_DE_MODE en_de_mode,ALG_KEY_BITS key_mode,UINT8 *key,UINT8 *src,UINT8 *dest,UINT32 datalen)
{
	UINT32 key_buf[6];

	if((key_mode != ALG_KEY64)
	 &&(key_mode != ALG_KEY128)
	 &&(key_mode!= ALG_KEY192))
	{
		return ERROR_KEY_LENGTH;
	}
	if((en_de_mode != ALG_ENCRYPT)
	 &&(en_de_mode != ALG_DECRYPT))
	{
		return ERROR_ENDE_MODE;
	}

	if((datalen&7)||(datalen == 0))     //不是8的整数倍
	{
		return ERROR_DATA_LENGTH;
	}

	if((key == NULL)||(src == NULL)||(dest == NULL))
	{
		return ERROR_DATA_BUF;
	}
	memcpy((UINT8 *)key_buf,key,key_mode == ALG_KEY64?8:(key_mode == ALG_KEY128?16:24));

	cpm_arith_enable(ARITH_DES3);
	des_en_de_crypt(en_de_mode,
			        key_mode,
			        ALG_ECB,
			        (UINT32 *)src,
			        (UINT32 *)dest,
			        datalen,
				    key_buf,
				    NULL,
				    0,   //false
					0,   //false
					1    //true
					);

	cpm_arith_disable(ARITH_DES3);
	return SUCCESS_ALG;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 des_cbc_encrypt_decrypt
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    des cbc encrypt or decrypt
//
// Input:
//    en_de_mode, EncryptDecrypt mode, should be ALG_ENCRYPT or ALG_DECRYPT
//    key_mode, key bits width, should be ALG_KEY64, ALG_KEY128 or ALG_KEY192
//    key, KEY address
//    iv, IV(Initial Vector) address
//    data_in, input data address
//    data_out, output data buffer address
//    datalen, data length
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ALG_STATUS des_cbc_encrypt_decrypt(ALG_EN_DE_MODE en_de_mode,ALG_KEY_BITS key_mode,UINT8 *key,UINT8 *iv,UINT8 *src,UINT8 *dest,	UINT32 datalen)
{
	UINT32 key_buf[6];
	UINT32 iv_buf[2];

	if((key_mode != ALG_KEY64)
	 &&(key_mode != ALG_KEY128)
	 &&(key_mode!= ALG_KEY192))
	{
		return ERROR_KEY_LENGTH;
	}

	if((en_de_mode != ALG_ENCRYPT)
	 &&(en_de_mode != ALG_DECRYPT))
	{
		return ERROR_ENDE_MODE;
	}

	if((datalen&7)||(datalen == 0))     //不是8的整数倍
	{
		return ERROR_DATA_LENGTH;
	}

	if((key == NULL)||(src == NULL)||(dest == NULL)||(iv == NULL))
	{
		return ERROR_DATA_BUF;
	}
	memcpy((UINT8 *)key_buf,key,key_mode == ALG_KEY64?8:(key_mode == ALG_KEY128?16:24));
	memcpy((UINT8 *)iv_buf,iv,8);
	
	cpm_arith_enable(ARITH_DES3 );
	des_en_de_crypt(en_de_mode,
			        key_mode,
			        ALG_CBC,
			        (UINT32 *)src,
			        (UINT32 *)dest,
			        datalen,
				    key_buf,
				    iv_buf,
				    0,   //false
					0,   //false
					1    //true
					);

	cpm_arith_disable(ARITH_DES3 );
	return SUCCESS_ALG;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 aes_ecb_encrypt_decrypt
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    aes ecb encrypt or decrypt
//
// Input:
//    en_de_mode, EncryptDecrypt mode, should be ALG_ENCRYPT or ALG_DECRYPT
//    key_mode, key bits width, should be ALG_KEY128, ALG_KEY192 or ALG_KEY256
//    key, KEY address
//    data_in, input data address
//    data_out, output data buffer address
//    datalen, data length
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ALG_STATUS aes_ecb_encrypt_decrypt(ALG_EN_DE_MODE en_de_mode,ALG_KEY_BITS key_mode,UINT8 *key,UINT8 *src,UINT8 *dest,UINT32 datalen)
{
	UINT32 key_buf[8];

	if((key_mode != ALG_KEY128)
	 &&(key_mode != ALG_KEY192)
	 &&(key_mode != ALG_KEY256))
	{
		return ERROR_KEY_LENGTH;
	}

	if((en_de_mode != ALG_ENCRYPT)
	 &&(en_de_mode != ALG_DECRYPT))
	{
		return ERROR_ENDE_MODE;
	}

	if((datalen&0x0f)||(datalen == 0))    //不是8的整数倍
	{
		return ERROR_DATA_LENGTH;
	}

	if((key == NULL)||(src == NULL)||(dest == NULL))
	{
		return ERROR_DATA_BUF;
	}
	memcpy((UINT8 *)key_buf,key,key_mode == ALG_KEY128?16:(key_mode == ALG_KEY192?24:32));

	cpm_arith_enable(ARITH_AES );
	aes_en_de_crypt(en_de_mode,
					key_mode,
					ALG_ECB,
					(UINT32 *)src,
					(UINT32 *)dest,
					datalen,
					key_buf,
					NULL,
					0,    //false
					1     //true
					);
	cpm_arith_disable(ARITH_AES );
	return SUCCESS_ALG;
}

ALG_STATUS aes_cbc_encrypt_decrypt(ALG_EN_DE_MODE en_de_mode,ALG_KEY_BITS key_mode,UINT8 *key,UINT8 *iv,UINT8 *src,UINT8 *dest,UINT32 datalen)
{

	UINT32 key_buf[8];
	UINT32 i, j;
	UINT32 crypto[4];		        //CBC模式临时缓冲区
	UINT32 algorithm_buf[4];		//CBC模式临时缓冲区

	if((key_mode != ALG_KEY128)
	 &&(key_mode != ALG_KEY192)
	 &&(key_mode != ALG_KEY256))
	{
		return ERROR_KEY_LENGTH;
	}

	if((en_de_mode != ALG_ENCRYPT)
	 &&(en_de_mode != ALG_DECRYPT))
	{
		return ERROR_ENDE_MODE;
	}

	if((datalen&0x0f)||(datalen == 0))    //不是8的整数倍
	{
		return ERROR_DATA_LENGTH;
	}

	if((key == NULL)||(src == NULL)||(dest == NULL)||(iv == NULL))
	{
		return ERROR_DATA_BUF;
	}

	memcpy((UINT8 *)key_buf,key,key_mode == ALG_KEY128?16:(key_mode == ALG_KEY192?24:32));
	memcpy((UINT8 *)crypto,iv,16);

	cpm_arith_enable(ARITH_AES );
	if(en_de_mode == ALG_ENCRYPT)
	{
		for(i=0;i<datalen;i+=16)
		{
			memcpy((UINT8 *)algorithm_buf,src+i,16);
			for(j=0;j<4;j++)
			{
				algorithm_buf[j] ^= crypto[j];
			}
			aes_en_de_crypt(ALG_ENCRYPT,
							key_mode,
							ALG_ECB,
							(UINT32 *)(algorithm_buf),
							(UINT32 *)(dest+i),
							16,
							key_buf,
							NULL,
							0,      //false
							1       //true
							);
			memcpy((UINT8 *)crypto,dest+i,16);
		}
	}
	else
	{
		for(i=0;i<datalen;i+=16)
		{
			aes_en_de_crypt(ALG_DECRYPT,
							key_mode,
							ALG_ECB,
							(UINT32 *)(src+i),
							algorithm_buf,
							16,
							key_buf,
							NULL,
							0,      //false
							1       //true
							);
			for(j=0;j<4;j++)
			{
				algorithm_buf[j] ^= crypto[j];
			}
			memcpy(dest+i,(UINT8 *)algorithm_buf,16);
			memcpy((UINT8 *)crypto,src+i,16);
		}
	}
	cpm_arith_disable(ARITH_AES );
	return SUCCESS_ALG;
}

ALG_STATUS hash_init(HASH_MODE hashType)
{
	if((hashType != MODE_SM3)
	 &&(hashType != MODE_SHA0)
	 &&(hashType != MODE_SHA1)
	 &&(hashType != MODE_SHA224)
	 &&(hashType != MODE_SHA256)
	 &&(hashType != MODE_SHA384)
	 &&(hashType != MODE_SHA512))
	{
		return ERROR_OTHER_PARA;
	}

	sha_init(hashType);
	return SUCCESS_ALG;
}


ALG_STATUS hash_update(UINT8 *pMessageBlock,UINT32 len)
{
	if((len == 0)||(len > 512))
	{
		return ERROR_DATA_LENGTH;
	}
	if(pMessageBlock == NULL)
	{
		return ERROR_DATA_BUF;
	}
	sha_update((UINT32)pMessageBlock,len);
	return SUCCESS_ALG;
}

ALG_STATUS hash_dofinal(HASH_MODE hashType,UINT8 *result)
{
	UINT32 hash_result[16];
	UINT32 hash_len = 0;

	if((hashType != MODE_SM3)
	 &&(hashType != MODE_SHA0)
	 &&(hashType != MODE_SHA1)
	 &&(hashType != MODE_SHA224)
	 &&(hashType != MODE_SHA256)
	 &&(hashType != MODE_SHA384)
	 &&(hashType != MODE_SHA512))
	{
		return ERROR_OTHER_PARA;
	}
	if(result == NULL)
	{
		return ERROR_DATA_BUF;
	}
	sha_final(hash_result);

	if(hashType == MODE_SHA0)
	{
		hash_len = 20;
	}
	else if(hashType == MODE_SHA1)
	{
		hash_len = 20;
	}
	else if(hashType == MODE_SHA224)
	{
		hash_len = 28;
	}
	else if(hashType == MODE_SHA384)
	{
		hash_len = 48;
	}
	else if(hashType == MODE_SHA512)
	{
		hash_len = 64;
	}
	else
	{
		hash_len = 32;
	}
	memcpy(result,(UINT8 *)hash_result,hash_len);

	return SUCCESS_ALG;
}


ALG_STATUS rsa_generate_key(UINT8 fixkey,UINT32 bits,RSA_publicKey *pubkey,RSA_privateKey *prikey)
{

	if((fixkey != 0)&&(fixkey != 1))
	{
		return ERROR_OTHER_PARA;
	}

	if((bits <512)||(bits >2048))
	{
		return ERROR_OTHER_PARA;
	}

	if(bits &0x3F)
	{
		return ERROR_OTHER_PARA;
	}

	if((pubkey == NULL)||(prikey == NULL))
	{
		return ERROR_DATA_BUF;
	}
	if((pubkey->pE == NULL)||(pubkey->pN == NULL)
	 ||(prikey->pN == NULL)||(prikey->pD == NULL)
	 ||(prikey->pP == NULL)||(prikey->pQ == NULL)
	 ||(prikey->pDP == NULL)||(prikey->pDQ == NULL)
	 ||(prikey->pQINV == NULL))
	{
		return ERROR_DATA_BUF;
	}
	memset((UINT8 *)&stu_rsa_pubkey,0x00,sizeof(STU_RSA_PUBKEY));
	memset((UINT8 *)&stu_rsa_prikey,0x00,sizeof(STU_RSA_PRIVKEY));


	cpm_arith_enable(ARITH_CRYPTO);
	rsa_generate_key_pair(bits,&stu_rsa_pubkey,&stu_rsa_prikey,fixkey,1); //采用CRT格式存储密钥
	cpm_arith_disable(ARITH_CRYPTO);;

	/*私钥*/
	prikey->bits = bits;
	u32_2_u8(stu_rsa_prikey.modulus,bits>>5,prikey->pN);              //n
	u32_2_u8(stu_rsa_prikey.exponent,bits>>5,prikey->pD);             //d

	u32_2_u8(stu_rsa_prikey.prime[0],bits>>6,prikey->pP);             //p
	u32_2_u8(stu_rsa_prikey.prime[1],bits>>6,prikey->pQ);             //q
	u32_2_u8(stu_rsa_prikey.primeExponent[0],bits>>6,prikey->pDP);    //dp
	u32_2_u8(stu_rsa_prikey.primeExponent[1],bits>>6,prikey->pDQ);    //dq
	u32_2_u8(stu_rsa_prikey.coefficient,bits>>6,prikey->pQINV);       //pq
	/*公钥*/
	pubkey->bits = bits;
	memcpy(pubkey->pN,prikey->pN,bits>>3);
	if(fixkey == 0)
	{
		u32_2_u8(stu_rsa_pubkey.exponent,bits>>5,pubkey->pE);         //E
		pubkey->ExpLen = bits>>3;
	}
	else
	{
		pubkey->pE[0] = 0x01;
		pubkey->pE[1] = 0x00;
		pubkey->pE[2] = 0x01;
		pubkey->ExpLen = 3;
	}
	return SUCCESS_ALG;
}


ALG_STATUS rsa_privateKey_operation(UINT8 mode,	RSA_privateKey *prikey,UINT8 *src,UINT8 *dest,UINT32 inLen,UINT32 *outLen)
{
	UINT32          in[0x40];
	UINT32          out[0x40];
	UINT32          len;
	int             result;

	if(mode & 0xFE)
	{
		return ERROR_OTHER_PARA;
	}

	if((inLen < 0x40)||(inLen >0x100)||(inLen &0x03))
	{
		return ERROR_DATA_LENGTH;
	}

	if((prikey == NULL)||(src == NULL) ||(dest == NULL))
	{
		return ERROR_DATA_BUF;
	}
	if(mode == 0)  //非CRT模式
	{
		if((prikey->pN == NULL)||(prikey->pD == NULL))
		{
			return ERROR_DATA_BUF;
		}
	}
	else
	{
		if((prikey->pP == NULL)||(prikey->pQ == NULL)
		 ||(prikey->pDP == NULL)||(prikey->pDQ == NULL)
		 ||(prikey->pQINV == NULL))
		{
			return ERROR_DATA_BUF;
		}
	}

	if((prikey->bits == 0)||((prikey->bits & 0x3F)!= 0))
	{
		return ERROR_OTHER_PARA;
	}


	u8_2_u32(src,inLen,in);  //src

	memset((UINT8 *)&stu_rsa_prikey,0x00,sizeof(STU_RSA_PRIVKEY));
	stu_rsa_prikey.bits = prikey->bits;
	cpm_arith_enable(ARITH_CRYPTO );
	if(mode == 0)  //非CRT模式
	{
		u8_2_u32(prikey->pN,prikey->bits>>3,stu_rsa_prikey.modulus);  //n
		u8_2_u32(prikey->pD,prikey->bits>>3,stu_rsa_prikey.exponent); //d
		result = rsa_priv_key(out,&len,in,inLen>>2,&stu_rsa_prikey);
	}
	else
	{
		//注意： CRT模式，这里要置成全FF
		memset(stu_rsa_prikey.modulus,0xFF,sizeof(stu_rsa_prikey.modulus));
		u8_2_u32(prikey->pP,prikey->bits>>4,stu_rsa_prikey.prime[0]); //p
		u8_2_u32(prikey->pQ,prikey->bits>>4,stu_rsa_prikey.prime[1]); //q
		u8_2_u32(prikey->pDP,prikey->bits>>4,stu_rsa_prikey.primeExponent[0]); //dp
		u8_2_u32(prikey->pDQ,prikey->bits>>4,stu_rsa_prikey.primeExponent[1]); //dq
		u8_2_u32(prikey->pQINV,prikey->bits>>4,stu_rsa_prikey.coefficient); //pq

		result = rsa_priv_key_CRT(out,&len,in,inLen>>2,&stu_rsa_prikey);
	}
	cpm_arith_disable(ARITH_CRYPTO );
	if(result)
	{
		return FAIL_ALG;
	}
	*outLen = u32_2_u8(out,inLen>>2,dest);
	return SUCCESS_ALG;
}

ALG_STATUS rsa_publicKey_operation(UINT8 fixkey,RSA_publicKey *pubkey,UINT8 *src,UINT8 *dest,UINT32 inLen,UINT32 *outLen)
{
	UINT32         in[0x40];
	UINT32         out[0x40];
	UINT32         len;
	int            result;

	if(fixkey &0xFE)
	{
		return ERROR_OTHER_PARA;
	}

	if((inLen <0X40)||(inLen >0x100)||(inLen &0x03))
	{
		return ERROR_DATA_LENGTH;
	}

	if((src == NULL)||(dest == NULL)||(pubkey == NULL))
	{
		return ERROR_DATA_BUF;
	}
	if((pubkey->pN == NULL)||(pubkey->pE == NULL))
	{
		return ERROR_DATA_BUF;
	}
	if(pubkey->ExpLen == 0)
	{
		return ERROR_DATA_LENGTH;
	}
	if((pubkey->bits == 0)||((pubkey->bits&0x3F) != 0))
	{
		return ERROR_OTHER_PARA;
	}
	u8_2_u32(src,inLen,in);  //src

	memset((UINT8 *)&stu_rsa_pubkey,0x00,sizeof(STU_RSA_PUBKEY));

	stu_rsa_pubkey.bits = pubkey->bits;
	u8_2_u32(pubkey->pE,pubkey->ExpLen,stu_rsa_pubkey.exponent);   //E
	u8_2_u32(pubkey->pN,pubkey->bits>>3,stu_rsa_pubkey.modulus);   //N

	cpm_arith_enable(ARITH_CRYPTO );
	result = rsa_pub_key(out,&len,in,inLen>>2,&stu_rsa_pubkey);
	cpm_arith_disable(ARITH_CRYPTO );
	if(result)
	{
		return FAIL_ALG;
	}
	*outLen =u32_2_u8(out,inLen>>2,dest);
	return SUCCESS_ALG;
}

ALG_STATUS sm2_init(UINT16 nbits)
{
	UINT8 databuf[64];

	if(nbits != 256)
	{
		return ERROR_OTHER_PARA;
	}
	stu_sm2_prams.uBits = nbits;

	//初始化ECC参数
	EccBig32Initial(&(stu_sm2_prams.stuPrimeP));
	EccBig32Initial(&(stu_sm2_prams.stuCoefficientA));
	EccBig32Initial(&(stu_sm2_prams.stuCoefficientB));
	EccBig32Initial(&(stu_sm2_prams.stuGx));
	EccBig32Initial(&(stu_sm2_prams.stuGy));
	EccBig32Initial(&(stu_sm2_prams.stuPrimeN));
	EccBig32Initial(&(stu_sm2_prikey));
	EccBig32Initial(&(stu_sm2_pubkey.stuQx));
	EccBig32Initial(&(stu_sm2_pubkey.stuQy));
	EccBig32Initial(&stu_sm2_signature_r);
	EccBig32Initial(&stu_sm2_signature_s);
	EccCharToHex((UINT8*)charGx,databuf,stu_sm2_prams.uBits/4);
	EccByBufToBigInt32(databuf,stu_sm2_prams.uBits/8,&(stu_sm2_prams.stuGx));

	EccCharToHex((UINT8*)charGy,databuf,stu_sm2_prams.uBits/4);
	EccByBufToBigInt32(databuf,stu_sm2_prams.uBits/8,&(stu_sm2_prams.stuGy));

	EccCharToHex((UINT8*)charPrimeN,databuf,stu_sm2_prams.uBits/4);
	EccByBufToBigInt32(databuf,stu_sm2_prams.uBits/8,&(stu_sm2_prams.stuPrimeN));

	EccCharToHex((UINT8*)charPrimeP,databuf,stu_sm2_prams.uBits/4);
	EccByBufToBigInt32(databuf,stu_sm2_prams.uBits/8,&(stu_sm2_prams.stuPrimeP));

	EccCharToHex((UINT8*)charCoefficientA,databuf,stu_sm2_prams.uBits/4);
	EccByBufToBigInt32(databuf,stu_sm2_prams.uBits/8,&(stu_sm2_prams.stuCoefficientA));

	EccCharToHex((UINT8*)charCoefficientB,databuf,stu_sm2_prams.uBits/4);
	EccByBufToBigInt32(databuf,stu_sm2_prams.uBits/8,&(stu_sm2_prams.stuCoefficientB));
	return SUCCESS_ALG;
}

ALG_STATUS sm2_generate_keypair(UINT8  *pubkey,UINT8  *prvkey)
{
	if((pubkey == NULL)||(prvkey == NULL))
	{
		return ERROR_DATA_BUF;
	}

	cpm_arith_enable(ARITH_CRYPTO );
	sm2_generate_key_pair(&stu_sm2_prams,&stu_sm2_prikey,&stu_sm2_pubkey);
	cpm_arith_disable(ARITH_CRYPTO );

	u32_2_u8(stu_sm2_prikey.auValue,8,prvkey);
	u32_2_u8(stu_sm2_pubkey.stuQx.auValue,8,pubkey);
	u32_2_u8(stu_sm2_pubkey.stuQy.auValue,8,pubkey+32);
	return SUCCESS_ALG;
}

ALG_STATUS sm2_encrypt(UINT8 *pubkey,UINT8 *Message,UINT32 MessageLen,UINT8 *Crypto,UINT32 *CryptoLen)
{
	if((MessageLen == 0)||(MessageLen > 0x400))
	{
		return ERROR_DATA_LENGTH;
	}
	if((pubkey == NULL)||(Message == NULL)||(Crypto == NULL))
	{
		return ERROR_DATA_BUF;
	}

	stu_sm2_pubkey.stuQx.uLen = 8;
	stu_sm2_pubkey.stuQy.uLen = 8;

	u8_2_u32(pubkey,32,stu_sm2_pubkey.stuQx.auValue);
	u8_2_u32(pubkey+32,32,stu_sm2_pubkey.stuQy.auValue);

	cpm_arith_enable(ARITH_CRYPTO );
	sm2_encrypt_V2(Message,MessageLen,&stu_sm2_pubkey,&stu_sm2_prams,Crypto);
	cpm_arith_disable(ARITH_CRYPTO );
	
	*CryptoLen = MessageLen+96;
	return SUCCESS_ALG;
}


ALG_STATUS sm2_decrypt(UINT8 *prvkey,UINT8 *Crypto,UINT32 CryptoLen,UINT8 *Message,UINT32 *MessageLen)
{
	if((CryptoLen > 0x460)||(CryptoLen < 0x60))
	{
		return ERROR_DATA_LENGTH;
	}
	if((prvkey == NULL)||(Crypto == NULL)||(Message == NULL))
	{
		return ERROR_DATA_BUF;
	}

	stu_sm2_prikey.uLen = 8;
	u8_2_u32(prvkey,32,stu_sm2_prikey.auValue);

	cpm_arith_enable(ARITH_CRYPTO );
	sm2_decrypt_V2(Crypto,CryptoLen-0X60,&stu_sm2_prikey,&stu_sm2_prams,Message);
	cpm_arith_disable(ARITH_CRYPTO );

	*MessageLen = CryptoLen-0X60;
	return SUCCESS_ALG;
}


ALG_STATUS sm2_generate_e(UINT8 *pubkey,UINT8 *ID,UINT32 IDLen,UINT8 *Message,UINT32 MessageLen,UINT8 *result_E)
{
	UINT32         za[8];
	UINT32         block,offset;

	if((MessageLen == 0)||(IDLen == 0))
	{
		return ERROR_DATA_LENGTH;
	}
	if((ID == NULL)||(Message == NULL)||(pubkey == NULL)||(result_E == NULL))
	{
		return ERROR_DATA_BUF;
	}

	stu_sm2_pubkey.stuQx.uLen = 8;
	stu_sm2_pubkey.stuQy.uLen = 8;

	u8_2_u32(pubkey,32,stu_sm2_pubkey.stuQx.auValue);
	u8_2_u32(pubkey+32,32,stu_sm2_pubkey.stuQy.auValue);

	cpm_arith_enable(ARITH_CRYPTO);
	sign(ID,IDLen,&stu_sm2_pubkey,&stu_sm2_prams,za);
	cpm_arith_disable(ARITH_CRYPTO);

	hash_init(MODE_SM3);
	hash_update((UINT8 *)za,32);
	offset = 0;
	while(offset < MessageLen)
	{
		block = (MessageLen>512?512:MessageLen);
		hash_update((Message+offset),block);
		offset += block;
	}
	hash_dofinal(MODE_SM3,result_E);

	return SUCCESS_ALG;
}

ALG_STATUS sm2_sign(UINT8 *prvkey,UINT8 *e,UINT8 *signature)
{
	UINT32 message[8];
	if((prvkey == NULL)||(e == NULL)||(signature == NULL))
	{
		return ERROR_DATA_BUF;
	}

	stu_sm2_prikey.uLen = 8;

	u8_2_u32(prvkey,32,stu_sm2_prikey.auValue);
	memcpy((UINT8 *)message,e,32);
	swap_word(message,message,8);

	cpm_arith_enable(ARITH_CRYPTO );
	sm2_signature((UINT8 *)message,32,&stu_sm2_prams,&stu_sm2_prikey,&stu_sm2_signature_r,&stu_sm2_signature_s);
	cpm_arith_disable(ARITH_CRYPTO );

	u32_2_u8(stu_sm2_signature_r.auValue,8,signature);
	u32_2_u8(stu_sm2_signature_s.auValue,8,signature+32);
	return SUCCESS_ALG;
}

ALG_STATUS sm2_verify(UINT8 *pubkey,UINT8 *e,UINT8 *signature)
{
	UINT8 result;
	UINT32 message[8];

	if((pubkey == NULL)||(e == NULL)||(signature == NULL))
	{
		return ERROR_DATA_BUF;
	}

	memcpy((UINT8 *)message,e,32);
	swap_word(message,message,8);

	stu_sm2_pubkey.stuQx.uLen = 8;
	stu_sm2_pubkey.stuQy.uLen = 8;

	u8_2_u32(pubkey,32,stu_sm2_pubkey.stuQx.auValue);
	u8_2_u32(pubkey+32,32,stu_sm2_pubkey.stuQy.auValue);

	stu_sm2_signature_r.uLen = 8;
	stu_sm2_signature_s.uLen = 8;

	u8_2_u32(signature,32,stu_sm2_signature_r.auValue);
	u8_2_u32(signature+32,32,stu_sm2_signature_s.auValue);

	cpm_arith_enable(ARITH_CRYPTO );
	result = sm2_verification((UINT8 *)message,32,&stu_sm2_prams,&stu_sm2_pubkey,&stu_sm2_signature_r,&stu_sm2_signature_s);
	cpm_arith_disable(ARITH_CRYPTO );


	if(result == 0)
	{
		return FAIL_ALG;
	}
	return SUCCESS_ALG;
}

ALG_STATUS sm2_generate_z(UINT8 *pubkey,UINT8 *IDA,	UINT32 IDA_length,UINT8 *result_Z)
{
	if(IDA_length == 0)
	{
		return ERROR_DATA_LENGTH;
	}

	if((IDA == NULL)||(pubkey == NULL)||(result_Z == NULL))
	{
		return ERROR_DATA_BUF;
	}

	stu_sm2_pubkey.stuQx.uLen = 8;
	stu_sm2_pubkey.stuQy.uLen = 8;

	u8_2_u32(pubkey,32,stu_sm2_pubkey.stuQx.auValue);
	u8_2_u32(pubkey+32,32,stu_sm2_pubkey.stuQy.auValue);


	cpm_arith_enable(ARITH_CRYPTO );
	sign(IDA,IDA_length,&stu_sm2_pubkey,&stu_sm2_prams,(UINT32 *)result_Z);
	cpm_arith_disable(ARITH_CRYPTO );


	return SUCCESS_ALG;
}


ALG_STATUS sm2_key_exchange(
	UINT8  			*s_prvkey,                     //己方私钥
	UINT8  			*s_tempPubkey,                 //己方临时公钥
	UINT8  			*s_tempPrvkey,                 //己方临时私钥
	UINT8  			*o_pubkey,                     //对方公钥
	UINT8  			*o_tempPubkey,                 //对方临时公钥
	UINT8           *za,                           //己方Z值
	UINT8           *zb,                           //对方Z值
	UINT8 			*agreedKey,                    //协商密钥
	UINT32 			 agreedKeyLen,
	UINT8           *sA,
	UINT8           *sB,
	UINT8            mode                           //己方或对方
)
{
	SM2_STU_PUBKEY   self_temp_pubkey;
	SM2_STU_PRVKEY   self_prvkey;
	SM2_STU_PRVKEY   self_temp_prvkey;

	SM2_STU_PUBKEY   other_pubkey;
	SM2_STU_PUBKEY   other_temp_pubkey;
	UINT8            result;

	if((s_prvkey == NULL)||(s_tempPrvkey == NULL)||(s_tempPubkey == NULL)
	 ||(o_pubkey == NULL)||(o_tempPubkey == NULL)||(za == NULL)||(zb == NULL)
	 ||(agreedKey == NULL)||(sA == NULL)||(sB == NULL))
	{
		return ERROR_DATA_BUF;
	}
	if(mode & 0xFE)
	{
		return ERROR_OTHER_PARA;
	}

	if(agreedKeyLen > 32)
	{
		return ERROR_DATA_LENGTH;
	}

	EccBig32Initial(&self_temp_pubkey.stuQx);
	EccBig32Initial(&self_temp_pubkey.stuQy);
	EccBig32Initial(&self_prvkey);
	EccBig32Initial(&self_temp_prvkey);
	EccBig32Initial(&other_pubkey.stuQx);
	EccBig32Initial(&other_pubkey.stuQy);
	EccBig32Initial(&other_temp_pubkey.stuQx);
	EccBig32Initial(&other_temp_pubkey.stuQy);

	self_prvkey.uLen = 8;
	u8_2_u32(s_prvkey,32,self_prvkey.auValue);

	self_temp_prvkey.uLen = 8;
	u8_2_u32(s_tempPrvkey,32,self_temp_prvkey.auValue);

	self_temp_pubkey.stuQx.uLen = 8;
	self_temp_pubkey.stuQy.uLen = 8;
	u8_2_u32(s_tempPubkey,32,self_temp_pubkey.stuQx.auValue);
	u8_2_u32(s_tempPubkey+32,32,self_temp_pubkey.stuQy.auValue);


	other_pubkey.stuQx.uLen = 8;
	other_pubkey.stuQy.uLen = 8;
	u8_2_u32(o_pubkey,32,other_pubkey.stuQx.auValue);
	u8_2_u32(o_pubkey+32,32,other_pubkey.stuQy.auValue);

	other_temp_pubkey.stuQx.uLen = 8;
	other_temp_pubkey.stuQy.uLen = 8;
	u8_2_u32(o_tempPubkey,32,other_temp_pubkey.stuQx.auValue);
	u8_2_u32(o_tempPubkey+32,32,other_temp_pubkey.stuQy.auValue);

	cpm_arith_enable(ARITH_CRYPTO );
	W32(0x63F20000,0x80000010);

	result = SM2_KeyExchange_HT(&stu_sm2_prams,              // ECC上下文
							    &self_prvkey,              // 己方私钥
							    &self_temp_pubkey,         // 己方临时公钥。
							    &self_temp_prvkey,         // 己方临时私钥。
							    &other_pubkey,             // 对方公钥
							    &other_temp_pubkey,        // 对方临时公钥。
							    (UINT32 *)za,              // 己方Z值
							    (UINT32 *)zb,              // 对方Z值
							    (UINT32 *)agreedKey,       // 协商密钥。
							    agreedKeyLen,              // 协商密钥长度
							    (UINT32 *)sA,              // SA（或S2）。
							    (UINT32 *)sB,              // SB（或S1）。
							    mode);                     // 0表示己方为A方，1表示己方为B方
	cpm_arith_disable(ARITH_CRYPTO );

	if(result == 0)
	{
		return FAIL_ALG;
	}
	return SUCCESS_ALG;
}

