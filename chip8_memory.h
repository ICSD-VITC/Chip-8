#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H

#include <stdint.h>

// Defining RAM size of 4kb for the emulator. //

#define CHIP8_MEMORY_SIZE 4096

// Any game rom must be loaded into memory starting at address 0x200.//
// The first 512 bytes (0x000 to 0x1FF) are reserved for the interpreter and fonts.//

#define PROGRAM_START_ADDRESS 0x200

// We put the array inside a struct so it stays safely bundled together when we hand the memory over to the CPU code.//

typedef struct
{
    uint8_t memory[CHIP8_MEMORY_SIZE];
} Chip8Memory;

/* =========================================================================
   Memory API Functions
   These are the functions the CPU and Display modules can use to interact
   with the memory.
   ========================================================================= */

// Wipes the entire memory array clean to 0x00 to prevent executing useless data.
void memory_init(Chip8Memory *mem);

// Loads the standard 80-byte CHIP-8 hexadecimal fontset into addresses 0x050 - 0x09F.
void memory_load_fonts(Chip8Memory *mem);

// Writes a byte to memory. Includes bounds checking to prevent bad ROMs from crashing the emulator.
void memory_write(Chip8Memory *mem, uint16_t address, uint8_t value);

// Reads a byte from memory. Includes bounds checking, returning 0 if the address is illegal.
uint8_t memory_read(Chip8Memory *mem, uint16_t address);

#endif // CHIP8_MEMORY_H