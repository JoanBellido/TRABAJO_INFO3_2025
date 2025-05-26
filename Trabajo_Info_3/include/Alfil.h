#pragma once
#include "Pieza.h"

class Alfil : public Pieza {
public:
    Alfil(Color c) : Pieza(c) {}

    char getID() const override { return 'A'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;

    TexturaPiezas::IDTextura getTipoTextura() const override {
        return esPiezaBlanca() ? TexturaPiezas::B_ALFIL : TexturaPiezas::N_ALFIL;
    }
};
