#include "TableroVisual.h"
#include "TexturaPiezas.h"
#include <string>

extern int tiempoBlanco, tiempoNegro;
extern TexturaPiezas texturaPiezas;
extern GLuint texturas[];

TableroVisual::TableroVisual(TableroLogico* logico, float tam)
    : logico(logico), size(tam) {
}

void TableroVisual::setSeleccionada(std::optional<Coordenada> sel) {
    seleccionada = sel;
}

void TableroVisual::dibujaReloj(int tiempo, float x, float y, const char* label) {
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.2f, y + 0.3f);
    glVertex2f(x + 2.2f, y + 0.3f);
    glVertex2f(x + 2.2f, y - 0.4f);
    glVertex2f(x - 0.2f, y - 0.4f);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - 0.2f, y + 0.3f);
    glVertex2f(x + 2.2f, y + 0.3f);
    glVertex2f(x + 2.2f, y - 0.4f);
    glVertex2f(x - 0.2f, y - 0.4f);
    glEnd();

    if (tiempo <= 30)
        glColor3f(1.0f, 0.2f, 0.2f);
    else
        glColor3f(0.0f, 0.0f, 0.0f);

    glRasterPos2f(x, y);
    std::string texto = std::string(label) + ": " + std::to_string(tiempo) + "s";
    for (char c : texto)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
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

                    GLuint texID = texturas[p->getTipoTextura()];
                    if (texID != 0) {
                        texturaPiezas.dibujarPieza(texID, x, y - size, size);
                    }


                }
            }
        }

        if (seleccionada) {
            Coordenada c = *seleccionada;
            float x = origenX + c.col * size;
            float y = origenY - c.fila * size;

            glColor3f(1.0f, 1.0f, 0.0f);
            glLineWidth(3.0f);
            glBegin(GL_LINE_LOOP);
            glVertex2f(x, y);
            glVertex2f(x + size, y);
            glVertex2f(x + size, y - size);
            glVertex2f(x, y - size);
            glEnd();
            glLineWidth(1.0f);
        }

        dibujaReloj(tiempoBlanco, 3.2f, 4.0f, "Blanco");
        dibujaReloj(tiempoNegro, 3.2f, -4.0f, "Negro");

        Color turnoActual = logico->getTurno();
        float turnoX = -5.2f;
        float turnoY = (turnoActual == Color::BLANCO) ? 4.0f : -4.0f;

        float r = (turnoActual == Color::BLANCO) ? 0.95f : 0.2f;
        float g = (turnoActual == Color::BLANCO) ? 0.95f : 0.2f;
        float b = (turnoActual == Color::BLANCO) ? 1.0f : 0.2f;

        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glVertex2f(turnoX - 0.2f, turnoY + 0.3f);
        glVertex2f(turnoX + 2.4f, turnoY + 0.3f);
        glVertex2f(turnoX + 2.4f, turnoY - 0.3f);
        glVertex2f(turnoX - 0.2f, turnoY - 0.3f);
        glEnd();

        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(turnoX - 0.2f, turnoY + 0.3f);
        glVertex2f(turnoX + 2.4f, turnoY + 0.3f);
        glVertex2f(turnoX + 2.4f, turnoY - 0.3f);
        glVertex2f(turnoX - 0.2f, turnoY - 0.3f);
        glEnd();

        glColor3f(0, 0, 0);
        glRasterPos2f(turnoX + 0.2f, turnoY - 0.05f);
        std::string textoTurno = "Turno: " + std::string(turnoActual == Color::BLANCO ? "Blanco" : "Negro");
        for (char c : textoTurno)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

    }
}













