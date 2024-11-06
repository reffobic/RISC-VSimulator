//
//  instruction.h
//  AssemblyProject1
//
//  Created by Mohamed El-Refai on 04/11/2024.
//

#ifndef INSTRUCTION_H  // Start of header guard
#define INSTRUCTION_H

#include <iostream>
#include <vector>

using namespace std;

class instruction {
    
private:
    string name;
    int opCode;
public:
    instruction() {
        
    }
    instruction(string n, int code) {
        name = n;
        opCode = code;
        
    }
    void setName(const string &n) {
            name = n;
    }
    
    // Setter for opCode
    void setOpCode(int code) {
        opCode = code;
    }
    
    string getName() const {
        return name;
    }
    
    int getOpCode() const {
        return opCode;
    }
};

#endif  // End of header guard
