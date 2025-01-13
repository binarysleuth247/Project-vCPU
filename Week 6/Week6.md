# CPU Simulation with Basic I/O Operations

This document explains the CPU simulation code that includes basic I/O operations. The code simulates a simple CPU with the ability to execute a set of instructions, perform ALU operations, manage memory, and handle basic I/O operations.

## Code Overview

### Enums and Classes

1. **InstructionType Enum:**
    ```cpp
    enum InstructionType { ADD, SUB, LOAD, STORE, INPUT, OUTPUT, UNKNOWN };
    ```
    Defines the types of instructions the CPU can handle.

2. **ALU Class:**
    ```cpp
    class ALU {
    public:
        int performOperation(const string& opcode, int operand1, int operand2) {
            if (opcode == "ADD") return operand1 + operand2;
            if (opcode == "SUB") return operand1 - operand2;
            if (opcode == "LOAD") return operand2;
            if (opcode == "STORE") return operand1;
            return 0;
        }
    };
    ```
    The Arithmetic Logic Unit (ALU) performs arithmetic and logic operations based on the opcode provided.

3. **Registers Class:**
    ```cpp
    class Registers {
    public:
        map<string, int> regs;
        Registers() {
            regs["R0"] = 0; regs["R1"] = 4; regs["R2"] = 9; regs["R3"] = 10;
        }
        int get(const string& reg) { return regs[reg]; }
        void set(const string& reg, int value) { regs[reg] = value; }
        void display(ostream& outputStream) {
            for (const auto& reg : regs) {
                outputStream << reg.first << ": " << reg.second << " ";
            }
            outputStream << endl;
        }
    };
    ```
    This class simulates general-purpose registers. It provides methods to get and set register values and display the register states.

4. **Memory Class:**
    ```cpp
    class Memory {
    public:
        vector<int> memorySpace;
        Memory(int size) : memorySpace(size, 0) {}
        int read(int address) {
            if (address < 0 || address >= memorySpace.size()) {
                cout << "Memory read error: Address out of bounds" << endl;
                return -1;
            }
            return memorySpace[address];
        }
        void write(int address, int value) {
            if (address < 0 || address >= memorySpace.size()) {
                cout << "Memory write error: Address out of bounds" << endl;
                return;
            }
            cout << "Writing value " << value << " to memory address " << address << endl;
            memorySpace[address] = value;
        }
        void display(ostream& outputStream) {
            for (int i = 0; i < memorySpace.size(); ++i) {
                outputStream << "Address " << i << ": " << memorySpace[i] << " ";
            }
            outputStream << endl;
        }
    };
    ```
    This class manages the memory of the CPU, allowing for reading and writing values to memory addresses, and displaying the memory state.

5. **CPU Class:**
    ```cpp
    class CPU {
    public:
        int programCounter;
        vector<int> instructionMemory;
        Registers registers;
        ALU alu;
        Memory memory;

        CPU() : programCounter(0), memory(25) {} // Initialize with memory size 25
        void loadProgram(const vector<int>& program) {
            instructionMemory = program;
        }
        void executeProgram(ostream& outputStream) {
            while (programCounter < instructionMemory.size()) {
                int instruction = instructionMemory[programCounter];
                outputStream << "Fetching instruction at address " << programCounter << ": " << instruction << endl;
                programCounter++;
                decodeAndExecute(instruction, outputStream);
            }
        }

    private:
        void decodeAndExecute(int instruction, ostream& outputStream) {
            int opcode = (instruction >> 6) & 0x03;
            int reg1 = (instruction >> 3) & 0x07;
            int reg2 = instruction & 0x07;
            string opcodeStr = getOpcodeString(opcode);

            outputStream << "Decoding instruction: " << instruction << " as (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")" << endl;

            int operand1 = registers.get("R" + to_string(reg1));
            int operand2 = registers.get("R" + to_string(reg2));

            outputStream << "Operands: " << "operand1 = " << operand1 << ", operand2 = " << operand2 << endl;

            if (opcodeStr == "INPUT") {
                int value;
                cout << "Enter value for R" << reg1 << ": ";
                cin >> value;
                registers.set("R" + to_string(reg1), value);
                outputStream << "Input value " << value << " into R" << reg1 << endl;
            } else if (opcodeStr == "OUTPUT") {
                int value = registers.get("R" + to_string(reg1));
                cout << "Output value from R" << reg1 << ": " << value << endl;
                outputStream << "Output value from R" << reg1 << ": " << value << endl;
            } else {
                int result = alu.performOperation(opcodeStr, operand1, operand2);
                if (opcodeStr == "LOAD") {
                    int value = memory.read(operand2);
                    registers.set("R" + to_string(reg1), value);
                    outputStream << "Loaded value " << value << " into R" << reg1 << endl;
                } else if (opcodeStr == "STORE") {
                    memory.write(operand2, operand1);
                    outputStream << "Stored value " << operand1 << " at memory address " << operand2 << endl;
                } else {
                    registers.set("R" + to_string(reg1), result);
                    outputStream << "Executing instruction: " << instruction << " (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")" << endl;
                    outputStream << "Updated R" << reg1 << " to " << result << endl;
                }
            }

            outputStream << "Current Register States: ";
            registers.display(outputStream);
            outputStream << "Current Memory State: ";
            memory.display(outputStream);
            outputStream << endl;
        }

        string getOpcodeString(int opcode) {
            switch (opcode) {
                case 0: return "ADD";
                case 1: return "SUB";
                case 2: return "LOAD";
                case 3: return "STORE";
                case 4: return "INPUT";
                case 5: return "OUTPUT";
                default: return "UNKNOWN";
            }
        }
    };
    ```
    The CPU class simulates the CPU functionality. It includes methods to load a program, execute it, decode and execute instructions, and manage the program counter.

