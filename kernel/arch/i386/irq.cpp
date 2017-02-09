#include <kernel/irq.h>

#include <cstdio>

#include <kernel/idt.h>
#include <kernel/isr.h>

void irq_handler(registers_t regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= PIC_MASTER + PIC_MASTER_IRQ_ENTRIES)
       outb(PIC_SLAVE_COMMAND, PIC_EOI);

    // Send reset signal to master. (As well as slave, if necessary).
    outb(PIC_MASTER_COMMAND, PIC_EOI);

    if (isr_manager::has_handler(regs.int_no))
    {
        fct_handler handler = isr_manager::get_handler(regs.int_no);
        handler(regs);
    }   
}