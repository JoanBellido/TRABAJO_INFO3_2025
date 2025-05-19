#pragma once
#include "Pieza.h"

class Peon : public Pieza {
private:
    bool primerMovimiento = true;

public:
    using Pieza::Pieza;

    char getID() const override { return 'P'; }
    std::vector<Coordenada> movimientos_validos(const Coordenada& origen, const TableroLogico& t) const override;

    void desactivarPrimerMovimiento() { primerMovimiento = false; }
    bool puedeDoblePaso() const { return primerMovimiento; }
};

