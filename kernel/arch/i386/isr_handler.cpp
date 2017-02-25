#include <kernel/isr_handler.h>

#include <cstdio>

#include <kernel/KernelManager.h>
#include <kernel/InterruptManager.h>

extern KernelManager kernelManager;

void isr_handler(registers_t* pRegs)
{
    registers_t& regs = *pRegs;
    InterruptManager& interruptManager = kernelManager.getInterruptManager();
    if (interruptManager.hasHandler(regs.int_no))
    {
        fct_handler handler = interruptManager.getHandler(regs.int_no);
        handler(regs);
    }
    else
        printf("Unhandled interrupt: %d (%d)\n", regs.int_no, regs.err_code);
}