# Week 3: Basic CPU Components

## Objective
The goal of this week is to implement the core components of a CPU. This includes building the Arithmetic Logic Unit (ALU), implementing general-purpose registers, and creating the program counter and instruction register.

## Program Counter and Instruction Register

### Overview
The **Program Counter (PC)** and **Instruction Register (IR)** are critical components in the design of a CPU. They work together to ensure that instructions are fetched, decoded, and executed in a sequential manner.

### Program Counter (PC)
The PC holds the memory address of the next instruction to be executed. It increments automatically after each instruction fetch, ensuring the CPU processes instructions sequentially unless a jump or branch instruction modifies the sequence.

### Instruction Register (IR)
The IR holds the currently executing instruction fetched from memory. It temporarily stores the instruction so that the CPU can decode and execute it.

## Program Structure

[Source Code](/Week%203/Register.cpp)

## Explanation

### Program Counter (PC)
- **Initialization**: The PC is initialized to `0` in the CPU class constructor.
- **Fetching**: In the `fetchInstruction` method, the PC points to the memory address of the next instruction.
- **Incrementing**: After fetching an instruction, the PC is incremented to point to the next instruction.

### Instruction Register (IR)
- **Holding Instructions**: The IR holds the instruction fetched from memory.
- **Fetching**: In the `fetchInstruction` method, the IR is set to the value of the memory at the address pointed to by the PC.
- **Decoding and Executing**: The fetched instruction can then be decoded and executed by the CPU.

### Simulated CPU Execution
- **Memory Representation**: A vector `memory` is used to represent the instruction memory.
- **Fetching and Storing**: The CPU fetches instructions from this memory, stores them in the IR, and increments the PC.
- **Execution**: The ALU performs operations based on the fetched instructions, demonstrating how arithmetic and logical operations would be executed.

## Arithmetic Logic Unit (ALU)

The **Arithmetic Logic Unit (ALU)** is a critical component of the CPU that performs arithmetic and logic operations. It's the execution core of the CPU, where all the actual computation happens.

### Key Functions of the ALU

#### Arithmetic Operations
- **Addition**: Adds two numbers.
- **Subtraction**: Subtracts one number from another.
- **Multiplication**: Multiplies two numbers (though sometimes handled by a separate multiplier unit).
- **Division**: Divides one number by another (though often handled by a separate division unit).

#### Logical Operations
- **AND**: Performs a bitwise AND operation.
- **OR**: Performs a bitwise OR operation.
- **NOT**: Performs a bitwise NOT operation, inverting each bit.
- **XOR**: Performs a bitwise XOR operation.

#### Comparison Operations
- **Equality**: Checks if two numbers are equal.
- **Inequality**: Checks if two numbers are not equal.
- **Greater Than**: Checks if one number is greater than another.
- **Less Than**: Checks if one number is less than another.

#### Shift Operations
- **Left Shift**: Shifts bits to the left, filling with zeros.
- **Right Shift**: Shifts bits to the right, with the option of filling with zeros (logical shift) or preserving the sign bit (arithmetic shift).

### ALU Structure
An ALU is typically composed of:
- **Input Registers**: These hold the operands (the numbers to be operated on).
- **Operation Decoder**: This decodes the operation to be performed (e.g., add, subtract).
- **Arithmetic Circuitry**: Performs arithmetic operations.
- **Logic Circuitry**: Performs logic operations.
- **Output Register**: Holds the result of the operation.

## Conclusion
The Program Counter (PC) and Instruction Register (IR) are essential for the sequential execution of instructions in a CPU, while the ALU is responsible for performing the core computations. Together, these components form the backbone of CPU operations, enabling the execution of programs by processing instructions methodically and efficiently. This project lays the foundation for understanding how modern processors handle instruction cycles and perform computations, providing a solid base for further exploration into CPU architecture and design. 🚀
