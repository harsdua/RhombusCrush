//
// Created by hars on 23/07/22.
//

#include "Cell.h"


Cell::Cell(Coord cellLoc) {
    centerPxl = Pxl{static_cast<float>(7 + (cellLoc.x + 1) * cellSize), static_cast<float>(20 + (cellLoc.y + 1) * cellSize)};

    candy = Candy{centerPxl};
    sq =  Square{centerPxl};
}

void Cell::draw() {
    sq.draw();
    candy.draw();

}




