#pragma once
#include <vector>

enum class Color { BLANCO, NEGRO };

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

class Peon : public Pieza {

public:
    using Pieza::Pieza;
    char getID() const override { return 'P'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada&, const TableroLogico&) const override;
};

class Torre : public Pieza {
public:
    using Pieza::Pieza;
    char getID() const override { return 'T'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada&, const TableroLogico&) const override;
};

class Reina : public Pieza {
public:
    using Pieza::Pieza;
    char getID() const override { return 'Q'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada&, const TableroLogico&) const override;
};

class Rey : public Pieza {
public:
    using Pieza::Pieza;
    char getID() const override { return 'R'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada&, const TableroLogico&) const override;
};

class Alfil : public Pieza {
public:
    using Pieza::Pieza;
    char getID() const override { return 'A'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada&, const TableroLogico&) const override;
};

class Caballo : public Pieza {
public:
    using Pieza::Pieza;
    char getID() const override { return 'C'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada&, const TableroLogico&) const override;
};


