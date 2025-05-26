#pragma once
#include "pieza.h"

class Caballo : public Pieza {
public:
    Caballo(Color c) : Pieza(c) {}

    char getID() const override { return 'C'; }

    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;

    TexturaPiezas::IDTextura getTipoTextura() const override {
        return esPiezaBlanca() ? TexturaPiezas::B_CABALLO : TexturaPiezas::N_CABALLO;
    }
};

