#include <cstddef>
#include <cstdint>
#include <cstring>
#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;
    terminal_clear();
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scrolldown()
{
    // Move all lines up
    for (size_t y = 0; y < VGA_HEIGHT - 1; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            const size_t index_next_line = (y + 1) * VGA_WIDTH + x;

            terminal_buffer[index] =  terminal_buffer[index_next_line];
        }
    }

    // Clear last line
    for (size_t x = 0; x < VGA_WIDTH; x++)
    {
        const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;

        terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
}

void terminal_putchar(char c) {
    unsigned char uc = c;

    // Newline
    if (uc == '\n')
    {
        terminal_column = 0;
        ++terminal_row;
        return;
    }
    // Backspace
    else if (uc == '\b')
    {
        if (terminal_column == 0 && terminal_row > 0)
        {
            terminal_column = VGA_WIDTH - 1;
            --terminal_row;
        }
        else if (terminal_column > 0)
            --terminal_column;
        terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        return;
    }
    // Horizontal tab
    else if (uc == '\t')
    {
        terminal_column += 4;
        if (terminal_column >= VGA_WIDTH)
            terminal_column = VGA_WIDTH - 1;
        return;
    }
    // Carriage return
    else if (uc == '\r')
    {
        terminal_column = 0;
        return;
    }
    // Scrolling
    while (terminal_row >= VGA_HEIGHT)
    {
        terminal_scrolldown();
        --terminal_row;
    }
    terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
}

void terminal_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
    terminal_write(data, strlen(data));
}

void terminal_clear()
{
    for (size_t y = 0; y < VGA_HEIGHT; ++y)
    {
        for (size_t x = 0; x < VGA_WIDTH; ++x)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}
