#ifndef CANDYCRUSH_ANIMATIONS_H
#define CANDYCRUSH_ANIMATIONS_H


#include "Cell.h"
#include "Board.h"

class Animations {
public:
    Board &board;
    Animations(Board &board);

    void shrinkCandies(std::vector<Coord> &targets);

    void intersectCandy(Coord c1, Coord c2, int speedMultiplier);

    void restoreCandy(Coord c1, Coord c2, int speedMultiplier);

    void translateCandyPair(Coord c1, Coord c2, int speedMultiplier,
                            Pxl c1Target, Pxl c2Target, int xDir, int yDir);
};


#endif //CANDYCRUSH_ANIMATIONS_H
