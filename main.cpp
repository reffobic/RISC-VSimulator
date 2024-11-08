//
//  main.cpp
//  AssemblyProject1
//

#include "simulator.h"
#include <iostream>

using namespace std;

int main() {
    Simulator simulator;

    // Specify the file containing the instructions
    string filename = "/Users/refobic/Documents/Assembly/AssemblyProject1/AssemblyProject1/instructions.txt";  // Modify with your actual instruction file

    // Load instructions from the file
    simulator.loadInstructions(filename);

    // Run the simulator to execute the instructions
    cout << "\nStarting simulation..." << endl;
    simulator.run();

    // Simulation complete
    cout << "\nSimulation complete." << endl;

    return 0;
}
