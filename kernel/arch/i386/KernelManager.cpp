#include <kernel/KernelManager.h>

#include <cstring>
#include <cstdio>

#include <kernel/cpu.h>
#include <kernel/KeyboardDriver.h>

KernelManager::KernelManager()
{
}

GdtManager& KernelManager::getGdtManager()
{
    return _gdtManager;
}

InterruptManager& KernelManager::getInterruptManager()
{
    return _interruptManager;
}

TimerManager& KernelManager::getTimerManager()
{
    return _timerManager;
}

TtyManager& KernelManager::getTtyManager()
{
    return _ttyManager;
}

void KernelManager::initialize()
{
    // Memory
    _gdtManager.initialize();

    // Interrupts
    _interruptManager.initialize();

    // Terminal
    _ttyManager.initialize();

    // System clock
    _interruptManager.enableInterrupts();
    _timerManager.initialize();

    // Keyboard
    keyboard_driver::initialize();
}

void KernelManager::displayBanner()
{
    const char* FOX_BANNER = " ,-.      .-,\n |-.\\ __ /.-|\n \\  `    `  /\n / _     _  \\\n | _`q  p _ |\n \'._=/  \\=_.'\n   {`\\()/`}`\\                   FoxOS\n   {      }  \\\n   |{    }    \\\n   \\ '--'   .- \\\n   |-      /    \\\n   | | | | |     ;\n   | | |.;.,..__ |\n .-\"\";`         `|\n /    |           /\n `-../____,..---'`\n";
    
    printf(FOX_BANNER);
}

void KernelManager::runLoop()
{
    displayBanner();

    // TODO: Add a test so that calling that should return an interrupt message
    // asm volatile ("int $0x3");

    while (42)
        cpu_manager::halt();
}