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
    //-----------------Screen TESTING-----------------------
    //chip8_screen_set(&chip8.screen,10,10);
    //chip8_screen_draw_sprite(&chip8.screen, 32, 30,(const char*)&chip8.memory.memory[0x05], 5);
    //-----------------Sound and Delay TESTING-----------------------
    //chip8.registers.delay_timer = 255;
    //chip8.registers.sound_timer = 30;
    //----------------File Buffer Read TESTING-----------------------
    //printf("Buffer %s\n",buf);
    //----------------OPCODE TESTING-----------------------
    //chip8_screen_draw_sprite(&chip8.screen, 32, 30,(const char*)&chip8.memory.memory[0x05], 5);
    //chip8_exec(&chip8,0x00E0);   //clearing the screen

    //chip8_exec(&chip8,0x1ff2)  // jumping to instruction JP and changes PC
    //printf("%x\n",chip8.registers.PC);

    //chip8->registers.PC = 0x00; //3xnn opcode
    // chip8.registers.V[0x00] = 0x22;
    //chip8_exec(&chip8,0x3022)
    //printf("%x\n",chip8.registers.PC);
