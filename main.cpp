#include <iostream>
#include "include/vpc.h"
#include "include/ops.h"


int main(int argc, const char* argv[]) {
    vpc::registers_t registers{0};
    vpc::operations_t operations = vpc::make_instructions();
    vpc::memory_t memory{0};


    // DATA
    memory[255] = vpc::create_instruction({vpc::CPU_NOP, 0x5});
    memory[254] = vpc::create_instruction({vpc::CPU_NOP, 0x5});


    // PROGRAM
    // this program adds 5 + 5 and prints the result.
    // load value at memory[11] into register a.
    memory[0] = vpc::create_instruction({vpc::CPU_LOAD_A, 0xFF});
    // load value at memory[12] into register b.
    memory[1] = vpc::create_instruction({vpc::CPU_LOAD_B, 0xFE});

    // add values in registers a and b then output them to register c.
    memory[2] = vpc::create_instruction({vpc::CPU_ADD});
    // store the value of register c to memory[10].
    memory[3] = vpc::create_instruction({vpc::CPU_STORE_C, 0xFD});


    // emit the value in the output register to the display.
    memory[5] = vpc::create_instruction({vpc::CPU_EMIT, 0xFD});
    // print the value 10 which is a newline in ascii.
    memory[6] = vpc::create_instruction({vpc::CPU_PRINT, 0xFD});

    // halt the cpu.
    memory[7] = vpc::create_instruction({vpc::CPU_HALT});


    /*uint8_t op = vpc::CPU_ADD;
    uint8_t arg1 = 0x5;
    uint8_t arg2 = 0xFF;

    uint32_t instr = vpc::create_instruction({op, arg1, arg2});

    std::cout << (int)op << ", " << (int)arg1 << ", " << (int)arg2 << std::endl;

    std::cout << instr << std::endl;

    vpc::bundle b = vpc::split_instruction(instr);

    std::cout << (int)b.op << ", " << (int)b.arg1 << ", " << (int)b.arg2 << std::endl;*/

    vpc::execute(operations, registers, memory);

    return 0;
}