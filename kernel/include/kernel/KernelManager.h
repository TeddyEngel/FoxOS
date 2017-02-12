#ifndef _KERNEL_KERNEL_MANAGER_H
#define _KERNEL_KERNEL_MANAGER_H

#include <kernel/GdtManager.h>
#include <kernel/InterruptManager.h>
#include <kernel/TimerManager.h>
#include <kernel/KeyboardDriver.h>
#include <kernel/TtyManager.h>

class KernelManager
{
public:
    KernelManager();

    GdtManager& getGdtManager();
    InterruptManager& getInterruptManager();
    TimerManager& getTimerManager();
    TtyManager& getTtyManager();

    KeyboardDriver& getKeyboardDriver();

    void initialize();
    void runLoop();

private:
    void displayBanner();

private:
    GdtManager _gdtManager;
    InterruptManager _interruptManager;
    TimerManager _timerManager;
    TtyManager _ttyManager;

    KeyboardDriver _keyboardDriver;
};

#endif /* _KERNEL_KERNEL_MANAGER_H */
