//
//  main.cpp
//  Simulated Annealing
//
//  Created by Chadwick,Eric on 2/11/18.
//  Copyright © 2018 Eric Chadwick. All rights reserved.
//

#include <iostream>
#include <vector>
#include "section.h"
#include "state.h"
#include <fstream>
#include <cmath>
using namespace std;

State simulate_annealing(State, int);

int main() {
    ifstream in;
    in.open("input1.txt");
    if(in.fail()){
        cout << "Didn't open input file";
        return -1;
    }
    
    State the_state;
    the_state.build_state(in);
    
    cout << "Initial State Score: " << the_state.score() << endl << "Beginning simulated annealing..." << endl;
    
    simulate_annealing(the_state, 10000);
    
    ofstream out;
    out.open("output.txt");
    the_state.print(out);
    
    return 0;
}

// The simulated annealing function.
State simulate_annealing(State the_state, int temp){
    int attempts = 0;
    int swaps = 0;
    while(true){
        if(temp == 0){
            return the_state;
        }
        cout << "Temp: " << temp << "   Attempts: " << attempts << "  Swaps: " << swaps << "  Score: " << the_state.score() << endl;

        if(attempts == 10000 || swaps == 1000){
            temp = temp * .95;
            attempts = 0;
            swaps = 0;
        }
        
        State new_state = the_state.generate_successor();
        if(new_state.score() < the_state.score()){
            the_state = new_state;
            swaps++;
        }
        else {
            double skill_check = pow(M_E, -( (new_state.score() - the_state.score() ) / static_cast<double>(temp) ) );
            double dice_roll = ((rand() % 100) + 1) * .01;
            if(dice_roll <= skill_check){
                the_state = new_state;
                swaps++;
            }
        }
        attempts++;
    }
};
