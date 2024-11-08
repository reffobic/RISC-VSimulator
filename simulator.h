//
//  simulator.h
//  AssemblyProject1
//

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "instruction.h"
#include "registers.h"
#include <vector>
#include <string>

using namespace std;

class Simulator {
private:
    registers registers;  // Use RegisterFile for registers
    int pc;  // Program Counter
    vector<string> instructions;  // Instruction list
    int memory[4096];  // Memory array

public:
    Simulator();
    void loadInstructions(const string& filename);
    instruction* createInstruction(const string& instName, const vector<string>& operands);
    void run();
};

#endif  // SIMULATOR_H
