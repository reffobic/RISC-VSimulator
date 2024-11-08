#ifndef UJTYPE_H
#define UJTYPE_H

#include "instruction.h"
#include "registers.h"
#include <iostream>

using namespace std;

class UJType : public instruction {
private:
    int rd;       // Destination register
    int imm;      // 20-bit upper immediate value

public:
    // Constructor to initialize all members, including inherited name and opCode
    UJType(const string &name, int opCode, int rd, int imm)
        : instruction(name, opCode), rd(rd), imm(imm) {}

    int getImmediate() const {
        int decodedImm = ((imm & 0xFF000) >> 12)    // Bits 19-12
                       | ((imm & 0x80000) >> 9)     // Bit 11
                       | ((imm & 0x7FE) << 1)       // Bits 10-1
                       | ((imm & 0x1) << 20);       // Bit 20 (sign bit)
        
        // Sign extend if the 20th bit is set
        if (decodedImm & (1 << 20)) {
            decodedImm |= 0xFFE00000;  // Sign extend to 32 bits
        }
        return decodedImm;
    }

    // Execution function specific to UJ-type instructions (e.g., JAL)
    void execute(registers &registerFile, int &pc, int *memory) override {
        if (getName() == "JAL") {
            registerFile.set(rd, pc + 4);  // Save return address
            pc = pc + getImmediate();      // Set pc to jump target
            cout << "Executing JAL: x" << rd << " = " << (pc + 4) << ", PC = " << pc << endl;
        } else {
            cout << "Unknown UJ-Type Instruction with opcode = " << getOpCode() << endl;
        }
    }

    // Display function for debugging or logging
    void display() const override {
        cout << "UJ-Type Instruction - "
             << "Name: " << getName() << ", Opcode: " << getOpCode()
             << ", RD: " << rd << ", Immediate: " << getImmediate() << endl;
    }
};

#endif /* UJTYPE_H */
