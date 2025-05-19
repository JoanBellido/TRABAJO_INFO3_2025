#pragma once
#include "Pieza.h"

class Reina : public Pieza {
public:
    using Pieza::Pieza;

    char getID() const override { return 'Q'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;
};