### Assembler

```cpp
vector<int> assemble(const string& assemblyCode) {
    map<string, int> opcodes = {{"ADD", 0}, {"SUB", 1}, {"LOAD", 2}, {"STORE", 3}, {"INPUT", 4}, {"OUTPUT", 5}};
    map<string, int> registers = {{"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3}};
    istringstream iss(assemblyCode);
    string line;
    vector<int> machineCode;
    while (getline(iss, line)) {
        istringstream linestream(line);
        string opcode, reg1, reg2;
        linestream >> opcode >> reg1 >> reg2;
        int machineInstruction = (opcodes[opcode] << 6) | (registers[reg1] << 3) | registers[reg2];
        machineCode.push_back(machineInstruction);
    }
    return machineCode;
}
```
### Difference Between week 5 & 6

| Feature                           | Original Code                                                                 | Updated Code                                                                 |
|-----------------------------------|-------------------------------------------------------------------------------|------------------------------------------------------------------------------|
| **Instruction Types**             | `enum InstructionType { ADD, SUB, LOAD, STORE, UNKNOWN };`                     | `enum InstructionType { ADD, SUB, LOAD, STORE, INPUT, OUTPUT, UNKNOWN };`    |
| **ALU Operations**                | `int performOperation(const string& opcode, int operand1, int operand2)`       | No change                                                                   |
| **Registers Class**               | No change                                                                     | No change                                                                   |
| **Memory Class**                  | No change                                                                     | No change                                                                   |
| **CPU Class Constructor**         | `CPU() : programCounter(0), memory(25) {}`                                     | No change                                                                   |
| **CPU Class `executeProgram`**    | No change                                                                     | No change                                                                   |
| **CPU Class `decodeAndExecute`**  | `void decodeAndExecute(int instruction, ostream& outputStream)`                | Added handling for `INPUT` and `OUTPUT` instructions                        |
| **Decode And Execute Function**   | Handles `ADD`, `SUB`, `LOAD`, `STORE` instructions                            | Added cases for `INPUT`, `OUTPUT` instructions                              |
| **Opcode String Conversion**      | `string getOpcodeString(int opcode)`                                           | Added cases for `INPUT`, `OUTPUT`                                           |
| **Assembler Function**            | Handles `ADD`, `SUB`, `LOAD`, `STORE` instructions                            | Added handling for `INPUT`, `OUTPUT` instructions                           |
| **Main Function - Input File**    | `ifstream inputFile("input.txt");`                                            | No change                                                                   |
| **Main Function - Assembly Code** | `string assemblyCode;`                                                        | No change                                                                   |
| **Main Function - Output File**   | `ofstream outputFile("output.txt");`                                          | No change                                                                   |
| **Input Instruction Handling**    | Not present                                                                   | `if (opcodeStr == "INPUT") { int value; cout << "Enter value for R" << ...` |
| **Output Instruction Handling**   | Not present                                                                   | `if (opcodeStr == "OUTPUT") { int value = registers.get("R" + ...`           |


### Summary of Changes:
- **Instruction Types:** Added `INPUT` and `OUTPUT` instructions.
- **CPU Class `decodeAndExecute`:** Added handling for `INPUT` and `OUTPUT` instructions.
- **Decode And Execute Function:** Extended to include I/O instructions.
- **Opcode String Conversion:** Extended to return strings for `INPUT` and `OUTPUT` opcodes.
- **Assembler Function:** Extended to handle `INPUT` and `OUTPUT` instructions.
- **Input and Output Handling:** Added logic to read from the keyboard and write to the display. 
