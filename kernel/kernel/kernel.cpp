#include <kernel/kernel.h>

#include <kernel/kernel_types.h>
#include <kernel/KernelManager.h>

KernelManager kernelManager;

void kernelEarly()
{
    kernelManager.initialize();
}

void kernelMain()
{
    #ifdef TEST_MODE
        kernelManager.runTests();
    #endif
    kernelManager.runLoop();
}
