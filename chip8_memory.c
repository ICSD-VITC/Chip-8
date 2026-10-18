#include "chip8_memory.h"
#include <stdio.h>
#include <string.h>

// The standard CHIP-8 fontset.//
// Hexadecimal digits from 0 to F.//

const uint8_t chip8_fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void memory_init(Chip8Memory *mem)
{
    // Wipes the whole 4KB array with zeros.
    // If we don't do this, the emulator might try to run random garbage leftover in our computer's RAM.
    memset(mem->memory, 0, CHIP8_MEMORY_SIZE);
}

void memory_load_fonts(Chip8Memory *mem)
{
    // CHIP-8 games expect fonts to be stored starting at address 0x050.
    // This loops through our 80 bytes of font data and puts them in that exact spot.
    for (int i = 0; i < 80; i++)
    {
        mem->memory[0x050 + i] = chip8_fontset[i];
    }
}

void memory_write(Chip8Memory *mem, uint16_t address, uint8_t value)
{
    // The "if" statement stops a broken game from writing outside our 4096-byte array.
    // Without this check, a bad address could crash the whole emulator.
    if (address < CHIP8_MEMORY_SIZE)
    {
        mem->memory[address] = value;
    }
    else
    {
        printf("ERROR: Attempted to write out of bounds at 0x%04X\n", address);
    }
}

uint8_t memory_read(Chip8Memory *mem, uint16_t address)
{
    // Same safety check as the write function.
    // If a game asks for an address that doesn't exist, we print an error and return 0 instead of crashing.
    if (address < CHIP8_MEMORY_SIZE)
    {
        return mem->memory[address];
    }
    printf("ERROR: Attempted to read out of bounds at 0x%04X\n", address);
    return 0;
}