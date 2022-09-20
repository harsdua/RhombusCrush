//
// Created by hars on 23/07/22.
//

#include <random>
#include "Candy.h"


Candy::Candy(Pxl centerPoint) {
    //generate random candy type, each type has a color mapped,
    shuffleType();
    center = centerPoint;
    colorIn();
}

void Candy::shuffleType() {
    setCandyType(Candy::drawType(std::vector<int>()));
}

void Candy::colorIn() {
    //colors candy according to current type
    resetLength();
    switch (candyType) {
        case 0:
            candyColor = FL_WHITE;
            break;
        case 1:
            candyColor = FL_RED;
            break;
        case 2:
            candyColor = FL_DARK_YELLOW;
            break;
        case 3:
            candyColor = FL_GREEN;
            break;
        case 4:
            candyColor = FL_BLUE;
            break;
        case 5:
            candyColor = FL_CYAN;
            break;
        case 6:
            candyColor = FL_MAGENTA;
            break;
    };
}

void Candy::draw(){
    fl_color(candyColor);
    //draws a rhombus with color candyColor.
    fl_polygon	(center.x,center.y+length/2,
                   center.x-length/2,center.y,
                   center.x,center.y-length/2,
                   center.x+length/2,center.y);
}


void Candy::setCandyType(int candyType) {
    Candy::candyType = candyType;
    colorIn();
}

void Candy::resetLength() {
    length= defaultCandyLength;
}

int Candy::drawType(std::vector<int> blackList,int n, bool trueRand) {
    //n : draws a number between 1 to n, inclusive.
    int c;
    std::vector<int> hat;
    makeHat(n, hat, blackList);
    if (trueRand) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, hat.size() - 1);
    c = distrib(gen);
    }
        //the function rand() will use the seed set by srand in main.cpp
        //to produce the same exact sequence every time for testing
    else  c = rand() % hat.size();
    return hat[c];
}



void Candy::makeHat(int n,std::vector<int> &hat, std::vector<int>& blackList){
    //adds to vector hat containing {1,2...n} and where no element of hat is part of blacklist
    for (int i = 1; i < n+1; ++i) {
        if(std::find(blackList.begin(), blackList.end(), i) != blackList.end()){
            continue;}
        hat.push_back(i);
    }
};



