#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <string>

using namespace std;

class registers;  // Forward declaration for use in execute

class instruction {
    
private:
    string name;
    int opCode;

public:
    instruction() : name(""), opCode(0) {}

    instruction(const string& n, int code) : name(n), opCode(code) {}

    // Setters
    void setName(const string &n) { name = n; }
    void setOpCode(int code) { opCode = code; }

    // Getters
    string getName() const { return name; }
    int getOpCode() const { return opCode; }

    // Pure virtual execute method, to be implemented by derived classes
    virtual void execute(registers &registerFile, int &pc, int *memory) = 0;

    virtual void display() const {
        cout << "Instruction: " << name << ", Opcode: " << opCode << endl;
    }

    // Virtual destructor to allow proper cleanup of derived classes
    virtual ~instruction() = default;
};

#endif  // End of header guard
