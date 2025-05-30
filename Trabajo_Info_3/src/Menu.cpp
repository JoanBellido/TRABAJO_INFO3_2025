#include "Menu.h"
#include "TableroLogico.h"
#include "freeglut.h"

Menu::Menu()
    : boton1vs1{ 0.0f, 2.0f, 4.0f, 1.2f, "Jugador vs Jugador" },
    botonVsIA{ 0.0f, 0.6f, 4.0f, 1.2f, "Jugador vs Ordenador" }, 
    botoncred{ 0.0f, -2.2f, 4.0f, 1.2f, "Creditos" },
    botonconfig{ 0.0f, -0.8f, 4.0f, 1.2f, "Configuracion" } {
}

void Menu::dibujar() const {
    glClearColor(0.9f, 0.9f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.1f, 0.1f, 0.3f);
    glRasterPos2f(-2.0f, 3.0f);
    const char* titulo = "Ajedrez Balbo";
    for (const char* c = titulo; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    dibujarBoton(boton1vs1);
    dibujarBoton(botonVsIA);
    dibujarBoton(botoncred);
    dibujarBoton(botonconfig);

    glutSwapBuffers();
}

void Menu::dibujarBoton(const Boton& boton) const {
    glColor3f(0.6f, 0.6f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(boton.centroX - boton.ancho / 2, boton.centroY + boton.alto / 2);
    glVertex2f(boton.centroX + boton.ancho / 2, boton.centroY + boton.alto / 2);
    glVertex2f(boton.centroX + boton.ancho / 2, boton.centroY - boton.alto / 2);
    glVertex2f(boton.centroX - boton.ancho / 2, boton.centroY - boton.alto / 2);
    glEnd();

    glColor3f(0, 0, 0);
    glRasterPos2f(boton.centroX - 1.5f, boton.centroY - 0.2f);
    for (char c : boton.texto)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

void Menu::procesarClic(float glX, float glY, EstadoJuego& estadoJuego, ModoJuego& modoJuego, TableroLogico* logico) const {
    auto clicEnBoton = [](float x, float y, const Boton& b) {
        return x >= b.centroX - b.ancho / 2 && x <= b.centroX + b.ancho / 2 &&
            y >= b.centroY - b.alto / 2 && y <= b.centroY + b.alto / 2;
        };

    if (clicEnBoton(glX, glY, boton1vs1)) {
        modoJuego = ModoJuego::JugadorVsJugador;
        logico->inicializar();
        logico->imprimir();
        estadoJuego = EstadoJuego::JUGANDO;
    }
    else if (clicEnBoton(glX, glY, botonVsIA)) {
        modoJuego = ModoJuego::JugadorVsIA;
        logico->inicializar();
        logico->imprimir();
        estadoJuego = EstadoJuego::JUGANDO;
    }
    else if (clicEnBoton(glX, glY, botoncred)) {
        estadoJuego = EstadoJuego::CREDITOS;
    }
    else if (clicEnBoton(glX, glY, botonconfig)) {
        estadoJuego = EstadoJuego::CONFIG;
    }
}


