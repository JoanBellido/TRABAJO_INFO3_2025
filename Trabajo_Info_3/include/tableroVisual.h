#pragma once
#include "TableroLogico.h"
#include "freeglut.h"
#include <optional>

class TableroVisual {
private:
    TableroLogico* logico;
    float size;
    std::optional<Coordenada> seleccionada; // ? NUEVO

public:
    TableroVisual(TableroLogico* logico, float tam = 1.0f);
    void dibujaReloj(int tiempo, float x, float y, const char* label);
    void dibuja();
    void setSeleccionada(std::optional<Coordenada> sel); // ? NUEVO
};


