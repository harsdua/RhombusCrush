cmake_minimum_required(VERSION 3.22)
project(candycrush)

set(CMAKE_CXX_STANDARD 17)

add_executable(candycrush main.cpp MainWindow.cpp MainWindow.h Game.cpp Game.h Board.cpp Board.h Point.h Cell.cpp Cell.h Candy.cpp Candy.h Constants.h Square.h Square.cpp Animations.cpp Animations.h)
