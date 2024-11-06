//
//  SType.h
//  AssemblyProject1
//
//  Created by Mohamed El-Refai on 06/11/2024.
//

#ifndef SType_h
#define SType_h

#include "instruction.h"
#include <iostream>

using namespace std;

class SType : public instruction {

private:
    int rs1;    // Source register 1
    int rs2;    // Source register 2
    int imm;    // Immediate value (could be split in encoding)
    int func3;  // Function code 3

public:
    // Constructor to initialize all members, including inherited name and opCode
    SType(const string &name, int opCode, int rs1, int rs2, int imm, int func3)
        : rs1(rs1), rs2(rs2), imm(imm), func3(func3) {
            setName(name);     // Setting inherited member
            setOpCode(opCode); // Setting inherited member
    }

    // Getters for each member
    int getRS1() const {
        return rs1;
    }

    int getRS2() const {
        return rs2;
    }

    int getImmediate() const {
        return imm;
    }

    int getFunc3() const {
        return func3;
    }

    // Display function for debugging or logging
    void display() const {
        cout << "S-Type Instruction - "
        << "Name: " << getName() << ", Opcode: " << getOpCode()
             << ", RS1: " << rs1 << ", RS2: " << rs2
             << ", IMM: " << imm << ", FUNC3: " << func3 << endl;
    }
};

#endif /* SType_h */
