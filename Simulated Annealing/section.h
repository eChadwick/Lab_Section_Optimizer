//
//  section.h
//  Simulated Annealing
//
//  Created by Chadwick,Eric on 2/12/18.
//  Copyright © 2018 Eric Chadwick. All rights reserved.
//

#ifndef section_h
#define section_h
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class Section{
public:
    vector<pair<int, vector<char>>> roster;
    int score;
    char name;
    
    Section(char);
    void add_student(pair<int, vector<char>>);
    pair<int, vector<char>> remove_student();
    void print(ostream&);
};

// Implementation

// Constuctor
Section::Section(char new_name){
    name = new_name;
}

// Add a student to the roster and update the section score.
// @param new_kid is a pair with the first element being an integer that is the student id
//  and the second element being a vector of that student's section preferences.
void Section::add_student(pair<int, vector<char>> new_kid){
    
    roster.push_back(make_pair(new_kid.first, new_kid.second));
    int temp_score = 36;
    for(int i = 0; i < 5; i++){
        if (new_kid.second[i] == name)
            temp_score = (i + 1) * (i + 1);
    }
    score += temp_score;
}

// Remove a student from the roster and update the score
// @return is the student that was removed.
pair<int, vector<char>> Section::remove_student(){
    srand(time(0));
    int roster_spot = rand() % 20;
    pair<int, vector<char>> temp = roster[roster_spot];
    int temp_score = 36;
    for(int i = 0; i < 5; i++){
        if (roster[roster_spot].second[i] == name)
            temp_score = (i + 1) * (i + 1);
    }
    score -= temp_score;
    roster.erase(roster.begin() + roster_spot);
    return temp;
}

// Prints the score and roster for the section.
void Section::print(ostream& out){
    out << "Section " << name << " -- Score: " << score << endl << endl;
    for(int i = 0; i < 20; i++){
        pair<int, vector<char>> temp = roster[i];
        out << temp.first << "  Preferences: ";
        for(int j = 0; j < 5; j++){
            out << temp.second[j] << " ";
        }
        out << endl;
    }
    out << endl;
    
}

#endif /* section_h */
