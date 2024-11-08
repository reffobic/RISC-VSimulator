#ifndef ITYPE_H
#define ITYPE_H

#include "instruction.h"
#include "registers.h"
#include <iostream>

class IType : public instruction {
private:
    int rd, rs1, imm, func3;
    int *memory;  // Pointer to memory for load/store operations

public:
    // Constructor to initialize members and set memory access pointer
    IType(int rd, int rs1, int imm, int func3, int opCode, int *mem)
        : instruction("IType", opCode), rd(rd), rs1(rs1), imm(imm), func3(func3), memory(mem) {}

    void execute(registers &registerFile, int &pc, int *memory) override {
        int sourceRegisterValue = registerFile.get(rs1);  // Get value from rs1
        int result = 0;
        int effectiveAddress = sourceRegisterValue + imm;  // Calculate effective address for memory access

        if (getOpCode() == 0x13) {  // Immediate arithmetic/logical instructions
            switch (func3) {
                case 0:  // ADDI
                    result = sourceRegisterValue + imm;
                    cout << "Executing ADDI: x" << rd << " = x" << rs1 << " + " << imm << " = " << result << endl;
                    break;
                case 1:  // SLLI (Shift Left Logical Immediate)
                    result = sourceRegisterValue << (imm & 0x1F);  // Mask immediate to 5 bits
                    cout << "Executing SLLI: x" << rd << " = x" << rs1 << " << " << (imm & 0x1F) << " = " << result << endl;
                    break;
                case 2:  // SLTI
                    result = (sourceRegisterValue < imm) ? 1 : 0;
                    cout << "Executing SLTI: x" << rd << " = (x" << rs1 << " < " << imm << ") ? 1 : 0 = " << result << endl;
                    break;
                case 3:  // SLTIU
                    result = (static_cast<unsigned int>(sourceRegisterValue) < static_cast<unsigned int>(imm)) ? 1 : 0;
                    cout << "Executing SLTIU: x" << rd << " = (unsigned x" << rs1 << " < " << imm << ") ? 1 : 0 = " << result << endl;
                    break;
                case 4:  // XORI
                    result = sourceRegisterValue ^ imm;
                    cout << "Executing XORI: x" << rd << " = x" << rs1 << " ^ " << imm << " = " << result << endl;
                    break;
                case 5:  // SRLI and SRAI
                    if ((imm & 0x400) == 0) {  // SRLI (Shift Right Logical Immediate)
                        result = static_cast<unsigned int>(sourceRegisterValue) >> (imm & 0x1F);
                        cout << "Executing SRLI: x" << rd << " = x" << rs1 << " >> " << (imm & 0x1F) << " = " << result << endl;
                    } else {  // SRAI (Shift Right Arithmetic Immediate)
                        result = sourceRegisterValue >> (imm & 0x1F);
                        cout << "Executing SRAI: x" << rd << " = x" << rs1 << " >> " << (imm & 0x1F) << " = " << result << endl;
                    }
                    break;
                case 6:  // ORI
                    result = sourceRegisterValue | imm;
                    cout << "Executing ORI: x" << rd << " = x" << rs1 << " | " << imm << " = " << result << endl;
                    break;
                case 7:  // ANDI
                    result = sourceRegisterValue & imm;
                    cout << "Executing ANDI: x" << rd << " = x" << rs1 << " & " << imm << " = " << result << endl;
                    break;
                default:
                    cout << "Unknown I-Type Arithmetic/Logical Instruction with func3 = " << func3 << endl;
                    break;
            }
            registerFile.set(rd, result);  // Update destination register with the result
        } else if (getOpCode() == 0x03) {  // Load instructions
            switch (func3) {
                case 0:  // LB
                    result = static_cast<int8_t>(memory[effectiveAddress]);
                    cout << "Executing LB: x" << rd << " = " << result << " from address " << effectiveAddress << endl;
                    break;
                case 1:  // LH
                    result = static_cast<int16_t>(memory[effectiveAddress] | (memory[effectiveAddress + 1] << 8));
                    cout << "Executing LH: x" << rd << " = " << result << " from address " << effectiveAddress << endl;
                    break;
                case 2:  // LW
                    result = memory[effectiveAddress] | (memory[effectiveAddress + 1] << 8) |
                             (memory[effectiveAddress + 2] << 16) | (memory[effectiveAddress + 3] << 24);
                    cout << "Executing LW: x" << rd << " = " << result << " from address " << effectiveAddress << endl;
                    break;
                case 4:  // LBU
                    result = static_cast<uint8_t>(memory[effectiveAddress]);
                    cout << "Executing LBU: x" << rd << " = " << result << " from address " << effectiveAddress << endl;
                    break;
                case 5:  // LHU
                    result = static_cast<uint16_t>(memory[effectiveAddress] | (memory[effectiveAddress + 1] << 8));
                    cout << "Executing LHU: x" << rd << " = " << result << " from address " << effectiveAddress << endl;
                    break;
                default:
                    cout << "Unknown Load Instruction with func3 = " << func3 << endl;
                    break;
            }
            registerFile.set(rd, result);  // Store the loaded value in the destination register
        } else if (getOpCode() == 0x67) {  // JALR instruction
            registerFile.set(rd, pc + 4);  // Store return address in rd
            pc = (sourceRegisterValue + imm) & ~1;  // Set PC to target address (alignment adjustment)
            cout << "Executing JALR: x" << rd << " = PC + 4, PC = (x" << rs1 << " + " << imm << ") & ~1 = " << pc << endl;
        } else {
            cout << "Unknown I-Type Instruction with opcode = " << getOpCode() << endl;
        }
    }

    void display() const override {
        cout << "I-Type Instruction - Opcode: " << getOpCode() << ", RD: " << rd
             << ", RS1: " << rs1 << ", IMM: " << imm
             << ", FUNC3: " << func3 << endl;
    }
};

#endif /* ITYPE_H */
