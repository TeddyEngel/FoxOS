#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <cstddef>
#include <cstdint>

class tty_manager
{
public:
    static void initialize();
    static void write(const char* data, size_t size);
    static void write_string(const char* data);
    static void clear();
    static void move_cursor_left();
    static void move_cursor_right();
    static void move_cursor_up();
    static void move_cursor_down();

private:
    static void set_color(uint8_t color);

    static void put_entry_at(unsigned char c, uint8_t color, size_t x, size_t y);
    static void put_entry_at_cursor(unsigned char c, uint8_t color);
    static void scrolldown();
    static void scrolldown_if_needed();
    static void putchar(char c);
    static void move_physical_cursor(uint8_t x, uint8_t y);

private:
    static const size_t VGA_WIDTH;
    static const size_t VGA_HEIGHT;
    static uint16_t* const VGA_MEMORY;
    static const uint8_t TAB_WIDTH;

private:
    static size_t _cursor_row;
    static size_t _cursor_column;
    static uint8_t _color;
    static uint16_t* _buffer;
};

#endif
