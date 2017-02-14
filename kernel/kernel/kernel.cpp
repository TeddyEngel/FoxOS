#include <kernel/kernel.h>

#include <kernel/KernelManager.h>

KernelManager kernelManager;

void kernelEarly()
{
    kernelManager.initialize();
}

void kernelMain()
{
    kernelManager.runLoop();
}
