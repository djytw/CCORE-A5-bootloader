// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : alg_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __ALG_DRV_H__
#define __ALG_DRV_H__
#include "cpm_drv.h"


/* RSA key lengths. */
#define MIN_RSA_MODULUS_BITS 508
#define MAX_RSA_MODULUS_BITS 2048
#define MAX_RSA_MODULUS_LEN ((MAX_RSA_MODULUS_BITS + 31) / 32)
#define MAX_RSA_PRIME_BITS	((MAX_RSA_MODULUS_BITS + 1) / 2)
#define MAX_RSA_PRIME_LEN	((MAX_RSA_PRIME_BITS   + 31) / 32)

/*SM2 key length*/
#define	PK	2048
#define	CK	2144 //2048 + 256/8 + 256/8 + 256/8
#define ECC_BIGINT32_MAXLEN 	12

// 公钥
typedef struct {
	UINT32 bits;								/* length in bits of modulus */
	UINT32 modulus[MAX_RSA_MODULUS_LEN];		/* modulus */
	UINT32 exponent[MAX_RSA_MODULUS_LEN]; 		/* public exponent */
} STU_RSA_PUBKEY;

// 私钥
typedef struct {
	UINT32 bits;								/* length in bits of modulus */
	UINT32 modulus[MAX_RSA_MODULUS_LEN];		/* modulus */
	UINT32 publicExponent[MAX_RSA_MODULUS_LEN];	/* public exponent */
	UINT32 exponent[MAX_RSA_MODULUS_LEN];		/* private exponent */
	UINT32 prime[2][MAX_RSA_PRIME_LEN];			/* prime factors, p, q */
	UINT32 primeExponent[2][MAX_RSA_PRIME_LEN];	/* exponents for CRT */
	UINT32 coefficient[MAX_RSA_PRIME_LEN];		/* CRT coefficient, inv */
} STU_RSA_PRIVKEY;


//定义大数的32位数组结构
//auValue数组的低32位地址存放大数的低32位有效数，高32位地址存放大数的高32位有效数
typedef struct
{
 	UINT16   uLen;							//32位数组的实际长度
	UINT32   auValue[ECC_BIGINT32_MAXLEN];	//32位数组的值
}ECC_STU_BIGINT32;

//定义ECC参数的格式
typedef struct
{
    UINT16 uBits;							// 模数P的位数
	ECC_STU_BIGINT32  stuPrimeP;			// 模数P
	ECC_STU_BIGINT32  stuCoefficientA;		// 椭圆系数A
	ECC_STU_BIGINT32  stuCoefficientB;		// 椭圆系数B
	ECC_STU_BIGINT32  stuGx;				// 椭圆基点坐标Gx
	ECC_STU_BIGINT32  stuGy;				// 椭圆基点坐标Gy
	ECC_STU_BIGINT32  stuPrimeN;			// 椭圆基点坐标G的阶
} SM2_STU_PRAMS;

//定义ECC公钥的格式
typedef struct
{
	ECC_STU_BIGINT32  stuQx;				// 公钥坐标Qx
	ECC_STU_BIGINT32  stuQy;				// 公钥坐标Qy
} SM2_STU_PUBKEY;

typedef ECC_STU_BIGINT32   SM2_STU_PRVKEY;
typedef enum{
	ALG_ENCRYPT = 0,
	ALG_DECRYPT = 1
} ALG_EN_DE_MODE;

typedef enum{
	ALG_ECB,
	ALG_CBC,
	ALG_CTR,
	ALG_CFB,
	ALG_OFB
} ALG_OP_MODE;

typedef enum{
	ALG_KEY64 = 64,
	ALG_KEY128 = 128,
	ALG_KEY192 = 192,
	ALG_KEY256 = 256,
	ALG_KEY384 = 384,
	ALG_KEY512 = 512,
	ALG_KEY1024 = 1024,
	ALG_KEY2048 = 2048
} ALG_KEY_BITS;

typedef enum{
	ALG_COFBIT_DUMMY = 0,	/* for other modes, except CFB, OFB */
	ALG_COFBIT01 = 1,
	ALG_COFBIT08 = 8,
	ALG_COFBIT16 = 16,
	ALG_COFBIT32 = 32,
	ALG_COFBIT64 = 64
} ALG_COFBITS;

typedef enum{
	ALG_SK_INTERNAL = 0,
	ALG_SK_EXTERNAL = 1
} ALG_SK_MODE;

typedef enum{
	MODE_SM3 = 0x00,
	MODE_SHA0 = 0x10,
	MODE_SHA1 = 0x20,
	MODE_SHA224 = 0x30,
	MODE_SHA256 = 0x40,
	MODE_SHA384 = 0x50,
	MODE_SHA512 = 0x60
} HASH_MODE;

