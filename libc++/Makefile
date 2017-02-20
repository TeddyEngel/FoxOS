DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CFLAGS?=-O2 -g
CPPFLAGS?=-O2 -g
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(EXEC_PREFIX)/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_libcpp -Iinclude
LIBK++_CFLAGS:=$(CFLAGS)
LIBK++_CPPFLAGS:=$(CPPFLAGS) -D__is_libkpp

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK++_CFLAGS:=$(LIBK++_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK++_CPPFLAGS:=$(LIBK++_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS=\
$(ARCH_FREEOBJS) \
cstdio/outb.o \
cstdio/inb.o \
cstdio/inw.o \
cstdio/io_wait.o \
cstdio/printf.o \
cstdio/putchar.o \
cstdio/putint.o \
cstdio/puts.o \
cstring/memcmp.o \
cstring/memcpy.o \
cstring/memmove.o \
cstring/memset.o \
cstring/strlen.o \
memory/kmalloc.o \
collection/ordered_array.o \
predicates/less_than.o \
# stdlib/abort.o \

HOSTEDOBJS=\
$(ARCH_HOSTEDOBJS) \

OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

LIBK++_OBJS=$(FREEOBJS:.o=.libk++.o)

#BINARIES=libc.a libk.a # Not ready for libc yet.
BINARIES=libk++.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk++.o .cpp .S

all: $(BINARIES)

libc++.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk++.a: $(LIBK++_OBJS)
	$(AR) rcs $@ $(LIBK++_OBJS)

.cpp.o:
	$(CPP) -MD -c $< -o $@ $(CPPFLAGS)

.cpp.libk++.o:
	$(CPP) -MD -c $< -o $@ $(LIBK++_CPPFLAGS)

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK++_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK++_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK++_OBJS:.o=.d)
