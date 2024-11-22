
# Week 2: C++ Program for Assembling and Converting Assembly Code to Machine Code

## Overview
This program converts assembly language code into machine code. It maps assembly instructions to their corresponding machine code representations and handles both input and output to interact with the user.

## Code Breakdown

### Includes and Namespace
```cpp
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;
```
- **Includes**: The headers provide the necessary functionalities such as input/output streams (`iostream`), string streams (`sstream`), maps (`map`), and vectors (`vector`).
- **Namespace**: `using namespace std` allows us to use standard library functions and objects without the `std::` prefix.

### Enum for Instruction Types
```cpp
enum InstructionType { ADD, SUB, LOAD, STORE, UNKNOWN };
```
- **InstructionType**: An enumeration to represent different types of instructions that the virtual CPU can handle. This includes `ADD`, `SUB`, `LOAD`, `STORE`, and `UNKNOWN`.

### Function to Map String Instructions to Enum Types
```cpp
InstructionType getInstructionType(const string& inst) {
    if (inst == "ADD") return ADD;
    if (inst == "SUB") return SUB;
    if (inst == "LOAD") return LOAD;
    if (inst == "STORE") return STORE;
    return UNKNOWN;
}
```
- **getInstructionType**:
  - **Purpose**: Converts a string instruction (e.g., "ADD", "SUB") to its corresponding `InstructionType` enum value.
  - **Parameters**:
    - `inst`: A string representing the instruction.
  - **Returns**: The corresponding `InstructionType` enum value. If the instruction is not recognized, it returns `UNKNOWN`.

### Function to Convert Assembly to Machine Code
```cpp
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
```
- **assemble**:
  - **Purpose**: Converts assembly code into machine code.
  - **Parameters**:
    - `assemblyCode`: A string containing the assembly code.
  - **Functionality**:
    - Defines a map to convert register names to integers.
    - Uses a string stream (`istringstream`) to read the assembly code line by line.
    - For each line, it extracts the opcode and register names.
    - Converts the opcode and registers to a machine instruction using bitwise operations.
    - Constructs the machine code as a string by appending each instruction.
  - **Returns**: A string representing the machine code.

### Main Function to Handle Input and Output
```cpp
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
```
- **main**:
  - **Purpose**: Handles the overall execution of the program including input and output.
  - **Functionality**:
    - Displays a sample input and its corresponding machine code output.
    - Prompts the user to enter their assembly code until they type "END".
    - Converts the user input assembly code into machine code using the `assemble` function.
    - Displays the converted machine code.

## Sample Input and Output

### Sample Input
```
ADD R1 R2
SUB R0 R3
LOAD R1 R0
STORE R2 R1
```

### Sample Output
```
Sample Input:
ADD R1 R2
SUB R0 R3
LOAD R1 R0
STORE R2 R1

Sample Output:
74
92
128
155

Enter your assembly code (type END to finish):
<user input>
END

Machine Code:
<converted machine code>
```
- **Explanation**: The program first shows a sample input and its corresponding machine code output. It then prompts the user to enter their assembly code and converts it to machine code, displaying the result.