typedef enum
{
	SUCCESS_ALG          =  1,
	FAIL_ALG             =  0,
	ERROR_DATA_LENGTH    = -1,
	ERROR_KEY_LENGTH     = -2,
	ERROR_KEY_MODE       = -3,
	ERROR_ENDE_MODE      = -4,
	ERROR_ECBCBC_MODE    = -5,
	ERROR_DATA_BUF       = -6,
	ERROR_OTHER_PARA     = -7,
}ALG_STATUS;

extern SM2_STU_PRAMS    stu_sm2_prams;
extern SM2_STU_PUBKEY   stu_sm2_pubkey;
extern SM2_STU_PRVKEY   stu_sm2_prikey;
extern ECC_STU_BIGINT32 stu_sm2_signature_r;
extern ECC_STU_BIGINT32 stu_sm2_signature_s;

extern STU_RSA_PUBKEY  stu_rsa_pubkey;
extern STU_RSA_PRIVKEY stu_rsa_prikey;

extern const UINT8 charGx[];
extern const UINT8 charGy[];
extern const UINT8 charPrimeN[];
extern const UINT8 charPrimeP[];
extern const UINT8 charCoefficientA[];
extern const UINT8 charCoefficientB[];


//SM2 Functions
UINT8 sm2_generate_key_pair(SM2_STU_PRAMS *pstuEccPrams,ECC_STU_BIGINT32 *pstuPrivKey,SM2_STU_PUBKEY *pstuPubKey);
void sm2_encrypt_V2(UINT8 *mes,UINT16 klen,SM2_STU_PUBKEY *pstuPubKey,SM2_STU_PRAMS *pstuEccPrams,UINT8 *cipher);
UINT8 sm2_decrypt_V2(UINT8 *cipher,UINT16 klen,ECC_STU_BIGINT32 *stuPrivKey,SM2_STU_PRAMS *pstuEccPrams,UINT8 *plain);
void sm2_signature(UINT8 *mes,UINT16 klen,SM2_STU_PRAMS *pstuEccPrams,ECC_STU_BIGINT32 *pstuPrivKey,ECC_STU_BIGINT32 *pSignatureR,ECC_STU_BIGINT32 *pSignatureS);
UINT8 sm2_verification(UINT8 *mes,UINT16 klen,SM2_STU_PRAMS *pstuEccPrams,SM2_STU_PUBKEY *pstuPubKey,ECC_STU_BIGINT32 *pSignatureR,ECC_STU_BIGINT32 *pSignatureS);
void sm2_signature_with_IDA(UINT8 *mes,UINT16 klen,UINT8 *IDA,UINT16 entla,SM2_STU_PRAMS *pstuEccPrams,SM2_STU_PUBKEY *pstuPubKey,ECC_STU_BIGINT32 *pstuPrivKey,ECC_STU_BIGINT32 *pSignatureR,ECC_STU_BIGINT32 *pSignatureS);
UINT8 sm2_verification_with_IDA(UINT8 *mes,UINT16 klen,UINT8 *IDA,UINT16 entla,SM2_STU_PRAMS *pstuEccPrams,SM2_STU_PUBKEY *pstuPubKey,ECC_STU_BIGINT32 *pSignatureR,ECC_STU_BIGINT32 *pSignatureS);
void sign(unsigned char *IDA,unsigned short entla,SM2_STU_PUBKEY *pstuPubKey,SM2_STU_PRAMS *pstuEccPrams,unsigned int *za);
UINT8 TestKeyChange(ECC_STU_BIGINT32 *pstuPrivKey_A,SM2_STU_PUBKEY *pstuPubKey_A,ECC_STU_BIGINT32 *pstuPrivKey_B,SM2_STU_PUBKEY *pstuPubKey_B,SM2_STU_PRAMS *pstuEccPrams,unsigned int *za,unsigned int *zb);
void SM2GenerateRA(SM2_STU_PRAMS *pstuEccPrams,ECC_STU_BIGINT32 *RA_x1,ECC_STU_BIGINT32 *RA_y1,ECC_STU_BIGINT32 *rA);
void SM2GenerateRBKB(SM2_STU_PRAMS *pstuEccPrams,SM2_STU_PUBKEY *pstuPubKey_A,ECC_STU_BIGINT32 *pstuPrivKey_B, unsigned int *sB,unsigned int *s2,unsigned int *za,unsigned int *zb,ECC_STU_BIGINT32 *RA_x1,ECC_STU_BIGINT32 *RA_y1,ECC_STU_BIGINT32 *RB_x2,ECC_STU_BIGINT32 *RB_y2,unsigned int *kB);
UINT8 SM2GenerateKA(SM2_STU_PRAMS *pstuEccPrams,SM2_STU_PUBKEY *pstuPubKey_B,ECC_STU_BIGINT32 *pstuPrivKey_A,unsigned int *za,unsigned int *zb,ECC_STU_BIGINT32 *rA,unsigned int *sB,unsigned int *sA,ECC_STU_BIGINT32 *RA_x1,ECC_STU_BIGINT32 *RA_y1,ECC_STU_BIGINT32 *RB_x2,ECC_STU_BIGINT32 *RB_y2,unsigned int *kA);
UINT8 SM2VerifySA(unsigned int *s2, unsigned int * sA,SM2_STU_PRAMS *pstuEccPrams);
UINT8 AB_Check(unsigned int *s1, unsigned int * sB, unsigned int * sA, unsigned int * s2,SM2_STU_PRAMS *pstuEccPrams);
UINT8 SM2_KeyExchange_HT(SM2_STU_PRAMS *pstuEccPrams,  // ECC上下文
                       ECC_STU_BIGINT32 *pSelfPrikey,   // 己方私钥
                       SM2_STU_PUBKEY *pSelfTempPubkey, // 己方临时公钥。
                       ECC_STU_BIGINT32 *pSelfTempPrikey,   // 己方临时私钥。
                       SM2_STU_PUBKEY *pOtherPubkey,      // 对方公钥
                       SM2_STU_PUBKEY *pOtherTempPubkey,  // 对方临时公钥。
                       UINT32 *za,            // 己方Z值
                       UINT32 *zb,           // 对方Z值
                       UINT32 *pAgreedKey,        // 协商密钥。
        	           UINT32 AgreedKeyLen,       // 协商密钥长度
            	       UINT32 *sA,               // SA（或S2）。
                	   UINT32 *sB,               // SB（或S1）。
                       UINT32 Mode);              // 0表示己方为A方，1表示己方为B方
