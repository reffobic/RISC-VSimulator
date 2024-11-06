#include "instruction.h"
#include "RType.h"
#include "IType.h"
#include "SType.h"
#include "SBType.h"
#include "UType.h"
#include "UJType.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>  // For smart pointers

using namespace std;

// Tokenize function to split the line into tokens
vector<string> tokenize(const string &line) {
    vector<string> tokens;
    istringstream stream(line);
    string token;

    while (stream >> token) {
        if (token.back() == ',')
            token.pop_back();
        tokens.push_back(token);
    }
    return tokens;
}

// Function to parse the instruction and return an appropriate instance
instruction parseInstruction(const vector<string> &tokens) {
    
    instruction temp;
    
    if (tokens.empty()) return temp;

    string inst_type = tokens[0];

    // R-Type Instructions
    if (inst_type == "add" || inst_type == "sub" || inst_type == "sll" || inst_type == "slt" ||
        inst_type == "sltu" || inst_type == "xor" || inst_type == "srl" || inst_type == "sra" ||
        inst_type == "or" || inst_type == "and") {

        if (tokens.size() < 4) {
            cerr << "Error: Invalid R-type instruction format" << endl;
            return temp;
        }

        int rd = stoi(tokens[1].substr(1));
        int rs1 = stoi(tokens[2].substr(1));
        int rs2 = stoi(tokens[3].substr(1));
        int func3 = 0, func7 = 0;

        if (inst_type == "sub" || inst_type == "add") func3 = 0;
        else if (inst_type == "sll") func3 = 1;
        else if (inst_type == "slt") func3 = 2;
        else if (inst_type == "sltu") func3 = 3;
        else if (inst_type == "xor") func3 = 4;
        else if (inst_type == "srl" || inst_type == "sra") func3 = 5;
        else if (inst_type == "or") func3 = 6;
        else func3 = 7;  // for "and"

        func7 = (inst_type == "sub" || inst_type == "sra") ? 32 : 0;
        
        RType R (rd, rs1, rs2, func3, func7);
        // Create and return an RTypeInstruction instance
        return R;
    }

    // I-Type Instructions
    else if (inst_type == "addi" || inst_type == "slti" || inst_type == "sltiu" || inst_type == "xori" ||
             inst_type == "ori" || inst_type == "andi" || inst_type == "lb" || inst_type == "lh" ||
             inst_type == "lw" || inst_type == "lbu" || inst_type == "lhu" || inst_type == "jalr") {

        if (tokens.size() < 4) {
            cerr << "Error: Invalid I-type instruction format" << endl;
            return temp;
        }

        int rd = stoi(tokens[1].substr(1));
        int rs1 = stoi(tokens[2].substr(1));
        int imm = stoi(tokens[3]);
        int func3 = (inst_type == "addi") ? 0 : (inst_type == "slti") ? 2 :
                    (inst_type == "sltiu") ? 3 : (inst_type == "xori") ? 4 :
                    (inst_type == "ori") ? 6 : 7;

        if (inst_type == "jalr"){
            int OpCode = 103;
            IType I (rd, rs1, imm, func3);
            return I;
        } else{
            return make_unique<IType>(inst_type, 0 /* opCode */, rd, rs1, imm, func3);}
    }

    // S-Type Instructions
    else if (inst_type == "sb" || inst_type == "sh" || inst_type == "sw") {

        if (tokens.size() < 4) {
            cerr << "Error: Invalid S-type instruction format" << endl;
            return nullptr;
        }

        int rs1 = stoi(tokens[2].substr(1));
        int rs2 = stoi(tokens[1].substr(1));
        int imm = stoi(tokens[3]);
        int func3 = (inst_type == "sb") ? 0 : (inst_type == "sh") ? 1 : 2;

        // Create and return an STypeInstruction instance
        return make_unique<SType>(inst_type, 0 /* opCode */, rs1, rs2, imm, func3);
    }

    // U-Type Instructions
    else if (inst_type == "lui" || inst_type == "auipc") {

        if (tokens.size() < 3) {
            cerr << "Error: Invalid U-type instruction format" << endl;
            return nullptr;
        }

        int rd = stoi(tokens[1].substr(1));  // `rd` is usually the second token after the instruction name
        int imm = stoi(tokens[2]);
        
        return make_unique<UType>(inst_type, 0 /* opCode */, rd, imm);
    }
    
    // UJ-Type Instructions
    else if (inst_type == "jal") {

        if (tokens.size() < 3) {
            cerr << "Error: Invalid UJ-type instruction format" << endl;
            return nullptr;
        }

        int rd = stoi(tokens[1].substr(1));
        int imm = stoi(tokens[2]);
        
        return make_unique<UJType>(inst_type, 0 /* opCode */, rd, imm);
    }
    
    // SB-Type Instructions
    else if (inst_type == "beq" || inst_type == "bne" || inst_type == "blt" ||
             inst_type == "bge" || inst_type == "bltu" || inst_type == "bgeu") {

        if (tokens.size() < 4) {
            cerr << "Error: Invalid SB-type instruction format" << endl;
            return nullptr;
        }

        int rs1 = stoi(tokens[1].substr(1));  // Source register 1
        int rs2 = stoi(tokens[2].substr(1));  // Source register 2
        int imm = stoi(tokens[3]);            // Immediate offset

        // Determine func3 based on the instruction type
        int func3;
        if (inst_type == "beq") func3 = 0;
        else if (inst_type == "bne") func3 = 1;
        else if (inst_type == "blt") func3 = 4;
        else if (inst_type == "bge") func3 = 5;
        else if (inst_type == "bltu") func3 = 6;
        else if (inst_type == "bgeu") func3 = 7;
        else func3 = 0;  // Default, though we shouldn't reach here

        // Create and return an SBType instance
        return make_unique<SBType>(inst_type, 0 /* opCode */, rs1, rs2, imm, func3);
    }
    

    return nullptr;  // Return nullptr if the instruction type is unknown
}
