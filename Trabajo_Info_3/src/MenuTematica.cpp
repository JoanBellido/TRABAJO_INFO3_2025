#include "MenuTematica.h"
#include "freeglut.h"
#include "TexturaPiezas.h"
extern GLuint texturas[];

MenuTematica::MenuTematica()
    : botonClasico{ 0.0f, 1.0f, 4.0f, 1.2f, "Modo Clasico" },
    botonEgipcio{ 0.0f, -1.0f, 4.0f, 1.2f, "Modo Egipcio" } {
}

void MenuTematica::dibujar() const {
    glClearColor(0.9f, 0.9f, 0.95f, 1.0f);
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
    const char* titulo = "Selecciona Tematica";
    for (const char* c = titulo; *c; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    dibujarBoton(botonClasico);
    dibujarBoton(botonEgipcio);
    glutSwapBuffers();
}

void MenuTematica::dibujarBoton(const Boton& boton) const {
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

void MenuTematica::procesarClic(float glX, float glY, EstadoJuego& estadoJuego, ModoJuego modoJuego, TematicaJuego& tematica) {
    extern TexturaPiezas texturaPiezas;
    extern GLuint texturas[];  // Usamos los mismos arrays globales

    auto clicEnBoton = [](float x, float y, const Boton& b) {
        return x >= b.centroX - b.ancho / 2 && x <= b.centroX + b.ancho / 2 &&
            y >= b.centroY - b.alto / 2 && y <= b.centroY + b.alto / 2;
        };

    if (clicEnBoton(glX, glY, botonClasico)) {
        tematica = TematicaJuego::Clasico;
        texturaPiezas.cargarTexturasClasicas(texturas);   // <-- Aqu� cargas las cl�sicas
        estadoJuego = EstadoJuego::JUGANDO;
    }
    else if (clicEnBoton(glX, glY, botonEgipcio)) {
        tematica = TematicaJuego::Egipcio;
        texturaPiezas.cargarTexturasEgipcias(texturas);   // <-- Aqu� cargas las egipcias
        estadoJuego = EstadoJuego::JUGANDO;
    }
}

