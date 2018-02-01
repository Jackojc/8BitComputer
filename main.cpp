#include <iostream>
#include "include/vpc.h"
#include "include/ops.h"


int main(int argc, const char* argv[]) {
    vpc::registers_t registers{0};
    vpc::operations_t operations = vpc::make_instructions();
    vpc::memory_t memory{0};


    // DATA
    memory[240] = vpc::create_data(0x00);  // start
    memory[241] = vpc::create_data(0x01);  // step
    memory[242] = vpc::create_data(0x05);  // end
    memory[243] = vpc::create_data(0x0A);  // newline constant

    // PROGRAM
    memory[0] = vpc::create_instruction({vpc::CPU_JIM, 0x08, 0xF0, 0xF2});
    memory[1] = vpc::create_instruction({vpc::CPU_JIE, 0x08, 0xF0, 0xF2});
    memory[2] = vpc::create_instruction({vpc::CPU_LDA, 0xF0});
    memory[3] = vpc::create_instruction({vpc::CPU_LDB, 0xF1});
    memory[4] = vpc::create_instruction({vpc::CPU_EMT, 0xF0});
    memory[5] = vpc::create_instruction({vpc::CPU_ADD});
    memory[6] = vpc::create_instruction({vpc::CPU_STC, 0xF0});
    memory[7] = vpc::create_instruction({vpc::CPU_JMP, 0x00});
    memory[8] = vpc::create_instruction({vpc::CPU_PRT, 0xF3});
    memory[9] = vpc::create_instruction({vpc::CPU_HLT});


    vpc::execute(operations, registers, memory);

    return 0;
}