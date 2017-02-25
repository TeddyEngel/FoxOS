#ifndef _KERNEL_TTY_MANAGER_H
#define _KERNEL_TTY_MANAGER_H

#include <cstddef>
#include <cstdint>

class KernelManager;

class TtyManager
{
public:
    static const char* SERVICE_NAME;
    
public:
    TtyManager(KernelManager&);

    int initialize();
    void write(const char* data, std::size_t size);
    void writeString(const char* data);
    void clear();
    void setTextColorLightGrey();
    void setTextColorRed();
    void setTextColorGreen();
    void moveCursorLeft();
    void moveCursorRight();
    void moveCursorUp();
    void moveCursorDown();

private:
    void setColor(uint8_t color);
    void putEntryAt(unsigned char c, uint8_t color, std::size_t x, std::size_t y);
    void putEntryAtCursor(unsigned char c, uint8_t color);
    void scrollUp();
    void scrollDown();
    void putchar(char c);
    void movePhysicalCursor(uint8_t x, uint8_t y);
    void moveCursorNewLine();
    void moveCursorBeginLine();

private:
    static const std::size_t VGA_WIDTH;
    static const std::size_t VGA_HEIGHT;
    static uint16_t* const VGA_MEMORY;
    static const uint8_t TAB_WIDTH;

private:
    KernelManager& _kernelManager;
    std::size_t _cursor_row;
    std::size_t _cursor_column;
    uint8_t _color;
    uint16_t* _buffer;
};

#endif /* _KERNEL_TTY_MANAGER_H */
