#define STB_IMAGE_IMPLEMENTATION
#ifdef _WIN32
#include <Windows.h>
#endif 
#include <gl/GL.h>
#include <gl/GLU.h>
#include "TexturaPiezas.h"
#include "stb_image.h"
#include <iostream>
#include "pieza.h"



GLuint TexturaPiezas::cargarTexturaPNG(const char* filename) {
    int ancho, alto, canales;
    unsigned char* data = stbi_load(filename, &ancho, &alto, &canales, STBI_rgb_alpha);
    if (!data) {
        std::cerr << "Error cargando: " << filename << std::endl;
        return 0;
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return texID;
}

void TexturaPiezas::cargarTodasLasTexturas(GLuint texturas[]) {
    // imagen inicio (menu)
    texturas[TexturaPiezas::FONDO_MENU] = cargarTexturaPNG("bin/piezas/fondo_menu.jpg");

    texturas[TexturaPiezas::B_PEON] = cargarTexturaPNG("bin/piezas/b_peon.png");
    texturas[TexturaPiezas::B_TORRE] = cargarTexturaPNG("bin/piezas/b_torre.png");
    texturas[TexturaPiezas::B_CABALLO] = cargarTexturaPNG("bin/piezas/b_caballo.png");
    texturas[TexturaPiezas::B_ALFIL] = cargarTexturaPNG("bin/piezas/b_alfil.png");
    texturas[TexturaPiezas::B_REINA] = cargarTexturaPNG("bin/piezas/b_reina.png");
    texturas[TexturaPiezas::B_REY] = cargarTexturaPNG("bin/piezas/b_rey.png");

    texturas[TexturaPiezas::N_PEON] = cargarTexturaPNG("bin/piezas/n_peon.png");
    texturas[TexturaPiezas::N_TORRE] = cargarTexturaPNG("bin/piezas/n_torre.png");
    texturas[TexturaPiezas::N_CABALLO] = cargarTexturaPNG("bin/piezas/n_caballo.png");
    texturas[TexturaPiezas::N_ALFIL] = cargarTexturaPNG("bin/piezas/n_alfil.png");
    texturas[TexturaPiezas::N_REINA] = cargarTexturaPNG("bin/piezas/n_reina.png");
    texturas[TexturaPiezas::N_REY] = cargarTexturaPNG("bin/piezas/n_rey.png");
}

void TexturaPiezas::dibujarPieza(GLuint texID, float x, float y, float size) {
   
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Transparencia

        glBindTexture(GL_TEXTURE_2D, texID);

        glColor3f(1.0f, 1.0f, 1.0f); // Sin tinte

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(x, y);
        glTexCoord2f(1, 0); glVertex2f(x + size, y);
        glTexCoord2f(1, 1); glVertex2f(x + size, y + size);
        glTexCoord2f(0, 1); glVertex2f(x, y + size);
        glEnd();

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);

};


