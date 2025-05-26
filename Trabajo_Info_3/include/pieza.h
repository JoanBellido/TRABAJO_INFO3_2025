#pragma once
#include <vector>

enum Color { BLANCO, NEGRO };

struct Coordenada {
    int fila;
    int col;
};

class TableroLogico;

class Pieza {
protected:
    Color color;

public:
    Pieza(Color c) : color(c) {}
    virtual ~Pieza() = default;

    Color getColor() const { return color; }
    virtual char getID() const = 0;
    virtual std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const = 0;
};




