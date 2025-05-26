#pragma once
#include "pieza.h"

class Reina : public Pieza {
public:
    Reina(Color c) : Pieza(c) {}

    char getID() const override { return 'Q'; }

    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;

    TexturaPiezas::IDTextura getTipoTextura() const override {
        return esPiezaBlanca() ? TexturaPiezas::B_REINA : TexturaPiezas::N_REINA;
    }
};

