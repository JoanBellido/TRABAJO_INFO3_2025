#include "TableroVisual.h"

TableroVisual::TableroVisual(TableroLogico* logico, float tam)
    : logico(logico), size(tam) {
}

void TableroVisual::dibuja() {
    float centroY = 0.0f;
    float centroX = 0.0f;
    int totalFilas = logico->filas();

    for (int i = 0; i < totalFilas; ++i) {
        int numColumnas = logico->columnas(i);
        float y = centroY + (totalFilas / 2 - i) * size;
        float inicioX = centroX - (numColumnas / 2.0f) * size;
        bool invertir = i >= (totalFilas / 2);

        for (int j = 0; j < numColumnas; ++j) {
            float x = inicioX + j * size;

            glColor3f((j % 2 == 0) ^ invertir ? 0.6f : 0.3f, 0.8f, 0.6f);
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + size, y);
            glVertex2f(x + size, y - size);
            glVertex2f(x, y - size);
            glEnd();

            Pieza* p = logico->getPieza({ i, j });
            if (p) {
                glColor3f(0, 0, 0);
                glRasterPos2f(x + 0.3f, y - 0.7f);
                char text[3] = { (p->getColor() == Color::BLANCO ? 'B' : 'N'), p->getID(), '\0' };
                for (int k = 0; text[k]; ++k)
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[k]);
            }
        }
    }
}









