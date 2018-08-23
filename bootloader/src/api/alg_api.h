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
UINT8  *pubkey,                               //��Կ
UINT8  *prvkey                                //˽Կ
);

ALG_STATUS sm2_encrypt(
UINT8  		   *pubkey,                       //��Կ
UINT8          *Message,                      //�������ݵ�ַ
UINT32          MessageLen,                   //�������ݳ���
UINT8           *Crypto,                      //�������ݵ�ַ
UINT32          *CryptoLen                    //�������ݳ���
);

ALG_STATUS sm2_decrypt(
UINT8  			*prvkey,                       //˽Կ
UINT8           *Crypto,                       //�������ݵ�ַ
UINT32           CryptoLen,                    //�������ݳ���
UINT8           *Message,                      //�������ݵ�ַ
UINT32          *MessageLen                    //�������ݳ���
);


ALG_STATUS sm2_generate_e(
UINT8 			*pubkey,                       //��Կ
UINT8           *ID,
UINT32           IDLen,
UINT8           *message,
UINT32           MessageLen,
UINT8           *result_E
);

ALG_STATUS sm2_sign(
	UINT8  		*pubkey,                       //��Կ
	UINT8  		*e,                            //��ǩ�����ݵ�ժҪֵ��32�ֽ�
	UINT8  		*signature		               //ǩ��ֵ64�ֽ�
);

ALG_STATUS sm2_verify(
	UINT8  		*pubkey,                       //��Կ
	UINT8  		*e,                            //��ǩ�����ݵ�ժҪֵ��32�ֽ�
	UINT8  		*signature		               //ǩ��ֵ64�ֽ�
);


ALG_STATUS sm2_generate_z(
	UINT8  			*pubkey,                     //��Կ
	UINT8           *IDA,                        //id
	UINT32           IDA_length,                 //id����
	UINT8           *result_Z                    //�û���Ϣ
);

ALG_STATUS sm2_key_exchange(
	UINT8  			*s_prvkey,                     //����˽Կ
	UINT8  			*s_tempPubkey,                 //������ʱ��Կ
	UINT8  			*s_tempPrikey,                 //������ʱ˽Կ
	UINT8  			*o_pubkey,                     //�Է���Կ
	UINT8  			*o_tempPubkey,                 //�Է���ʱ��Կ
	UINT8           *za,                           //����Zֵ
	UINT8           *zb,                           //�Է�Zֵ
	UINT8 			*agreedKey,                    //Э����Կ
	UINT32 			 agreedKeyLen,
	UINT8           *sA,
	UINT8           *sB,
	UINT8            mode                           //������Է�
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
	UINT8            fixkey,                      //�Ƿ�̶���Կ��־λ
	UINT32           bits,                        //RSA�㷨����bit��С
	RSA_publicKey   *pubkey,                      //RSA��Կ
	RSA_privateKey  *prikey                       //RSA˽Կ
);

ALG_STATUS rsa_privateKey_operation(
	UINT8            mode,                        //CRTģʽ���CRTģʽ
	RSA_privateKey  *prikey,                      //RSA˽Կ
	UINT8           *src,                         //����Դ��ַ
	UINT8           *dest,                        //����Ŀ�ĵ�ַ
	UINT32           inLen,                       //Դ���ݳ���
	UINT32          *outLen                       //Ŀ�����ݳ���
);

ALG_STATUS rsa_publicKey_operation(
	UINT8           fixkey,                      //�Ƿ�̶���Կ��־λ
	RSA_publicKey  *pubkey,                      //RSA��Կ
	UINT8          *src,                         //����Դ��ַ
	UINT8          *dest,                        //����Ŀ�ĵ�ַ
	UINT32          inLen,                       //Դ���ݳ���
	UINT32         *outLen                       //Ŀ�����ݳ���
);

#endif /* __ALG_API_H__ */
