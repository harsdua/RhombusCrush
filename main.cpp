//#include <FL/Fl.H>
//#include <FL/Fl_Window.H>
//#include <FL/Fl_Box.H>

#include "MainWindow.h"


int main(int argc, char** argv){
    srand(0);
    MainWindow mw;
    mw.show();
    return Fl::run();
}