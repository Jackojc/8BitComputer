#include <iostream>
#include "include/vpc.h"
#include "include/ops.h"


int main(int argc, const char* argv[]) {
    vpc::registers_t registers{0};
    vpc::operations_t operations = vpc::make_instructions();
    vpc::memory_t memory{0};


    // DATA
    memory[11] = vpc::create_instruction({vpc::CPU_NOP, 0x5});
    memory[12] = vpc::create_instruction({vpc::CPU_NOP, 0x5});


    // PROGRAM
    // this program adds 5 + 5 and prints the result.
    // load value at memory[11] into register a.
    memory[0] = vpc::create_instruction({vpc::CPU_LOAD_A, 0xB});
    // load value at memory[12] into register b.
    memory[1] = vpc::create_instruction({vpc::CPU_LOAD_B, 0xC});

    // add values in registers a and b then output them to register c.
    memory[2] = vpc::create_instruction({vpc::CPU_ADD});
    // store the value of register c to memory[10].
    memory[3] = vpc::create_instruction({vpc::CPU_STORE_C, 0xA});


    // emit the value in the output register to the display.
    memory[5] = vpc::create_instruction({vpc::CPU_EMIT, 0xA});

    // halt the cpu.
    memory[6] = vpc::create_instruction({vpc::CPU_HALT});


    vpc::execute(operations, registers, memory);

    return 0;
}