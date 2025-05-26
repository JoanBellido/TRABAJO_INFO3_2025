#pragma once
#include "pieza.h"

class Rey : public Pieza {
public:
    Rey(Color c) : Pieza(c) {}

    char getID() const override { return 'R'; }

    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;

    TexturaPiezas::IDTextura getTipoTextura() const override {
        return esPiezaBlanca() ? TexturaPiezas::B_REY : TexturaPiezas::N_REY;
    }
};
