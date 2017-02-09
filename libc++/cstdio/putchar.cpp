#include <cstdio>

#if defined(__is_libkpp)
#include <kernel/tty.h>
#endif

int putchar(int ic)
{
#if defined(__is_libkpp)
    char c = (char) ic;
    tty_manager::write(&c, sizeof(c));
#else
    // TODO: Implement stdio and the write system call.
#endif
    return ic;
}
