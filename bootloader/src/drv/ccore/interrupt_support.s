# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# File name    : interrup_support.s
# Version      : V0.1
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.text

#Read PSR and VBR
.export Read_PSR,Read_VBR

Read_PSR:
	mfcr r2,cr0
	rts
	
Read_VBR:
	mfcr r2,cr1
	rts
	
#Write PSR and VBR
.export Write_PSR,Write_VBR

Write_PSR:
	mtcr r2,cr0
	rts
	
Write_VBR:
	mtcr r2,cr1
	rts
	
	
#########################################
#Disable interrupt by clearing IE and FE
#########################################

.export Disable_Ints

Disable_Ints:
	mfcr r1,cr0
	bclri r1,0x4
	bclri r1,0x6
	mtcr r1,cr0
	jmp r15
	
#########################################
#Enable interrupt by setting IE and FE
#########################################

.export Enable_Ints

Enable_Ints:
	mfcr r1,cr0
	bseti r1,0x4
	bseti r1,0x6
	mtcr r1,cr0
	jmp r15

#########################################
/*
 *	__memcpy	-	linkable version of __memcpy() intrinsic function
 *
 *	If the compiler sees a call to the __memcpy() intrinsic whose 3rd argument
 *	is not a constant-expression, it will generate a call to this routine. We must
 *	move the data byte-by-byte as we do not know if the source and destination
 *	are aligned to any particular boundary.
 *
 */
#########################################

.export __memcpy

__memcpy:
	tst		r4,r4;
	bf		L2;
L1:	ld.b	r1,(r3,0);
	subi	r4,1;
	st.b	r1,(r2,0);
	addi	r3,1;
	addi	r2,1;
	tst		r4,r4;
	bt		L1;
L2:
	jmp		r15
#########################################
/*
 *	memcpy	-	linkable version of __memcpy() intrinsic function
 *
 *	If the compiler sees a call to the __memcpy() intrinsic whose 3rd argument
 *	is not a constant-expression, it will generate a call to this routine. We must
 *	move the data byte-by-byte as we do not know if the source and destination
 *	are aligned to any particular boundary.
 *
 */
#########################################
.export memcpy

memcpy:
	tst		r4,r4;
	bf		L4;
L3:	ld.b	r1,(r3,0);
	subi	r4,1;
	st.b	r1,(r2,0);
	addi	r3,1;
	addi	r2,1;
	tst		r4,r4;
	bt		L3;
L4:
	jmp		r15
