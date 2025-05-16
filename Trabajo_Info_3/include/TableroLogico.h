#pragma once
#include "pieza.h"

class TableroLogico {
private:
    std::vector<std::vector<Pieza*>> cuadricula;
    Color turno;

public:
    TableroLogico();
    ~TableroLogico();

    void asignar(const Coordenada& pos, Pieza* pieza);
    Pieza* getPieza(const Coordenada& pos) const;

    bool mover(const Coordenada& origen, const Coordenada& destino);
    Color getTurno() const { return turno; }
    void cambiarTurno();

    int filas() const;
    int columnas(int fila) const;
    bool coordenadaValida(const Coordenada& c) const;

    void inicializar();
    void imprimir() const;

    bool reyEnJaque(Color colorRey) const; 
    bool esJaqueMate(Color color);
private:
    bool esCasillaFinalPromocionable(const Coordenada& c, Color color) const;
};








