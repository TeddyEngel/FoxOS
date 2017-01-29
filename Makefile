OSNAME = foxOS
COMPILER = i686-elf-g++
AS_COMPILER = i686-elf-as
OPTIONS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -nostartfiles
BOOT_FILE_NAME = boot
KERNEL_FILE_NAME = kernel

all: 
	@echo "Building Bootloader"
	$(AS_COMPILER) $(BOOT_FILE_NAME).s -o $(BOOT_FILE_NAME).o

	@echo "Building Kernel"
	$(COMPILER) $(OPTIONS) -c $(KERNEL_FILE_NAME).cpp -o $(KERNEL_FILE_NAME).o
	$(COMPILER) $(OPTIONS) -T linker.ld -o $(OSNAME).bin $(BOOT_FILE_NAME).o $(KERNEL_FILE_NAME).o -lgcc

clean:
	rm $(KERNEL_FILE_NAME).o $(BOOT_FILE_NAME).o $(OSNAME).bin