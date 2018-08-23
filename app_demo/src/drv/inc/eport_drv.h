// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : eport_drv.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __EPORT_DRV_H__
#define __EPORT_DRV_H__

#define EPORT0_ISR_NUM				0x25
#define EPORT1_ISR_NUM				0x26
#define EPORT2_ISR_NUM				0x27
#define EPORT3_ISR_NUM				0x28
#define EPORT4_ISR_NUM				0x29
#define EPORT5_ISR_NUM				0x2a
#define EPORT6_ISR_NUM				0x2b
#define EPORT7_ISR_NUM				0x2c

#define EPORT_PIN0					0
#define EPORT_PIN1					1
#define EPORT_PIN2					2
#define EPORT_PIN3					3
#define EPORT_PIN4					4
#define EPORT_PIN5					5
#define EPORT_PIN6					6
#define EPORT_PIN7					7

#define EPORT_INPUT					0
#define EPROT_OUTPUT				1

typedef enum
{
    LOW_LEVEL_INT = 0,
    HIGH_LEVEL_INT,
    RISING_EDGE_INT,
    FALLING_EDGE_INT,
    RISING_FALLING_EDGE_INT,
}EPORT_INT_MODE;

extern void eport0_isr(void);
extern void eport1_isr(void);
extern void eport2_isr(void);
extern void eport3_isr(void);
extern void eport4_isr(void);
extern void eport5_isr(void);
extern void eport6_isr(void);
extern void eport7_isr(void);

extern void eport_make_dir(UINT8 eport_no, UINT8 dir);
extern void eport_write_val(UINT8 eport_no, UINT8 val);
extern UINT8 eport_read_val(UINT8 eport_no);

extern void eport_config_isrtype(UINT8 eport_no, EPORT_INT_MODE int_mode);
extern void eport_int_enable(UINT8 eport_no);
extern void eport_int_disable(UINT8 eport_no);
extern void eport_pullup_enable(UINT8 eport_no);
extern void eport_pullup_disable(UINT8 eport_no);

extern void eport_init_int(UINT8 eport_no);
extern void eport_init(void);

#endif /* __EPORT_DRV_H__ */
