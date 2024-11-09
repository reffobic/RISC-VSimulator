//
//  registers.h
//  AssemblyProject1
//
//  Created by Mohamed El-Refai on 08/11/2024.
//

#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <iostream>
#include <array>
#include <iomanip>

using namespace std;

class registers {
private:
    array<int, 32> reg;  // Array to store 32 integer registers

public:
    registers() {
        reg.fill(0);  // Initialize all registers to 0
    }

    // Method to set a register value
    void set(int index, int value) {
        if (index != 0) {  // Register x0 is always 0 in RISC-V
            reg[index] = value;
        }
    }

    // Method to get a register value
    int get(int index) const {
        return reg[index];
    }

    // Method to display all registers in a clean format
    void display() const {
        cout << "\n---------------- Register State ----------------" << endl;
        for (int i = 0; i < 32; i += 8) {
            for (int j = 0; j < 8; ++j) {
                cout << "x" << setw(2) << (i + j) << ":\t" << setw(8) << reg[i + j] << "\t";
            }
            cout << endl;
        }
        cout << "------------------------------------------------" << endl;
    }
};

#endif  // REGISTERFILE_H
