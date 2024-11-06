//
//  UType.h
//  AssemblyProject1
//
//  Created by Mohamed El-Refai on 06/11/2024.
//

#ifndef UType_h
#define UType_h

#include "instruction.h"
#include <iostream>

using namespace std;

class UType : public instruction {

private:
    int rd;       // Destination register
    int imm;      // 20-bit upper immediate value

public:
    // Constructor to initialize all members, including inherited name and opCode
    UType(const string &name, int opCode, int rd, int imm)
        : rd(rd), imm(imm) {
            setName(name);     // Setting inherited member
            setOpCode(opCode); // Setting inherited member
    }

    // Getters for rd and the immediate
    int getRD() const {
        return rd;
    }

    int getImmediate() const {
        // Shift the 20-bit immediate to the upper 20 bits as per U-type encoding
        return imm << 12;
    }

    // Display function for debugging or logging
    void display() const {
        cout << "U-Type Instruction - "
        << "Name: " << getName() << ", Opcode: " << getOpCode()
             << ", RD: " << rd
             << ", Immediate (shifted): " << getImmediate() << endl;
    }
};

#endif /* UType_h */
