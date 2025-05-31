#pragma once
#include <string>

enum class EstadoJuego {
    MENU,
    JUGANDO,
    CREDITOS,
    CONFIG
};
enum class ModoJuego {
    Ninguno,
    JugadorVsJugador,
    JugadorVsIA
};

class TableroLogico; 

class Menu {
public:
    Menu();

    virtual void dibujar() const;
    virtual void procesarClic(float glX, float glY, EstadoJuego& estadoJuego, ModoJuego& modoJuego, TableroLogico* logico) const;


protected:
    struct Boton {
        float centroX, centroY;
        float ancho, alto;
        std::string texto;
    };

    Boton boton1vs1;
    Boton botonVsIA;
    Boton botoncred;
    Boton botonconfig;

    void dibujarBoton(const Boton& boton) const;
};

