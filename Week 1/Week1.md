# Week 1: Project Planning & Setup

## The Features of the Virtual CPU

### Instruction Set Features:
1. **Arithmetic Operations**:
   - **ADD**: Adds values from two registers.
   - **SUB**: Subtracts the value of one register from another.
   - **MUL**: Multiplies values from two registers.
   - **DIV**: Divides the value of one register by another.

2. **Logical Operations**:
   - **AND**: Performs a bitwise AND operation.
   - **OR**: Performs a bitwise OR operation.
   - **XOR**: Performs a bitwise XOR operation.
   - **NOT**: Performs a bitwise NOT operation.

3. **Data Transfer Operations**:
   - **LOAD**: Loads a value from memory into a register.
   - **STORE**: Stores the value from a register into memory.
   - **MOVE**: Moves data from one register to another.
   
4. **Control Flow Instructions**:
   - **JMP**: Jumps to a specified memory address.
   - **JZ**: Jumps if the zero flag is set.
   - **JNZ**: Jumps if the zero flag is not set.
   - **CALL**: Calls a subroutine.
   - **RET**: Returns from a subroutine.

5. **Comparison Operations**:
   - **CMP**: Compares the values of two registers.
   - **TEST**: Performs a logical comparison between two values.

### Architectural Features:
6. **Registers**:
   - General-purpose registers (R0, R1, R2, ...)
   - Special-purpose registers (Program Counter, Status Register, Stack Pointer)

7. **Memory**:
   - Main memory to store instructions and data.
   - Support for memory addressing modes (direct, indirect, indexed).

8. **Flags and Status Register**:
   - Zero flag, Carry flag, Overflow flag, Sign flag.

9. **Interrupt Handling**:
   - Basic interrupt system to handle hardware interrupts and exceptions.

### Execution Environment:
10. **Pipeline**:
    - Implement basic pipelining stages (Fetch, Decode, Execute, Memory Access, Write-back).

11. **Cache**:
    - Implement a simple cache mechanism to speed up memory access.

12. **I/O Operations**:
    - Input and output operations to simulate interaction with peripherals.

### Development and Testing:
13. **Assembler**:
    - A program to convert assembly language instructions into machine code.

14. **Debugger**:
    - Basic debugging tools to step through instructions, inspect register values, and set breakpoints.

15. **Simulator/Emulator**:
    - An environment to simulate the execution of programs on the vCPU.

16. **Documentation**:
    - Comprehensive documentation of the ISA, instruction formats, and operational behavior.

### Additional Considerations:
17. **Performance Metrics**:
    - Tools to measure execution time, memory usage, and other performance metrics.

18. **User Interface**:
    - A simple GUI to interact with the vCPU, load programs, and visualize execution.

## Programming Language: C++

### Why C++:
- **Performance**: C++ offers high performance, which is crucial for CPU emulation.
- **Control**: Greater control over system resources and memory management.
- **Extensive Libraries**: Access to numerous libraries for various functionalities.

### Tools and Frameworks:
- **Qt**: For GUI development.
- **Boost**: For a wide range of utility libraries.
- **Google Test**: For unit testing.
- **CMake**: For build automation.
- **GitHub/GitLab**: For version control.