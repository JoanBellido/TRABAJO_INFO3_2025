#pragma once
#include "Menu.h"

class MenuConfig : public Menu {
public:
    MenuConfig();

    void dibujar() const override;
    void procesarClic(float glX, float glY, EstadoJuego& estadoJuego, ModoJuego& modoJuego, TableroLogico* logico) const override;//override!!!

private:
    Menu::Boton botonTheme1;
    Menu::Boton botonTheme2;
    Menu::Boton botonVolver;
    Menu::Boton botonMute;
};
