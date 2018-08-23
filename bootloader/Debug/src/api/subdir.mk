################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/api/alg_api.c \
../src/api/cpm_api.c \
../src/api/crc_api.c \
../src/api/eflash_api.c \
../src/api/eport_api.c \
../src/api/wdt_api.c 

OBJS += \
./src/api/alg_api.o \
./src/api/cpm_api.o \
./src/api/crc_api.o \
./src/api/eflash_api.o \
./src/api/eport_api.o \
./src/api/wdt_api.o 

C_DEPS += \
./src/api/alg_api.d \
./src/api/cpm_api.d \
./src/api/crc_api.d \
./src/api/eflash_api.d \
./src/api/eport_api.d \
./src/api/wdt_api.d 


# Each subdirectory must supply rules for building sources it contributes
src/api/%.o: ../src/api/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mcore-elf-gcc -DCONF_DEBUG -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\include" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\lib" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\demo" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\common" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src" -I"C:\CCore_IDE/tool-chain/ccore-elf/lib/gcc/mcore-elf/4.6.0/include" -I"C:\CCore_IDE/tool-chain/ccore-elf/mcore-elf/include" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\ccore" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\inc" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\api" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\sd_drv" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\usb_drv" -O0 -fno-common -ffunction-sections -g -mlittle-endian -Wall -c  -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


