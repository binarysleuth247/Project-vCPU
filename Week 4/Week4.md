# Instruction Fetch-Decode-Execute Cycle

This project implements a simple instruction fetch-decode-execute cycle using a simulated CPU, ALU, and Registers in C++. The program reads assembly code, converts it to machine code, and executes it, displaying the register states before and after execution.

## Components

### 1. ALU (Arithmetic Logic Unit)
The `ALU` class performs arithmetic operations based on the opcode provided.

**Function:**

```cpp
int performOperation(const string& opcode, int operand1, int operand2);
```

- **Input:** 
  - `opcode`: The operation to perform (e.g., "ADD", "SUB").
  - `operand1`: The first operand.
  - `operand2`: The second operand.
- **Output:** The result of the operation.

**Example:**
- **Input:** `performOperation("ADD", 5, 3)`
- **Output:** `8`

### 2. Registers
The `Registers` class manages a set of general-purpose registers.

**Functions:**

```cpp
int get(const string& reg);
void set(const string& reg, int value);
void display();
```

- **Input:**
  - `get`: The register name (e.g., "R0").
  - `set`: The register name and value to set.
  - `display`: No input.
- **Output:**
  - `get`: The value of the specified register.
  - `set`: No output.
  - `display`: Prints the current state of all registers.

**Example:**
- **Input:** 
  - `get("R1")`
  - `set("R1", 10)`
- **Output:** 
  - `get`: `4` (initial value of R1)
  - `set`: No output
  - `display`: Prints current register states (e.g., `R0: 0 R1: 10 R2: 9 R3: 10`)

### 3. CPU
The `CPU` class simulates the program counter, instruction register, and manages the fetch-decode-execute cycle.

**Functions:**

```cpp
void loadProgram(const vector<int>& program);
void executeProgram();
```

- **Input:**
  - `loadProgram`: The program as a vector of machine instructions.
  - `executeProgram`: No input.
- **Output:**
  - `loadProgram`: No output.
  - `executeProgram`: Executes the loaded program and prints detailed fetch-decode-execute information and updated register states.

**Private Functions:**

```cpp
void decodeAndExecute(int instruction);
string getOpcodeString(int opcode);
```

- **Input:**
  - `decodeAndExecute`: The machine instruction to decode and execute.
  - `getOpcodeString`: The opcode to convert to string.
- **Output:**
  - `decodeAndExecute`: Executes the instruction and prints details.
  - `getOpcodeString`: Returns the string representation of the opcode.

**Example:**
- **Input:** 
  - `loadProgram({456, 889, 994, 1922})`
  - `executeProgram()`
- **Output:** 
  - Fetch, decode, and execute details for each instruction.

### 4. Assembler
The `assemble` function converts assembly code to machine code.

**Function:**

```cpp
vector<int> assemble(const string& assemblyCode);
```

- **Input:** The assembly code as a string.
- **Output:** The corresponding machine code as a vector of integers.

**Example:**
- **Input:** `assemble("ADD R1 R2\nSUB R3 R1\nLOAD R0 R2\nSTORE R3 R0")`
- **Output:** `{456, 889, 994, 1922}`

### 5. Main Function
The `main` function drives the program, handling user input and displaying the results.

**Function:**

```cpp
int main();
```

- **Input:** Assembly code entered by the user.
- **Output:** Prints the assembly code, machine code, and detailed execution steps including register states.

## Sample Execution

### Input Assembly Code:

```
ADD R1 R2
SUB R3 R1
LOAD R0 R2
STORE R3 R0
```

### Output:

```
Enter your assembly code (end with an empty line):
ADD R1 R2
SUB R3 R1
LOAD R0 R2
STORE R3 R0

Sample Assembly Code:
ADD R1 R2
SUB R3 R1
LOAD R0 R2
STORE R3 R0

Assembling code...
Converted Machine Code:
456 889 994 1922 

Initial Register States:
R0: 0 R1: 4 R2: 9 R3: 10 

Executing program...
Fetching instruction at address 0: 456
Decoding instruction: 456 as (ADD R1 R2)
Executing instruction: 456 (ADD R1 R2)
Updated R1 to 13
Current Register States: R0: 0 R1: 13 R2: 9 R3: 10 

Fetching instruction at address 1: 889
Decoding instruction: 889 as (SUB R3 R1)
Executing instruction: 889 (SUB R3 R1)
Updated R3 to -3
Current Register States: R0: 0 R1: 13 R2: 9 R3: -3 

Fetching instruction at address 2: 994
Decoding instruction: 994 as (LOAD R0 R2)
Executing instruction: 994 (LOAD R0 R2)
Updated R0 to 9
Current Register States: R0: 9 R1: 13 R2: 9 R3: -3 

Fetching instruction at address 3: 1922
Decoding instruction: 1922 as (STORE R3 R0)
Executing instruction: 1922 (STORE R3 R0)
Updated R3 to -3
Current Register States: R0: 9 R1: 13 R2: 9 R3: -3 

Final Register States:
R0: 9 R1: 13 R2: 9 R3: -3