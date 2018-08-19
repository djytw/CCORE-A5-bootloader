
source [find mem.tcl]
set read_value 3
#//////add your flash erase proce here
echo "erase your flash..........>>>>>>>>>>>>>>>>>>>>>........"

#//configure your flash register
set read_value [memread32 0x20000000]
echo $read_value
set read_value [memread32 0x20000004]
echo $read_value
memwrite32 0x20000008 0x000ffff0

#//check erase status
#do some loop, wait erase ok,add your own code
	echo "waiting for erase ok........."
	set check_status [read_register 0x20000008]
	while { [expr $check_status & 0x80000000] != 0x80000000 } { 
		#check register 
		memwrite32 0x20000008 0x80000000
		sleep 1 
		set check_status [read_register 0x20000008]		
		echo [format "check status 0x%x" $check_status]		
	}
echo "erase your flash ok >>>>>>>>>>>>>>>>>>>"
