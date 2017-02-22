#ifndef _KERNEL_CPU_MANAGER_H
#define _KERNEL_CPU_MANAGER_H

class KernelManager;

class CpuManager
{
public:
    CpuManager(KernelManager&);

    // Halts the central processing unit (CPU) until the next external interrupt is fired.
    void halt();

private:
    KernelManager& _kernelManager;
};

#endif /* _KERNEL_CPU_MANAGER_H */