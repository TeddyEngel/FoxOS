DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

# Default
AFLAGS?=
CFLAGS?=-O2 -g
CPPFLAGS?=-O2 -g
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

# Mandatory
AFLAGS:=$(AFLAGS)
CFLAGS:=$(CFLAGS) -std=gnu11 -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude -Wall -Wextra
LDFLAGS:=$(LDFLAGS)
# LIBS:=$(LIBS) -nostdlib -lk++
LIBS:=$(LIBS) -nostdlib -lk++ -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

AFLAGS:=$(AFLAGS) $(KERNEL_ARCH_AFLAGS)
CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/kernel.o \

OBJS=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .cpp .c .asm

all: $(OSNAME).kernel

$(OSNAME).kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CPP) -T $(ARCHDIR)/linker.ld -o $@ $(CPPFLAGS) $(LINK_LIST)
	# $(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot $(OSNAME).kernel

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CPP) $(CPPFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@
	# OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	# $(CC) -MD -c $< -o $@ $(CFLAGS)
	$(CPP) -MD -c $< -o $@ $(CPPFLAGS)

.cpp.o:
	$(CPP) -MD -c $< -o $@ $(CPPFLAGS)

.asm.o:
	$(AC) $(AFLAGS) $< -o $@

clean:
	rm -f $(OSNAME).kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: $(OSNAME).kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp $(OSNAME).kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
