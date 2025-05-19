#pragma once
#include "Pieza.h"

class Alfil : public Pieza {
public:
    using Pieza::Pieza;

    char getID() const override { return 'A'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;
};
