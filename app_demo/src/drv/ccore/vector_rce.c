// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File name    : vector_rce.c
// Version      : V0.1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "vector_table.h"
#include "debug.h"

void DummyHandler(void)
{
	MSG("WARNING: Default dummy interrupt handler entered \n");
}

void Misaligned_Access(void)
{
	MSG("WARNING: Unexpected Misaligned Access exception taken \n");
}

void Access_Error(void)
{
	asm("bkpt");
	MSG("WARNING: Unexpected Access Error exception taken \n");
}

void Illegal_Instrn(void)
{
	MSG("WARNING: Unexpected Illegal_Instrn exception taken \n");
}


void Breakpoint_Exception(void)
{
	MSG("WARNING: Unexpected Breakpoint exception taken \n");
}

void Unrecoverable_Error(void)
{
	MSG("WARNING: Unexpected Unrecoverable_Error exception taken \n");
}

extern char _end_text[];
extern char _start_data[];
extern char _end_data[];

extern char _bss_start[];
extern char _bss_end[];


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 __main
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//    Copy data section to the right place if necessary.
//    Initializing bss section
//
// Input:
//    None.
//
// Output:
//    None.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void __main(void)
{
	//need cp to mem 
	char *dst = _start_data;
	char *src = _end_text;
	/*  if the start of data (dst)
		is not equal to end of text (src) then
		copy it, else it's already in the right place
	*/
	if( _start_data != _end_text ) {
		memcpy( dst, src, (_end_data - _start_data));
	}

	/* zero the bss
	*/
	if( _bss_end - _bss_start ) {
		memset( _bss_start, 0x00, ( _bss_end - _bss_start ));
	}
}

