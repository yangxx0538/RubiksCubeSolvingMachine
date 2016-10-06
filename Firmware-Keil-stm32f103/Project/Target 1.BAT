SET PATH=D:\software\KEIL\ARM\ARMCC\bin\;C:\ProgramData\Oracle\Java\javapath;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x86;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x64;D:\software\Cadence\tools\pcb\bin;D:\software\Cadence\tools\bin;D:\software\Cadence\tools\libutil\bin;D:\software\Cadence\tools\fet\bin;D:\software\Cadence\tools\specctra\bin;D:\software\Cadence\tools\pspice;D:\software\Cadence\tools\capture;D:\software\Cadence\openaccess\bin\win32\opt;C:\Program Files (x86)\Nordic Semiconductor\nrf51\bin\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x007A1200
"D:\software\KEIL\ARM\ARMCC\bin\ArmCC" --Via "..\output\core_cm3.__i"
"D:\software\KEIL\ARM\ARMCC\bin\ArmCC" --Via "..\output\system_stm32f10x.__i"
"D:\software\KEIL\ARM\ARMCC\bin\ArmAsm" --Via "..\output\startup_stm32f10x_md._ia"
"D:\software\KEIL\ARM\ARMCC\bin\ArmCC" --Via "..\output\misc.__i"
"D:\software\KEIL\ARM\ARMCC\bin\ArmCC" --Via "..\output\stm32f10x_exti.__i"
"D:\software\KEIL\ARM\ARMCC\bin\ArmCC" --Via "..\output\stm32f10x_flash.__i"
