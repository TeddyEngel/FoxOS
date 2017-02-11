#include <kernel/irq.h>

#include <cstdio>

#include <kernel/KernelManager.h>
#include <kernel/InterruptManager.h>
#include <kernel/pic.h>
#include <kernel/idt_types.h>

extern KernelManager kernelManager;

void irq_handler(registers_t regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= PIC_MASTER + PIC_MASTER_IRQ_ENTRIES)
       outb(PIC_SLAVE_COMMAND, PIC_EOI);

    // Send reset signal to master. (As well as slave, if necessary).
    outb(PIC_MASTER_COMMAND, PIC_EOI);

    InterruptManager& interruptManager = kernelManager.getInterruptManager();
    if (interruptManager.hasHandler(regs.int_no))
    {
        fct_handler handler = interruptManager.getHandler(regs.int_no);
        handler(regs);
    }
 }