#include "menuconfig.h"
#include "freeglut.h"
#include <iostream>
#include "TexturaPiezas.h"
extern GLuint texturas[];

MenuConfig::MenuConfig()
    : botonTheme1{ 0.0f, 2.0f, 4.0f, 1.2f, "Tema1" },
    botonTheme2{ 0.0f, 0.6f, 4.0f, 1.2f, "Tema2" },
    botonMute{ 0.0f, -0.8f, 4.0f, 1.2f, "Sin sonido" },
    botonVolver{ 0.0f, -2.2f, 4.0f, 1.2f, "Volver" }{
}

void MenuConfig::dibujar() const {
    glClearColor(0.85f, 0.9f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.1f, 0.1f, 0.3f);
    glRasterPos2f(-2.0f, 3.0f);
    // dibuja fondo
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texturas[TexturaPiezas::FONDO_MENU]);

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-5.5f, 5.0f);
    glTexCoord2f(1, 0); glVertex2f(5.5f, 5.0f);
    glTexCoord2f(1, 1); glVertex2f(5.5f, -5.0f);
    glTexCoord2f(0, 1); glVertex2f(-5.5f, -5.0f);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    //
    const char* titulo = "Configuracion del Juego";
    for (const char* c = titulo; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    dibujarBoton(botonTheme1);
    dibujarBoton(botonTheme2);
    dibujarBoton(botonMute);
    dibujarBoton(botonVolver);

    glutSwapBuffers();
}


void MenuConfig::procesarClic(float glX, float glY, EstadoJuego& estadoJuego, ModoJuego& /*modojuego*/, TableroLogico* /*logico*/) const {
    auto clicEnBoton = [](float x, float y, const Boton& b) {
        return x >= b.centroX - b.ancho / 2 && x <= b.centroX + b.ancho / 2 &&
            y >= b.centroY - b.alto / 2 && y <= b.centroY + b.alto / 2;
        };

    if (clicEnBoton(glX, glY, botonTheme1)) {
        ETSIDI::play("bin/music/click.mp3");
        std::cout << "Botón de tema 1 clicado\n";
        ETSIDI::playMusica("bin/music/soundtrack1.mp3", true); //canción1
    }
    else if (clicEnBoton(glX, glY, botonTheme2)) {
        ETSIDI::play("bin/music/click.mp3");
        std::cout << "Botón de tema2 clicado\n";
        ETSIDI::playMusica("bin/music/soundtrack2.mp3", true); //canción2
    }
    else if (clicEnBoton(glX, glY, botonMute)) {
        ETSIDI::play("bin/music/click.mp3");
        std::cout << "Botón de mutear clicado\n";
        ETSIDI::stopMusica();
    }
    else if (clicEnBoton(glX, glY, botonVolver)) {
        ETSIDI::play("bin/music/click.mp3");
        estadoJuego = EstadoJuego::MENU;
    }
}

