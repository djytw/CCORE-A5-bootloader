# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# File name    : crt0.s
# Version      : V0.1
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	
	.text
	.export	__start
	.align 4
	.global __start
	.type __start,@function
__start:
	// set the stack
	lrw	r1, STACK_LOCATION
	mov	r0,r1

skip_set_vbr:	

  lrw	r1, VECTOR_LOCATION
	mtcr r1,vbr
	mfcr r2,vbr
	// setup argc, argv
	movi	r2,0		// argc
	movi	r3,0		// argv

	// zero the other regs
	movi	r1,0
	movi	r4,0
	movi	r5,0
	movi	r6,0
	movi	r7,0
	movi	r8,0
	movi	r9,0
	movi	r10,0
	movi	r11,0
	movi	r12,0
	movi	r13,0
	movi	r14,0
	movi	r15,0

	//Close MPU
	//lrw		r3,0x00
	//lrw		r2,0xFFFF0000
	//st.h	r3,(r2,0)

	//Close Watch dog
	//lrw		r3,0x0e
	//lrw		r2,0x70090000
	//st.h	r3,(r2,0)

	//Close RTC
	lrw		r3,0x00
	lrw		r2,0x70070000
	st.h	r3,(r2,0)

	//call main (of the C code)
	jsri  __main
	jsri	main
	
	.export	exit
exit:	
	
	br 	exit
		  
