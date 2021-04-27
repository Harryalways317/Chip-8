#include "chip8.h"
#include <memory.h>
#include <assert.h>
#include<stdio.h>


const char chip8_default_character_set[] = {
    0xf0, 0x90, 0x90, 0x90, 0xf0,
    0x20, 0x60, 0x20, 0x20, 0x70,
    0xf0, 0x10, 0xf0, 0x80, 0xf0,
    0xf0, 0x10, 0xf0, 0x10, 0xf0,
    0x90, 0x90, 0xf0, 0x10, 0x10,
    0xf0, 0x80, 0xf0, 0x10, 0xf0,
    0xf0, 0x80, 0xf0, 0x90, 0xf0,
    0xf0, 0x10, 0x20, 0x40, 0x40,
    0xf0, 0x90, 0xf0, 0x90, 0xf0,
    0xf0, 0x90, 0xf0, 0x10, 0xf0,
    0xf0, 0x90, 0xf0, 0x90, 0x90,
    0xe0, 0x90, 0xe0, 0x90, 0xe0,
    0xf0, 0x80, 0x80, 0x80, 0xf0,
    0xe0, 0x90, 0x90, 0x90, 0xe0,
    0xf0, 0x80, 0xf0, 0x80, 0xf0, 
    0xf0, 0x80, 0xf0, 0x80, 0x80
};

void chip8_init(struct chip8* chip8)
{
    memset(chip8, 0, sizeof(struct chip8));
    memcpy(&chip8->memory.memory, chip8_default_character_set, sizeof(chip8_default_character_set));
}

void chip8_load(struct chip8* chip8, const char* buf, size_t size)
{   //printf("%zu\n",size); //Size of the ROM File
    assert(size+CHIP8_PROGRAM_LOAD_ADDRESS < CHIP8_MEMORY_SIZE);
    memcpy(&chip8->memory.memory[CHIP8_PROGRAM_LOAD_ADDRESS], buf, size);
    chip8->registers.PC = CHIP8_PROGRAM_LOAD_ADDRESS;
}
static void chip8_exec_extended(struct chip8* chip8,unsigned short opcode)
{
    switch (opcode & 0xf000)   //take the first four digits of opcode to select case
    {
        unsigned short nnn = opcode & 0x0fff; //ggetting the last 12 bits for shifting
        unsigned char x = (opcode >> 8) & 0x000f; //3xkk extracting x  bit shifting if 3126 then extract 1
        unsigned char y = (opcode >> 4) & 0x000f; //5xy0 extracting y
        unsigned char kk = opcode & 0x00ff; //if 3126 extract 66
        

        //JP addr, 1nnn jump to location nnn's 
        case 0x1000:
            chip8->registers.PC = nnn;
            break;
        //CALL addr,2nnn subroutine at location nnn
        case 0x2000:
            chip8_stack_push(&chip8,chip8->registers.PC);
            chip8->registers.PC = nnn;
            break;
        // SE Vx, byte - 3xkk Skip next instruction if V[x] == kk
        case 0x3000:
            if(chip8->registers.V[x] == kk)
            {
                chip8->registers.PC += 2; //each instruction is 2 bytes
            }
            break;
        // SNE Vx, byte - 3xkk Skip next instruction if V[x] != kk
        case 0x4000:
            if(chip8->registers.V[x] != kk)
            {
                chip8->registers.PC += 2; //each instruction is 2 bytes
            }
            break;
        //5xy0 SE Vx, Vy -  Skip next instruction if V[x] == V[y]
        case 0x5000:
            if(chip8->registers.V[x] == chip8->registers.V[y])
            {
                chip8->registers.PC += 2; //each instruction is 2 bytes
            }
            break;
        //6xkk LD Vx, byte -  Vx = kk
        case 0x6000:
            chip8->registers.V[x] == kk;
            break;
        
        
        default:
            break;
    }
}

void chip8_exec(struct chip8* chip8, unsigned short opcode)
{
    switch (opcode)
    {
        //clear the display
        case 0x00E0:
            chip8_screen_clear(&chip8->screen);
            break;
        //return from subroutine
        case 0x00EE:
            chip8->registers.PC = chip8_stack_pop(&chip8->stack);
            break;
        
        default:
            chip8_exec_extended(&chip8,opcode);
    }
}