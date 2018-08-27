// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : type.h
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef __TYPES_H__
#define __TYPES_H__


// strongly recommend using these types
typedef void                             VOID;
typedef          unsigned      char      BYTE;
typedef          unsigned      char      BOOL;
typedef          unsigned      char      STATUS;
                 
typedef          unsigned      char      UINT8;
typedef          signed        char      INT8;
typedef          unsigned      short     UINT16;
typedef          signed        short     INT16;
typedef          unsigned      int       UINT32;
typedef          signed        int       INT32;

typedef          unsigned long long      UINT64;
typedef          signed   long long      INT64;
typedef float                            FP32;
typedef double                           FP64;


//modified by djytw

typedef UINT8 uint8_t;
typedef UINT16 uint16_t;
typedef UINT32 uint32_t;

typedef UINT8 u8;
typedef UINT16 u16;
typedef UINT32 u32;

typedef	volatile unsigned      char      VUINT8;
typedef	volatile signed        char      VINT8;
typedef	volatile unsigned      short     VUINT16;
typedef	volatile signed        short     VINT16;
typedef volatile unsigned      int       VUINT32;
typedef	volatile signed        int       VINT32;

typedef volatile unsigned long long      VUINT64;
typedef volatile signed   long long      VINT64;

//typedef          unsigned      long      UINT32;
//typedef          signed        long      INT32;
//typedef volatile unsigned      long      VUINT32;
//typedef volatile signed        long      VINT32;

#define GPIO_INPUT    0
#define GPIO_OUTPUT   1

/* Bit_SET and Bit_RESET enumeration -----------------------------------------*/
typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;

#define TRUE          0
#define FALSE         1

#define BIT0          (1<<0)
#define BIT1          (1<<1)
#define BIT2          (1<<2)
#define BIT3          (1<<3)
#define BIT4          (1<<4)
#define BIT5          (1<<5)
#define BIT6          (1<<6)
#define BIT7          (1<<7)
#define BIT8          (1<<8)
#define BIT9          (1<<9)
#define BIT11         (1<<11)


#define _U	          0x01	/* upper */
#define _L	          0x02	/* lower */
#define _D	          0x04	/* digit */
#define _C	          0x08	/* cntrl */
#define _P	          0x10	/* punct */
#define _S	          0x20	/* white space (space/lf/tab) */
#define _X	          0x40	/* hex digit */
#define _SP	          0x80	/* hard space (0x20) */

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

#define isalnum(c)    ((_ctype+1)[c]&(_U|_L|_D))
#define isalpha(c)    ((_ctype+1)[c]&(_U|_L))
#define iscntrl(c)    ((_ctype+1)[c]&(_C))
#define isdigit(c)    ((_ctype+1)[c]&(_D))
#define isgraph(c)    ((_ctype+1)[c]&(_P|_U|_L|_D))
#define islower(c)    ((_ctype+1)[c]&(_L))
#define isprint(c)    ((_ctype+1)[c]&(_P|_U|_L|_D|_SP))
#define ispunct(c)    ((_ctype+1)[c]&(_P))
#define isspace(c)    ((_ctype+1)[c]&(_S))
#define isupper(c)    ((_ctype+1)[c]&(_U))
#define isxdigit(c)   ((_ctype+1)[c]&(_D|_X))
#define isascii(c)    (((unsigned) c)<=0x7f)
#define toascii(c)    (((unsigned) c)&0x7f)
#define tolower(c)    (_ctmp=c,isupper(_ctmp)?_ctmp-('A'-'a'):_ctmp)
#define toupper(c)    (_ctmp=c,islower(_ctmp)?_ctmp-('a'-'A'):_ctmp)

extern unsigned char  _ctype[];
extern signed   char  _ctmp;





#endif /* __TYPES_H__ */

