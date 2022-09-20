//
// Created by hars on 22/07/22.
//

#ifndef CANDYCRUSH_MAINWINDOW_H
#define CANDYCRUSH_MAINWINDOW_H
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include "Game.h"
using namespace std;

class MainWindow : public Fl_Window{
    Game game;
public:
    Square resetSquare;
    static int isLoading;
    MainWindow();
    void draw() override;
        int handle(int event) override;
        static void Timer_CB(void *userdata);
    void drawLoadingScreen();
    void drawScore();
};


#endif //CANDYCRUSH_MAINWINDOW_H
