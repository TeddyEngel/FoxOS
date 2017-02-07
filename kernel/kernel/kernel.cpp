#include <cstring>
#include <cstdio>

#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/timer.h>
#include <kernel/tty.h>

extern "C"
void kernel_early()
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
    // timer_manager::initialize(DEFAULT_FREQUENCY);
}

extern "C"
void kernel_main(void)
{
    const char* FOX_BANNER = " ,-.      .-,\n |-.\\ __ /.-|\n \\  `    `  /\n / _     _  \\\n | _`q  p _ |\n \'._=/  \\=_.'\n   {`\\()/`}`\\                   FoxOS\n   {      }  \\\n   |{    }    \\\n   \\ '--'   .- \\\n   |-      /    \\\n   | | | | |     ;\n   | | |.;.,..__ |\n .-\"\";`         `|\n /    |           /\n `-../____,..---'`\n";
	
    printf(FOX_BANNER);

    // asm volatile ("int $0x0");
    // asm volatile ("int $0x3");

    // TODO: Check why I only get one from the clock
}
