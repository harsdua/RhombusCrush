//
// Created by hars on 23/07/22.
//

#ifndef CANDYCRUSH_POINT_H
#define CANDYCRUSH_POINT_H


#include <vector>
#include <iostream>
#include "Constants.h"

//Point class to wrap any {x,y} pair of type T (T is numerical).
template<typename T>
class Point{
public:
    T x;
    T y;
    Point(T x, T y) : x(x), y(y) {
    }
    T xDistanceTo(Point c2){
        return c2.x-x;
    }
    T yDistanceTo(Point c2){
        return c2.y-y;
    }
    Point() = default;
};
//The Pxl class is strictly used to refer to pixel coordinates of the fltk window.
class Pxl : public Point<float>{
    using Point<float>::Point;

};

//The coord class is strictly used to refer to the boardCell indices
// ie: A Coord{1,2} refers to boardCells[1][2]
class Coord: public Point<int> {
    using Point<int>::Point;
};





#endif //CANDYCRUSH_POINT_H
