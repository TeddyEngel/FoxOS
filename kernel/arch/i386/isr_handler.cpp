#include <kernel/isr_handler.h>

#include <cstdio>

#include <kernel/KernelManager.h>
#include <kernel/InterruptManager.h>

extern KernelManager kernelManager;

void isr_handler(registers_t* regs)
{
    if (!regs)
        return;
    registers_t& regsRef = *regs;
    InterruptManager& interruptManager = kernelManager.getInterruptManager();
    if (interruptManager.hasHandler(regsRef.int_no))
    {
        fct_handler handler = interruptManager.getHandler(regsRef.int_no);
        handler(regsRef);
    }
    else
        printf("Unhandled interrupt: %d (%d)\n", regsRef.int_no, regsRef.err_code);
}