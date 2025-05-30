#pragma once
#include "freeglut.h"
class TexturaPiezas
{
public:

    enum IDTextura {
        B_PEON,
        B_TORRE,
        B_CABALLO,
        B_ALFIL,
        B_REINA,
        B_REY,
        N_PEON,
        N_TORRE,
        N_CABALLO,
        N_ALFIL,
        N_REINA,
        N_REY,
        FONDO_MENU,
        TOTAL_TEXTURAS
    };

    GLuint cargarTexturaPNG(const char* filename);
    void cargarTodasLasTexturas(GLuint texturas[]);
    void dibujarPieza(GLuint texID, float x, float y, float size);

};
