# Chip-8 Emulator

**CHIP-8** is an [interpreted](https://en.wikipedia.org/wiki/Interpreter_(computing)) [programming language](https://en.wikipedia.org/wiki/Programming_language), developed by [Joseph Weisbecker](https://en.wikipedia.org/wiki/Joseph_Weisbecker) CHIP-8 [programs](https://en.wikipedia.org/wiki/Computer_program) are run on a CHIP-8 [virtual machine](https://en.wikipedia.org/wiki/Virtual_machine). It was made to allow [video games](https://en.wikipedia.org/wiki/Video_game) to be more easily programmed for these computers.



Chip - 8 Emulator consists of 7 main components

1. memory
2. registers
3. stack
4. timers
5. Keyboard / io
6. Screen (Graphics)
7. Opcode table

This is implemented in C Language because

1. it is closer to system 
2. can handle low level xor operations on bits stored in [big-endian](https://en.wikipedia.org/wiki/Endianness).

i have used the SDL Library becasue it provides low level access to audio, keyboard, mouse, joystick, and graphics hardware and everyone knows SDL library is the basic requirement for games and emulators in c

## References:
1. [Cowgods Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
2. [Wiki page](https://en.wikipedia.org/wiki/CHIP-8)



