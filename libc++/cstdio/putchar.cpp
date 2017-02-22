#include <cstdio>

#if defined(__is_libkpp)
    #include <kernel/KernelManager.h>
    #include <kernel/TtyManager.h>

    extern KernelManager kernelManager;
#endif

int putchar(int ic)
{
#if defined(__is_libkpp)
    char c = (char) ic;
    TtyManager& ttyManager = kernelManager.getTtyManager();
    ttyManager.write(&c, sizeof(c));
#else
    // TODO: Implement stdio and the write system call.
#endif
    return ic;
}
