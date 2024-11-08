#ifndef SBTYPE_H
#define SBTYPE_H

#include "instruction.h"
#include "registers.h"
#include <iostream>

class SBType : public instruction {
private:
    int rs1, rs2, imm4_1, imm10_5, imm11, imm12, func3;

public:
    // Constructor to initialize all members, including inherited name and opCode
    SBType(int opCode, int rs1, int rs2, int imm4_1, int imm10_5, int imm11, int imm12, int func3)
        : instruction("SBType", opCode), rs1(rs1), rs2(rs2), imm4_1(imm4_1), imm10_5(imm10_5), imm11(imm11), imm12(imm12), func3(func3) {}

    // Method to assemble the immediate field
    int getImmediate() const {
        // Combine immediate bits according to RISC-V SB-type format
        int imm = (imm12 << 12) | (imm11 << 11) | (imm10_5 << 5) | (imm4_1 << 1);
        
        // Sign-extend the 13-bit immediate
        if (imm & (1 << 12)) {
            imm |= 0xFFFFE000;  // Sign-extend to 32 bits if the sign bit is set
        }
        return imm;
    }
    
    // Execution function specific to SB-type instructions
    void execute(registers &registerFile, int &programCounter, int *memory) override {
        int rs1Value = registerFile.get(rs1);  // Get value from rs1
        int rs2Value = registerFile.get(rs2);  // Get value from rs2
        int targetPC = programCounter + getImmediate();

        switch (func3) {
            case 0:  // BEQ: Branch if Equal
                if (rs1Value == rs2Value) {
                    programCounter = targetPC;
                    cout << "Executing BEQ: Branching to " << programCounter << " as x" << rs1 << " == x" << rs2 << endl;
                } else {
                    cout << "Executing BEQ: No branch as x" << rs1 << " != x" << rs2 << endl;
                }
                break;

            case 1:  // BNE: Branch if Not Equal
                if (rs1Value != rs2Value) {
                    programCounter = targetPC;
                    cout << "Executing BNE: Branching to " << programCounter << " as x" << rs1 << " != x" << rs2 << endl;
                } else {
                    cout << "Executing BNE: No branch as x" << rs1 << " == x" << rs2 << endl;
                }
                break;

            case 4:  // BLT: Branch if Less Than
                if (rs1Value < rs2Value) {
                    programCounter = targetPC;
                    cout << "Executing BLT: Branching to " << programCounter << " as x" << rs1 << " < x" << rs2 << endl;
                } else {
                    cout << "Executing BLT: No branch as x" << rs1 << " >= x" << rs2 << endl;
                }
                break;

            case 5:  // BGE: Branch if Greater or Equal
                if (rs1Value >= rs2Value) {
                    programCounter = targetPC;
                    cout << "Executing BGE: Branching to " << programCounter << " as x" << rs1 << " >= x" << rs2 << endl;
                } else {
                    cout << "Executing BGE: No branch as x" << rs1 << " < x" << rs2 << endl;
                }
                break;

            case 6:  // BLTU: Branch if Less Than Unsigned
                if (static_cast<unsigned int>(rs1Value) < static_cast<unsigned int>(rs2Value)) {
                    programCounter = targetPC;
                    cout << "Executing BLTU: Branching to " << programCounter << " as x" << rs1 << " < x" << rs2 << " (unsigned)" << endl;
                } else {
                    cout << "Executing BLTU: No branch as x" << rs1 << " >= x" << rs2 << " (unsigned)" << endl;
                }
                break;

            case 7:  // BGEU: Branch if Greater or Equal Unsigned
                if (static_cast<unsigned int>(rs1Value) >= static_cast<unsigned int>(rs2Value)) {
                    programCounter = targetPC;
                    cout << "Executing BGEU: Branching to " << programCounter << " as x" << rs1 << " >= x" << rs2 << " (unsigned)" << endl;
                } else {
                    cout << "Executing BGEU: No branch as x" << rs1 << " < x" << rs2 << " (unsigned)" << endl;
                }
                break;

            default:
                cout << "Unknown SB-Type Instruction with func3 = " << func3 << endl;
                break;
        }
    }

    // Display function for debugging or logging
    void display() const override {
        cout << "SB-Type Instruction - "
             << "Name: " << getName() << ", Opcode: " << getOpCode()
             << ", RS1: " << rs1 << ", RS2: " << rs2
             << ", Immediate: " << getImmediate() << ", FUNC3: " << func3 << endl;
    }
};

#endif /* SBTYPE_H */
