# Week 2: Instruction Set Architecture (ISA)

## Assembler Program Description

The Assembler Program is a tool designed to convert assembly code into machine code. It allows users to write assembly instructions, which are then translated into the binary code that a CPU can execute. This program provides an intuitive interface for entering assembly instructions and viewing the corresponding machine code.

### How to Use the Program

1. **Input Assembly Code**:
   - Enter your assembly instructions in the "Input" section. Each instruction should be on a new line.

2. **Assemble the Code**:
   - Click the "Assemble" button to convert the assembly code into machine code.

3. **View Output**:
   - The resulting machine code will be displayed in the "Output" section.

### Sample Input and Output

**Sample Input**:
```assembly
ADD R1, R2, R3
SUB R4, R5, R6
LOAD R1, [R2]
STORE R3, [R4]
```
**Sample Output**:
```text
0001000100100011
0010010001010110
0011000100100000
0100001101000000
```

### ADD:
**Operation**: Adds the values from two registers and stores the result in a destination register.  
**Format**: `ADD R1, R2, R3`  
**Description**: `R1 = R2 + R3`

### SUB:
**Operation**: Subtracts the value of the second register from the first register and stores the result in the destination register.  
**Format**: `SUB R1, R2, R3`  
**Description**: `R1 = R2 - R3`

### LOAD:
**Operation**: Loads a value from memory into a register.  
**Format**: `LOAD R1, [R2]`  
**Description**: `R1 = Memory[R2]`

### STORE:
**Operation**: Stores the value from a register into memory.  
**Format**: `STORE R1, [R2]`  
**Description**: `Memory[R2] = R1`

### MUL (Multiplication):
**Operation**: Multiplies the values from two registers and stores the result in a destination register.  
**Format**: `MUL R1, R2, R3`  
**Description**: `R1 = R2 * R3`

### DIV (Division):
**Operation**: Divides the value of the first register by the value of the second register and stores the result in a destination register.  
**Format**: `DIV R1, R2, R3`  
**Description**: `R1 = R2 / R3`

### AND (Bitwise AND):
**Operation**: Performs a bitwise AND operation on two registers and stores the result in a destination register.  
**Format**: `AND R1, R2, R3`  
**Description**: `R1 = R2 & R3`

### OR (Bitwise OR):
**Operation**: Performs a bitwise OR operation on two registers and stores the result in a destination register.  
**Format**: `OR R1, R2, R3`  
**Description**: `R1 = R2 | R3`

### XOR (Bitwise XOR):
**Operation**: Performs a bitwise XOR operation on two registers and stores the result in a destination register.  
**Format**: `XOR R1, R2, R3`  
**Description**: `R1 = R2 ^ R3`

### NOT (Bitwise NOT):
**Operation**: Performs a bitwise NOT operation on a single register and stores the result in the same register.  
**Format**: `NOT R1`  
**Description**: `R1 = ~R1`

### JMP (Jump):
**Operation**: Jumps to a specified memory address.  
**Format**: `JMP [address]`  
**Description**: `PC = address`

### JZ (Jump if Zero):
**Operation**: Jumps to a specified memory address if the zero flag is set.  
**Format**: `JZ [address]`  
**Description**: `if (ZF == 1) PC = address`

### JNZ (Jump if Not Zero):
**Operation**: Jumps to a specified memory address if the zero flag is not set.  
**Format**: `JNZ [address]`  
**Description**: `if (ZF == 0) PC = address`

### CALL (Call Subroutine):
**Operation**: Calls a subroutine at a specified memory address.  
**Format**: `CALL [address]`  
**Description**: `SP = PC; PC = address`

### RET (Return from Subroutine):
**Operation**: Returns from a subroutine to the instruction following the CALL.  
**Format**: `RET`  
**Description**: `PC = SP`

### CMP (Compare):
**Operation**: Compares the values of two registers and sets the appropriate flags.  
**Format**: `CMP R1, R2`  
**Description**: `ZF = (R1 == R2); SF = (R1 < R2)`


## Document the Instruction Formats:
Each instruction can have a specific format, often including the opcode and operands. Here’s a simple example:

| Instruction | Opcode | Format           | Description                      |
|-------------|--------|------------------|----------------------------------|
| ADD         | 0001   | ADD R1, R2, R3   | R1 = R2 + R3                     |
| SUB         | 0010   | SUB R1, R2, R3   | R1 = R2 - R3                     |
| LOAD        | 0011   | LOAD R1, [R2]    | R1 = Memory[R2]                  |
| STORE       | 0100   | STORE R1, [R2]   | Memory[R2] = R1                  |
| MUL         | 0101   | MUL R1, R2, R3   | R1 = R2 * R3                     |
| DIV         | 0110   | DIV R1, R2, R3   | R1 = R2 / R3                     |
| AND         | 0111   | AND R1, R2, R3   | R1 = R2 & R3                     |
| OR          | 1000   | OR R1, R2, R3    | R1 = R2 | R3                     |
| XOR         | 1001   | XOR R1, R2, R3   | R1 = R2 ^ R3                     |
| NOT         | 1010   | NOT R1           | R1 = ~R1                         |
| JMP         | 1011   | JMP [address]    | PC = address                     |
| JZ          | 1100   | JZ [address]     | if (ZF == 1) PC = address        |
| JNZ         | 1101   | JNZ [address]    | if (ZF == 0) PC = address        |
| CALL        | 1110   | CALL [address]   | SP = PC; PC = address            |
| RET         | 1111   | RET              | PC = SP                          |
| CMP         | 0000   | CMP R1, R2       | ZF = (R1 == R2); SF = (R1 < R2)  |


#### Create a Simple Assembler:
1. **Parser**: Read assembly code and parse each line to identify the instruction and operands.
2. **Opcode Mapping**: Create a mapping from instruction names to their corresponding opcode values.
3. **Code Generation**: Convert parsed instructions into machine code by replacing instruction names with opcodes and resolving operand addresses.
