#include <iostream>
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

    return 0;
}
