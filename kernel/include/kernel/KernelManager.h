#ifndef _KERNEL_KERNEL_MANAGER_H
#define _KERNEL_KERNEL_MANAGER_H

#include <kernel/GdtManager.h>
#include <kernel/InterruptManager.h>

class KernelManager
{
public:
    KernelManager();

    GdtManager& getGdtManager();
    InterruptManager& getInterruptManager();

    void initialize();
    void runLoop();

private:
    void displayBanner();

private:
    GdtManager _gdtManager;
    InterruptManager _interruptManager;
};

#endif /* _KERNEL_KERNEL_MANAGER_H */
