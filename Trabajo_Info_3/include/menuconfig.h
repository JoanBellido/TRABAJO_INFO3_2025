#pragma once
#include "Menu.h"
#include "ETSIDI.h"

class MenuConfig : public Menu {
public:
    MenuConfig();

    void dibujar() const override;
    void procesarClic(float glX, float glY, EstadoJuego& estadoJuego, ModoJuego& modoJuego, TableroLogico* logico) const override;//override!!!

private:
    Boton botonTheme1;
    Boton botonTheme2;
    Boton botonVolver;
    Boton botonMute;
};
