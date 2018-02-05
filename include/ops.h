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
        registers[vpc::REGISTER_A] = load_byte(memory, registers[vpc::REGISTER_ARG]);
    }


    void cpu_ldb(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_B] = load_byte(memory, registers[vpc::REGISTER_ARG]);
    }


    void cpu_ldg(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_GENERAL1] = load_byte(memory, registers[vpc::REGISTER_ARG]);
    }


    void cpu_sta(
            vpc::registers_t& registers,
            vpc::memory_t& memory,
            bool& running
        ) {
        save_byte(memory, registers[vpc::REGISTER_ARG], registers[vpc::REGISTER_A]);
    }


    void cpu_stg(
            vpc::registers_t& registers,
            vpc::memory_t& memory,
            bool& running
        ) {
        save_byte(memory, registers[vpc::REGISTER_ARG], registers[vpc::REGISTER_GENERAL1]);
    }


    void cpu_emt(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        std::cout << (int)load_byte(memory, registers[vpc::REGISTER_ARG]) << std::flush;
    }


    void cpu_prt(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        std::cout << load_byte(memory, registers[vpc::REGISTER_ARG]) << std::flush;
    }


    void cpu_add(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_A] = registers[vpc::REGISTER_A] + registers[vpc::REGISTER_B];
    }


    void cpu_sub(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_A] = registers[vpc::REGISTER_A] - registers[vpc::REGISTER_B];
    }


    void cpu_and(
            vpc::registers_t& registers,
            vpc::memory_t& memory,
            bool& running
        ) {
        registers[vpc::REGISTER_A] = registers[vpc::REGISTER_A] & registers[vpc::REGISTER_B];
    }


    void cpu_or(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_A] = registers[vpc::REGISTER_A] | registers[vpc::REGISTER_B];
    }


    void cpu_not(
            vpc::registers_t& registers,
            vpc::memory_t& memory,
            bool& running
        ) {
        registers[vpc::REGISTER_A] = ~registers[vpc::REGISTER_A];
    }


    void cpu_cmp(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_FLAGS] = registers[vpc::REGISTER_A] == registers[vpc::REGISTER_B];
    }


    void cpu_nul(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        save_byte(memory, registers[vpc::REGISTER_ARG], 0x0);
    }



    void cpu_jmp(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        registers[vpc::REGISTER_PC] = registers[vpc::REGISTER_ARG];
    }


    void cpu_jmr(
            vpc::registers_t& registers,
            vpc::memory_t& memory,
            bool& running
        ) {
        registers[vpc::REGISTER_PC] += registers[vpc::REGISTER_ARG];
    }


    void cpu_jin(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        if (!registers[vpc::REGISTER_FLAGS])
            registers[vpc::REGISTER_PC] = registers[vpc::REGISTER_ARG];
    }


    void cpu_jie(
        vpc::registers_t& registers,
        vpc::memory_t& memory,
        bool& running
    ) {
        if (registers[vpc::REGISTER_FLAGS])
            registers[vpc::REGISTER_PC] = registers[vpc::REGISTER_ARG];
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

        ops[vpc::CPU_NOP] = cpu_nop;

        ops[vpc::CPU_LDA] = cpu_lda;
        ops[vpc::CPU_LDB] = cpu_ldb;
        ops[vpc::CPU_LDG] = cpu_ldg;

        ops[vpc::CPU_STA] = cpu_sta;
        ops[vpc::CPU_STG] = cpu_stg;

        ops[vpc::CPU_EMT] = cpu_emt;
        ops[vpc::CPU_PRT] = cpu_prt;

        ops[vpc::CPU_CMP] = cpu_cmp;
        ops[vpc::CPU_ADD] = cpu_add;
        ops[vpc::CPU_SUB] = cpu_sub;
        ops[vpc::CPU_AND] = cpu_and;
        ops[vpc::CPU_OR]  = cpu_or;
        ops[vpc::CPU_NOT] = cpu_not;

        ops[vpc::CPU_NUL] = cpu_nul;

        ops[vpc::CPU_JMP] = cpu_jmp;
        ops[vpc::CPU_JMR] = cpu_jmr;

        ops[vpc::CPU_JIN] = cpu_jin;
        ops[vpc::CPU_JIE] = cpu_jie;

        ops[vpc::CPU_HLT] = cpu_hlt;

        return ops;
    }
}