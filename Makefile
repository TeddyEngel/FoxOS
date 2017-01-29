OSNAME = foxOS
TRIPLET = i686-elf

CC = $(TRIPLET)-g++
OPTIONS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -nostartfiles

AC = $(TRIPLET)-as

ISO_DIR = isodir/
ISO_BOOT_DIR = $(ISO_DIR)/boot/
BOOT_FILE_NAME = boot
KERNEL_FILE_NAME = kernel

GRUB_FILE_CHECKER = grub-file
GRUB_MKRESCUE = grub-mkrescue
GRUB_CFG_FILE = grub.cfg
GRUB_ISO_BOOT_DIR = $(ISO_BOOT_DIR)/grub/
GRUB_SANITY_CHECK = $(GRUB_FILE_CHECKER) --is-x86-multiboot $(OSNAME).bin

DEPENDENCIES = $(CC) $(AC) $(GRUB_FILE_CHECKER) $(GRUB_MKRESCUE)
# Used to check all dependencies
K := $(foreach exec,$(DEPENDENCIES),\
	$(if $(shell which $(exec)),some string,$(error "No $(exec) in PATH)))

all: build clean

build: build_boot build_kernel build_iso

build_boot:
	@echo "\nBuilding Bootloader"
	$(AC) $(BOOT_FILE_NAME).s -o $(BOOT_FILE_NAME).o

build_kernel:
	@echo "\nBuilding Kernel"
	$(CC) $(OPTIONS) -c $(KERNEL_FILE_NAME).cpp -o $(KERNEL_FILE_NAME).o
	$(CC) $(OPTIONS) -T linker.ld -o $(OSNAME).bin $(BOOT_FILE_NAME).o $(KERNEL_FILE_NAME).o -lgcc

	@echo "\nChecking if valid multiboot file"
	$(GRUB_SANITY_CHECK) || (echo "$(GRUB_SANITY_CHECK) failed, code $$?"; exit 1)

build_iso:
	@echo "\nBuilding Iso"
	mkdir -p $(GRUB_ISO_BOOT_DIR)
	cp $(OSNAME).bin $(ISO_BOOT_DIR)/$(OSNAME).bin
	cp $(GRUB_CFG_FILE) $(GRUB_ISO_BOOT_DIR)/$(GRUB_CFG_FILE)
	$(GRUB_MKRESCUE) -o $(OSNAME).iso $(ISO_DIR)

clean:
	@echo "\nCleaning"
	rm $(KERNEL_FILE_NAME).o $(BOOT_FILE_NAME).o

clean_all: clean
	rm $(OSNAME).bin $(OSNAME).iso