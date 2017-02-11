#include <kernel/KernelManager.h>

#include <cstring>
#include <cstdio>

#include <kernel/cpu.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/timer.h>
#include <kernel/tty.h>
#include <kernel/keyboard_driver.h>

KernelManager::KernelManager()
{
}

void KernelManager::initialize()
{
    // Memory
    gdt_manager::initialize();

    // Interrupts
    idt_manager::initialize();
    isr_manager::initialize();

    // Terminal
    tty_manager::initialize();

    // System clock
    idt_manager::enable_interrupts();
    timer_manager::initialize(DEFAULT_FREQUENCY);

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

    while (42)
    {
        cpu_manager::halt();
    }   
}