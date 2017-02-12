/*
** Keyboard Mapping DVORAK
*/

#ifndef _KERNEL_KEYBOARD_MAPPING_DVORAK_H
#define _KERNEL_KEYBOARD_MAPPING_DVORAK_H

#include <cstdint>

#include <kernel/KeyboardConstants.h>

static const uint8_t KeyboardMappingDvorak[KEYS_COUNT] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '[', ']', '\b', /* Backspace */
  '\t',         /* Tab */
  '\'', ',', '.', 'p',   /* 19 */
  'y', 'f', 'g', 'c', 'r', 'l', '/', '=', '\n', /* Enter key */
    0,          /* 29   - Control */
  'a', 'o', 'e', 'u', 'i', 'd', 'h', 't', 'n', 's', /* 39 */
 '-', '\\',   0,        /* Left shift */
 '`', ';', 'q', 'j', 'k', 'x', 'b',            /* 49 */
  'm', 'w', 'v', 'z',   0,              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */

    /* Buffer keys */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    /* End of buffer keys */

    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(',  /* 9 */
  ')', '{', '}', '\b', /* Backspace */
  '\t',         /* Tab */
  '"', '<', '>', 'P',   /* 19 */
  'Y', 'F', 'G', 'C', 'R', 'L', '?', '+', '\n', /* Enter key */
    0,          /* 29   - Control */
  'A', 'O', 'E', 'U', 'I', 'D', 'H', 'T', 'N', 'S', /* 39 */
 '_', '|',   0,        /* Left shift */
 '|', ':', 'Q', 'J', 'K', 'X', 'B',            /* 49 */
  'M', 'W', 'V', 'Z',   0,              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};  

#endif /* _KERNEL_KEYBOARD_MAPPING_DVORAK_H */