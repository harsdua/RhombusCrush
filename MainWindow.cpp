//
// Created by hars on 22/07/22.
//

#include "MainWindow.h"


//set to 2 if u want loading screen
int MainWindow::isLoading = 2;

void MainWindow::drawLoadingScreen(){
    fl_font(FL_HELVETICA,18);
    fl_color(FL_BLACK);
    fl_draw("By: Harsh",windowWidth/3,windowHeight/2);
    fl_draw("Rhombus crush 1.0",windowWidth/2.5,windowHeight/2.5);
    isLoading-=1;

}
void MainWindow::drawScore() {
    fl_font(FL_HELVETICA, 18);
    fl_color(FL_BLACK);
    //draw score
    fl_draw("Score : ", windowWidth * 0.05, windowHeight * 0.05);
    fl_draw(std::to_string(game.score).c_str(), windowWidth * .15, windowHeight * 0.05);
    //draw best score
    fl_draw("Best Score : ", windowWidth * 0.25, windowHeight * 0.05);
    fl_draw(std::to_string(game.bestScore).c_str(), windowWidth * .42, windowHeight * 0.05);

    fl_draw("Reset Score : ", windowWidth * 0.55, windowHeight * 0.05);
    resetSquare = Square{Pxl{windowWidth * 0.73,windowHeight * 0.04}};
    resetSquare.l = 35;
    resetSquare.setFillColor(FL_RED);
    resetSquare.draw();
}

MainWindow::MainWindow() : Fl_Window(100, 100,
                                    windowWidth, windowHeight,
                                    "Candy Crush") {
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
    resizable(this);
}

void MainWindow::draw() {
    //std::cout<< isLoading;
    Fl_Window::draw();
    if(isLoading)drawLoadingScreen();
    else {
        drawScore();
        game.draw();
    }

}

int MainWindow::handle(int event) {
    Pxl eventLoc = Pxl{static_cast<float>(Fl::event_x()), static_cast<float>(Fl::event_y())};
    switch (event) {
        case FL_PUSH:
            if (resetSquare.contains(eventLoc)) game.saveScore();
            game.handleMouseEvent(eventLoc);
            return 1;

        case FL_RELEASE:
            game.handleMouseEvent(eventLoc);
            return 1;
    }
    return 0;
}


void MainWindow::Timer_CB(void *userdata) {
    MainWindow *o = (MainWindow*) userdata;
    o->redraw();
    float fq = 1/ refreshPerSecond;
    float t = isLoading * 3 + fq;
    Fl::repeat_timeout(t, Timer_CB, userdata);}
    //Fl::repeat_timeout(1.0/refreshPerSecond, Timer_CB, userdata);}
    //Fl::repeat_timeout(0.5, Timer_CB, userdata);}





