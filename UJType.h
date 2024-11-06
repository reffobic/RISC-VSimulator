//
//  UJType.h
//  AssemblyProject1
//
//  Created by Mohamed El-Refai on 06/11/2024.
//

#ifndef UJType_h
#define UJType_h

#include "instruction.h"
#include <iostream>

using namespace std;

class UJType : public instruction {

private:
    int rd;        // Destination register
    int imm19_12;  // Immediate bits 19-12
    int imm11;     // Immediate bit 11
    int imm10_1;   // Immediate bits 10-1
    int imm20;     // Immediate bit 20 (most significant bit)

public:
    // Constructor to initialize all members, including inherited name and opCode
    UJType(const string &name, int opCode, int rd, int imm19_12, int imm11, int imm10_1, int imm20)
        : rd(rd), imm19_12(imm19_12), imm11(imm11), imm10_1(imm10_1), imm20(imm20) {
            setName(name);     // Setting inherited member
            setOpCode(opCode); // Setting inherited member
    }

    // Method to assemble the immediate field
    int getImmediate() const {
        // Combine immediate bits according to RISC-V UJ-type format
        int imm = (imm20 << 20)      // imm[20]
                | (imm19_12 << 12)   // imm[19:12]
                | (imm11 << 11)      // imm[11]
                | (imm10_1 << 1);    // imm[10:1]
        
        // Sign extend the 21-bit immediate to 32 bits
        if (imm & (1 << 20)) {  // If the 21st bit is set
            imm |= 0xFFE00000;  // Sign extend to 32 bits
        }
        
        return imm;
    }

    // Getter for the destination register
    int getRD() const {
        return rd;
    }

    // Display function for debugging or logging
    void display() const {
        cout << "UJ-Type Instruction - "
        << "Name: " << getName() << ", Opcode: " << getOpCode()
             << ", RD: " << rd
             << ", Immediate (assembled): " << getImmediate() << endl;
    }
};

#endif /* UJType_h */
