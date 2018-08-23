// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : usi_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#ifndef __USI_DRV_H__
#define __USI_DRV_H__

#define SW_SUCCESS							(UINT16)0x9000
#define SW_NULL								(UINT8)0x60
//#define SW_MEMORY_VERIFY_ERROR				(UINT16)0x6581
#define SW_FLASH_ERASE_ERROR				(UINT16)0x6581
#define SW_FLASH_PROGRAM_ERROR				(UINT16)0x6582
#define SW_WRONG_LENGTH						(UINT16)0x6700
#define SW_WRONG_DATA						(UINT16)0x6A80
#define SW_WRONG_P1P2						(UINT16)0x6A86
#define SW_INS_NOT_SUPPORTED				(UINT16)0x6D00
#define SW_UNKNOWN							(UINT16)0x6F00

#define SW_SECURITY_STATUS_NOT_SATISFIED	(UINT16)0x6982
#define SW_CONDITIONS_NOT_SATISFIED			(UINT16)0x6985
#define SW_FUNC_NOT_SUPPORTED				(UINT16)0x6A81
#define SW_CLA_NOT_SUPPORTED				(UINT16)0x6E00
#define SW_WARNING_61						(UINT16)0x6100
#define SW_WARNING_63						(UINT16)0x6300
#define SW_WARNING_67						(UINT16)0x6700
#define SW_WARNING_6C						(UINT16)0x6C00

#define SW61_GET_RESPONSE					(UINT16)0x6100

#define	APDU_CMD_LEN		5

#define	APDU_STATE_IDLE		0
#define	APDU_STATE_PPS		1
#define	APDU_STATE_CMD		2
#define	APDU_STATE_DATA		3

#define	APDU_STATE_PPS_OK	4
#define	APDU_STATE_CMD_OK	5
#define	APDU_STATE_DATA_OK	6

#define	APDU_STATE_ATR		7

#define USI1_INT_NUM        0x2D
#define USI2_INT_NUM        0x37
#define USI3_INT_NUM        0x3A

extern UINT8 adpu_status;
extern UINT8 *apdu_buf;
extern UINT8 *apdu_data;
extern UINT8 apdu_cmdbuf[];
extern UINT8 apdu_cnt;
extern UINT16 apdu_datalen;
extern UINT32 apdu_addr;
extern UINT16 result_code;
extern UINT16 response_len;
extern UINT16 apdu_offset;

extern void usi_isr(void);
extern void usi_interrput_init();
extern void usi_apdu_init();

extern void usi_en_wto(void);
extern void usi_dis_wto(void);
extern void usi_send_le_data(void);
extern void usi_send_pb (UINT8 val);
extern void usi_send_status(void);

extern void usi_gpioconfig(UINT8 pcr, UINT8 ddr);
extern void usi_gpiovalu(UINT8 ucval, BOOL ben);
extern BOOL usi_readiodata();

extern BOOL usi_pin_config(UINT8 ucid, UINT8 pin, UINT8 dir);
extern UINT8 usi_pin_read(UINT8 ucid, UINT8 pin);
extern BOOL usi_pin_write(UINT8 ucid, UINT8 pin, UINT8 val);

#endif /* __USI_DRV_H__ */
