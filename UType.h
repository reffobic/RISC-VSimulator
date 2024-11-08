#ifndef UTYPE_H
#define UTYPE_H

#include "instruction.h"
#include "registers.h"
#include <iostream>

using namespace std;

class UType : public instruction {
    
private:
    int rd;       // Destination register
    int imm;      // 20-bit upper immediate value

public:
    // Constructor to initialize all members, including inherited name and opCode
    UType(const string &name, int opCode, int rd, int imm)
        : instruction(name, opCode), rd(rd), imm(imm) {}

    // Function to retrieve the full immediate by shifting to the upper 20 bits
    int getImmediate() const {
        return imm << 12;
    }

    // Execution function specific to U-type instructions
    void execute(registers &registerFile, int &currentPC, int *memory) override {
        if (getName() == "LUI") {
            registerFile.set(rd, getImmediate());  // Set immediate in destination register
            cout << "Executing LUI: x" << rd << " = " << getImmediate() << endl;
        } else if (getName() == "AUIPC") {
            registerFile.set(rd, getImmediate() + currentPC);  // Add immediate to PC
            cout << "Executing AUIPC: x" << rd << " = " << getImmediate() << " + " << currentPC << " = " << (getImmediate() + currentPC) << endl;
        } else {
            cout << "Unknown U-Type Instruction" << endl;
        }
    }

    // Display function for debugging or logging
    void display() const override {
        cout << "U-Type Instruction - "
             << "Name: " << getName() << ", Opcode: " << getOpCode()
             << ", RD: " << rd
             << ", Immediate (shifted): " << getImmediate() << endl;
    }
};

#endif /* UTYPE_H */
