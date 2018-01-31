# 8BitComputer
Simple 8 bit computer emulator.

```
NOP / []                 / No operation.

LDA / [ADDR]             / Load value at [ADDR] into A.
LDB / [ADDR]             / Load value at [ADDR] into B.
STC / [ADDR]             / Store value in C to [ADDR].

EMT / [ADDR]             / Emit value at [ADDR] to the output device(terminal) as a raw value.
PRT / [ADDR]             / Print a value at [ADDR] to the output device(terminal) as an ASCII value.

ADD / []                 / Add A and B together then store the result in C.
SUB / []                 / Sub B from A then store the result in C.
AND / []                 / AND A and B together then store the result in C.
OR  / []                 / OR A and B together then store the result in C.
NOT / []                 / NOT A then store the result in C.

JMP / [ADDR]             / Set the program counter to [ADDR].
JMR / [ADDR]             / Set the program counter to current address + [ADDR].
JIN / [ADDR, CMPR]       / Set the program counter to [ADDR] if value at [CMPR] == 0.
JIE / [ADDR, CMPR, VALU] / Set the program counter to [ADDR] if value at [CMPR] == [VALU].

HLT / []                 / Halt the CPU.
```

Instructions take the shape of the following format.
```
INSTR [ARG1, ARG2, ARG3]
```