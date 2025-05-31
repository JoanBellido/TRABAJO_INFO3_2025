#pragma once
#include "Menu.h"

class MenuTematica : public Menu {
public:
    MenuTematica();

    void dibujar() const override;
    void procesarClic(float glX, float glY, EstadoJuego& estadoJuego, ModoJuego modoJuego, TematicaJuego& tematica);
private:
    Menu::Boton botonClasico;
    Menu::Boton botonEgipcio;

    void dibujarBoton(const Boton& boton) const;
};
