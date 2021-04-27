#include <stdio.h>
#include "SDL2/SDL.h"
//#include<windows.h> //winapi
#include "chip8.h"
#include<unistd.h>
#include <stdbool.h>
const char keyboard_map[CHIP8_TOTAL_KEYS] = {
    SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5,
    SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_a, SDLK_b,
    SDLK_c, SDLK_d, SDLK_e, SDLK_f};

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("You must provide a file to Load into memory");
        return -1;
    }
    const char* filename = argv[1];
    printf("The file name %s\n",filename);
    FILE* f = fopen(filename,"r");
    if(!f)
    {
        printf("File not opened correctly");
        return -1;
    }
    fseek(f,0,SEEK_END);
    long size = ftell(f);
    fseek(f,0,SEEK_SET);
    char buf[size];
    int res  = fread(buf,size,1,f);
    if(res!=1)
    {
        printf("Failed to read the file");
        return -1;
    }

    
    struct chip8 chip8;
    //----------------MEMORY TESTING-----------------------
    //chip8_memory_set(&chip8.memory, 0x400, 'Z');
    //printf("%c\n", chip8_memory_get(&chip8.memory, 50));
    //-----------------STACK TESTING-----------------------
    // chip8.registers.SP = 0;
    // chip8_stack_push( &chip8,0xff);
    // chip8_stack_push( &chip8,0xaa);
    // printf("%x\n",chip8_stack_pop(&chip8));
    // printf("%x\n",chip8_stack_pop(&chip8));
    //-----------------Keyboard TESTING-----------------------
    // chip8_keyboard_down(&chip8.keyboard,0x0a);
    // chip8_keyboard_up(&chip8.keyboard,0x0f);
    // bool is_down = chip8_keyboard_is_down(&chip8.keyboard,0x0f);
    //printf("%i\n",(int)is_down);
    chip8_init(&chip8);
    chip8_load(&chip8,buf,size);

    //-----------------Screen TESTING-----------------------
    //chip8_screen_set(&chip8.screen,10,10);
    chip8_screen_draw_sprite(&chip8.screen, 32, 30,(const char*)&chip8.memory.memory[0x05], 5);
    //-----------------Sound and Delay TESTING-----------------------
    //chip8.registers.delay_timer = 255;
    //chip8.registers.sound_timer = 30;
    //----------------File Buffer Read TESTING-----------------------
    //printf("Buffer %s\n",buf);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow(
        EMULATOR_WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        CHIP8_WIDTH * CHIP8_WINDOW_MULTIPLIER,
        CHIP8_HEIGHT * CHIP8_WINDOW_MULTIPLIER, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);
    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                goto out;
                break;

            case SDL_KEYDOWN:
            {
                char key = event.key.keysym.sym;
                int vkey = chip8_keyboard_map(keyboard_map, key);
                if (vkey != -1)
                {
                    chip8_keyboard_down(&chip8.keyboard, vkey);
                }
                break;
            }
            case SDL_KEYUP:
            {
                char key = event.key.keysym.sym;
                int vkey = chip8_keyboard_map(keyboard_map, key);
                if (vkey != -1)
                {
                    chip8_keyboard_up(&chip8.keyboard, vkey);
                }
                break;
            }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        for (int x = 0; x < CHIP8_WIDTH; x++)
        {
            for (int y = 0; y < CHIP8_HEIGHT; y++)
            {
                if (chip8_screen_is_set(&chip8.screen,x,y))
                {
                    SDL_Rect r;
                    r.x = x*CHIP8_WINDOW_MULTIPLIER;
                    r.y = y*CHIP8_WINDOW_MULTIPLIER;
                    r.w = CHIP8_WINDOW_MULTIPLIER;
                    r.h = CHIP8_WINDOW_MULTIPLIER;
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }

        SDL_RenderPresent(renderer);
        if(chip8.registers.delay_timer>0)
        {
            //Sleep(100);  //only in windowsapi
            usleep(1000);
            //printf("Hii");
            chip8.registers.delay_timer-=1;
            
        }
        if(chip8.registers.sound_timer>0)
        { 
            //Beep(15000,100*chip8.registers.sound_timer);  //only in windows api
            chip8.registers.sound_timer = 0;
            
        }
        unsigned short opcode = chip8_memory_get_short(&chip8.memory,chip8.registers.PC);
    }

out:
    SDL_DestroyWindow(window);
    return 0;
}