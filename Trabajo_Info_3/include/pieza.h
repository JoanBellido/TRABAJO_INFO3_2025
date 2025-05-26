#pragma once
#include <vector>
#include "TexturaPiezas.h"

enum Color { BLANCO, NEGRO };

struct Coordenada {
    int fila;
    int col;
};

class TableroLogico;

class Pieza {
protected:
    Color color;
    bool esBlanca;

public:
    Pieza(Color c) : color(c), esBlanca(c == BLANCO) {}
    virtual ~Pieza() = default;

    Color getColor() const { return color; }
    bool esPiezaBlanca() const { return esBlanca; }

    virtual char getID() const = 0;
    virtual std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const = 0;
    virtual TexturaPiezas::IDTextura getTipoTextura() const = 0;

    virtual void dibujar(float x, float y, float size, GLuint texturas[]) {
        TexturaPiezas tp;
        tp.dibujarPieza(texturas[getTipoTextura()], x, y, size);
    }
};




