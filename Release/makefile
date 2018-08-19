################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/drv/usb_drv/subdir.mk
-include src/drv/sd_drv/subdir.mk
-include src/drv/ccore/subdir.mk
-include src/drv/subdir.mk
-include src/demo/subdir.mk
-include src/common/subdir.mk
-include src/api/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: A5(ET300)_CommonDemo.elf

# Tool invocations
A5(ET300)_CommonDemo.elf: $(OBJS) $(USER_OBJS) ../linkmap_release
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	mcore-elf-ld -EL --gc-sections -L"C:\CCore_IDE/tool-chain/ccore-elf/mcore-elf/lib/c0_div" -L"C:\CCore_IDE/tool-chain/ccore-elf/lib/gcc/mcore-elf/4.6.0/c0_div" -L"E:\001_工作\800_SVN\客户开发包发布\A5(ET300)\V1.1\Demo\A5(ET300)_CommonDemo\src\drv\lib" -e __start -N -t -warn-common -Map A5(ET300)_CommonDemo.map -T../linkmap_release -o "A5(ET300)_CommonDemo.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) A5(ET300)_CommonDemo.elf *.bin *.s *.obj *.map *.elf *.a
	-@echo ' '

post-build:
	-mcore-elf-objcopy  -O binary A5(ET300)_CommonDemo.elf A5(ET300)_CommonDemo.bin& mcore-elf-objdump -D A5(ET300)_CommonDemo.elf > A5(ET300)_CommonDemo.obj& mcore-elf-size A5(ET300)_CommonDemo.elf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
