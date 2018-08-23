################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/common/common.c \
../src/common/debug.c 

OBJS += \
./src/common/common.o \
./src/common/debug.o 

C_DEPS += \
./src/common/common.d \
./src/common/debug.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/%.o: ../src/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mcore-elf-gcc -DCONF_DEBUG -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\include" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\lib" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\demo" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\common" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src" -I"C:\CCore_IDE/tool-chain/ccore-elf/lib/gcc/mcore-elf/4.6.0/include" -I"C:\CCore_IDE/tool-chain/ccore-elf/mcore-elf/include" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\ccore" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\inc" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\api" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\sd_drv" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\usb_drv" -O0 -fno-common -ffunction-sections -g -mlittle-endian -Wall -c  -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


