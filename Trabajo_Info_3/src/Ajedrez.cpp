#include "freeglut.h"
#include "TableroLogico.h"
#include "TableroVisual.h"
#include <optional>
#include <iostream>

TableroLogico tableroLogico;
TableroVisual tableroVisual(&tableroLogico, 1.0f);

std::optional<Coordenada> seleccion;

bool casillaActiva(int fila, int col) {
    static int activos[] = { 3,5,7,9,11,11,9,7,5,3 };
    if (fila < 0 || fila >= 10 || col < 0 || col >= 11) return false;
    int inicio = (11 - activos[fila]) / 2;
    int fin = inicio + activos[fila];
    return col >= inicio && col < fin;
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
    float glX = -5.5f + (float)x / w * 11.0f;
    float glY = 5.0f - (float)y / h * 10.0f;

    int fila = static_cast<int>(5.0f - glY);
    int col = static_cast<int>(glX + 5.5f);

    if (!casillaActiva(fila, col)) return;

    Coordenada clic = { fila, col };
    std::cout << "Click en: [" << fila << "," << col << "]\n";

    Pieza* p = tableroLogico.getPieza(clic);
    if (!seleccion) {
        if (p && p->getColor() == tableroLogico.getTurno()) {
            seleccion = clic;
            std::cout << "Seleccionada pieza " << p->getID() << " en [" << fila << "," << col << "]\n";
        }
        else {
            std::cout << "Seleccion inválida\n";
        }
    }
    else {
        if (tableroLogico.mover(*seleccion, clic)) {
            std::cout << "Movimiento realizado a [" << clic.fila << "," << clic.col << "]\n";
        }
        else {
            std::cout << "Movimiento inválido\n";
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

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Ajedrez Balbo 2D");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.5f, 5.5f, -5.0f, 5.0f);

    glutDisplayFunc(OnDraw);
    glutMouseFunc(OnMouse);
    glutKeyboardFunc(OnKeyboardDown);
    glutTimerFunc(25, OnTimer, 0);

    tableroLogico.inicializar();
    glutMainLoop();
    return 0;
}


