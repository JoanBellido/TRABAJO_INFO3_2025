#pragma once
#include "TableroLogico.h"
#include "freeglut.h"

class TableroVisual {
private:
    TableroLogico* logico;
    float size;

public:
    TableroVisual(TableroLogico* logico, float tam = 1.0f);
    void dibujaReloj(int tiempo, float x, float y, const char* label);

    void dibuja();
};


