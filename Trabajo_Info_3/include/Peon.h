#pragma once
#include "pieza.h"

class Peon : public Pieza {
private:
    bool primerMovimiento = true;

public:
    Peon(Color c) : Pieza(c) {}

    char getID() const override { return 'P'; }

    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;

    void desactivarPrimerMovimiento() { primerMovimiento = false; }
    bool puedeDoblePaso() const { return primerMovimiento; }

    TexturaPiezas::IDTextura getTipoTextura() const override {
        return esPiezaBlanca() ? TexturaPiezas::B_PEON : TexturaPiezas::N_PEON;
    }
};
