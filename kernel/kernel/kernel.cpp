#include <kernel/KernelManager.h>

KernelManager kernelManager;

extern "C"
void kernel_early()
{
    kernelManager.initialize();
}

extern "C"
void kernel_main(void)
{
    kernelManager.runLoop();
}
