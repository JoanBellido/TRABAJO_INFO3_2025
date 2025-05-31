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

void TexturaPiezas::cargarTexturasClasicas(GLuint texturas[]) {
    texturas[B_PEON] = cargarTexturaPNG("bin/piezas/b_peon.png");
    texturas[B_TORRE] = cargarTexturaPNG("bin/piezas/b_torre.png");
    texturas[B_CABALLO] = cargarTexturaPNG("bin/piezas/b_caballo.png");
    texturas[B_ALFIL] = cargarTexturaPNG("bin/piezas/b_alfil.png");
    texturas[B_REINA] = cargarTexturaPNG("bin/piezas/b_reina.png");
    texturas[B_REY] = cargarTexturaPNG("bin/piezas/b_rey.png");
    texturas[N_PEON] = cargarTexturaPNG("bin/piezas/n_peon.png");
    texturas[N_TORRE] = cargarTexturaPNG("bin/piezas/n_torre.png");
    texturas[N_CABALLO] = cargarTexturaPNG("bin/piezas/n_caballo.png");
    texturas[N_ALFIL] = cargarTexturaPNG("bin/piezas/n_alfil.png");
    texturas[N_REINA] = cargarTexturaPNG("bin/piezas/n_reina.png");
    texturas[N_REY] = cargarTexturaPNG("bin/piezas/n_rey.png");
}
void TexturaPiezas::cargarmenu(GLuint texturas[]) {
    texturas[FONDO_MENU] = cargarTexturaPNG("bin/piezas/fondo_menu.jpg");
}
void TexturaPiezas::cargarTexturasEgipcias(GLuint texturas[]) {
    texturas[B_PEON] = cargarTexturaPNG("bin/piezas/buenos_peon.png");
    texturas[B_TORRE] = cargarTexturaPNG("bin/piezas/buenos_torre.png");
    texturas[B_CABALLO] = cargarTexturaPNG("bin/piezas/buenos_caballo.png");
    texturas[B_ALFIL] = cargarTexturaPNG("bin/piezas/buenos_alfil.png");
    texturas[B_REINA] = cargarTexturaPNG("bin/piezas/buenos_reina.png");
    texturas[B_REY] = cargarTexturaPNG("bin/piezas/buenos_rey.png");
    texturas[N_PEON] = cargarTexturaPNG("bin/piezas/malos_peon.png");
    texturas[N_TORRE] = cargarTexturaPNG("bin/piezas/malos_torre.png");
    texturas[N_CABALLO] = cargarTexturaPNG("bin/piezas/malos_caballo.png");
    texturas[N_ALFIL] = cargarTexturaPNG("bin/piezas/malos_alfil.png");
    texturas[N_REINA] = cargarTexturaPNG("bin/piezas/malos_reina.png");
    texturas[N_REY] = cargarTexturaPNG("bin/piezas/malos_rey.png");
}

void TexturaPiezas::dibujarPieza(GLuint texID, float x, float y, float size) {
   
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, texID);

        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(x, y);
        glTexCoord2f(1, 0); glVertex2f(x + size, y);
        glTexCoord2f(1, 1); glVertex2f(x + size, y + size);
        glTexCoord2f(0, 1); glVertex2f(x, y + size);
        glEnd();

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);

};


