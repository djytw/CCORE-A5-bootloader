// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : alg_api.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __ALG_API_H__
#define __ALG_API_H__
#include "includes.h"
#include "alg_drv.h"

//////////////////////////////////////////////////////////////
//		arith EDMA (used by all algorithm)
//////////////////////////////////////////////////////////////
void arith_edma_enable(void);
void arith_edma_disable(void);


//////////////////////////////////////////////////////////////
//		SM4
//////////////////////////////////////////////////////////////
ALG_STATUS sm4_ecb_encrypt_decrypt(
		ALG_EN_DE_MODE en_de_mode,
		UINT8 *key,
		UINT8 *src,
		UINT8 *dest,
		UINT32 datalen);

ALG_STATUS sm4_cbc_encrypt_decrypt(
		ALG_EN_DE_MODE en_de_mode,
		UINT8 *key,
		UINT8 *iv,
		UINT8 *src,
		UINT8 *dest,
		UINT32 datalen);

//////////////////////////////////////////////////////////////
//		DES
//////////////////////////////////////////////////////////////

ALG_STATUS des_ecb_encrypt_decrypt(
		ALG_EN_DE_MODE en_de_mode,
		ALG_KEY_BITS key_mode,
		UINT8 *key,
		UINT8 *src,
		UINT8 *dest,
		UINT32 datalen);

ALG_STATUS des_cbc_encrypt_decrypt(
		ALG_EN_DE_MODE en_de_mode,
		ALG_KEY_BITS key_mode,
		UINT8 *key,
		UINT8 *iv,
		UINT8 *src,
		UINT8 *dest,
		UINT32 datalen);


//////////////////////////////////////////////////////////////
//		AES
//////////////////////////////////////////////////////////////
ALG_STATUS aes_ecb_encrypt_decrypt(
		ALG_EN_DE_MODE en_de_mode,
		ALG_KEY_BITS key_mode,
		UINT8 *key,
		UINT8 *src,
		UINT8 *dest,
		UINT32 datalen);

ALG_STATUS aes_cbc_encrypt_decrypt(
		ALG_EN_DE_MODE en_de_mode,
		ALG_KEY_BITS key_mode,
		UINT8 *key,
		UINT8 *iv,
		UINT8 *src,
		UINT8 *dest,
		UINT32 datalen);


//////////////////////////////////////////////////////////////
//		SM3 (SHA)
//////////////////////////////////////////////////////////////
ALG_STATUS hash_init(HASH_MODE hashType);
ALG_STATUS hash_update(UINT8 *pMessageBlock,UINT32 len);
ALG_STATUS hash_dofinal(HASH_MODE hashType,UINT8 *result);


//////////////////////////////////////////////////////////////
//		SM2
//////////////////////////////////////////////////////////////
ALG_STATUS sm2_init(UINT16 nbits);

ALG_STATUS sm2_generate_keypair(
UINT8  *pubkey,                               //公钥
UINT8  *prvkey                                //私钥
);

ALG_STATUS sm2_encrypt(
UINT8  		   *pubkey,                       //公钥
UINT8          *Message,                      //明文数据地址
UINT32          MessageLen,                   //明文数据长度
UINT8           *Crypto,                      //密文数据地址
UINT32          *CryptoLen                    //密文数据长度
);

ALG_STATUS sm2_decrypt(
UINT8  			*prvkey,                       //私钥
UINT8           *Crypto,                       //密文数据地址
UINT32           CryptoLen,                    //密文数据长度
UINT8           *Message,                      //明文数据地址
UINT32          *MessageLen                    //明文数据长度
);


ALG_STATUS sm2_generate_e(
UINT8 			*pubkey,                       //公钥
UINT8           *ID,
UINT32           IDLen,
UINT8           *message,
UINT32           MessageLen,
UINT8           *result_E
);

ALG_STATUS sm2_sign(
	UINT8  		*pubkey,                       //公钥
	UINT8  		*e,                            //被签名数据的摘要值，32字节
	UINT8  		*signature		               //签名值64字节
);

ALG_STATUS sm2_verify(
	UINT8  		*pubkey,                       //公钥
	UINT8  		*e,                            //被签名数据的摘要值，32字节
	UINT8  		*signature		               //签名值64字节
);


ALG_STATUS sm2_generate_z(
	UINT8  			*pubkey,                     //公钥
	UINT8           *IDA,                        //id
	UINT32           IDA_length,                 //id长度
	UINT8           *result_Z                    //用户信息
);

ALG_STATUS sm2_key_exchange(
	UINT8  			*s_prvkey,                     //己方私钥
	UINT8  			*s_tempPubkey,                 //己方临时公钥
	UINT8  			*s_tempPrikey,                 //己方临时私钥
	UINT8  			*o_pubkey,                     //对方公钥
	UINT8  			*o_tempPubkey,                 //对方临时公钥
	UINT8           *za,                           //己方Z值
	UINT8           *zb,                           //对方Z值
	UINT8 			*agreedKey,                    //协商密钥
	UINT32 			 agreedKeyLen,
	UINT8           *sA,
	UINT8           *sB,
	UINT8            mode                           //己方或对方
);
//////////////////////////////////////////////////////////////
//		RSA
//////////////////////////////////////////////////////////////

typedef struct {
    unsigned int bits;       /* length in bits of modulus */
    unsigned char *pN;       /* modulus */
    unsigned char *pE;       /* public exponent */
    unsigned int ExpLen;     /* exponent bytes */
}RSA_publicKey;

typedef struct {
    unsigned int   bits;       /* length in bits of modulus */
    unsigned char *pN;         /* modulus */
    unsigned char *pD;         /* private exponent */
    unsigned char *pP;         /* prime factors, p */
    unsigned char *pQ;         /* prime factors, q */
	unsigned char *pDP;        /* CRT exponent dP */
	unsigned char *pDQ;        /* CRT exponent dQ */
	unsigned char *pQINV;      /* CRT coefficient qInv */
}RSA_privateKey;


ALG_STATUS rsa_generate_key(
	UINT8            fixkey,                      //是否固定公钥标志位
	UINT32           bits,                        //RSA算法运算bit大小
	RSA_publicKey   *pubkey,                      //RSA公钥
	RSA_privateKey  *prikey                       //RSA私钥
);

ALG_STATUS rsa_privateKey_operation(
	UINT8            mode,                        //CRT模式或非CRT模式
	RSA_privateKey  *prikey,                      //RSA私钥
	UINT8           *src,                         //数据源地址
	UINT8           *dest,                        //数据目的地址
	UINT32           inLen,                       //源数据长度
	UINT32          *outLen                       //目的数据长度
);

ALG_STATUS rsa_publicKey_operation(
	UINT8           fixkey,                      //是否固定公钥标志位
	RSA_publicKey  *pubkey,                      //RSA公钥
	UINT8          *src,                         //数据源地址
	UINT8          *dest,                        //数据目的地址
	UINT32          inLen,                       //源数据长度
	UINT32         *outLen                       //目的数据长度
);

#endif /* __ALG_API_H__ */
