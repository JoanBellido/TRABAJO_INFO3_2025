#pragma once
#ifndef TABLERO_H
#define TABLERO_H

#include <vector>

class Tablero {
private:
    std::vector<std::vector<char>> casillas;

public:
    Tablero();         // Constructor
    void dibuja();     // Dibuja en 2D usando OpenGL
};

#endif


