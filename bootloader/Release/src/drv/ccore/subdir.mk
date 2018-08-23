################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drv/ccore/vector_rce.c \
../src/drv/ccore/vector_table.c 

S_SRCS += \
../src/drv/ccore/crt0.s \
../src/drv/ccore/interrupt_support.s 

OBJS += \
./src/drv/ccore/crt0.o \
./src/drv/ccore/interrupt_support.o \
./src/drv/ccore/vector_rce.o \
./src/drv/ccore/vector_table.o 

C_DEPS += \
./src/drv/ccore/vector_rce.d \
./src/drv/ccore/vector_table.d 


# Each subdirectory must supply rules for building sources it contributes
src/drv/ccore/%.o: ../src/drv/ccore/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	mcore-elf-as -g -gstabs -EL -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drv/ccore/%.o: ../src/drv/ccore/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mcore-elf-gcc -DCONF_RELEASE -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\include" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\lib" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\demo" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\common" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src" -I"C:\CCore_IDE/tool-chain/ccore-elf/lib/gcc/mcore-elf/4.6.0/include" -I"C:\CCore_IDE/tool-chain/ccore-elf/mcore-elf/include" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\ccore" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\inc" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\api" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\sd_drv" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\usb_drv" -O3 -fno-common -ffunction-sections -mlittle-endian -Wall -c  -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


