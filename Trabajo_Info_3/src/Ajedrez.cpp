#include "freeglut.h"
#include "TableroLogico.h"
#include "TableroVisual.h"
#include <optional>
#include <iostream>

TableroLogico tableroLogico;
TableroVisual tableroVisual(&tableroLogico, 1.0f);

std::optional<Coordenada> seleccion;

void OnDraw();
void OnMouse(int button, int state, int x, int y);
void OnKeyboardDown(unsigned char key, int x, int y);
void OnTimer(int value);

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Ajedrez Balbo 2D");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-7, 7, -6, 6);

    glutDisplayFunc(OnDraw);
    glutMouseFunc(OnMouse);
    glutKeyboardFunc(OnKeyboardDown);
    glutTimerFunc(25, OnTimer, 0);

    tableroLogico.inicializar();
    glutMainLoop();
    return 0;
}

void OnDraw() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    tableroVisual.dibuja();
    glutSwapBuffers();
}

void OnMouse(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    float glX = -7.0f + (float)x / w * 14.0f;
    float glY = -6.0f + (float)(h - y) / h * 12.0f;

    int fila = static_cast<int>(6 - glY);
    if (fila < 0 || fila >= tableroLogico.filas()) return;

    int cols = tableroLogico.columnas(fila);
    float inicioX = -cols * 0.5f;
    int col = -1;
    for (int j = 0; j < cols; ++j) {
        float xMin = inicioX + j;
        float xMax = xMin + 1;
        if (glX >= xMin && glX < xMax) {
            col = j;
            break;
        }
    }

    if (col == -1) return;
    Coordenada clic = { fila, col };

    std::cout << "Click en: fila = " << fila << ", col = " << col << std::endl;
    Pieza* p = tableroLogico.getPieza(clic);
    if (p) {
        std::cout << "Pieza detectada: "
            << (p->getColor() == Color::BLANCO ? "BLANCO " : "NEGRO ")
            << p->getID() << std::endl;
    }
    else {
        std::cout << "No hay pieza en esta casilla\n";
    }

    if (!seleccion) {
        if (p && p->getColor() == tableroLogico.getTurno()) {
            seleccion = clic;
            std::cout << "Pieza seleccionada en [" << clic.fila << "," << clic.col << "]\n";
        }
        else {
            std::cout << "Seleccion inválida.\n";
        }
    }
    else {
        if (tableroLogico.mover(*seleccion, clic)) {
            std::cout << "Movimiento realizado de [" << seleccion->fila << "," << seleccion->col
                << "] a [" << clic.fila << "," << clic.col << "]\n";
        }
        else {
            std::cout << "Movimiento no permitido de [" << seleccion->fila << "," << seleccion->col
                << "] a [" << clic.fila << "," << clic.col << "]\n";
        }
        seleccion.reset();
    }

    glutPostRedisplay();
}

void OnKeyboardDown(unsigned char key, int, int) {
    if (key == 'r') {
        tableroLogico.inicializar();
        seleccion.reset();
        std::cout << "Tablero reiniciado\n";
    }
    glutPostRedisplay();
}

void OnTimer(int value) {
    glutTimerFunc(25, OnTimer, 0);
    glutPostRedisplay();
}


