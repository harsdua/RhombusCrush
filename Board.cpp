//
// Created by hars on 23/07/22.
//

#include <stdexcept>
#include <iostream>
#include "Board.h"


Board::Board() {
    //Assign and init cell for each entry of boardCells
    for (int i = 0; i <9 ; ++i) {
        for (int j = 0; j < 9; ++j) {
            boardCells[i][j] = Cell{Coord{i, j}};
        }
    }
    cleanupStreaks();
}

void Board::cleanupStreaks(){
    //cleanup :
    // Goes through each cell horizontally, if there is a streak, then change the 3rd candy to be "disjoint" from the surrounding candies.
    // Repeat vertically.

    for (int i = 0; i < 2; ++i) {
        for (int y = 0; y <9 ; ++y){
            int previousType = 0;
            int counter = 0;
            for (int x = 0; x < 9; ++x) {
                Coord target = Coord{x, y};
                //if horizontal cleanup = done
                if(i) {
                    //swap coords to scan vertically
                    target.x = y;
                    target.y = x;
                }
                if (previousType == getCandyType(target)) {
                    if (++counter == 2) {
                        generateDisjointCandy(target);
                    }
                }
                else{
                    counter = 0;
                }
                previousType = getCandyType(target);
            }
        }
    }
}



Cell& Board::getCell(Coord target) {
    return boardCells[target.x][target.y];
}

Candy& Board::getCandy(Coord target) {
    return getCell(target).candy;
}
int Board::getCandyType(Coord target) {
    return getCandy(target).candyType;
}
void Board::setCandyType(Coord target, int candyType) {
    getCandy(target).setCandyType(candyType);
}

void Board::swapCandyType(Coord c1, Coord c2) {
    int c1type = getCandyType(c1);
    int c2type = getCandyType(c2);
    setCandyType(c1,c2type);
    setCandyType(c2,c1type);
}


std::vector<Coord> Board::cellsOnPath(int range, Coord target, int xDir, int yDir) {
    //Goes through a path given a range from target with xDir/yDir and returns all cellCoords on path.
    std::vector<Coord> output;
    int x = target.x + xDir;
    int y = target.y + yDir;

    for (int i = 0; i < range; ++i) {
        while (y>=0 && y<=9 && x>=0 && x<=9){
            output.emplace_back(x,y);
            y+=yDir;
            x+=xDir;
        }
    }
    return output;
}



void Board::generateDisjointCandy(Coord c1) {
    //move if statements inside fxns.
    std::vector <int> neighborTypes;
    //if cell is not on edge, then proceed to pushback
    if(c1.x!=0) {
        neighborTypes.push_back(getCandyType(cellsOnPath(1, c1, -1, 0)[0]));
    }
    if(c1.x!=8) {
        neighborTypes.push_back(getCandyType(cellsOnPath(1, c1, 1, 0)[0]));
    }
    if(c1.y!=0){
        neighborTypes.push_back(getCandyType(cellsOnPath(1, c1, 0, -1)[0]));
    }
    if(c1.y!=8){
        neighborTypes.push_back(getCandyType(cellsOnPath(1, c1, 0, 1)[0]));
    }
    setCandyType(c1, Candy::drawType(neighborTypes));
}



void Board::draw() {
    for (int i = 0; i <9 ; ++i) {
        for (int j = 0; j < 9; ++j) {
            boardCells[i][j].draw();
        }
    }
}


