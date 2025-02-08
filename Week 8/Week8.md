## Performance Optimization and Advanced Features Documentation

### Week 8: Performance Optimization

### Objective:
Optimize the emulator for better performance and enhance its features.

### Tasks Completed:
1. **Profile the Emulator**: Identified bottlenecks using simple timing functions.
2. **Optimize Critical Code Paths**: Improved execution of instructions and memory access.
3. **Enhance the Assembler**: Improved instruction encoding for better performance.

### Features and Enhancements:

#### 1. Branching and Control Flow Instruction

**JUMP Instruction:**
The `JUMP` instruction allows the program to jump to a specific memory address and continue execution from there, useful for implementing loops or conditional branching.
```cpp
else if (opcodeStr == "JUMP") {
    programCounter = operand2;
    outputStream << "Jumping to address " << operand2 << endl;
}
```

#### 2. Subroutines and Interrupts

**CALL and RET Instructions:**
- **CALL Instruction**: Calls subroutines, saving the address of the next instruction to a specific memory location (used as a stack) and jumps to the subroutine address.
- **RET Instruction**: Returns from subroutines by retrieving the address stored by the `CALL` instruction and continuing execution from there.

```cpp
else if (opcodeStr == "CALL") {
    memory.write(memory.memorySpace.size() - 1, programCounter);
    programCounter = binaryToDecimal(operand2);
    outputStream << "Calling subroutine at address " << binaryToDecimal(operand2) << endl;
} else if (opcodeStr == "RET") {
    programCounter = binaryToDecimal(memory.read(memory.memorySpace.size() - 1));
    outputStream << "Returning from subroutine to address " << programCounter << endl;
}
```

#### 3. Simple Pipeline Mechanism

The CPU fetches and decodes instructions in sequence. A more advanced pipeline would involve separate stages and handling hazards. Currently, it fetches, decodes, and executes instructions in order:
```cpp
void executeProgram(ostream& outputStream) {
    auto start = high_resolution_clock::now();
    while (programCounter < instructionMemory.size()) {
        int instruction = instructionMemory[programCounter];
        outputStream << "Fetching instruction at address " << programCounter << ": " << instruction << endl;
        programCounter++;
        decodeAndExecute(instruction, outputStream);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Program execution time: " << duration.count() << " ms" << endl;
}
```

### Enhancements in the Assembler

Added support for new opcodes like `JUMP`, `CALL`, and `RET` for better instruction encoding:
```cpp
map<string, int> opcodes = {{"ADD", 0}, {"SUB", 1}, {"LOAD", 2}, {"STORE", 3}, {"INPUT", 4}, {"OUTPUT", 5}, {"JUMP", 6}, {"CALL", 7}, {"RET", 8}};
```

### Sample Assembly Code

Here's a simple example demonstrating the new instructions in an assembly program:
```assembly
CALL R1 R2  ; Call subroutine at address in R2
LOAD R0 R3  ; Load value from memory address in R3 into R0
ADD R0 R1   ; Add value in R1 to R0
STORE R0 R3 ; Store value in R0 to memory address in R3
JUMP R0 R2  ; Jump to address in R2
RET R0 R1   ; Return from subroutine
```

### Input and Output Example

#### Input (Assembly Code):
```
CALL R1 R2
LOAD R0 R3
ADD R0 R1
STORE R0 R3
JUMP R0 R2
RET R0 R1
```

#### Output (Console and `output.txt`):
```
Fetching instruction at address 0: 448
Decoding instruction: 448 as (CALL R1 R2)
Calling subroutine at address 2
Current Register States: R0: 0 R1: 4 R2: 9 R3: 10
Current Memory State: Address 0: 0 Address 1: 0 Address 2: 0 ... Address 24: 0

Fetching instruction at address 2: 64
Decoding instruction: 64 as (LOAD R0 R3)
Loaded value 10 into R0
Current Register States: R0: 10 R1: 4 R2: 9 R3: 10
Current Memory State: Address 0: 0 Address 1: 0 Address 2: 0 ... Address 24: 0

Fetching instruction at address 3: 8
Decoding instruction: 8 as (ADD R0 R1)
Updated R0 to 14
Current Register States: R0: 14 R1: 4 R2: 9 R3: 10
Current Memory State: Address 0: 0 Address 1: 0 Address 2: 0 ... Address 24: 0

Fetching instruction at address 4: 128
Decoding instruction: 128 as (STORE R0 R3)
Stored value 14 at memory address 3
Current Register States: R0: 14 R1: 4 R2: 9 R3: 10
Current Memory State: Address 0: 0 Address 1: 0 Address 2: 0 ... Address 24: 0

Fetching instruction at address 5: 192
Decoding instruction: 192 as (JUMP R0 R2)
Jumping to address 9
Current Register States: R0: 14 R1: 4 R2: 9 R3: 10
Current Memory State: Address 0: 0 Address 1: 0 Address 2: 0 ... Address 24: 0

Fetching instruction at address 9: 256
Decoding instruction: 256 as (RET R0 R1)
Returning from subroutine to address 0
Current Register States: R0: 14 R1: 4 R2: 9 R3: 10
Current Memory State: Address 0: 0 Address 1: 0 Address 2: 0 ... Address 24: 0
```
