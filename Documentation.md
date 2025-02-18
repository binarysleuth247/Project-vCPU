# CPU Emulator Documentation

## Overview

This program simulates a simple CPU with an Arithmetic Logic Unit (ALU), general-purpose registers, memory management, and an assembler to convert assembly code into machine code. The program executes instructions provided in a specified assembly file.

## Components

### Enumerations

```cpp
enum InstructionType { ADD, SUB, LOAD, STORE, INPUT, OUTPUT, JUMP, CALL, RET, UNKNOWN };
```
- Represents different types of instructions that the CPU can execute.

### Helper Functions

```cpp
// Converts a binary string to a decimal integer
int binaryToDecimal(const string& binary) {
    return stoi(binary, nullptr, 2);
}

// Converts a decimal integer to an 8-bit binary string
string decimalToBinary(int decimal) {
    return bitset<8>(decimal).to_string();
}
```

### Classes

#### ALU Class

Handles arithmetic and logic operations.

- **Member Functions:**

```cpp
class ALU {
public:
    string performOperation(const string& opcode, const string& operand1, const string& operand2) {
        int op1 = binaryToDecimal(operand1);
        int op2 = binaryToDecimal(operand2);
        int result;
        if (opcode == "ADD") result = op1 + op2;
        else if (opcode == "SUB") result = op1 - op2;
        else if (opcode == "LOAD") result = op2;
        else if (opcode == "STORE") result = op1;
        else result = 0;
        return decimalToBinary(result);
    }
};
```

#### Registers Class

Manages general-purpose registers.

- **Member Variables:**
  - `map<string, string> regs`
    - Stores the values of the registers in binary format.

- **Constructor and Member Functions:**

```cpp
class Registers {
public:
    map<string, string> regs;
    Registers() {
        regs["R0"] = decimalToBinary(0);
        regs["R1"] = decimalToBinary(4);
        regs["R2"] = decimalToBinary(9);
        regs["R3"] = decimalToBinary(10);
    }
    string get(const string& reg) { return regs[reg]; }
    void set(const string& reg, const string& value) { regs[reg] = value; }
    void display(ostream& outputStream) {
        for (const auto& reg : regs) {
            outputStream << reg.first << ": " << binaryToDecimal(reg.second) << " ";
        }
        outputStream << endl;
    }
};
```

#### Memory Class

Manages the CPU's memory space.

- **Member Variables:**
  - `vector<string> memorySpace`
    - Stores the values in memory in binary format.

- **Constructor and Member Functions:**

```cpp
class Memory {
public:
    vector<string> memorySpace;
    Memory(int size) : memorySpace(size, decimalToBinary(0)) {}
    string read(int address) {
        if (address < 0 || address >= memorySpace.size()) {
            cout << "Memory read error: Address out of bounds" << endl;
            return decimalToBinary(-1);
        }
        return memorySpace[address];
    }
    void write(int address, const string& value) {
        if (address < 0 || address >= memorySpace.size()) {
            cout << "Memory write error: Address out of bounds" << endl;
            return;
        }
        cout << "Writing value " << binaryToDecimal(value) << " to memory address " << address << endl;
        memorySpace[address] = value;
    }
    void display(ostream& outputStream) {
        for (int i = 0; i < memorySpace.size(); ++i) {
            outputStream << "Address " << i << ": " << binaryToDecimal(memorySpace[i]) << " ";
        }
        outputStream << endl;
    }
};
```

#### CPU Class

Represents the central processing unit, which manages the execution of instructions.

- **Member Variables:**
  - `int programCounter`
    - Keeps track of the current instruction address.
  - `vector<int> instructionMemory`
    - Stores the machine code instructions.
  - `Registers registers`
    - Manages the general-purpose registers.
  - `ALU alu`
    - Handles arithmetic and logic operations.
  - `Memory memory`
    - Manages the memory space.

- **Constructor and Member Functions:**

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

