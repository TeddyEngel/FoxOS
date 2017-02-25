#ifndef _KERNEL_KERNEL_MANAGER_H
#define _KERNEL_KERNEL_MANAGER_H

#include <kernel/kernel_types.h>
#include <kernel/CpuManager.h>
#include <kernel/GdtManager.h>
#include <kernel/PagingManager.h>
#include <kernel/InterruptManager.h>
#include <kernel/TimerManager.h>
#include <kernel/UserManager.h>
#include <kernel/KeyboardDriver.h>
#include <kernel/TtyManager.h>
#include <kernel/MemoryHeap.h>

class User;

class KernelManager
{
public:
    KernelManager();

    CpuManager& getCpuManager();
    GdtManager& getGdtManager();
    PagingManager& getPagingManager();
    InterruptManager& getInterruptManager();
    TimerManager& getTimerManager();
    UserManager& getUserManager();
    TtyManager& getTtyManager();

    KeyboardDriver& getKeyboardDriver();

    MemoryHeap& getMemoryHeap();

    void initialize();
    #ifdef TEST_MODE
    void runTests();
    #endif
    void runLoop();

    void reportStepOk(const char* stepMessage, const char* stepName);
    void reportStepFailed(const char* stepMessage, const char* stepName);
    void panic(const char* message);

private:
    void displayBanner();
    void displayUserPrompt(const User& user);

private:
    CpuManager _cpuManager;
    GdtManager _gdtManager;
    PagingManager _memoryManager;
    InterruptManager _interruptManager;
    TimerManager _timerManager;
    UserManager _userManager;
    TtyManager _ttyManager;

    /*
    ** Drivers
    */
    KeyboardDriver _keyboardDriver;

    /*
    ** Memory related
    */
    MemoryHeap _memoryHeap;
};

#endif /* _KERNEL_KERNEL_MANAGER_H */
