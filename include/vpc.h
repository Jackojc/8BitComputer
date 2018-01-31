#include <cstdint>
#include <array>


namespace vpc {
    constexpr int TOTAL_ADDRESSABLE_MEMORY = 256;
    constexpr int TOTAL_CPU_INSTRUCTIONS   = 256;
    constexpr int TOTAL_REGISTERS          = 16;


    using instruction = uint32_t;
    using byte        = uint8_t;


    enum: byte {
        CPU_NOP, // NO OPERATION

        CPU_LDA, // LOAD VALUE INTO REGISTER_A
        CPU_LDB, // LOAD VALUE INTO REGISTER_B
        CPU_STC, // STORE VALUE IN REGISTER_C

        CPU_EMT, // EMIT VALUE AT ADDRESS AS ASCII
        CPU_PRT, // PRINT VALUE AT ADDRESS AS RAW VALUE

        CPU_ADD, // ADD A AND B THEN OUTPUT TO REGISTER_C
        CPU_SUB, // SUB A AND B THEN OUTPUT TO REGISTER_C

        CPU_AND, // AND A AND B THEN OUTPUT TO REGISTER_C
        CPU_OR,  // OR A AND B THEN OUTPUT TO REGISTER_C
        CPU_NOT, // NOT A AND THEN OUTPUT TO REGISTER_C

        CPU_JMP, // JUMP TO AN ADDRESS IN MEMORY
        CPU_JMR, // JUMP TO AN ADDRESS RELATIVE TO CURRENT
        CPU_JIN, // JUMP TO AN ADDRESS IN MEMORY IF VALUE IS NULL
        CPU_JIE, // JUMP TO AN ADDRESS IN MEMORY IF VALUE IS EQUAL

        CPU_HLT  // HALT THE CPU
    };


    enum: byte {
        REGISTER_A,     // A REGISTER
        REGISTER_B,     // B REGISTER
        REGISTER_C,     // C REGISTER

        REGISTER_ARG1,  // ARG REGISTERS
        REGISTER_ARG2,
        REGISTER_ARG3,

        REGISTER_PC,    // PROGRAM COUNTER
        REGISTER_IR,    // INSTRUCTION REGISTER

        REGISTER_NULL   // CONSTANT VALUE OF NULL
    };


    struct bundle {
        byte op;
        byte arg1;
        byte arg2;
        byte arg3;

        bundle(
            byte op_   = CPU_NOP,
            byte arg1_ = 0x0,
            byte arg2_ = 0x0,
            byte arg3_ = 0x0
        ):
            op(op_),
            arg1(arg1_),
            arg2(arg2_),
            arg3(arg3_)
        {}
    };


    bundle split_instruction(instruction instr) {
        bundle b;

        byte* msg = reinterpret_cast<byte*>(&instr);

        b.op   = msg[3];
        b.arg1 = msg[2];
        b.arg2 = msg[1];
        b.arg3 = msg[0];

        return b;
    }


    instruction create_instruction(bundle b) {
        byte tmp[4];

        tmp[0] = b.arg3;
        tmp[1] = b.arg2;
        tmp[2] = b.arg1;
        tmp[3] = b.op;

        return *reinterpret_cast<instruction*>(&tmp);
    }


    using memory_t = std::array<instruction, TOTAL_ADDRESSABLE_MEMORY>;
    using registers_t = std::array<byte, TOTAL_REGISTERS>;


    using operation = void(*)(registers_t&, memory_t&, bool&);
    using operations_t = std::array<operation, TOTAL_CPU_INSTRUCTIONS>;


    byte load_byte(memory_t& memory, unsigned index) {
        bundle b = split_instruction(memory[index]);
        return b.arg1;
    }


    void save_byte(memory_t& memory, unsigned index, byte c) {
        memory[index] = create_instruction({CPU_NOP, c, 0x0});
    }


    void execute(
        operations_t& operations,
        registers_t& registers,
        memory_t& memory
    ) {
        bool running  = true;

        byte& pc   = registers[REGISTER_PC];
        byte& ir   = registers[REGISTER_IR];

        byte& arg1 = registers[REGISTER_ARG1];
        byte& arg2 = registers[REGISTER_ARG2];
        byte& arg3 = registers[REGISTER_ARG3];


        while (running) {
            bundle b = split_instruction(memory[pc]);

            ir   = b.op;
            arg1 = b.arg1;
            arg2 = b.arg2;
            arg3 = b.arg3;

            pc++;

            operations[ir](registers, memory, running);
        }
    }
}