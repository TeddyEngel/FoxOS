#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <cstddef>
#include <cstdint>

extern "C"
{
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_movecursor(uint8_t x, uint8_t y);
void terminal_clear();
}

#endif
