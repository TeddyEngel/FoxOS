#include <kernel/cpu.h>

// Halts the central processing unit (CPU) until the next external interrupt is fired.
void cpu_manager::halt()
{
    asm volatile("hlt");
}
