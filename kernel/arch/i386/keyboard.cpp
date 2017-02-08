#include <kernel/keyboard.h>

#include <cstdio>

#include <kernel/isr.h>
#include <kernel/irq.h>

void keyboard_manager::on_keypress(registers_t)
{
   printf("Keypress\n");
}

void keyboard_manager::initialize(uint32_t frequency)
{
    // Firstly, register our keyboard callback.
    isr_manager::register_handler(IRQ1, &on_keypress);

    // Send the command byte.
    // outb(PIT_COMMAND_PORT, PIT_REPEATING_MODE);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    // uint8_t l = (uint8_t)(divisor & 0xFF);
    // uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

    // Send the frequency divisor.
    // outb(PIT_DATA_PORT_CHANNEL_0, l);
    // outb(PIT_DATA_PORT_CHANNEL_0, h);
} 
