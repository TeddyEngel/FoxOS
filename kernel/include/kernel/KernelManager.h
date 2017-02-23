#ifndef _KERNEL_KERNEL_MANAGER_H
#define _KERNEL_KERNEL_MANAGER_H

#include <kernel/kernel_types.h>
#include <kernel/CpuManager.h>
#include <kernel/GdtManager.h>
#include <kernel/MemoryManager.h>
#include <kernel/InterruptManager.h>
#include <kernel/TimerManager.h>
#include <kernel/UserManager.h>
#include <kernel/KeyboardDriver.h>
#include <kernel/TtyManager.h>

class User;

class KernelManager
{
public:
    KernelManager();

    CpuManager& getCpuManager();
    GdtManager& getGdtManager();
    MemoryManager& getMemoryManager();
    InterruptManager& getInterruptManager();
    TimerManager& getTimerManager();
    UserManager& getUserManager();
    TtyManager& getTtyManager();

    KeyboardDriver& getKeyboardDriver();

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
    MemoryManager _memoryManager;
    InterruptManager _interruptManager;
    TimerManager _timerManager;
    UserManager _userManager;
    TtyManager _ttyManager;

    KeyboardDriver _keyboardDriver;
};

#endif /* _KERNEL_KERNEL_MANAGER_H */
