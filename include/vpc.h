#include <cstdint>
#include <array>


namespace vpc {
    constexpr int TOTAL_ADDRESSABLE_MEMORY = 256;
    constexpr int TOTAL_CPU_INSTRUCTIONS   = 256;
    constexpr int TOTAL_REGISTERS          = 16;


    using instruction = uint16_t;
    using byte        = uint8_t;


    enum: byte {
        CPU_NOP, // NO OPERATION

        CPU_LDA, // LOAD VALUE INTO REGISTER_A
        CPU_LDB, // LOAD VALUE INTO REGISTER_B

        CPU_STA, // STORE VALUE FROM REGISTER_A TO ADDR

        CPU_EMT, // EMIT VALUE AT ADDRESS AS ASCII
        CPU_PRT, // PRINT VALUE AT ADDRESS AS RAW VALUE

        CPU_ADD, // ADD A AND B THEN OUTPUT TO REGISTER_A
        CPU_SUB, // SUB A AND B THEN OUTPUT TO REGISTER_A

        CPU_CMP, // COMPARE A AND B THEN OUTPUT TO REGISTER_FLAGS
        CPU_AND, // AND A AND B THEN OUTPUT TO REGISTER_A
        CPU_OR,  // OR A AND B THEN OUTPUT TO REGISTER_A
        CPU_NOT, // NOT A AND THEN OUTPUT TO REGISTER_A

        CPU_NUL, // ZERO OUT A VALUE A AN ADDRESS
        CPU_MOV, // MOVE MEMORY FROM ONE PLACE TO ANOTHER

        CPU_JMP, // JUMP TO AN ADDRESS IN MEMORY
        CPU_JMR, // JUMP TO AN ADDRESS RELATIVE TO CURRENT

        CPU_JIN, // JUMP TO AN ADDRESS IF FLAGS IS FALSE
        CPU_JIE, // JUMP TO AN ADDRESS IF FLAGS IS TRUE

        CPU_HLT  // HALT THE CPU
    };


    enum: byte {
        REGISTER_A,     // A REGISTER
        REGISTER_B,     // B REGISTER

        REGISTER_ARG,

        REGISTER_FLAGS,

        REGISTER_PC,    // PROGRAM COUNTER
        REGISTER_IR,    // INSTRUCTION REGISTER

        REGISTER_GENERAL1, // GENERAL PURPOSE REGISTERS
        REGISTER_GENERAL2,
        REGISTER_GENERAL3,
        REGISTER_GENERAL4,
        REGISTER_GENERAL5,
        REGISTER_GENERAL6,

        REGISTER_NULL   // CONSTANT VALUE OF NULL
    };


    struct bundle {
        byte op;
        byte arg;

        bundle(
            byte op_   = 0x0,
            byte arg_  = 0x0
        ):
            op(op_),
            arg(arg_)
        {}
    };


    bundle split_instruction(instruction instr) {
        bundle b;

        byte* msg = reinterpret_cast<byte*>(&instr);

        b.op   = msg[1];
        b.arg  = msg[0];

        return b;
    }


    instruction create_instruction(bundle b) {
        byte tmp[2];

        tmp[0] = b.arg;
        tmp[1] = b.op;

        return *reinterpret_cast<instruction*>(&tmp);
    }


    instruction create_data(byte data) {
        return create_instruction({CPU_NOP, data});
    }


    using memory_t = std::array<instruction, TOTAL_ADDRESSABLE_MEMORY>;
    using registers_t = std::array<byte, TOTAL_REGISTERS>;


    using operation = void(*)(registers_t&, memory_t&, bool&);
    using operations_t = std::array<operation, TOTAL_CPU_INSTRUCTIONS>;


    byte load_byte(memory_t& memory, unsigned index) {
        bundle b = split_instruction(memory[index]);
        return b.arg;
    }


    void save_byte(memory_t& memory, unsigned index, byte c) {
        memory[index] = create_instruction({CPU_NOP, c});
    }


    void execute(
        operations_t& operations,
        registers_t& registers,
        memory_t& memory
    ) {
        bool running  = true;

        byte& pc   = registers[REGISTER_PC];
        byte& ir   = registers[REGISTER_IR];

        byte& arg  = registers[REGISTER_ARG];


        while (running) {
            bundle b = split_instruction(memory[pc]);

            ir   = b.op;
            arg  = b.arg;

            pc++;

            operations[ir](registers, memory, running);
        }
    }
}