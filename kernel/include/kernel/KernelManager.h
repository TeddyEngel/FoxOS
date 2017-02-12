#ifndef _KERNEL_KERNEL_MANAGER_H
#define _KERNEL_KERNEL_MANAGER_H

#include <kernel/GdtManager.h>
#include <kernel/InterruptManager.h>
#include <kernel/TimerManager.h>
#include <kernel/TtyManager.h>

class KernelManager
{
public:
    KernelManager();

    GdtManager& getGdtManager();
    InterruptManager& getInterruptManager();
    TimerManager& getTimerManager();
    TtyManager& getTtyManager();

    void initialize();
    void runLoop();

private:
    void displayBanner();

private:
    GdtManager _gdtManager;
    InterruptManager _interruptManager;
    TimerManager _timerManager;
    TtyManager _ttyManager;
};

#endif /* _KERNEL_KERNEL_MANAGER_H */
