#include <cstring>
#include <cstdio>

#include <kernel/gdt.h>
#include <kernel/tty.h>

extern "C"
void kernel_early()
{
    gdt_install();
    terminal_initialize();
}

extern "C"
void kernel_main(void)
{
    const char* FOX_BANNER = " ,-.      .-,\n |-.\\ __ /.-|\n \\  `    `  /\n / _     _  \\\n | _`q  p _ |\n \'._=/  \\=_.'\n   {`\\()/`}`\\                   FoxOS\n   {      }  \\\n   |{    }    \\\n   \\ '--'   .- \\\n   |-      /    \\\n   | | | | |     ;\n   | | |.;.,..__ |\n .-\"\";`         `|\n /    |           /\n `-../____,..---'`\n ";

	printf(FOX_BANNER);
}
