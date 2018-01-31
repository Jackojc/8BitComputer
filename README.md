# 8BitComputer
Simple 8 bit computer emulator.

```
NOP []     No operation.
LDA [ADDR] Load value at [ADDR] into A.
LDB [ADDR] Load value at [ADDR] into B.
LDM [ADDR] Load value at [ADDR] into COMPARE.
STC [ADDR] Store value in C to [ADDR].
EMT [ADDR] Emit value at [ADDR] to the output device(terminal).
ADD []     Add A and B together then store the result in C.
SUB []     Sub B from A then store the result in C.
AND []     AND A and B together then store the result in C.
OR  []     OR A and B together then store the result in C.
NOT []     NOT A then store the result in C.
JMP [ADDR] Set the program counter to [ADDR].
JMR [ADDR] Set the program counter to current address + [ADDR].
JIN [ADDR] Set the program counter to value in COMPARE if value at [ADDR] == 0.
HLT []     Halt the CPU.
```