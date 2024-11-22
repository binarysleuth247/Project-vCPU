#include <iostream>
<<<<<<< HEAD
#include <sstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

// Enum for instruction types
enum InstructionType { ADD, SUB, LOAD, STORE, UNKNOWN };

// ALU class that also decodes the instruction type
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

// General-purpose registers class
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

// Program Counter and Instruction Register class
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

// Assembler: Convert assembly code to machine code
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

=======
#include <vector>

class ALU {
public:
    int performOperation(const std::string& operation, int operand1, int operand2) {
        if (operation == "ADD") return operand1 + operand2;
        if (operation == "SUB") return operand1 - operand2;
        if (operation == "AND") return operand1 & operand2;
        if (operation == "OR") return operand1 | operand2;
        return 0; // Default case
    }
};

class CPU {
    int programCounter;
    int instructionRegister;
public:
    CPU() : programCounter(0), instructionRegister(0) {}

    int getPC() const { return programCounter; }
    void setPC(int value) { programCounter = value; }

    int getIR() const { return instructionRegister; }
    void setIR(int value) { instructionRegister = value; }

    void fetchInstruction(const std::vector<int>& memory) {
        instructionRegister = memory[programCounter];
        programCounter++;
    }
};

class Registers {
    int reg[4]; // Let's assume 4 general-purpose registers
public:
    int getRegister(int index) const { return reg[index]; }
    void setRegister(int index, int value) { reg[index] = value; }
};


int main() {
    ALU alu;
    Registers regs;
    CPU cpu;

    std::vector<int> memory = {0x010203, 0x040506}; // Example instructions in memory

    // Simulating fetching and executing instructions
    for (int i = 0; i < memory.size(); ++i) {
        cpu.fetchInstruction(memory);
        int instruction = cpu.getIR();
        int operand1 = (instruction & 0xFF0000) >> 16; // Extracting operands
        int operand2 = (instruction & 0x00FF00) >> 8;
        int operation = instruction & 0x0000FF;

        // For simplicity, let's assume operations are encoded as integers
        int result = alu.performOperation("ADD", operand1, operand2); // Assuming ADD operation
        std::cout << "Instruction: " << instruction << ", Result: " << result << std::endl;
    }

>>>>>>> c70d70303a5d72c4a39d48491cf8e55b7bd81225
    return 0;
}
