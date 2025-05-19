#pragma once
#include "Pieza.h"

class Caballo : public Pieza {
public:
    using Pieza::Pieza;

    char getID() const override { return 'C'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;
};
