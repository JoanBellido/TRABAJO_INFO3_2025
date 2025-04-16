#include "tablero.h"
#include "freeglut.h"

Tablero::Tablero() {
    // 10 filas del tablero Balbo real: forma de rombo completa
    int tamanios[] = { 3, 5, 7, 9, 11, 11, 9, 7, 5, 3 };
    for (int i = 0; i < 10; ++i)
        casillas.push_back(std::vector<char>(tamanios[i], '.'));
}

void Tablero::dibuja() {
    float size = 1.0f;
    float centroY = 0.0f;
    float centroX = 0.0f;

    int totalFilas = casillas.size();

    for (int i = 0; i < totalFilas; ++i) {
        int numColumnas = casillas[i].size();
        float y = centroY + (totalFilas / 2 - i) * size;
        float inicioX = centroX - (numColumnas / 2.0f) * size;

        // Parte inferior empieza con patrón invertido
        bool invertir = i >= (totalFilas / 2);

        for (int j = 0; j < numColumnas; ++j) {
            float x = inicioX + j * size;

            // Alternancia de colores con inversión en la segunda mitad
            if ((j % 2 == 0) ^ invertir)
                glColor3f(0.6f, 0.8f, 0.6f); // verde claro
            else
                glColor3f(0.3f, 0.5f, 0.3f); // verde oscuro

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + size, y);
            glVertex2f(x + size, y - size);
            glVertex2f(x, y - size);
            glEnd();
        }
    }
}







