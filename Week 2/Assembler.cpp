#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

enum InstructionType { ADD, SUB, LOAD, STORE, UNKNOWN };

// Function to map string instructions to enum types
InstructionType getInstructionType(const string& inst) {
    if (inst == "ADD") return ADD;
    if (inst == "SUB") return SUB;
    if (inst == "LOAD") return LOAD;
    if (inst == "STORE") return STORE;
    return UNKNOWN;
}

// Function to convert assembly to machine code
string assemble(const string& assemblyCode) {
    map<string, int> registers = { {"R0", 0}, {"R1", 1}, {"R2", 2}, {"R3", 3} };
    istringstream iss(assemblyCode);
    string line, machineCode;
    while (getline(iss, line)) {
        istringstream linestream(line);
        string opcode, reg1, reg2;
        linestream >> opcode >> reg1 >> reg2;
        int machineInstruction = getInstructionType(opcode) << 6 | registers[reg1] << 3 | registers[reg2];
        machineCode += to_string(machineInstruction) + "\n";
    }
    return machineCode;
}

// Main function to handle input and output
int main() {
    // Display sample input and output
    string sampleInput = "ADD R1 R2\nSUB R0 R3\nLOAD R1 R0\nSTORE R2 R1\n";
    cout << "Sample Input:\n" << sampleInput;
    cout << "\nSample Output:\n" << assemble(sampleInput) << endl;
    
    // Take user input
    cout << "Enter your assembly code (type END to finish):\n";
    string assemblyCode, line;
    while (getline(cin, line)) {
        if (line == "END") break;
        assemblyCode += line + "\n";
    }
    cout << "\nMachine Code:\n" << assemble(assemblyCode) << endl;
    
    return 0;
}
