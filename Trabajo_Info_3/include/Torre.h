#pragma once
#include "Pieza.h"

class Torre : public Pieza {
public:
    using Pieza::Pieza;

    char getID() const override { return 'T'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;
};

