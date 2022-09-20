#include <FL/Fl.H>
#include "Animations.h"


void Animations::shrinkCandies(std::vector<Coord> &targets) {
    int l = defaultCandyLength;
    //Loop causes candy length to get 75% smaller and redraws it w/ each iteration
    //breaks if length is 5% or less.
    while (l>=defaultCandyLength*0.05) {
        l *=0.75;
        for (Coord &c: targets) {
            board.getCandy(c).length= l;
            board.getCandy(c).draw();
            Fl::wait(0.5);
        }
    }
    //Once candies are small, change type to invis candy
    for (Coord &c: targets) {
        board.setCandyType(c,0);
    }
}

void Animations::translateCandyPair(Coord c1, Coord c2, int speedMultiplier,
                                    Pxl c1Target, Pxl c2Target,
                                    int c1xDir, int c1yDir) {
    Candy &candy1 = board.getCandy(c1);
    Candy &candy2 = board.getCandy(c2);
    int c2xDir = c1xDir*-1;
    int c2yDir = c1yDir*-1;

    //Loop causes candy to move towards the intersection.
    while(true){
        //break condition:
        //If the distance of candy1-c1target is less than the multiplier,
        if(abs(candy1.center.xDistanceTo(c1Target)<=speedMultiplier
           && abs(candy1.center.yDistanceTo(c1Target))<=speedMultiplier)){
            // Then place both candies on target
            candy1.center = c1Target;
            candy2.center = c2Target;
            break;
        }
        else {
            //Increments by both candies by speed multiplier * direction (see above)
            candy1.center.x += speedMultiplier*c1xDir;
            candy2.center.x += speedMultiplier*c2xDir;
            candy1.center.y += speedMultiplier*c1yDir;
            candy2.center.y += speedMultiplier*c2yDir;
        }

        candy1.draw();
        candy2.draw();

        Fl::wait(0.1);
    }

}

void Animations::intersectCandy(Coord c1, Coord c2, int speedMultiplier) {

    Pxl intersectionPxl = Pxl{board.getCandy(c1).center.x + c1.xDistanceTo(c2) * cellSize / 2,
                              board.getCandy(c1).center.y+c1.yDistanceTo(c2)*cellSize/2};

    translateCandyPair(c1,c2,speedMultiplier,intersectionPxl,intersectionPxl,
                       c1.xDistanceTo(c2),c1.yDistanceTo(c2));

}
void Animations::restoreCandy(Coord c1, Coord c2, int speedMultiplier) {
    Pxl cell1_Center = board.getCell(c1).centerPxl;
    Pxl cell2_Center = board.getCell(c2).centerPxl;
    translateCandyPair(c1,c2,speedMultiplier,cell1_Center,cell2_Center,
                       -c1.xDistanceTo(c2),-c1.yDistanceTo(c2));
}

//void Animations::intersectCandy(Coord c1, Coord c2, int speedMultiplier) {
//    Candy &candy1 = board.getCandy(c1);
//    Candy &candy2 = board.getCandy(c2);
//    Pxl intersectionPxl = Pxl{candy1.center.x + c1.xDistanceTo(c2) * cellSize / 2,
//                              candy1.center.y+c1.yDistanceTo(c2)*cellSize/2};
//
//    //Loop causes candy to move towards the intersection.
//    while(true){
//        //break condition:
//        //   If the distance of candy1-candy2 is less than the multiplier, then just get it to intersect
//        if(abs(candy1.center.xDistanceTo(intersectionPxl))<=speedMultiplier*1.5
//           && abs(candy1.center.yDistanceTo(intersectionPxl))<=speedMultiplier*1.5 ){
//            candy1.center = intersectionPxl;
//            candy2.center = intersectionPxl;
//            break;
//        }
//        //if candy must translate horizontally to move closer to intersection
//        if(c1.x!=c2.x){
//            //Increments by speed multiplier * direction (positive or negative 1), direction is given by distanceTo(c2/c1)
//            candy1.center.x += speedMultiplier*c1.xDistanceTo(c2);
//            candy2.center.x += speedMultiplier*c2.xDistanceTo(c1);
//        }
//            //if candy must translate vertically to move closer to intersection
//        else{
//            //Increments by speed multiplier * direction (see above)
//            candy1.center.y += speedMultiplier*c1.yDistanceTo(c2);
//            candy2.center.y += speedMultiplier*c2.yDistanceTo(c1);
//        }
//
//        candy1.draw();
//        candy2.draw();
//
//        Fl::wait(0.1);
//    }
//}
//void Animations::restoreCandy(Coord c1, Coord c2, int speedMultiplier) {
//    /*
//    Restores candy back to where it belongs.
//    Logic is identical to intersectCandy
//    I "repeated" code because the calculation for the increments is done differently.
//    I could make a generalized function with the same logic, and take in parameters for the different calculations,
//    and have intersect/restore functions to calculate the parameters seperately,
//    but the calculation that would take place within the restore/intersect functions would be
//    It did not seem worth it, and repeating a few lines did not seem like a big deal
//     */
//
//
//    Candy &candy1 = board.getCandy(c1);
//    Candy &candy2 = board.getCandy(c2);
//
//    Pxl cell1_Center = board.getCell(c1).centerPxl;
//    Pxl cell2_Center = board.getCell(c2).centerPxl;
//    //Causes candy to move towards their respective cell.
//    while(true){
//
//        if(abs(candy1.center.xDistanceTo(cell1_Center))<=speedMultiplier*1.5
//           && abs(candy1.center.yDistanceTo(cell1_Center))<=speedMultiplier*1.5 ){
//            candy1.center = cell1_Center;
//            candy2.center = cell2_Center;
//            break;
//        }
//        if(c1.x!=c2.x){
//            candy1.center.x += speedMultiplier*c2.xDistanceTo(c1);
//            candy2.center.x += speedMultiplier*c1.xDistanceTo(c2);
//        }
//        else{
//            candy1.center.y += speedMultiplier*c2.yDistanceTo(c1);
//            candy2.center.y += speedMultiplier*c1.yDistanceTo(c2);
//        }
//        candy1.draw();
//        candy2.draw();
//        Fl::wait(0.1);
//
//    }
//}


Animations::Animations(Board &board) : board(board) {}


