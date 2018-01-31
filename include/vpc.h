#include <cstdint>
#include <array>


namespace vpc {
    constexpr int TOTAL_ADDRESSABLE_MEMORY = 16;
    constexpr int TOTAL_CPU_INSTRUCTIONS = 16;
    constexpr int TOTAL_REGISTERS = 16;


    enum: uint8_t {
        CPU_NOP,           // NO OPERATION

        CPU_LOAD_A,        // LOAD VALUE INTO REGISTER_A
        CPU_LOAD_B,        // LOAD VALUE INTO REGISTER_B
        CPU_LOAD_CMR,      // LOAD VALUE INTO REGISTER_CMR

        CPU_STORE_C,       // STORE VALUE IN REGISTER_C

        CPU_EMIT,          // PRINT VALUE IN REGISTER_OR

        CPU_ADD,           // ADD A AND B THEN OUTPUT TO REGISTER_C
        CPU_SUB,           // SUB A AND B THEN OUTPUT TO REGISTER_C

        CPU_AND,           // AND A AND B THEN OUTPUT TO REGISTER_C
        CPU_OR,            // OR A AND B THEN OUTPUT TO REGISTER_C
        CPU_NOT,           // NOT A AND THEN OUTPUT TO REGISTER_C

        CPU_JUMP,          // JUMP TO AN ADDRESS IN MEMORY
        CPU_JUMP_REL,      // JUMP TO AN ADDRESS RELATIVE TO CURRENT
        CPU_JUMP_IF_NULL,  // JUMP TO AN ADDRESS IN MEMORY IF VALUE IS NULL

        CPU_HALT           // HALT THE CPU
    };


    enum: uint8_t {
        REGISTER_A,     // A REGISTER
        REGISTER_B,     // B REGISTER
        REGISTER_C,     // C REGISTER

        REGISTER_DATA,  // MEMORY ADDRESS REGISTER
        REGISTER_PC,    // PROGRAM COUNTER
        REGISTER_IR,    // INSTRUCTION REGISTER
        REGISTER_CMR    // FOR CONDITIONAL LOGIC
    };


    struct bundle {
        uint8_t op;
        uint8_t data;

        bundle(uint8_t op_, uint8_t data_):
            op(op_),
            data(data_)
        {}

        bundle(uint8_t op_):
            op(op_),
            data(0x0)
        {}

        bundle():
            op(0x0),
            data(0x0)
        {}
    };


    bundle split_instruction(uint8_t instr) {
        bundle b;

        b.op = instr >> 4;
        b.data = instr & 0x0F;

        return b;
    }


    uint8_t create_instruction(bundle b) {
        return (b.op << 4) | b.data;
    }


    using memory_t = std::array<uint8_t, TOTAL_ADDRESSABLE_MEMORY>;
    using registers_t = std::array<uint8_t, TOTAL_REGISTERS>;


    using operation = void(*)(registers_t&, memory_t&, bool&);
    using operations_t = std::array<operation, TOTAL_CPU_INSTRUCTIONS>;


    void execute(
        operations_t& operations,
        registers_t& registers,
        memory_t& memory
    ) {
        uint8_t& pc   = registers[REGISTER_PC];
        uint8_t& ir   = registers[REGISTER_IR];
        uint8_t& data = registers[REGISTER_DATA];
        bool running  = true;

        while (running) {
            bundle b = split_instruction(memory[pc]);

            ir = b.op;
            data = b.data;

            pc++;

            operations[ir](registers, memory, running);
        }
    }
}