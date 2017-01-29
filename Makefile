OSNAME = foxOS
TRIPLET = i686-elf

CC = $(TRIPLET)-g++
OPTIONS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -nostartfiles

AC = $(TRIPLET)-as

GRUB_CHECKER = grub-file

BOOT_FILE_NAME = boot
KERNEL_FILE_NAME = kernel

GRUB_SANITY_CHECK = $(GRUB_CHECKER) --is-x86-multiboot $(OSNAME).bin

DEPENDANCIES = $(CC) $(AC) $(GRUB_CHECKER)
# Used to check all dependancies
K := $(foreach exec,$(DEPENDANCIES),\
	$(if $(shell which $(exec)),some string,$(error "No $(exec) in PATH)))

all: check build

check:

build:
	@echo "Building Bootloader"
	$(AC) $(BOOT_FILE_NAME).s -o $(BOOT_FILE_NAME).o

	@echo "Building Kernel"
	$(CC) $(OPTIONS) -c $(KERNEL_FILE_NAME).cpp -o $(KERNEL_FILE_NAME).o
	$(CC) $(OPTIONS) -T linker.ld -o $(OSNAME).bin $(BOOT_FILE_NAME).o $(KERNEL_FILE_NAME).o -lgcc

	@echo "Checking if valid multiboot file"
	$(GRUB_SANITY_CHECK) || (echo "$(GRUB_SANITY_CHECK) failed, code $$?"; exit 1)

clean:
	rm $(KERNEL_FILE_NAME).o $(BOOT_FILE_NAME).o $(OSNAME).bin