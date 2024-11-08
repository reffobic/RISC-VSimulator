#ifndef STYPE_H
#define STYPE_H

#include "instruction.h"
#include "registers.h"
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

class SType : public instruction {
private:
    int rs1;    // Source register 1 (for base address)
    int rs2;    // Source register 2 (for value to store)
    int imm;    // Immediate value
    int func3;  // Function code 3

public:
    // Constructor to initialize all members, including inherited name and opCode
    SType(int opCode, int rs1, int rs2, int imm, int func3)
        : instruction("SType", opCode), rs1(rs1), rs2(rs2), imm(imm), func3(func3) {}

    // Execution function specific to S-type instructions
    void execute(registers &registerFile, vector<int8_t> &memory) {
        // Calculate the effective address
        int baseAddress = registerFile.get(rs1);
        int valueToStore = registerFile.get(rs2);
        int address = baseAddress + imm;

        // Perform store operation based on func3 (SB, SH, SW)
        switch (func3) {
            case 0:  // SB (Store Byte)
                if (address >= 0 && address < memory.size()) {
                    memory[address] = static_cast<int8_t>(valueToStore & 0xFF);
                    cout << "Executing SB: Memory[" << address << "] = " << (valueToStore & 0xFF) << endl;
                } else {
                    cout << "Error: Address out of bounds in SB operation" << endl;
                }
                break;

            case 1:  // SH (Store Halfword)
                if (address >= 0 && address + 1 < memory.size()) {
                    memory[address] = static_cast<int8_t>(valueToStore & 0xFF);
                    memory[address + 1] = static_cast<int8_t>((valueToStore >> 8) & 0xFF);
                    cout << "Executing SH: Memory[" << address << "] = " << (valueToStore & 0xFF)
                              << ", Memory[" << address + 1 << "] = " << ((valueToStore >> 8) & 0xFF) << endl;
                } else {
                    cout << "Error: Address out of bounds in SH operation" << endl;
                }
                break;

            case 2:  // SW (Store Word)
                if (address >= 0 && address + 3 < memory.size()) {
                    memory[address] = static_cast<int8_t>(valueToStore & 0xFF);
                    memory[address + 1] = static_cast<int8_t>((valueToStore >> 8) & 0xFF);
                    memory[address + 2] = static_cast<int8_t>((valueToStore >> 16) & 0xFF);
                    memory[address + 3] = static_cast<int8_t>((valueToStore >> 24) & 0xFF);
                    cout << "Executing SW: Memory[" << address << "] = " << (valueToStore & 0xFF)
                              << ", Memory[" << address + 1 << "] = " << ((valueToStore >> 8) & 0xFF)
                              << ", Memory[" << address + 2 << "] = " << ((valueToStore >> 16) & 0xFF)
                              << ", Memory[" << address + 3 << "] = " << ((valueToStore >> 24) & 0xFF) << endl;
                } else {
                    cout << "Error: Address out of bounds in SW operation" << endl;
                }
                break;

            default:
                cout << "Unknown S-Type Instruction with func3 = " << func3 << endl;
                break;
        }
    }

    // Display function for debugging or logging
    void display() const override {
        cout << "S-Type Instruction - "
                  << "Name: " << getName() << ", Opcode: " << getOpCode()
                  << ", RS1: " << rs1 << ", RS2: " << rs2
                  << ", IMM: " << imm << ", FUNC3: " << func3 << endl;
    }
};

#endif /* STYPE_H */
