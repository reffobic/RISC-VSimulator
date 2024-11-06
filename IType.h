//
//  IType.h
//  AssemblyProject1
//
//  Created by Mohamed El-Refai on 06/11/2024.
//

#ifndef IType_h
#define IType_h

#include "instruction.h"
#include <iostream>
#include <vector>

using namespace std;

class IType : public instruction {
    
private:
    int rd;     // Destination register
    int rs1;    // Source register 1
    int imm;    // Immediate value
    int func3;  // Function code 3
    
public:
    // Constructor to initialize the members
    IType (int rd, int rs1, int imm, int func3)
        : rd(rd), rs1(rs1), imm(imm), func3(func3) {}

    // Getters for each private member variable
    int getRS1() const {
        return rs1;
    }
    
    int getRD() const {
        return rd;
    }
    
    int getImmediate() const {
        return imm;
    }
    
    int getFunc3() const {
        return func3;
    }

    // Display function for debugging or logging
    void display() const {
        cout << "I-Type Instruction - "
             << "RD: " << rd << ", RS1: " << rs1
             << ", IMM: " << imm << ", FUNC3: " << func3 << endl;
    }
};

#endif /* IType_h */
