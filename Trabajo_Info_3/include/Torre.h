#pragma once
#include "pieza.h"

class Torre : public Pieza {
public:
    Torre(Color c) : Pieza(c) {}

    char getID() const override { return 'T'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;

    TexturaPiezas::IDTextura getTipoTextura() const override {
        return esPiezaBlanca() ? TexturaPiezas::B_TORRE : TexturaPiezas::N_TORRE;
    }
};

