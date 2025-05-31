#pragma once
#include "Menu.h"

class MenuTematica {
public:
    MenuTematica();
    void dibujar() const;
    void procesarClic(float glX, float glY, EstadoJuego& estadoJuego, ModoJuego modoJuego, TematicaJuego& tematica);

private:
    struct Boton {
        float centroX, centroY;
        float ancho, alto;
        std::string texto;
    };

    Boton botonClasico;
    Boton botonEgipcio;
    void dibujarBoton(const Boton& boton) const;
};
