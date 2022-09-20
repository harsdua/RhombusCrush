//
// Created by hars on 23/07/22.
//
#include <FL/fl_draw.H>
#include "Square.h"

void Square::draw() {
    fl_draw_box(FL_FLAT_BOX,center.x-l/2,center.y-l/2,l,l,fillColor);
    fl_draw_box(FL_BORDER_FRAME,center.x-l/2,center.y-l/2,l,l,frameColor);
}

void Square::setFillColor(Fl_Color newFillColor) {
    fillColor = newFillColor;

}


bool Square::contains(Pxl p) {
    return p.x>=center.x-l/2 &&
           p.x<center.x+l/2 &&
           p.y>=center.y-l/2 &&
           p.y<center.y+l/2;
}

Square::Square(Pxl centerPoint) {
    l = cellSize;
    center = centerPoint;
}


