#include <kernel/timer.h>

#include <cstdio>

#include <kernel/KernelManager.h>
#include <kernel/InterruptManager.h>
#include <kernel/irq_types.h>

extern KernelManager kernelManager;

uint32_t timer_manager::_tick = 0;

void timer_manager::on_tick(registers_t)
{
   ++_tick;
   // printf("Tick: %d\n", _tick);
}

void timer_manager::initialize(uint32_t frequency)
{
    // Firstly, register our timer callback.
    InterruptManager& interruptManager = kernelManager.getInterruptManager();
    interruptManager.registerHandler(IRQ0, &on_tick);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = 1193180 / frequency;

    // Send the command byte.
    outb(PIT_COMMAND_PORT, PIT_REPEATING_MODE);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

    // Send the frequency divisor.
    outb(PIT_DATA_PORT_CHANNEL_0, l);
    outb(PIT_DATA_PORT_CHANNEL_0, h);
} 
