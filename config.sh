SYSTEM_HEADER_PROJECTS="libc++ kernel" # Add libc if needed
PROJECTS="libc++ kernel" # Add libc if needed

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export AR=${HOST}-ar
export AC=nasm
export CC=${HOST}-gcc
export CPP=${HOST}-g++

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export AFLAGS=''
export CFLAGS='-O2 -g'
export CPPFLAGS='-O2 -g -fstack-protector'

# Configure the target os name
export OSNAME="$(./osname.sh)"

# Configure the cross-compiler to use the desired system root.
export SYSROOT="$(pwd)/sysroot"
export AC="$AC"
export CC="$CC --sysroot=$SYSROOT"
export CPP="$CPP --sysroot=$SYSROOT"

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
  export CPP="$CPP -isystem=$INCLUDEDIR"
fi
