//
//  SBType.h
//  AssemblyProject1
//
//  Created by Mohamed El-Refai on 06/11/2024.
//

#ifndef SBType_h
#define SBType_h

//
// SBTypeInstruction.h
// AssemblyProject1
//

#include "instruction.h"
#include <iostream>

using namespace std;

class SBType : public instruction {

private:
    int rs1;      // Source register 1
    int rs2;      // Source register 2
    int imm4_1;   // Immediate bits 4-1
    int imm10_5;  // Immediate bits 10-5
    int imm11;    // Immediate bit 11
    int imm12;    // Immediate bit 12 (most significant bit)
    int func3;    // Function code 3

public:
    // Constructor to initialize all members, including inherited name and opCode
    SBType(const string &name, int opCode, int rs1, int rs2, int imm4_1, int imm10_5, int imm11, int imm12, int func3)
        : rs1(rs1), rs2(rs2), imm4_1(imm4_1), imm10_5(imm10_5), imm11(imm11), imm12(imm12), func3(func3) {
            setName(name);     // Setting inherited member
            setOpCode(opCode); // Setting inherited member
    }

    // Method to assemble the immediate field
    int getImmediate() const {
        // Combine immediate bits according to RISC-V SB-type format
        int imm = (imm12 << 12)     // imm[12]
                | (imm11 << 11)     // imm[11]
                | (imm10_5 << 5)    // imm[10:5]
                | (imm4_1 << 1);    // imm[4:1]
        
        // Sign extend the 13-bit immediate
        if (imm & (1 << 12)) {  // If the 13th bit is set
            imm |= 0xFFFFE000;  // Sign extend to 32 bits
        }
        
        return imm;
    }

    // Getters for each register and function code
    int getRS1() const {
        return rs1;
    }

    int getRS2() const {
        return rs2;
    }

    int getFunc3() const {
        return func3;
    }

    // Display function for debugging or logging
    void display() const {
        cout << "SB-Type Instruction - "
        << "Name: " << getName()<< ", Opcode: " << getOpCode()
             << ", RS1: " << rs1 << ", RS2: " << rs2
             << ", Immediate: " << getImmediate() << ", FUNC3: " << func3 << endl;
    }
};

#endif /* SBType_h */
