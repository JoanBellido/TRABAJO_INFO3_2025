#include "TableroVisual.h"

TableroVisual::TableroVisual(TableroLogico* logico, float tam)
    : logico(logico), size(tam) {
}

void TableroVisual::dibuja() {
    const int filas = 10;
    const int columnas = 11;
    float origenX = -columnas / 2.0f * size;
    float origenY = filas / 2.0f * size;
    int activos_por_fila[] = { 3, 5, 7, 9, 11, 11, 9, 7, 5, 3 };

    for (int i = 0; i < filas; ++i) {
        int activos = activos_por_fila[i];
        int inicio_col = (columnas - activos) / 2;

        for (int j = inicio_col; j < inicio_col + activos; ++j) {
            float x = origenX + j * size;
            float y = origenY - i * size;

            bool claro = (i + j) % 2 == 0;
            glColor3f(claro ? 0.8f : 0.3f, claro ? 0.9f : 0.4f, claro ? 0.8f : 0.3f);

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + size, y);
            glVertex2f(x + size, y - size);
            glVertex2f(x, y - size);
            glEnd();

            if (logico->coordenadaValida({ i, j })) {
                Pieza* p = logico->getPieza({ i, j });
                if (p) {
                    glColor3f(0, 0, 0);
                    glRasterPos2f(x + 0.3f, y - 0.7f);
                    char text[3] = {
                        (p->getColor() == Color::BLANCO ? 'B' : 'N'),
                        p->getID(), '\0'
                    };
                    for (int k = 0; text[k]; ++k)
                        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[k]);
                }
            }
        }
    }
}













