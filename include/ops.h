namespace vpc {
    void cpu_nop(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        return;
    }


    void cpu_lda(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_A] = load_byte(memory, registers[vpc::REGISTER_ARG1]);
    }


    void cpu_ldb(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_B] = load_byte(memory, registers[vpc::REGISTER_ARG1]);
    }


    void cpu_stc(
            vpc::registers_t& registers,
            vpc::memory_t& memory,
            bool& running
        ) {
        save_byte(memory, registers[vpc::REGISTER_ARG1], registers[vpc::REGISTER_C]);
    }


    void cpu_emt(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        std::cout << (int)load_byte(memory, registers[vpc::REGISTER_ARG1]);
    }


    void cpu_prt(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        std::cout << load_byte(memory, registers[vpc::REGISTER_ARG1]);
    }


    void cpu_add(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_C] = registers[vpc::REGISTER_A] + registers[vpc::REGISTER_B];
    }


    void cpu_sub(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_C] = registers[vpc::REGISTER_A] - registers[vpc::REGISTER_B];
    }


    void cpu_and(
            vpc::registers_t& registers,
            vpc::memory_t& memory,
            bool& running
        ) {
        registers[vpc::REGISTER_C] = registers[vpc::REGISTER_A] & registers[vpc::REGISTER_B];
    }


    void cpu_or(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_C] = registers[vpc::REGISTER_A] | registers[vpc::REGISTER_B];
    }


    void cpu_not(
            vpc::registers_t& registers,
            vpc::memory_t& memory,
            bool& running
        ) {
        registers[vpc::REGISTER_C] = ~registers[vpc::REGISTER_A];
    }


    void cpu_jmp(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_PC] = registers[vpc::REGISTER_ARG1];
    }


    void cpu_jmr(
            vpc::registers_t& registers,
            vpc::memory_t& memory,
            bool& running
        ) {
        registers[vpc::REGISTER_PC] += registers[vpc::REGISTER_ARG1];
    }


    void cpu_jin(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        if (registers[vpc::REGISTER_ARG2] == 0x0)
            registers[vpc::REGISTER_PC] = registers[vpc::REGISTER_ARG1];
    }


    void cpu_jie(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        if (registers[vpc::REGISTER_ARG2] == registers[vpc::REGISTER_ARG3])
            registers[vpc::REGISTER_PC] = registers[vpc::REGISTER_ARG1];
    }


    void cpu_hlt(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        running = false;
    }


    vpc::operations_t make_instructions() {
        vpc::operations_t ops{cpu_nop};

        ops[vpc::CPU_NOP]           = cpu_nop;
        ops[vpc::CPU_LOAD_A]        = cpu_lda;
        ops[vpc::CPU_LOAD_B]        = cpu_ldb;
        ops[vpc::CPU_STORE_C]       = cpu_stc;
        ops[vpc::CPU_EMIT]          = cpu_emt;
        ops[vpc::CPU_PRINT]         = cpu_prt;
        ops[vpc::CPU_ADD]           = cpu_add;
        ops[vpc::CPU_SUB]           = cpu_sub;
        ops[vpc::CPU_AND]           = cpu_and;
        ops[vpc::CPU_OR]            = cpu_or;
        ops[vpc::CPU_NOT]           = cpu_not;
        ops[vpc::CPU_JUMP]          = cpu_jmp;
        ops[vpc::CPU_JUMP_REL]      = cpu_jmr;
        ops[vpc::CPU_JUMP_IF_NULL]  = cpu_jin;
        ops[vpc::CPU_JUMP_IF_EQUAL] = cpu_jie;
        ops[vpc::CPU_HALT]          = cpu_hlt;

        return ops;
    }
}