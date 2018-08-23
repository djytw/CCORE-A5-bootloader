################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drv/alg_drv.c \
../src/drv/analog_drv.c \
../src/drv/ccm_drv.c \
../src/drv/cpm_drv.c \
../src/drv/crc_drv.c \
../src/drv/dmac_drv.c \
../src/drv/edmac_drv.c \
../src/drv/eflash_drv.c \
../src/drv/eport_drv.c \
../src/drv/ept_drv.c \
../src/drv/fd_drv.c \
../src/drv/i2c_drv.c \
../src/drv/int_drv.c \
../src/drv/led_drv.c \
../src/drv/lowpower_drv.c \
../src/drv/mim_drv.c \
../src/drv/pit_drv.c \
../src/drv/reset_drv.c \
../src/drv/sci_drv.c \
../src/drv/spi_drv.c \
../src/drv/tc_drv.c \
../src/drv/td_drv.c \
../src/drv/trng_drv.c \
../src/drv/usi_drv.c \
../src/drv/vd_drv.c \
../src/drv/wdt_drv.c 

OBJS += \
./src/drv/alg_drv.o \
./src/drv/analog_drv.o \
./src/drv/ccm_drv.o \
./src/drv/cpm_drv.o \
./src/drv/crc_drv.o \
./src/drv/dmac_drv.o \
./src/drv/edmac_drv.o \
./src/drv/eflash_drv.o \
./src/drv/eport_drv.o \
./src/drv/ept_drv.o \
./src/drv/fd_drv.o \
./src/drv/i2c_drv.o \
./src/drv/int_drv.o \
./src/drv/led_drv.o \
./src/drv/lowpower_drv.o \
./src/drv/mim_drv.o \
./src/drv/pit_drv.o \
./src/drv/reset_drv.o \
./src/drv/sci_drv.o \
./src/drv/spi_drv.o \
./src/drv/tc_drv.o \
./src/drv/td_drv.o \
./src/drv/trng_drv.o \
./src/drv/usi_drv.o \
./src/drv/vd_drv.o \
./src/drv/wdt_drv.o 

C_DEPS += \
./src/drv/alg_drv.d \
./src/drv/analog_drv.d \
./src/drv/ccm_drv.d \
./src/drv/cpm_drv.d \
./src/drv/crc_drv.d \
./src/drv/dmac_drv.d \
./src/drv/edmac_drv.d \
./src/drv/eflash_drv.d \
./src/drv/eport_drv.d \
./src/drv/ept_drv.d \
./src/drv/fd_drv.d \
./src/drv/i2c_drv.d \
./src/drv/int_drv.d \
./src/drv/led_drv.d \
./src/drv/lowpower_drv.d \
./src/drv/mim_drv.d \
./src/drv/pit_drv.d \
./src/drv/reset_drv.d \
./src/drv/sci_drv.d \
./src/drv/spi_drv.d \
./src/drv/tc_drv.d \
./src/drv/td_drv.d \
./src/drv/trng_drv.d \
./src/drv/usi_drv.d \
./src/drv/vd_drv.d \
./src/drv/wdt_drv.d 


# Each subdirectory must supply rules for building sources it contributes
src/drv/%.o: ../src/drv/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mcore-elf-gcc -DCONF_DEBUG -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\include" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\lib" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\demo" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\common" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src" -I"C:\CCore_IDE/tool-chain/ccore-elf/lib/gcc/mcore-elf/4.6.0/include" -I"C:\CCore_IDE/tool-chain/ccore-elf/mcore-elf/include" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\ccore" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\inc" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\api" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\sd_drv" -I"C:\CCore_IDE\ccore-eclipse\workspace\A5(ET300)_CommonDemo\src\drv\usb_drv" -O0 -fno-common -ffunction-sections -g -mlittle-endian -Wall -c  -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


