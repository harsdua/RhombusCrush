//
// Created by hars on 23/07/22.
//

#ifndef CANDYCRUSH_CANDY_H
#define CANDYCRUSH_CANDY_H


#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include "Point.h"
#include "Square.h"
#include <algorithm>


class Candy {
    std::vector<int> emptyBlackList;
public:
    Pxl center{};
    int candyType{};
    Fl_Color candyColor{};
    int length = defaultCandyLength;
    void draw();
    explicit Candy(Pxl centerPoint);
    Candy() = default;
    void resetLength();
    void setCandyType(int candyType);
    void shuffleType();
    void colorIn();
    static int drawType(std::vector<int> blackList,int n=6, bool trueRand = true);
    static void makeHat(int n, std::vector<int> &hat, std::vector<int> &blackList);
};


#endif //CANDYCRUSH_CANDY_H
