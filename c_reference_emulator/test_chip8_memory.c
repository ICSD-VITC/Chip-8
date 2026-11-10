#include <stdio.h>
#include <assert.h>
#include "chip8_memory.h"

int main()
{
    Chip8Memory mem;

    printf("Starting CHIP-8 Memory Testbench...\n");
    printf("-----------------------------------\n");

    // TEST 1: Initialization
    // We expect the entire 4KB array to be wiped to exactly 0.
    memory_init(&mem);
    assert(mem.memory[0] == 0);
    assert(mem.memory[4095] == 0);
    assert(mem.memory[PROGRAM_START_ADDRESS] == 0);
    printf("[PASS] Memory initialized to zeros.\n");

    // TEST 2: Font Loading
    // We expect the 80 bytes of font data to be placed exactly at 0x050.
    memory_load_fonts(&mem);
    // The first byte of the '0' sprite is 0xF0, loaded at 0x050
    assert(memory_read(&mem, 0x050) == 0xF0);
    // The second byte of the '0' sprite is 0x90, loaded at 0x051
    assert(memory_read(&mem, 0x051) == 0x90);
    // The first byte of the 'F' sprite is 0xF0, loaded at 0x09B (0x050 + 75)
    assert(memory_read(&mem, 0x09B) == 0xF0);
    printf("[PASS] Fontset successfully loaded into interpreter memory (0x050).\n");

    // TEST 3: Valid Read and Write
    // We expect basic data storage to work perfectly.
    memory_write(&mem, 0x200, 0xAB);
    memory_write(&mem, 0xFFF, 0x12);
    assert(memory_read(&mem, 0x200) == 0xAB);
    assert(memory_read(&mem, 0xFFF) == 0x12);
    printf("[PASS] Valid read and write operations successful.\n");

    // TEST 4: Out-of-Bounds Write
    // We expect the program to print an error but NOT crash.
    printf("\n--- Expecting Write Error Log ---\n");
    memory_write(&mem, 4096, 0xFF);
    printf("[PASS] Out-of-bounds write handled safely.\n");

    // TEST 5: Out-of-Bounds Read
    // We expect the program to print an error and return 0.
    printf("\n--- Expecting Read Error Log ---\n");
    uint8_t bad_read = memory_read(&mem, 4096);
    assert(bad_read == 0);
    printf("[PASS] Out-of-bounds read handled safely.\n\n");

    // If assert() ever fails, the program crashes immediately.
    // Reaching this line proves everything works perfectly.
    printf("SUCCESS: All memory tests passed!\n");
    return 0;
}