#ifndef _KERNEL_MEMORY_MANAGER_H
#define _KERNEL_MEMORY_MANAGER_H

#include <kernel/PageTypes.h>

class KernelManager;

class MemoryManager
{
public:
    MemoryManager(KernelManager&);

    void initialize();

private:
    KernelManager& _kernelManager;
};

#endif /* _KERNEL_MEMORY_MANAGER_H */
