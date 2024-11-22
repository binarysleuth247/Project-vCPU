# Week 3: Basic CPU Components

### 1. ALU Class
```cpp
class ALU {
public:
    int performOperation(const string& opcode, int operand1, int operand2) {
        if (opcode == "ADD") return operand1 + operand2;
        if (opcode == "SUB") return operand1 - operand2;
        if (opcode == "LOAD") return operand2; // Example operation for LOAD
        if (opcode == "STORE") return operand1; // Example operation for STORE
        return 0; // Default for UNKNOWN or unsupported instructions
    }
};
```
- **performOperation**:
  - **Purpose**: This function performs arithmetic and logical operations based on the opcode provided.
  - **Parameters**:
    - `opcode`: A string representing the operation to be performed (e.g., "ADD", "SUB").
    - `operand1`: The first operand for the operation.
    - `operand2`: The second operand for the operation.
  - **Functionality**: Depending on the `opcode`, it executes the corresponding operation:
    - `ADD`: Adds `operand1` and `operand2`.
    - `SUB`: Subtracts `operand2` from `operand1`.
    - `LOAD`: Returns `operand2` (a simplified example of a load operation).
    - `STORE`: Returns `operand1` (a simplified example of a store operation).
    - For any unknown `opcode`, it returns `0`.

### 2. Registers Class
```cpp
class Registers {
public:
    map<string, int> regs;
    Registers() {
        regs["R0"] = 0; regs["R1"] = 4; regs["R2"] = 9; regs["R3"] = 10;
    }
    int get(const string& reg) { return regs[reg]; }
    void set(const string& reg, int value) { regs[reg] = value; }
    void display() {
        for (const auto& reg : regs) {
            cout << reg.first << ": " << reg.second << " ";
        }
        cout << endl;
    }
};
```
- **regs**:
  - **Purpose**: A map that stores register names as keys and their values as the associated integer.
  - **Initialization**: The constructor initializes the registers with default values (`R0 = 0`, `R1 = 4`, `R2 = 9`, `R3 = 10`).
- **get**:
  - **Purpose**: Returns the value of the specified register.
  - **Parameters**:
    - `reg`: The name of the register as a string (e.g., "R1").
  - **Returns**: The integer value stored in the register.
- **set**:
  - **Purpose**: Sets the value of the specified register.
  - **Parameters**:
    - `reg`: The name of the register as a string.
    - `value`: The integer value to set in the register.
- **display**:
  - **Purpose**: Displays the current values of all the registers.
  - **Functionality**: Iterates over the `regs` map and prints each register and its value.

### 3. CPU Class
```cpp
class CPU {
public:
    int programCounter;
    vector<int> instructionMemory;
    Registers registers;
    ALU alu;
    CPU() : programCounter(0) {}

    void loadProgram(const vector<int>& program) {
        instructionMemory = program;
    }

    void executeProgram() {
        while (programCounter < instructionMemory.size()) {
            int instruction = instructionMemory[programCounter];
            programCounter++;
            int opcode = (instruction >> 6) & 0x3F;
            int reg1 = (instruction >> 3) & 0x07;
            int reg2 = instruction & 0x07;

            string opcodeStr = getOpcodeString(opcode);
            int operand1 = registers.get("R" + to_string(reg1));
            int operand2 = registers.get("R" + to_string(reg2));
            int result = alu.performOperation(opcodeStr, operand1, operand2);

            registers.set("R" + to_string(reg1), result);

            cout << "Executed instruction: " << instruction << " (" << opcodeStr << " R" << reg1 << " R" << reg2 << ")" << endl;
            cout << "Updated R" << reg1 << " to " << result << endl;
            cout << "Current Register States: ";
            registers.display();
            cout << endl;
        }
    }

private:
    string getOpcodeString(int opcode) {
        switch (opcode) {
            case 0: return "ADD";
            case 1: return "SUB";
            case 2: return "LOAD";
            case 3: return "STORE";
            default: return "UNKNOWN";
        }
    }
};
```
- **programCounter**:
  - **Purpose**: Keeps track of the current instruction being executed.
  - **Initialization**: Initialized to `0` in the constructor.
- **instructionMemory**:
  - **Purpose**: Stores the machine code of the program.
- **registers**:
  - **Purpose**: An instance of the `Registers` class to manage register values.
- **alu**:
  - **Purpose**: An instance of the `ALU` class to perform operations.
- **loadProgram**:
  - **Purpose**: Loads the program into `instructionMemory`.
  - **Parameters**:
    - `program`: A vector of integers representing the machine code.
- **executeProgram**:
  - **Purpose**: Executes the program by fetching, decoding, and executing each instruction.
  - **Functionality**:
    - Iterates over the `instructionMemory` using the `programCounter`.
    - Extracts the `opcode`, `reg1`, and `reg2` from each instruction.
    - Converts the `opcode` to a string using `getOpcodeString`.
    - Fetches the operand values from the `registers`.
    - Performs the operation using the `alu`.
    - Updates the register with the result.
    - Prints the executed instruction, updated register value, and current register states after each instruction.
- **getOpcodeString**:
  - **Purpose**: Converts an opcode integer to its string representation.
  - **Parameters**:
    - `opcode`: An integer representing the opcode.
  - **Returns**: A string representing the opcode.

### 4. Assembler Function
```cpp
vector<int> assemble(const string& assemblyCode) {
    map<string, int> registers = { {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3} };
    istringstream iss(assemblyCode);
    string line;
    vector<int> machineCode;
    while (getline(iss, line)) {
        istringstream linestream(line);
        string opcode, reg1, reg2;
        linestream >> opcode >> reg1 >> reg2;
        int machineInstruction = static_cast<int>(ALU().performOperation(opcode, registers[reg1], registers[reg2])) << 6 | registers[reg1] << 3 | registers[reg2];
        machineCode.push_back(machineInstruction);
    }
    return machineCode;
}
```
- **assemble**:
  - **Purpose**: Converts assembly code into machine code.
  - **Parameters**:
    - `assemblyCode`: A string containing the assembly code.
  - **Functionality**:
    - Defines a map to convert register names to integers.
    - Reads the assembly code line by line.
    - Extracts the opcode and register names from each line.
    - Converts the opcode and registers to a machine instruction using the `ALU`.
    - Adds the machine instruction to the `machineCode` vector.
  - **Returns**: A vector of integers representing the machine code.

### 5. Main Function
```cpp
int main() {
    // Initialize components
    CPU cpu;

    // Get assembly code input from the user
    string assemblyCode;
    cout << "Enter your assembly code (end with an empty line):" << endl;
    string line;
    while (getline(cin, line) && !line.empty()) {
        assemblyCode += line + "\n";
    }

    // Display the sample assembly code
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
    cpu.registers.display();

    // Load and execute program
    cpu.loadProgram(machineCode);
    cout << "\nExecuting program...\n";
    cpu.executeProgram();

    // Display final register states
    cout << "Final Register States:\n";
    cpu.registers.display();

    return 0;
}
```
- **main**:
  - **Purpose**: Orchestrates the entire process from input to execution and output.
  - **Functionality**:
    - Initializes the `CPU` components.
    - Reads assembly code input from the user until an empty line is entered.
    - Displays the entered assembly code.
    - Converts the assembly code to machine code using the `assemble` function.
    - Displays the converted machine code.
    - Displays the initial state of the registers.
    - Loads the machine code into the
