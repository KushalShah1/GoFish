cmake_minimum_required(VERSION 3.14)
project(GoFish)

set(CMAKE_CXX_STANDARD 14)

add_executable(GoFish go_fish.cpp deck.cpp card.cpp card.h player.cpp player.h)