cmake_minimum_required(VERSION 3.17)
project(Pentamino_DESLOT_DUNAND C)

set(CMAKE_C_STANDARD 99)
find_package(SDL2 REQUIRED SDL2)
SET(CMAKE_CXX_LINK_FLAGS "-lSDL2")
add_executable(Pentamino_DESLOT_DUNAND main.c main.h sdl_functions.c sdl_functions.h)
target_link_libraries(Pentamino_DESLOT_DUNAND PRIVATE SDL2)
