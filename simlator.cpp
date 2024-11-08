//
//  simulator.cpp
//  AssemblyProject1
//

#include "simulator.h"
#include "RType.h"
#include "IType.h"
#include "SBType.h"
#include "UType.h"
#include "UJType.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Simulator::Simulator() : pc(0) {
    fill(begin(memory), end(memory), 0);  // Initialize memory to 0
}

void Simulator::loadInstructions(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Cannot open file" << endl;
        exit(1);
    }

    string line;
    while (getline(inFile, line)) {
        instructions.push_back(line);
    }
    inFile.close();
}

// Helper function to create the correct instruction type based on name and operands
instruction* Simulator::createInstruction(const string& instName, const vector<string>& operands) {
    if (instName == "ADD" || instName == "SUB" || instName == "SLL" || instName == "SLT" ||
        instName == "SLTU" || instName == "XOR" || instName == "SRL" || instName == "SRA" ||
        instName == "OR" || instName == "AND") {
        
        int rd = stoi(operands[0].substr(1));
        int rs1 = stoi(operands[1].substr(1));
        int rs2 = stoi(operands[2].substr(1));
        
        int func3 = 0, func7 = 0;
        if (instName == "ADD") { func3 = 0; func7 = 0; }
        else if (instName == "SUB") { func3 = 0; func7 = 32; }
        else if (instName == "SLL") { func3 = 1; func7 = 0; }
        else if (instName == "SLT") { func3 = 2; func7 = 0; }
        else if (instName == "SLTU") { func3 = 3; func7 = 0; }
        else if (instName == "XOR") { func3 = 4; func7 = 0; }
        else if (instName == "SRL") { func3 = 5; func7 = 0; }
        else if (instName == "SRA") { func3 = 5; func7 = 32; }
        else if (instName == "OR") { func3 = 6; func7 = 0; }
        else if (instName == "AND") { func3 = 7; func7 = 0; }

        return new RType(rd, rs1, rs2, func3, func7, 0x33);  // R-Type opcode 0x33

    } else if (instName == "ADDI" || instName == "SLTI" || instName == "SLTIU" ||
               instName == "XORI" || instName == "ORI" || instName == "ANDI") {
        
        int rd = stoi(operands[0].substr(1));
        int rs1 = stoi(operands[1].substr(1));
        int imm = stoi(operands[2]);

        int func3 = 0;
        if (instName == "ADDI") func3 = 0;
        else if (instName == "SLTI") func3 = 2;
        else if (instName == "SLTIU") func3 = 3;
        else if (instName == "XORI") func3 = 4;
        else if (instName == "ORI") func3 = 6;
        else if (instName == "ANDI") func3 = 7;

        return new IType(rd, rs1, imm, func3, 0x13, memory);  // I-Type opcode 0x13

    } else if (instName == "LUI" || instName == "AUIPC") {
        int rd = stoi(operands[0].substr(1));
        int imm = stoi(operands[1]);

        int opcode = (instName == "LUI") ? 0x37 : 0x17;

        return new UType(instName, opcode, rd, imm);  // Pass instName as the name
        
    } else if (instName == "JAL") {
        int rd = stoi(operands[0].substr(1));
        int imm = stoi(operands[1]);

        return new UJType(instName, 0x6F, rd, imm);  // Pass instName as the name
        
    } else if (instName == "JALR") {
        
        int rd = stoi(operands[0].substr(1));
        int rs1 = stoi(operands[1].substr(1));
        int imm = stoi(operands[2]);

        return new IType(rd, rs1, imm, 0, 0x67, memory);  // func3 = 0, opcode = 0x67

    } else if (instName == "BEQ" || instName == "BNE" || instName == "BLT" ||
               instName == "BGE" || instName == "BLTU" || instName == "BGEU") {
        
        int rs1 = stoi(operands[0].substr(1));
        int rs2 = stoi(operands[1].substr(1));
        int imm = stoi(operands[2]);

        int imm4_1 = (imm >> 1) & 0xF;       // Bits 4-1
        int imm10_5 = (imm >> 5) & 0x3F;     // Bits 10-5
        int imm11 = (imm >> 11) & 0x1;       // Bit 11
        int imm12 = (imm >> 12) & 0x1;       // Bit 12 (most significant)

        int func3 = 0;
        if (instName == "BEQ") func3 = 0;
        else if (instName == "BNE") func3 = 1;
        else if (instName == "BLT") func3 = 4;
        else if (instName == "BGE") func3 = 5;
        else if (instName == "BLTU") func3 = 6;
        else if (instName == "BGEU") func3 = 7;

        return new SBType(0x63, rs1, rs2, imm4_1, imm10_5, imm11, imm12, func3);  // SB-Type opcode 0x63
    }

    return nullptr;  // Return nullptr if instruction type is unrecognized
}

void Simulator::run() {
    cout << "==================== Instruction Execution ====================" << endl;
    for (const string& instLine : instructions) {
        istringstream iss(instLine);
        string instName;
        iss >> instName;

        vector<string> operands;
        string operand;
        while (iss >> operand) {
            operands.push_back(operand);
        }

        instruction* inst = createInstruction(instName, operands);
        if (inst) {
            cout << "Executing: " << instName << " ";
            for (const auto& op : operands) cout << op << " ";
            cout << endl;

            // Execute the instruction, passing registers, pc, and memory
            inst->execute(registers, pc, memory);

            registers.display();  // Display the current register state
            delete inst;  // Clean up dynamically allocated memory
        } else {
            cout << "Unknown instruction: " << instName << endl;
        }
    }
    cout << "==============================================================" << endl;
}
