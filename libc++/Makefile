DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(EXEC_PREFIX)/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_libc++ -Iinclude
LIBK++_CFLAGS:=$(CFLAGS)
LIBK++_CPPFLAGS:=$(CPPFLAGS) -D__is_libk++

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK++_CFLAGS:=$(LIBK++_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK++_CPPFLAGS:=$(LIBK++_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS=\
$(ARCH_FREEOBJS) \
# stdio/printf.o \
# stdio/putchar.o \
# stdio/puts.o \
# stdlib/abort.o \
# string/memcmp.o \
# string/memcpy.o \
# string/memmove.o \
# string/memset.o \
string/strlen.o \

HOSTEDOBJS=\
$(ARCH_HOSTEDOBJS) \

OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

LIBK_OBJS=$(FREEOBJS:.o=.libk++.o)

#BINARIES=libc.a libk.a # Not ready for libc yet.
BINARIES=libk++.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk++.o .cpp .S

all: $(BINARIES)

libc++.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk++.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

.c.o:
	$(CPP) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.S:
	$(CPP) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.libk++.o:
	$(CPP) -MD -c $< -o $@ $(LIBK++_CFLAGS) $(LIBK++_CPPFLAGS)

.S.libk++.o:
	$(CPP) -MD -c $< -o $@ $(LIBK++_CFLAGS) $(LIBK++_CPPFLAGS)

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)