void EccPointMul(ECC_STU_BIGINT32 *pStuK,ECC_STU_BIGINT32 *pPointAx,ECC_STU_BIGINT32 *pPointAy,ECC_STU_BIGINT32 *pPointBx,ECC_STU_BIGINT32 *pPointBy,SM2_STU_PRAMS *pstuEccPrams);
void EccBig32Initial(void *);
void EccCharToHex(UINT8 *, UINT8 *, UINT16 );
void EccByBufToBigInt32(UINT8 *, UINT16 , void *);

/*hash*/
void sha_enable(void);
void sha_disable(void);
void sha_init(HASH_MODE mode);
void sha_update(UINT32 src_addr,UINT32 len);
void sha_final(UINT32* pout);
void sha_resume(HASH_MODE mode, UINT32 *deal_len, UINT32 *mid_res);
void sha_read_mid_data(UINT32 *deal_len, UINT32 *mid_res);
void sha_get_hash(HASH_MODE mode, UINT8* src, UINT32 len, UINT32* res);

/*rsa*/
UINT8 rsa_generate_key_pair( UINT32 rsa_bits, STU_RSA_PUBKEY * pub_key, STU_RSA_PRIVKEY * prv_key, UINT8 fixkey, UINT8 crt);
int rsa_pub_key(UINT32 *output, UINT32 *output_len,UINT32 *input,UINT32  input_len, STU_RSA_PUBKEY *pub_key);
int rsa_priv_key(UINT32 *output, UINT32 *output_len,UINT32 *input, UINT32 input_len,STU_RSA_PRIVKEY * prv_key);
int rsa_priv_key_CRT(UINT32 *output, UINT32 *output_len,UINT32 *input, UINT32 input_len,STU_RSA_PRIVKEY * prv_key);

/*aes*/
void release_alg_mem(void);
void aes_init(UINT32 csr);
void aes_set_key(UINT32 *key, UINT32 key_mode);
void aes_set_cnt(UINT32* cnt);
void aes_en_de_crypt(ALG_EN_DE_MODE en_de_mode, ALG_KEY_BITS key_mode, ALG_OP_MODE sel_mode,
					UINT32 *data_in, UINT32 *data_out, int length,
					UINT32 *key, UINT32 *cnt, BOOL bDPA, BOOL bUseEdma);
/*des*/
void des_en_de_crypt(ALG_EN_DE_MODE en_de_mode, ALG_KEY_BITS key_mode, ALG_OP_MODE sel_mode,
					UINT32 *data_in, UINT32 *data_out, UINT32 length,
					UINT32 *key, UINT32 *iv, BOOL bVDES, BOOL bDisturb, BOOL bEdma);
/*sm4*/
void sm4_init(UINT32 sms4_csr);
void sm4_set_key(UINT32 *key);
void sm4_set_iv(UINT32 *iv);
void sm4_en_de_crypt(ALG_EN_DE_MODE en_de_mode, ALG_OP_MODE sel_mode, ALG_COFBITS cofbits,
					UINT32 *data_in, UINT32 *data_out, UINT32 length,
					UINT32 *key, UINT32 *iv, BOOL bVSM4, BOOL bDisturb, BOOL bUseEdma);


extern unsigned int u32_2_u8(unsigned int *src,unsigned int inlen,unsigned char *dest);
extern unsigned int u8_2_u32(unsigned char *src,unsigned int inlen,unsigned int *dest);
extern void swap_word(unsigned int *dest, unsigned int *src, unsigned int wordLen);
#endif /* __ALG_DRV_H__ */
