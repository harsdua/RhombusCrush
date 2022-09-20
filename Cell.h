//
// Created by hars on 23/07/22.
//

#ifndef CANDYCRUSH_CELL_H
#define CANDYCRUSH_CELL_H


#include "Point.h"
#include "Square.h"
#include "Candy.h"

class Cell {

public:
    Pxl centerPxl;
    Cell(Coord cellLoc);
    void draw();
    Cell() = default;
    Candy candy;
    Square sq;
};


#endif //CANDYCRUSH_CELL_H
