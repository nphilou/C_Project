cmake_minimum_required(VERSION 2.8.4)
project(C_Project)

SET(GCC_COVERAGE_COMPILE_FLAGS "-lm -lSDL -lSDL_image -lSDL_ttf")
SET(GCC_COVERAGE_LINK_FLAGS    "-lm -lSDL -lSDL_image -lSDL_ttf")

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

set(SOURCE_FILES
    config.h
    structures.h
    affichage.h
    affichage.c
    plateau.c
    plateau.h
    init.c
    init.h
    combat.c
    combat.h
    deplacement.c
    deplacement.h
    instructions.c
    instructions.h
    app.c
    app.h
    fourmido.c
    fourmido_sdl.c)

add_executable(C_Project ${SOURCE_FILES})
