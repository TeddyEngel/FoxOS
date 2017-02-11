#ifndef _KERNEL_KERNEL_MANAGER_H
#define _KERNEL_KERNEL_MANAGER_H

class KernelManager
{
public:
    KernelManager();

    void initialize();
    void runLoop(); // "main"

private:
    void displayBanner();
};

#endif /* _KERNEL_KERNEL_MANAGER_H */
