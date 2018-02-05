# 8BitComputer
Simple 8 bit computer emulator.

- 16 general purpose registers.
- 256 bytes of addressable memory.
- 20 instructions.

```
NOP / []                  / No operation.

LDA / [ADDR]              / Load value at [ADDR] into A.
LDB / [ADDR]              / Load value at [ADDR] into B.
LDG / [ADDR]              / Load value at [ADDR] into G.

STC / [ADDR]              / Store value in C to [ADDR].
STG / [ADDR]              / Store value in G to [ADDR].

CLA / []                  / Clear register A.
CLB / []                  / Clear register B.
CLG / []                  / Clear register G.
CLF / []                  / Clear register FLAGS.

EMT / [ADDR]              / Emit value at [ADDR] to the output device(terminal) as a raw value.
PRT / [ADDR]              / Print a value at [ADDR] to the output device(terminal) as an ASCII value.

CMP / []                  / Store the resulting bool from A == B and store it in REGISTER_FLAGS.

INC / [VAL]               / Increment value in A by [VAL].
DEC / [VAL]               / Decrement value in A by [VAL].

LSH / [BITS]              / Shift value in A to the left by [BITS] and store result in A.
RSH / [BITS]              / Shift value in A to the right by [BITS] and store result in A.

ADD / []                  / Add A and B together then store the result in A.
SUB / []                  / Sub B from A then store the result in A.
MUL / []                  / Multiply A by B then store the result in A.
DIV / []                  / Divide A by B then store the result in A.
NEG / []                  / Negate A and then store the result in A.

AND / []                  / AND A and B together then store the result in A.
OR  / []                  / OR A and B together then store the result in A.
NOT / []                  / NOT A then store the result in A.

NUL / [ADDR]              / Set value at [ADDR] to null.

JMP / [ADDR]              / Set the program counter to [ADDR].
JMR / [ADDR]              / Set the program counter to current address + [ADDR].

JIN / [ADDR]              / Set the program counter to [ADDR] if FLAGS is false.
JIE / [ADDR]              / Set the program counter to [ADDR] if FLAGS is true.

HLT / []                  / Halt the CPU.
```
