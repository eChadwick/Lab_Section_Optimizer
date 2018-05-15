//
//  state.h
//  Simulated Annealing
//
//  Created by Chadwick,Eric on 2/12/18.
//  Copyright © 2018 Eric Chadwick. All rights reserved.
//

#ifndef state_h
#define state_h
#include "section.h"
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

class State {
public:
    Section lab_sections[5] = { Section('A'), Section('B'), Section('C'), Section('D'), Section('E') };
    
    int score();
    void build_state(ifstream& in);
    State generate_successor();
    void print(ostream&);
};

// Implementation

// Returns the sum of the scores of the sections.
// @return is state score.
int State::score(){
    int temp = 0;
    for(int i = 0; i < 5; i++){
        temp += lab_sections[i].score;
    }
    return temp;
}

// Populates the initial state by reading in from file.
// @param in is the file stream to build the state from.
void State::build_state(ifstream& in){
    for(int k = 0; k < 5; k++){
        for(int i = 0; i < 20; i++){
            pair<int, vector<char>> temp;
            in >> temp.first ;
            for(int j = 0; j < 5; j++){
                char pref;
                in >> pref;
                temp.second.push_back(pref);
            }
            lab_sections[k].add_student(temp);
        }
    }
}

// Generates a successor state by randomly choosing 2 sections, removing a student from each
// and adding it to the other.
// @return is a randomly generated successor of the current state.
State State::generate_successor(){
    State new_state = *this;
    srand(time(0));
    int section1 = rand() % 5;
    int section2 = rand() % 5;
    while (section2 == section1){
        section2 = rand() % 5;
    }
    
    pair<int, vector<char>> student1 = new_state.lab_sections[section1].remove_student();
    pair<int, vector<char>> student2 = new_state.lab_sections[section2].remove_student();
    
    new_state.lab_sections[section1].add_student(student2);
    new_state.lab_sections[section2].add_student(student1);
    
    return new_state;
}

// Print out all of the sections in the current state.
void State::print(ostream& out){
    for(int i = 0; i < 5; i++){
        lab_sections[i].print(out);
    }
}

#endif /* state_h */
