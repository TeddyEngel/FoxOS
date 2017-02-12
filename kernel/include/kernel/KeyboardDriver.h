/*
** Keyboard driver
*/

#pragma once

#include <cstdint>

#include <kernel/registers.h>
#include <kernel/KeyboardConstants.h>

class KernelManager;

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_SCANCODE_PORT 0x60

#define SHIFT_MODIFIER 128
#define KEY_UP_DECAL 128

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

/*
** Mappings
*/
#define MAPPING_COUNT 2
#define MAPPING_EN_US 0
#define MAPPING_DVORAK 1

class KeyboardDriver
{
public:
    KeyboardDriver(KernelManager&);

    void initialize();
    void enable();
    void disable();
    void restart();
    
    void registerMapping(uint8_t index, const uint8_t mapping[KEYS_COUNT]);
    void setActiveMapping(uint8_t index);

    void onKeypress();

private:
    uint8_t readStatus();
    uint8_t readScancode();

    void showLightIfNeeded();

private:
    static void onKeypressHook(registers_t);

private:
    // static const uint8_t MAPPING_US[KEYS_COUNT];

private:
    KernelManager& _kernelManager;
    uint8_t _status;
    uint8_t _scancode;
    bool _shiftPressed;
    uint8_t _currentMappingIndex;
    uint8_t _mappings[MAPPING_COUNT][KEYS_COUNT];
};
