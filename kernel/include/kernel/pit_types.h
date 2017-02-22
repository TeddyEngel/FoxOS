#ifndef _KERNEL_PIT_TYPES_H
#define _KERNEL_PIT_TYPES_H

#define PIT_DATA_PORT_CHANNEL_0 0x40 // Output connected to IRQ0
#define PIT_DATA_PORT_CHANNEL_1 0x41 // Controls refresh rates of DRAM
#define PIT_DATA_PORT_CHANNEL_2 0x42 // Controls the pc speaker
#define PIT_COMMAND_PORT 0x43
#define PIT_REPEATING_MODE 0x36 // To set the clock to repeat once it reaches 0

#endif /* _KERNEL_PIT_TYPES_H */