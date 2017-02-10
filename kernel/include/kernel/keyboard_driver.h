/*
** Keyboard driver
*/

#ifndef _KERNEL_KEYBOARD_DRIVER_H
#define _KERNEL_KEYBOARD_DRIVER_H

#include <cstdint>

#include <kernel/registers.h>

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_SCANCODE_PORT 0x60

#define KEY_UP_DECAL 128
// #define KEY_LEFT_SHIFT 0x2A
// #define KEY_SHIFT_UP_FLAG 0xAA

/*These r scan codes of non-displayable keys*/
#define NIL        -1
#define ESC       27
#define CTRL    29
#define SHFT    42
#define ALT       56
#define CAPS    58
#define F1         59
#define F2         60
#define F3         61
#define F4         62
#define F5         63
#define F6         64
#define F7         65
#define F8         66
#define F9         67
#define F10       68
#define NUM     69
#define SCRL    70
#define HOME   71
#define UP        72
#define PGUP    73
#define LEFT    75
#define FIVE     76
#define RGHT   77
#define END      79
#define DOWN  80
#define PGDN   81
#define INS       82
#define DEL      83
#define F11      87
#define F12      88
#define WIN     91
#define RTCK  93
#define POWR  94
#define SLEP   95
#define WAKE  99

class keyboard_driver
{
public:
    static void initialize();
    static void enable();
    static void disable();
    static void restart();

private:
    static uint8_t read_status();
    static uint8_t read_scancode();

    static void show_light_if_needed();
    static void on_keypress(registers_t);

private:
    static uint8_t _status;
    static uint8_t _scancode;
    static bool _shiftPressed;
    // static uint8_t _shiftPressed;
    static uint8_t _kbdus[];
};

#endif /* _KERNEL_KEYBOARD_DRIVER_H */