DEFAULT_HOST := $(shell ../default-host.sh)
HOST := $(DEFAULT_HOST)
OSNAME = foxOS
HOSTARCH := $(shell ../target-triplet-to-arch.sh $(HOST))

ARCH_PATH = ./arch/$(HOSTARCH)/
BOOT_FILE_NAME = boot
KERNEL_FILE_NAME = kernel

OBJS := $(KERNEL_FILE_NAME).o $(ARCH_PATH)/$(BOOT_FILE_NAME).o 
# OBJS := $(KERNEL_FILE_NAME).o $(ARCH_PATH)$(BOOT_FILE_NAME).o 
CC = $(HOST)-g++
# Default CFLAGS:
CFLAGS ?= -O2 -g
CPPFLAGS ?= -O2 -g
LDFLAGS ?=
LIBS ?=

# Add mandatory options to CFLAGS:
CFLAGS := $(CFLAGS) -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib
CRTI = crti
CRTI_OBJ = $(ARCH_PATH)/$(CRTI).o
# CRTI_OBJ = $(CRTI).o
CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN = crtn
CRTN_OBJ = $(ARCH_PATH)/$(CRTN).o
# CRTN_OBJ = $(CRTN).o
OBJ_LINK_LIST := $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJS := $(CRTI_OBJ) $(OBJS) $(CRTN_OBJ)

AC = $(HOST)-as

ISO_DIR = isodir/
ISO_BOOT_DIR = $(ISO_DIR)/boot/

GRUB_FILE_CHECKER = grub-file
GRUB_MKRESCUE = grub-mkrescue
GRUB_CFG_FILE = grub.cfg
GRUB_ISO_BOOT_DIR = $(ISO_BOOT_DIR)/grub/
GRUB_SANITY_CHECK = $(GRUB_FILE_CHECKER) --is-x86-multiboot $(OSNAME).bin

QEMU = qemu-system-i386

DEPENDENCIES = $(CC) $(AC) $(GRUB_FILE_CHECKER) $(GRUB_MKRESCUE) $(QEMU)
# Used to check all dependencies
K := $(foreach exec,$(DEPENDENCIES),\
	$(if $(shell which $(exec)),some string,$(error "No $(exec) in PATH)))

all: build clean

build: build_crti build_boot build_kernel build_os build_iso

build_crti:
	@echo $(DEFAULT_HOST)
	@echo $(HOSTARCH)
	@echo "\nBuilding Crtis"
	$(AC) $(ARCH_PATH)/$(CRTI).s -o $(ARCH_PATH)/$(CRTI).o
	# $(AC) $(CRTI).s -o $(CRTI).o
	$(AC) $(ARCH_PATH)/$(CRTN).s -o $(ARCH_PATH)/$(CRTN).o
	# $(AC) $(CRTN).s -o $(CRTN).o

build_boot:
	@echo "\nBuilding Bootloader"
	$(AC) $(ARCH_PATH)/$(BOOT_FILE_NAME).s -o $(ARCH_PATH)/$(BOOT_FILE_NAME).o
	# $(AC) $(BOOT_FILE_NAME).s -o $(BOOT_FILE_NAME).o

build_kernel: 
	@echo "\nBuilding Kernel"
	$(CC) $(CFLAGS) -c $(KERNEL_FILE_NAME).cpp -o $(KERNEL_FILE_NAME).o

build_os:
	@echo "\nBuilding OS"
	$(CC) $(CFLAGS) -T $(ARCH_PATH)/linker.ld -o $(OSNAME).bin $(OBJ_LINK_LIST) -lgcc
	# $(CC) $(CFLAGS) -T linker.ld -o $(OSNAME).bin $(OBJ_LINK_LIST) -lgcc

	@echo "\nChecking if valid multiboot file"
	$(GRUB_SANITY_CHECK) || (echo "$(GRUB_SANITY_CHECK) failed, code $$?"; exit 1)

build_iso:
	@echo "\nBuilding Iso"
	mkdir -p $(GRUB_ISO_BOOT_DIR)
	cp $(OSNAME).bin $(ISO_BOOT_DIR)/$(OSNAME).bin
	cp $(GRUB_CFG_FILE) $(GRUB_ISO_BOOT_DIR)/$(GRUB_CFG_FILE)
	$(GRUB_MKRESCUE) -o $(OSNAME).iso $(ISO_DIR)

test: test_iso

test_iso:
	$(QEMU) -cdrom $(OSNAME).iso

test_kernel:
	$(QEMU) -kernel $(OSNAME).bin

clean:
	@echo "\nCleaning"
	rm $(INTERNAL_OBJS)

clean_all: clean
	rm $(OSNAME).bin $(OSNAME).iso