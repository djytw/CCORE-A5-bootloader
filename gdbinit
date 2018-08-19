################################################################################
# Automatically-generated file. Do not edit!
################################################################################
#CCore Type:C0
#Chip Type:FPGA_DEMO
echo Setting up for CCore C0.\n



set endian little

target remote localhost:3333

echo halt target C0 \n

monitor halt

#monitor load_without_resume

monitor core_reset

#monitor mem_config "C:/CCore_IDE/tool-chain/memory_config/C0.memcfg"

#monitor script "E:/001_工作/800_SVN/客户开发包发布/A5(ET300)/V1.1/Demo/A5(ET300)_CommonDemo/debug_eflash/flash_erase.tcl"

#monitor script "E:/001_工作/800_SVN/客户开发包发布/A5(ET300)/V1.1/Demo/A5(ET300)_CommonDemo/debug_eflash/flash_pro.tcl"

#monitor reg pc 0x20000000



load



define core_reset
echo ---core reset
monitor core_reset
end

define fw_restart
echo ---reset
monitor reg pc $arg0
if $arg1 != 0
tbreak $arg1
end
continue
end


