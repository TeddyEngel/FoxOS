#ifndef _KERNEL_KERNEL_MANAGER_H
#define _KERNEL_KERNEL_MANAGER_H

#include <kernel/CpuManager.h>
#include <kernel/GdtManager.h>
#include <kernel/MemoryManager.h>
#include <kernel/InterruptManager.h>
#include <kernel/TimerManager.h>
#include <kernel/KeyboardDriver.h>
#include <kernel/TtyManager.h>

class KernelManager
{
public:
    KernelManager();

    CpuManager& getCpuManager();
    GdtManager& getGdtManager();
    MemoryManager& getMemoryManager();
    InterruptManager& getInterruptManager();
    TimerManager& getTimerManager();
    TtyManager& getTtyManager();

    KeyboardDriver& getKeyboardDriver();

    void initialize();
    void runLoop();

    void panic(const char* message);

private:
    void displayBanner();

private:
    CpuManager _cpuManager;
    GdtManager _gdtManager;
    MemoryManager _memoryManager;
    InterruptManager _interruptManager;
    TimerManager _timerManager;
    TtyManager _ttyManager;

    KeyboardDriver _keyboardDriver;
};

#endif /* _KERNEL_KERNEL_MANAGER_H */
