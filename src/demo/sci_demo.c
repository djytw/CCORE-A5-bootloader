// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : sci_demo.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "sci_demo.h"

#define SCI_DEMO_BUF_LENGTH		16

const UINT8 sci_demo_data[SCI_DEMO_BUF_LENGTH] = {
	0x68, 0x65, 0x72, 0x65, 0x20, 0x69, 0x73, 0x20,
	0x61, 0x20, 0x74, 0x65, 0x73, 0x74, 0x21, 0x21
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 sci_demo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Demo of SCI.
//    First send the string of "here is a test!!",
//    then receive the same string which sending by PC tool.
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void sci_demo(void)
{
	UINT32 i;
	UINT32 length;
	UINT8 sci_buf[SCI_DEMO_BUF_LENGTH];

	length = SCI_DEMO_BUF_LENGTH;
	sci_send_data(sci_demo_data, length);
	sci_receive_data(sci_buf, length);

	for (i = 0; i < SCI_DEMO_BUF_LENGTH; i++)
		if (sci_demo_data[i] != sci_buf[i])
			asm("bkpt");

	asm("bkpt");
}
