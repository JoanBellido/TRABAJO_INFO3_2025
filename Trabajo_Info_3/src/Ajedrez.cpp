#include "freeglut.h"
#include "TableroLogico.h"
#include "TableroVisual.h"
#include "Menu.h"
#include <optional>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

int tiempoBlanco = 300;
int tiempoNegro = 300;
bool tiempoFinalizado = false;
int lastTick = 0;
std::string mensajeEstado = "";

Menu menu;
EstadoJuego estadoJuego = EstadoJuego::MENU;
ModoJuego modojuego;
TableroLogico tableroLogico;
TableroVisual tableroVisual(&tableroLogico, 1.0f);

std::optional<Coordenada> seleccion;

// ✅ NUEVO: control para parpadeo de mensaje
bool mostrarMensaje = true;
int blinkTimer = 0;

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

    if (estadoJuego == EstadoJuego::MENU) {
        menu.dibujar();
        return;
    }

    if (estadoJuego == EstadoJuego::CREDITOS) {
        glColor3f(0.1f, 0.1f, 0.1f);
        glRasterPos2f(-2.0f, 2.5f);
        const char* titulo = "Equipo G08";
        for (const char* c = titulo; *c; ++c)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        const char* nombres[] = {
            "Sergio Ballesteros Palomo",
            "Joan Bellido Ines",
            "Nuria Garrido Gimenez",
            "Matias Gabriel Polo Reyes",
            "Manuel Gutierrez Huerta"
        };
        float y = 2.0f;
        for (int i = 0; i < 5; ++i, y -= 0.5f) {
            glRasterPos2f(-2.0f, y);
            for (const char* c = nombres[i]; *c; ++c)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
        glRasterPos2f(-2.0f, -1.2f);
        const char* volver = "Presiona ESC para volver al menu";
        for (const char* c = volver; *c; ++c)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        glutSwapBuffers();
        return;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    tableroVisual.dibuja();

    // ✅ Mensaje de JAQUE o JAQUE MATE con parpadeo
    if (!mensajeEstado.empty() && mostrarMensaje) {
        glColor3f(1.0f, 0.7f, 0.7f);
        glBegin(GL_QUADS);
        glVertex2f(-3.0f, 4.8f);
        glVertex2f(3.0f, 4.8f);
        glVertex2f(3.0f, 4.3f);
        glVertex2f(-3.0f, 4.3f);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos2f(-2.5f, 4.5f);
        for (char c : mensajeEstado)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glutSwapBuffers();
}

void OnMouse(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    float glX = -5.5f + (float)x / w * 11.0f;
    float glY = 5.0f - (float)y / h * 10.0f;

    if (estadoJuego == EstadoJuego::MENU) {
        menu.procesarClic(glX, glY, estadoJuego, modojuego, &tableroLogico);
        glutPostRedisplay();
        return;
    }

    if (tiempoFinalizado) return;

    int fila = static_cast<int>(5.0f - glY);
    int col = static_cast<int>(glX + 5.5f);
    if (!casillaActiva(fila, col)) return;

    Coordenada clic = { fila, col };
    Pieza* p = tableroLogico.getPieza(clic);

    if (!seleccion) {
        if (p && p->getColor() == tableroLogico.getTurno()) {
            seleccion = clic;
            tableroVisual.setSeleccionada(seleccion);
        }
    }
    else {
        if (tableroLogico.mover(*seleccion, clic)) {
            tableroLogico.imprimir();

            Color turnoTrasMovimiento = tableroLogico.getTurno();
            if (tableroLogico.reyEnJaque(turnoTrasMovimiento)) {
                mensajeEstado = "\u00a1Estás en jaque!";
                if (tableroLogico.esJaqueMate(turnoTrasMovimiento)) {
                    mensajeEstado = "\u00a1Jaque mate! Gana el jugador ";
                    mensajeEstado += (turnoTrasMovimiento == BLANCO ? "NEGRO" : "BLANCO");
                    tiempoFinalizado = true;
                }
            }
            else {
                mensajeEstado = "";
            }

            if (modojuego == ModoJuego::JugadorVsIA && !tiempoFinalizado) {
                std::thread iaThread([] {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    tableroLogico.movimientoIA();
                    glutPostRedisplay();
                    });
                iaThread.detach();
            }
        }

        seleccion.reset();
        tableroVisual.setSeleccionada(std::nullopt);
    }

    glutPostRedisplay();
}

void OnKeyboardDown(unsigned char key, int, int) {
    if (key == 'r') {
        seleccion.reset();
        tableroVisual.setSeleccionada(std::nullopt);
        tiempoBlanco = 300;
        tiempoNegro = 300;
        tiempoFinalizado = false;
        mensajeEstado = "";
        tableroLogico.inicializar();
        tableroLogico.imprimir();
    }

    if (key == 27) {
        tableroLogico.inicializar();
        seleccion.reset();
        tableroVisual.setSeleccionada(std::nullopt);
        tiempoBlanco = 300;
        tiempoNegro = 300;
        tiempoFinalizado = false;
        mensajeEstado = "";
        estadoJuego = EstadoJuego::MENU;
    }

    glutPostRedisplay();
}

void OnTimer(int value) {
    int now = glutGet(GLUT_ELAPSED_TIME);
    if (!tiempoFinalizado && estadoJuego == EstadoJuego::JUGANDO && now - lastTick >= 1000) {
        lastTick = now;

        if (tableroLogico.getTurno() == BLANCO) {
            if (--tiempoBlanco <= 0) {
                tiempoBlanco = 0;
                tiempoFinalizado = true;
                mensajeEstado = "\u00a1Tiempo agotado! Gana el jugador NEGRO";
            }
        }
        else {
            if (--tiempoNegro <= 0) {
                tiempoNegro = 0;
                tiempoFinalizado = true;
                mensajeEstado = "\u00a1Tiempo agotado! Gana el jugador BLANCO";
            }
        }
    }

    // ✅ Control de parpadeo del mensaje cada 500 ms
    blinkTimer += 25;
    if (blinkTimer >= 500) {
        mostrarMensaje = !mostrarMensaje;
        blinkTimer = 0;
    }

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

    lastTick = glutGet(GLUT_ELAPSED_TIME);

    glutDisplayFunc(OnDraw);
    glutMouseFunc(OnMouse);
    glutKeyboardFunc(OnKeyboardDown);
    glutTimerFunc(25, OnTimer, 0);

    glutMainLoop();
    return 0;
}







