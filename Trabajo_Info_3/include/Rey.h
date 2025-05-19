#pragma once
#include "Pieza.h"

class Rey : public Pieza {
public:
    using Pieza::Pieza;

    char getID() const override { return 'R'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;
};
