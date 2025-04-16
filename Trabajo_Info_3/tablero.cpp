#include "tablero.h"
#include "freeglut.h"
#include <cmath>

Tablero::Tablero() {
    int tamanios[] = { 1,2,3,4,5,6,5,4,3,2,1 };
    for (int i = 0; i < 11; ++i)
        casillas.push_back(std::vector<char>(tamanios[i], '.'));
}

void Tablero::dibuja() {
    float size = 1.0f;
    float startY = 5.0f;

    for (int i = 0; i < casillas.size(); ++i) {
        float offsetX = -casillas[i].size() * size / 2.0f;
        for (int j = 0; j < casillas[i].size(); ++j) {
            float x = offsetX + j * size;
            float y = startY - i * size;

            glColor3f(1.0f, 0.0f, 0.0f); // ROJO

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + size, y);
            glVertex2f(x + size, y - size);
            glVertex2f(x, y - size);
            glEnd();
        }
    }
}



