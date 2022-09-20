#ifndef CANDYCRUSH_BOARD_H
#define CANDYCRUSH_BOARD_H


#include "Cell.h"

class Board {
public:
    Board();
    void draw();
    Cell boardCells[9][9];

    Cell& getCell(Coord target);
    std::vector<Coord> cellsOnPath(int range, Coord target, int xDir, int yDir);
    void setCandyType(Coord target, int candyType);
    Candy& getCandy(Coord target);
    int getCandyType(Coord target);
    void generateDisjointCandy(Coord c1);
    void swapCandyType(Coord c1, Coord c2);
    void cleanupStreaks();
};

#endif //CANDYCRUSH_BOARD_H
