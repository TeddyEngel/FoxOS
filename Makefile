OSNAME = foxOS
TRIPLET = i686-elf
CC = $(TRIPLET)-g++
AC = $(TRIPLET)-as
OPTIONS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -nostartfiles
BOOT_FILE_NAME = boot
KERNEL_FILE_NAME = kernel

all: 
	@echo "Building Bootloader"
	$(AC) $(BOOT_FILE_NAME).s -o $(BOOT_FILE_NAME).o

	@echo "Building Kernel"
	$(CC) $(OPTIONS) -c $(KERNEL_FILE_NAME).cpp -o $(KERNEL_FILE_NAME).o
	$(CC) $(OPTIONS) -T linker.ld -o $(OSNAME).bin $(BOOT_FILE_NAME).o $(KERNEL_FILE_NAME).o -lgcc

clean:
	rm $(KERNEL_FILE_NAME).o $(BOOT_FILE_NAME).o $(OSNAME).bin