#ifndef RTYPE_H
#define RTYPE_H

#include "instruction.h"
#include "registers.h"  // Ensure RegisterFile is included

class RType : public instruction {
private:
    int rd, rs1, rs2, func3, func7;

public:
    RType(int rd, int rs1, int rs2, int func3, int func7, int opCode)
        : instruction("RType", opCode), rd(rd), rs1(rs1), rs2(rs2), func3(func3), func7(func7) {}

    void execute(registers &registerFile, int &pc, int *memory) override {
        int valueRs1 = registerFile.get(rs1);  // Get value from register rs1
        int valueRs2 = registerFile.get(rs2);  // Get value from register rs2
        int result = 0;

        if (func3 == 0 && func7 == 32) {  // SUB
            result = valueRs1 - valueRs2;
            cout << "Executing SUB: x" << rd << " = x" << rs1 << " - x" << rs2 << " = " << result << endl;
        } else if (func3 == 0 && func7 == 0) {  // ADD
            result = valueRs1 + valueRs2;
            cout << "Executing ADD: x" << rd << " = x" << rs1 << " + x" << rs2 << " = " << result << endl;
        } else if (func3 == 1) {  // SLL (Shift Left Logical)
            result = valueRs1 << (valueRs2 & 0x1F);
            cout << "Executing SLL: x" << rd << " = x" << rs1 << " << x" << rs2 << " = " << result << endl;
        } else if (func3 == 2) {  // SLT (Set Less Than)
            result = (valueRs1 < valueRs2) ? 1 : 0;
            cout << "Executing SLT: x" << rd << " = (x" << rs1 << " < x" << rs2 << ") ? 1 : 0 = " << result << endl;
        } else if (func3 == 3) {  // SLTU (Set Less Than Unsigned)
            result = (static_cast<unsigned int>(valueRs1) < static_cast<unsigned int>(valueRs2)) ? 1 : 0;
            cout << "Executing SLTU: x" << rd << " = (unsigned x" << rs1 << " < unsigned x" << rs2 << ") ? 1 : 0 = " << result << endl;
        } else if (func3 == 4) {  // XOR
            result = valueRs1 ^ valueRs2;
            cout << "Executing XOR: x" << rd << " = x" << rs1 << " ^ x" << rs2 << " = " << result << endl;
        } else if (func3 == 5 && func7 == 0) {  // SRL (Shift Right Logical)
            result = static_cast<unsigned int>(valueRs1) >> (valueRs2 & 0x1F);
            cout << "Executing SRL: x" << rd << " = x" << rs1 << " >> x" << rs2 << " = " << result << endl;
        } else if (func3 == 5 && func7 == 32) {  // SRA (Shift Right Arithmetic)
            result = valueRs1 >> (valueRs2 & 0x1F);
            cout << "Executing SRA: x" << rd << " = x" << rs1 << " >> x" << rs2 << " = " << result << endl;
        } else if (func3 == 6) {  // OR
            result = valueRs1 | valueRs2;
            cout << "Executing OR: x" << rd << " = x" << rs1 << " | x" << rs2 << " = " << result << endl;
        } else if (func3 == 7) {  // AND
            result = valueRs1 & valueRs2;
            cout << "Executing AND: x" << rd << " = x" << rs1 << " & x" << rs2 << " = " << result << endl;
        } else {
            cout << "Unknown R-Type Instruction with func3 = " << func3 << " and func7 = " << func7 << endl;
        }

        registerFile.set(rd, result); // Set the result in the destination register
    }

    void display() const override {
        cout << "R-Type Instruction - Opcode: " << getOpCode() << ", RD: " << rd
             << ", RS1: " << rs1 << ", RS2: " << rs2
             << ", FUNC3: " << func3 << ", FUNC7: " << func7 << endl;
    }
};

#endif /* RTYPE_H */
