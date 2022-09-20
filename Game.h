//
// Created by hars on 22/07/22.
//

#ifndef CANDYCRUSH_GAME_H
#define CANDYCRUSH_GAME_H
#include <vector>
#include <unistd.h>
#include "Board.h"
#include "Animations.h"
#include <cmath>

class Game{
    Board board;
    Animations animations{board};
public:
    int score;
    int bestScore;
    Coord selection{-1, -1};
    Game();
    void draw();
    void handleMouseEvent(Pxl mouseLoc);
    void evalSelect(Coord target);
    bool candyExterminator(Coord &core, bool evaluatingBoard);
    bool evalBoard();
    void multiDeleteCandies(std::vector <Coord> &markedCandies, bool evaluatingBoard);
    bool evalMove(Coord &c1, Coord &c2);
    void swapCandy(Coord c1, Coord c2, int speed=2);
    void sinkCandy(int x);
    void rainCandy(int x);
    int getBestScore();
    void saveScore();
};


#endif //CANDYCRUSH_GAME_H
