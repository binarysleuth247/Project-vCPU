#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

enum InstructionType { ADD, SUB, LOAD, STORE, UNKNOWN };

// Function to map string instructions to enum types
InstructionType getInstructionType(const std::string& inst) {
    if (inst == "ADD") return ADD;
    if (inst == "SUB") return SUB;
    if (inst == "LOAD") return LOAD;
    if (inst == "STORE") return STORE;
    return UNKNOWN;
}

// Function to convert assembly to machine code
std::string assemble(const std::string& assemblyCode) {
    std::map<std::string, int> registers = { {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3} };
    std::istringstream iss(assemblyCode);
    std::string line, machineCode;
    while (std::getline(iss, line)) {
        std::istringstream linestream(line);
        std::string opcode, reg1, reg2;
        linestream >> opcode >> reg1 >> reg2;
        int machineInstruction = getInstructionType(opcode) << 6 | registers[reg1] << 3 | registers[reg2];
        machineCode += std::to_string(machineInstruction) + "\n";
    }
    return machineCode;
}

// Main function to handle input and output
int main() {
    // Display sample input and output
    std::string sampleInput = "ADD R1 R2\nSUB R0 R3\nLOAD R1 R0\nSTORE R2 R1\n";
    std::cout << "Sample Input:\n" << sampleInput;
    std::cout << "\nSample Output:\n" << assemble(sampleInput) << std::endl;
    
    // Take user input
    std::cout << "Enter your assembly code (type END to finish):\n";
    std::string assemblyCode, line;
    while (std::getline(std::cin, line)) {
        if (line == "END") break;
        assemblyCode += line + "\n";
    }
    std::cout << "\nMachine Code:\n" << assemble(assemblyCode) << std::endl;
    
    return 0;
}
