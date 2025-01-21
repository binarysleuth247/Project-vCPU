## Updated Advance Features
### 1. Branching and Control Flow Instruction

**JUMP Instruction:**
The `JUMP` instruction allows the program to jump to a specific memory address and continue execution from there. This is useful for implementing loops or conditional branching.

In the `decodeAndExecute` method:
```cpp
else if (opcodeStr == "JUMP") {
    programCounter = operand2;
    outputStream << "Jumping to address " << operand2 << endl;
}
```

### 2. Subroutines and Interrupts

**CALL and RET Instructions:**
The `CALL` instruction is used to call subroutines. It saves the address of the next instruction to a specific memory location (used as a stack) and jumps to the address of the subroutine.

The `RET` instruction is used to return from subroutines. It retrieves the address stored by the `CALL` instruction and continues execution from there.

In the `decodeAndExecute` method:
```cpp
else if (opcodeStr == "CALL") {
    memory.write(memorySpace.size() - 1, programCounter);
    programCounter = operand2;
    outputStream << "Calling subroutine at address " << operand2 << endl;
} else if (opcodeStr == "RET") {
    programCounter = memory.read(memorySpace.size() - 1);
    outputStream << "Returning from subroutine to address " << programCounter << endl;
}
```

### 3. Simple Pipeline Mechanism

The CPU fetches and decodes instructions in sequence. A more advanced pipeline would involve implementing separate stages and handling hazards. For now, we’ve ensured the program fetches, decodes, and executes instructions in order:
```cpp
void executeProgram(ostream& outputStream) {
    while (programCounter < instructionMemory.size()) {
        int instruction = instructionMemory[programCounter];
        outputStream << "Fetching instruction at address " << programCounter << ": " << instruction << endl;
        programCounter++;
        decodeAndExecute(instruction, outputStream);
    }
}
```

### Changes in the Assembler

Added support for the new opcodes like `JUMP`, `CALL`, and `RET`:
```cpp
map<string, int> opcodes = {{"ADD", 0}, {"SUB", 1}, {"LOAD", 2}, {"STORE", 3}, {"INPUT", 4}, {"OUTPUT", 5}, {"JUMP", 6}, {"CALL", 7}, {"RET", 8}};
```

### Sample Assembly Code
Here's a simple example of how you might use these new instructions in an assembly program:
```assembly
CALL R1 R2  ; Call subroutine at address in R2
LOAD R0 R3  ; Load value from memory address in R3 into R0
ADD R0 R1   ; Add value in R1 to R0
STORE R0 R3 ; Store value in R0 to memory address in R3
JUMP R0 R2  ; Jump to address in R2
RET R0 R1   ; Return from subroutine
```

