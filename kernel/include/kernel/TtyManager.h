#ifndef _KERNEL_TTY_MANAGER_H
#define _KERNEL_TTY_MANAGER_H

#include <cstddef>
#include <cstdint>

class TtyManager
{
public:
    TtyManager();

    void initialize();
    void write(const char* data, size_t size);
    void write_string(const char* data);
    void clear();
    void move_cursor_left();
    void move_cursor_right();
    void move_cursor_up();
    void move_cursor_down();

private:
    void set_color(uint8_t color);
    void put_entry_at(unsigned char c, uint8_t color, size_t x, size_t y);
    void put_entry_at_cursor(unsigned char c, uint8_t color);
    void scrollup();
    void scrolldown();
    void putchar(char c);
    void move_physical_cursor(uint8_t x, uint8_t y);
    void move_cursor_newline();
    void move_cursor_beginline();

private:
    static const size_t VGA_WIDTH;
    static const size_t VGA_HEIGHT;
    static uint16_t* const VGA_MEMORY;
    static const uint8_t TAB_WIDTH;

private:
    size_t _cursor_row;
    size_t _cursor_column;
    uint8_t _color;
    uint16_t* _buffer;
};

#endif /* _KERNEL_TTY_MANAGER_H */
