#include <iostream>
#include "include/vpc.h"
#include "include/ops.h"


int main(int argc, const char* argv[]) {
    vpc::registers_t registers{0};
    vpc::operations_t operations = vpc::make_instructions();
    vpc::memory_t memory{0};

    int i = 0;
    auto next = [&i](){return i++;};


    // DATA
    memory[240] = vpc::create_data(0x00);  // start
    memory[241] = vpc::create_data(0x01);  // step
    memory[242] = vpc::create_data(0x0F);  // end
    memory[243] = vpc::create_data(0x0A);  // newline constant


    // PROGRAM
    memory[next()] = vpc::create_instruction({vpc::CPU_LDA, 0xF0});
    memory[next()] = vpc::create_instruction({vpc::CPU_LDB, 0xF2});
    memory[next()] = vpc::create_instruction({vpc::CPU_CMP});

    memory[next()] = vpc::create_instruction({vpc::CPU_JIE, 0x0B});

    memory[next()] = vpc::create_instruction({vpc::CPU_LDA, 0xF0});
    memory[next()] = vpc::create_instruction({vpc::CPU_LDB, 0xF1});
    memory[next()] = vpc::create_instruction({vpc::CPU_ADD});

    memory[next()] = vpc::create_instruction({vpc::CPU_EMT, 0xF0});
    memory[next()] = vpc::create_instruction({vpc::CPU_STA, 0xF0});
    memory[next()] = vpc::create_instruction({vpc::CPU_PRT, 0xF3});

    memory[next()] = vpc::create_instruction({vpc::CPU_JMP, 0x00});
    memory[next()] = vpc::create_instruction({vpc::CPU_HLT});


    vpc::execute(operations, registers, memory);

    return 0;
}