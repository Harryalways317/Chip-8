#ifndef CHIP8_KEYBOARD_H
#define CHIP8_KEYBOARD_H
#include<stdbool.h>
#include<config.h>
struct chip8_keyboard
{
    bool keyboard[CHIP8_TOTAL_KEYS];
};



#endif