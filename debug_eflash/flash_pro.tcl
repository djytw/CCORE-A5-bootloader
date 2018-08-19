#stop cpu
halt

#load program eflash code
load_image "E:/working_part/C0_work/C0_project/c0_flash_pro_dyn/out.elf"

#start program
eflash "E:/working_part/C0_work/C0_project/c0_flash_pro_dyn/pp.bin" 0x1000 0x20000000 0x20001000 512 0x20002000

#verify_image "E:/working_part/C0_work/C0_project/c0_flash_pro_dyn/out.elf"

