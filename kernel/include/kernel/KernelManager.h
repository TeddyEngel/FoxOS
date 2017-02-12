#pragma once

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

    GdtManager& getGdtManager();
    MemoryManager& getMemoryManager();
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
    MemoryManager _memoryManager;
    InterruptManager _interruptManager;
    TimerManager _timerManager;
    TtyManager _ttyManager;

    KeyboardDriver _keyboardDriver;
};
