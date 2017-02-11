#ifndef _KERNEL_KERNEL_MANAGER_H
#define _KERNEL_KERNEL_MANAGER_H

#include <kernel/GdtManager.h>

class KernelManager
{
public:
    KernelManager();

    void initialize();
    void runLoop(); // "main"

private:
    void displayBanner();

private:
    GdtManager _gdtManager;
};

#endif /* _KERNEL_KERNEL_MANAGER_H */
