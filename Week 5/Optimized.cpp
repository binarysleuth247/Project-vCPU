#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <fstream>

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
    void display(ostream& out) {
        out << "Registers: ";
        for (const auto& reg : regs) {
            out << reg.first << ": " << reg.second << " ";
        }
        out << endl;
    }
};

// Memory management class
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
        memorySpace[address] = value;
    }

    void display(ostream& out) {
        out << "Memory: ";
        for (int i = 0; i < memorySpace.size(); ++i) {
            if (i % 8 == 0) out << endl;
            out << "[" << i << "]: " << memorySpace[i] << " ";
        }
        out << endl;
    }
};

// Program Counter and Instruction Register class
class CPU {
public:
    int programCounter;
    vector<int> instructionMemory;
    Registers registers;
    ALU alu;
    Memory memory;
    ofstream outFile;
    CPU() : programCounter(0), memory(256) {
        outFile.open("execution_log.txt");
    }

    ~CPU() {
        if (outFile.is_open()) {
            outFile.close();
        }
    }

    void loadProgram(const vector<int>& program) {
        instructionMemory = program;
    }

    void executeProgram() {
        while (programCounter < instructionMemory.size()) {
            // Fetch instruction
            int instruction = instructionMemory[programCounter];
            log("Fetching instruction at address " + to_string(programCounter) + ": " + to_string(instruction));
            programCounter++;

            // Decode and execute instruction
            decodeAndExecute(instruction);
        }
    }

    void log(const string& message) {
        cout << message << endl;
        outFile << message << endl;
    }

private:
    void decodeAndExecute(int instruction) {
        int opcode = (instruction >> 6) & 0x03; // Assuming 2 bits for opcode
        int reg1 = (instruction >> 3) & 0x07;  // Assuming 3 bits for register
        int reg2 = instruction & 0x07;          // Assuming 3 bits for register

        string opcodeStr = getOpcodeString(opcode);
        log("Decoding instruction: " + to_string(instruction) + " as (" + opcodeStr + " R" + to_string(reg1) + " R" + to_string(reg2) + ")");

        int operand1 = registers.get("R" + to_string(reg1));
        int operand2 = registers.get("R" + to_string(reg2));
        int result = alu.performOperation(opcodeStr, operand1, operand2);

        if (opcodeStr == "LOAD") {
            int value = memory.read(operand2);
            registers.set("R" + to_string(reg1), value);
            log("Loaded value " + to_string(value) + " into R" + to_string(reg1));
        } else if (opcodeStr == "STORE") {
            memory.write(operand2, operand1);
            log("Stored value " + to_string(operand1) + " at memory address " + to_string(operand2));
        } else {
            registers.set("R" + to_string(reg1), result);
            log("Executing instruction: " + to_string(instruction) + " (" + opcodeStr + " R" + to_string(reg1) + " R" + to_string(reg2) + ")");
            log("Updated R" + to_string(reg1) + " to " + to_string(result));
        }

        log("Current Register States: ");
        registers.display(outFile);
        log("Current Memory State: ");
        memory.display(outFile);
        log("");
    }

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
    map<string, int> opcodes = {{"ADD", 0}, {"SUB", 1}, {"LOAD", 2}, {"STORE", 3}};
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

int main() {
    CPU cpu;

    // Get assembly code input from the user
    string assemblyCode;
    cout << "Enter your assembly code (end with an empty line):" << endl;
    string line;
    while (getline(cin, line) && !line.empty()) {
        assemblyCode += line + "\n";
    }

    // Display the sample assembly code
    cpu.log("Sample Assembly Code:\n" + assemblyCode);

    // Convert assembly to machine code
    cpu.log("\nAssembling code...");
    vector<int> machineCode = assemble(assemblyCode);
    cpu.log("Converted Machine Code:");
    for (int code : machineCode) {
        cpu.log(to_string(code) + " ");
    }
    cpu.log("");

    // Display initial register states
    cpu.log("\nInitial Register States:");
    cpu.registers.display(cpu.outFile);

    // Load and execute program
    cpu.loadProgram(machineCode);
    cpu.log("\nExecuting program...");
    cpu.executeProgram();

    // Display final register states
    cpu.log("Final Register States:");
    cpu.registers.display(cpu.outFile);

    return 0;
}

