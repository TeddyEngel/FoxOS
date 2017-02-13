#include <kernel/KernelManager.h>

#include <cstring>
#include <cstdio>

KernelManager::KernelManager()
    : _cpuManager(*this)
    , _gdtManager(*this)
    , _memoryManager(*this)
    , _interruptManager(*this)
    , _timerManager(*this)
    , _ttyManager(*this)
    , _keyboardDriver(*this)
{
}

CpuManager& KernelManager::getCpuManager()
{
    return _cpuManager;
}

GdtManager& KernelManager::getGdtManager()
{
    return _gdtManager;
}

MemoryManager& KernelManager::getMemoryManager()
{
    return _memoryManager;
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

KeyboardDriver& KernelManager::getKeyboardDriver()
{
    return _keyboardDriver;
}

extern uint32_t placement_address;
void KernelManager::initialize()
{
    // Memory
    _gdtManager.initialize();
    _memoryManager.initialize();

    // Interrupts
    _interruptManager.initialize();

    // Terminal
    _ttyManager.initialize();

    // System clock
    _interruptManager.enableInterrupts();
    _timerManager.initialize();

    // Keyboard
    _keyboardDriver.initialize();
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
        _cpuManager.halt();
}

void KernelManager::panic(const char* message)
{
    _interruptManager.disableInterrupts();

    printf("KERNEL PANIC, message: %s\n", message);

    while (42)
        ;
}