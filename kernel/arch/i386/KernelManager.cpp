#include <kernel/KernelManager.h>

#include <cstring>
#include <cstdint>
#include <cstdio>

KernelManager::KernelManager()
    : _cpuManager(*this)
    , _gdtManager(*this)
    , _pagingManager(*this)
    , _interruptManager(*this)
    , _timerManager(*this)
    , _userManager(*this)
    , _ttyManager(*this)
    , _keyboardDriver(*this)
    , _memoryHeap(nullptr)
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

PagingManager& KernelManager::getPagingManager()
{
    return _pagingManager;
}

InterruptManager& KernelManager::getInterruptManager()
{
    return _interruptManager;
}

TimerManager& KernelManager::getTimerManager()
{
    return _timerManager;
}

UserManager& KernelManager::getUserManager()
{
    return _userManager;
}

TtyManager& KernelManager::getTtyManager()
{
    return _ttyManager;
}

KeyboardDriver& KernelManager::getKeyboardDriver()
{
    return _keyboardDriver;
}

MemoryHeap* KernelManager::getMemoryHeap()
{
    return _memoryHeap;
}

void KernelManager::initialize()
{
    const char* initializeMessage = "Initializing";

    // Terminal
    if (!_ttyManager.initialize())
        reportStepOk(initializeMessage, TtyManager::SERVICE_NAME);
    else
        reportStepFailed(initializeMessage, TtyManager::SERVICE_NAME);

    // Gdt
    if (!_gdtManager.initialize())
        reportStepOk(initializeMessage, GdtManager::SERVICE_NAME);
    else
        reportStepFailed(initializeMessage, GdtManager::SERVICE_NAME);

    // Interrupts
    if (!_interruptManager.initialize())
        reportStepOk(initializeMessage, InterruptManager::SERVICE_NAME);
    else
        reportStepFailed(initializeMessage, InterruptManager::SERVICE_NAME);

    // Memory
    if (!_pagingManager.initialize())
        reportStepOk(initializeMessage, PagingManager::SERVICE_NAME);
    else
        reportStepFailed(initializeMessage, PagingManager::SERVICE_NAME);

    // System clock
    _interruptManager.enableInterrupts();
    if (!_timerManager.initialize())
        reportStepOk(initializeMessage, TimerManager::SERVICE_NAME);
    else
        reportStepFailed(initializeMessage, TimerManager::SERVICE_NAME);

    // User management
    if (!_userManager.initialize())
        reportStepOk(initializeMessage, UserManager::SERVICE_NAME);
    else
        reportStepFailed(initializeMessage, UserManager::SERVICE_NAME);

    // Keyboard
    if (!_keyboardDriver.initialize())
        reportStepOk(initializeMessage, KeyboardDriver::SERVICE_NAME);
    else
        reportStepFailed(initializeMessage, KeyboardDriver::SERVICE_NAME);

    // Heap
    _memoryHeap = new MemoryHeap(_pagingManager, MemoryHeap::KHEAP_START, MemoryHeap::KHEAP_START + MemoryHeap::KHEAP_INITIAL_SIZE, MemoryHeap::KHEAP_LIMIT, 0, 0); // TODO: Allocate like this later on
    // If needed, can also allocate using op new + placement
    // _memoryHeap = (MemoryHeap*) MemoryHeap::operator new(sizeof(MemoryHeap));
    // MemoryHeap::place(_memoryHeap, MemoryHeap::KHEAP_START, MemoryHeap::KHEAP_START + MemoryHeap::KHEAP_INITIAL_SIZE, MemoryHeap::KHEAP_LIMIT, 0, 0);
}

void KernelManager::displayBanner()
{
    const char* FOX_BANNER = " ,-.      .-,\n |-.\\ __ /.-|\n \\  `    `  /\n / _     _  \\\n | _`q  p _ |\n \'._=/  \\=_.'\n   {`\\()/`}`\\                   FoxOS\n   {      }  \\\n   |{    }    \\\n   \\ '--'   .- \\\n   |-      /    \\\n   | | | | |     ;\n   | | |.;.,..__ |\n .-\"\";`         `|\n /    |           /\n `-../____,..---'`\n";
    
    printf(FOX_BANNER);
}

void KernelManager::displayUserPrompt(const User& user)
{
    printf("\n%s$ ", user.getName());
}

#ifdef TEST_MODE
void KernelManager::runTests()
{
    // TODO: Add a test so that calling that should return an interrupt message
    // asm volatile ("int $0x3");
    // asm volatile ("int $0x3");

    // TODO: Add a test that triggers a page fault
    // uint32_t *ptr = (uint32_t*)0xA0000000;
    // uint32_t do_page_fault = *ptr;
    // asm volatile ("int $0xE");

    // TODO: Add a test that allocates, deallocates, allocates, and checks that the mem address is same as original

    // TODO:
    // int a = kmalloc(8); // Allocate 8 bytes: returns 0xC0080000 for sake of argument
    // int b = kmalloc(8); // Allocate another 8 bytes: returns 0xC0080008.
    // kfree(a);           // Release a
    // kfree(b);           // Release b
    // int c = kmalloc(16);// What will this allocation return? Same as original

    // _ttyManager.setTextColorGreen();
    // printf("TESTS SUCCESSFULL\n");
    // _ttyManager.setTextColorLightGrey();
}
#endif

void KernelManager::runLoop()
{
    displayBanner();
    displayUserPrompt(getUserManager()._activeUser);
}

void KernelManager::reportStepOk(const char* stepMessage, const char* stepName)
{
    printf("%s %s [", stepMessage, stepName);
    _ttyManager.setTextColorGreen();
    printf("OK");
    _ttyManager.setTextColorLightGrey();
    printf("]\n");
}

void KernelManager::reportStepFailed(const char* stepMessage, const char* stepName)
{
    printf("%s %s [", stepMessage, stepName);
    _ttyManager.setTextColorRed();
    printf("KO");
    _ttyManager.setTextColorLightGrey();
    printf("]\n");
}

void KernelManager::panic(const char* message)
{
    _interruptManager.disableInterrupts();

    _ttyManager.setTextColorRed();
    printf("KERNEL PANIC, message: %s\n", message);
    _cpuManager.halt();
}