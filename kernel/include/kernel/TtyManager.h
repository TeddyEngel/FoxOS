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
    void writeString(const char* data);
    void clear();
    void moveCursorLeft();
    void moveCursorRight();
    void moveCursorUp();
    void moveCursorDown();

private:
    void setColor(uint8_t color);
    void putEntryAt(unsigned char c, uint8_t color, size_t x, size_t y);
    void putEntryAtCursor(unsigned char c, uint8_t color);
    void scrollUp();
    void scrollDown();
    void putchar(char c);
    void movePhysicalCursor(uint8_t x, uint8_t y);
    void moveCursorNewLine();
    void moveCursorBeginLine();

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
