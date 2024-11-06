//
//  RType.h
//  AssemblyProject1
//
//  Created by Mohamed El-Refai on 04/11/2024.
//

#include "instruction.h"
#include <iostream>
#include <vector>

using namespace std;

class RType : public instruction {
    
private:
    int rd;
    int rs1;
    int rs2;
    int func3;
    int func7;
    
public:
    // Constructor
    RType(int rd, int rs1, int rs2, int func3, int func7)
        : rd(rd), rs1(rs1), rs2(rs2), func3(func3), func7(func7) {}
    
    int getRS1() const {
        return rs1;
    }
    
    int getRS2() const {
        return rs2;
    }
    
    int getRD() const {
        return rd;
    }
    
    int getFunc3() const {
        return func3;
    }
    
    int getFunc7() const {
        return func7;
    }
    
    void display() const {
        cout << "R-Type Instruction - "
             << "RD: " << rd << ", RS1: " << rs1
             << ", RS2: " << rs2 << ", FUNC3: " << func3 << "FUNC7: " << func7 << endl;
    }
};
