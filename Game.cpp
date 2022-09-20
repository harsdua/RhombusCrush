//
// Created by hars on 22/07/22.
//

#include <iostream>
#include <FL/Fl.H>
#include <fstream>
#include "Game.h"
Game::Game() {
    bestScore = getBestScore();
    score=0;


}
void Game::draw() {
    board.draw();
    }


void Game::handleMouseEvent(Pxl mouseLoc) {
    //handles a mouse click or release
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y) {
            Cell &target = board.getCell(Coord{x, y});
            if (target.sq.contains(mouseLoc)) {
                evalSelect(Coord {x,y});
            }
        }
    }
}


void Game::evalSelect(Coord target){
    /*Evaluates selection.
    by default, the selected square is {-1,-1} which is out of bounds
    In this case, if the coord of release is only 1 square away ,vertically or horizontally, then we will evaluate the attempted move.
    The selection is set back to default.
     */

    //If its at default, then the target is the location the user wants to swap(ie:the square the user clicked)
    if(selection.x == -1){
        selection = target;
        return;
    }
    // Else the user has released the mouse button , the target is the location to swap to.
    int absDistance = abs(selection.xDistanceTo(target)) + abs(selection.yDistanceTo(target));
    //If the target is 1 away, horizontally or vertically, then evaluate the move.
    if(absDistance==1){
        evalMove(selection,target);
    }
    //reset selection if released.
    selection = Coord{-1,-1};
}

bool Game::candyExterminator(Coord &core, bool evaluatingBoard = false){
    //Deletes candies if streaks are found, based on the type of the candy at core.
    std::vector <Coord> markedCandies;
    std::vector <Coord> tempMarked;
    int coreType = board.getCandyType(core);

    //Horizontal scan
        //scan right
    for (int x = 1; x < 9 - core.x; ++x) {
        if(board.getCandyType(Coord{core.x + x, core.y}) == coreType){
            tempMarked.emplace_back(core.x + x, core.y);
        }
        else break;
    }
        //scan left
    for (int x = 1; x < core.x + 1; ++x) {
        bool targetMatches = board.getCandyType(Coord{core.x - x, core.y}) == coreType;
        if (targetMatches) {
            tempMarked.emplace_back(core.x - x, core.y);
        }
        else break;
    }
    if(tempMarked.size()>=2){
        //if there is a streak of more than 2, put it into the markedCandies (ie: candies to be deleted)
        markedCandies.insert(markedCandies.end(), tempMarked.begin(), tempMarked.end());
    }
    tempMarked.clear();
    //Vertical Scan
        //scan up
    for (int y = 1; y < core.y + 1; ++y) {
        if(board.getCandyType(Coord{core.x, core.y - y}) == coreType){
            tempMarked.emplace_back(core.x, core.y - y);
        }
        else break;
    }
        //scan down
    for (int y = 1; y < 9 - core.y; ++y) {
        bool targetMatches = board.getCandyType(Coord{core.x, core.y + y}) == coreType;
        if(targetMatches){
            tempMarked.emplace_back(core.x, core.y + y);
        }
        else break;
    }
    if(tempMarked.size()>=2){
        markedCandies.insert(markedCandies.end(), tempMarked.begin(), tempMarked.end());
    }
    tempMarked.clear();

    //delete marked candies
    if(!markedCandies.empty()){
        markedCandies.push_back(core);
        multiDeleteCandies(markedCandies,evaluatingBoard);
        return true;
    }
    return false;
}

bool Game::evalMove(Coord &c1, Coord &c2){
    //Animate the swap
    swapCandy(c1, c2,4);
    //launch exterminator on both cells. If no candies were exterminated, then swap back
    if(!candyExterminator(c1) && !candyExterminator(c2)){
        swapCandy(c2, c1,4);
        return false;
    }
    //Check board for any other streaks formed
    evalBoard();
    return true;
}

bool Game::evalBoard(){
    //Launches exterminator with the core being each cell.
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y) {
            Coord core = Coord{x, y};
            if (candyExterminator(core, true)) {
                return false;
            }
        }
    }
    return true;
}


void Game::multiDeleteCandies(std::vector <Coord> &markedCandies, bool evaluatingBoard = false) {

    animations.shrinkCandies(markedCandies);
    //For each candy that was deleted, update score.
    for (Coord &c:markedCandies) {
        score+=1;
        if(score>bestScore) {
            bestScore=score;
            saveScore();
        }
        board.getCandy(c).resetLength();
    }
    //For each column containing candies deleted, add to columnsToUpdate
    std::vector <int> columnsToUpdate;
    for (Coord &c:markedCandies) {
        columnsToUpdate.push_back(c.x);
    }
    //Cause column's candies to fall, and new ones to appear
    std::sort(columnsToUpdate.begin(), columnsToUpdate.end());
    for (int &column:columnsToUpdate){
        sinkCandy(column);
        rainCandy(column);
    }

    //Check if more streaks are found, due to new candies falling.
    while(true){
        if(evalBoard()) break;
    }
}

void Game::swapCandy(Coord c1, Coord c2,int speed) {
    //Makes it look like candies are being swapped.
    // Intersects two candies, then swaps the candy types, and the candies return to their spots.
    // No swapping was done of the candies, but rather just the types.
    animations.intersectCandy(c1,c2,speed);
    board.swapCandyType(c1, c2);
    animations.restoreCandy(c1,c2,speed);
}


void Game::sinkCandy(int x) {
    //cause candies to "sink"
    //Swaps the deleted candies upwards, makes it look like its sinking.


    //if the top is not colored, then everything has been sunk and spaces are at the top.
    if(board.getCandyType(Coord{x,0})==0){
        return;
    }
    int spaceCount = 9;
    //counts number of spaces below
    for (int y = 0; y < 9; ++y) {
        if(y==8 || board.getCandyType(Coord{x,y+1})!=0) {
            spaceCount-=1;
        }
        //if a space has been found, shift it upwards. Swap with cell above
        else{
            swapCandy(Coord{x, y}, Coord{x, y + 1},25);
        }
    }
    //if no spaces remain, end fxn
    if(spaceCount==0) {
        return;
    }
    //else, spaces need to be shifted upwards.
    sinkCandy(x);
}


void Game::rainCandy(int x){
    //Fills a column with candies

    //if the top candy is colored, return
    if(board.getCandyType(Coord{x,0})!=0){
        return;
    }
    //else fill it and sink the candy down
    board.getCandy(Coord{x,0}).shuffleType();
    sinkCandy(x);
}

int Game::getBestScore() {
    //reads file "score", gets first line and sets it as bestscore.
    std::string s;
    std::fstream f;
    f.open("score");
    std::getline(f, s);
    return std::stoi(s);
}


void Game::saveScore() {
    //makes a temp file with current score, deletes the file "score", renames temp to score. From https://stackoverflow.com/questions/9505085/replace-a-line-in-text-file
    std::ofstream out("temp");
    out << score;
    out.close();
    remove("score");
    rename("temp","score");
    bestScore = getBestScore();
}
