//
// Created by hars on 23/07/22.
//

#ifndef CANDYCRUSH_SQUARE_H
#define CANDYCRUSH_SQUARE_H


#include <FL/Enumerations.H>
#include "Point.h"


class Square {
    public:
    Pxl center;
    int l;
    Fl_Color fillColor=FL_WHITE, frameColor=FL_BLACK;
    void draw();
    void setFillColor(Fl_Color newFillColor);
    bool contains(Pxl p);
    Square(Pxl centerPoint);
    Square() = default;
};


#endif //CANDYCRUSH_SQUARE_H