private:
    void decodeAndExecute(int instruction, ostream& outputStream) {
        int opcode = (instruction >> 6) & 0x03;
        int reg1 = (instruction >> 3) & 0x07;
        int reg2 = instruction & 0x07;
        string opcodeStr = getOpcodeString(opcode);

        outputStream << "Decoding instruction: " << instruction << " as (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")" << endl;

        string operand1 = registers.get("R" + to_string(reg1));
        string operand2 = registers.get("R" + to_string(reg2));

        outputStream << "Operands: " << "operand1 = " << binaryToDecimal(operand1) << ", operand2 = " << binaryToDecimal(operand2) << endl;

        if (opcodeStr == "INPUT") {
            int value;
            cout << "Enter value for R" << reg1 << ": ";
            cin >> value;
            registers.set("R" + to_string(reg1), decimalToBinary(value));
            outputStream << "Input value " << value << " into R" << reg1 << endl;
        } else if (opcodeStr == "OUTPUT") {
            int value = binaryToDecimal(registers.get("R" + to_string(reg1)));
            cout << "Output value from R" << reg1 << ": " << value << endl;
            outputStream << "Output value from R" << reg1 << ": " << value << endl;
        } else if (opcodeStr == "JUMP") {
            programCounter = binaryToDecimal(operand2);
            outputStream << "Jumping to address " << binaryToDecimal(operand2) << endl;
        } else if (opcodeStr == "CALL") {
            memory.write(memory.memorySpace.size() - 1, decimalToBinary(programCounter));
            programCounter = binaryToDecimal(operand2);
            outputStream << "Calling subroutine at address " << binaryToDecimal(operand2) << endl;
        } else if (opcodeStr == "RET") {
            programCounter = binaryToDecimal(memory.read(memory.memorySpace.size() - 1));
            outputStream << "Returning from subroutine to address " << programCounter << endl;
        } else {
            string result = alu.performOperation(opcodeStr, operand1, operand2);
            if (opcodeStr == "LOAD") {
                string value = memory.read(binaryToDecimal(operand2));
                registers.set("R" + to_string(reg1), value);
                outputStream << "Loaded value " <<binaryToDecimal(value)<<"into R"<<reg1<<endl;
            } else if (opcodeStr == "STORE") {
                memory.write(binaryToDecimal(operand2), operand1);
                outputStream << "Stored value " << binaryToDecimal(operand1) << " at memory address " << binaryToDecimal(operand2) << endl;
            } else {
                registers.set("R" + to_string(reg1), result);
                outputStream << "Executing instruction: " << instruction << " (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")" << endl;
                outputStream << "Updated R" << reg1 <<" to " << binaryToDecimal(result) << endl;
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
            case 6: return "JUMP";
            case 7: return "CALL";
            case 8: return "RET";
            default: return "UNKNOWN";
        }
    }
};
```

Sure, let's continue from where we left off!

### Assembler Function (continued)

```cpp
vector<int> assemble(const string& assemblyCode) {
    map<string, int> opcodes = {{"ADD", 0}, {"SUB", 1}, {"LOAD", 2}, {"STORE", 3}, {"INPUT", 4}, {"OUTPUT", 5}, {"JUMP", 6}, {"CALL", 7}, {"RET", 8}};
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

### Main Function

1. **Load Assembly Code:**
    - Loads assembly code from the `input.txt` file.
    
    ```cpp
    string assemblyCode;
    ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            assemblyCode += line + "\n";
        }
        inputFile.close();
        cout << "Input loaded from input.txt" << endl;
    } else {
        cout << "Unable to open input.txt" << endl;
        return 1;
    }
    ```

2. **Assemble Code:**
    - Converts the assembly code to machine code.
    
    ```cpp
    cout << "\nAssembling code...\n";
    vector<int> machineCode = assemble(assemblyCode);
    cout << "Converted Machine Code:\n";
    for (int code : machineCode) {
        cout << code << " ";
    }
    cout << endl;
    ```

3. **Initial Register States:**
    - Displays initial register states.
    
    ```cpp
    cout << "\nInitial Register States:\n";
    cpu.registers.display(cout);
    ```

4. **Load and Execute Program:**
    - Loads and executes the machine code program.
    
    ```cpp
    cpu.loadProgram(machineCode);
    cout << "\nExecuting program...\n";
    ```

5. **Redirect Output:**
    - Redirects output to both the console and the `output.txt` file.
    
    ```cpp
    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        ostringstream outputBuffer;
        cpu.executeProgram(outputBuffer);

        // Write buffer to file
        outputFile << outputBuffer.str();
        outputFile.close();

        cout << "Output saved in output.txt" << endl;
        cout << outputBuffer.str(); // Display buffer content to console
    } else {
        cout << "Unable to open output.txt" << endl;
    }
    ```

6. **Final Register States:**
    - Displays final register states.
    
    ```cpp
    cout << "Final Register States:\n";
    cpu.registers.display(cout);
    ```

### Complete Main Function

```cpp
int main() {
    CPU cpu;
    string assemblyCode;

    // Load assembly code from a file
    ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            assemblyCode += line + "\n";
        }
        inputFile.close();
        cout << "Input loaded from input.txt" << endl;
    } else {
        cout << "Unable to open input.txt" << endl;
        return 1;
    }

    cout << "Sample Assembly Code:\n" << assemblyCode << endl;

    // Convert assembly to machine code
    cout << "\nAssembling code...\n";
    vector<int> machineCode = assemble(assemblyCode);
    cout << "Converted Machine Code:\n";
    for (int code : machineCode) {
        cout << code << " ";
    }
    cout << endl;

    // Display initial register states
    cout << "\nInitial Register States:\n";
    cpu.registers.display(cout);

    // Load and execute program
    cpu.loadProgram(machineCode);
    cout << "\nExecuting program...\n";

    // Redirect output to both console and file
    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        ostringstream outputBuffer;
        cpu.executeProgram(outputBuffer);

        // Write buffer to file
        outputFile << outputBuffer.str();
        outputFile.close();

        cout << "Output saved in output.txt" << endl;
        cout << outputBuffer.str(); // Display buffer content to console
    } else {
        cout << "Unable to open output.txt" << endl;
    }

    // Display final register states
    cout << "Final Register States:\n";
    cpu.registers.display(cout);

    return 0;
}
```
## Usage

To compile and run the program:

1. Ensure the input assembly code is stored in `input.txt`.
2. Compile the program using a C++ compiler (e.g., `g++ -o cpu_emulator cpu_emulator.cpp`).
3. Run the executable (e.g., `./cpu_emulator`).

The program will read the assembly code from `input.txt`, execute it, and save the output to `output.txt`. The initial and final register states, along with intermediate execution steps, will be displayed on the console.

