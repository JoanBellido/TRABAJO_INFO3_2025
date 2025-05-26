#pragma once
#include <string>

enum class EstadoJuego {
    MENU,
    JUGANDO,
    CREDITOS
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

    void dibujar() const;
    void procesarClic(float glX, float glY, EstadoJuego& estadoJuego, ModoJuego& modoJuego, TableroLogico* logico) const;


private:
    struct Boton {
        float centroX, centroY;
        float ancho, alto;
        std::string texto;
    };

    Boton boton1vs1;
    Boton botonVsIA;
    Boton botoncred;

    void dibujarBoton(const Boton& boton) const;
};

