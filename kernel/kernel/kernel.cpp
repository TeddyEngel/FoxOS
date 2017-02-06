#include <cstring>
#include <cstdio>

#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/tty.h>

extern "C"
void kernel_early()
{
    gdt_manager::initialize();
    idt_manager::initialize();
    isr_manager::initialize();
    tty_manager::initialize();
}

extern "C"
void kernel_main(void)
{
    const char* FOX_BANNER = " ,-.      .-,\n |-.\\ __ /.-|\n \\  `    `  /\n / _     _  \\\n | _`q  p _ |\n \'._=/  \\=_.'\n   {`\\()/`}`\\                   FoxOS\n   {      }  \\\n   |{    }    \\\n   \\ '--'   .- \\\n   |-      /    \\\n   | | | | |     ;\n   | | |.;.,..__ |\n .-\"\";`         `|\n /    |           /\n `-../____,..---'`\n";
	
    printf(FOX_BANNER);

    asm volatile ("int $0x0");
    asm volatile ("int $0x3");
    asm volatile ("int $0x4"); 
}
