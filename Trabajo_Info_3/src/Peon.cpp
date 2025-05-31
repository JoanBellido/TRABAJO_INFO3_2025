#include "Peon.h"
#include "TableroLogico.h"

std::vector<Coordenada> Peon::movimientos_validos(const Coordenada& origen, const TableroLogico& t) const {
    std::vector<Coordenada> movs;
    int dir = (color == BLANCO) ? 1 : -1;

    Coordenada adelante = { origen.fila + dir, origen.col };
    if (t.coordenadaValida(adelante) && t.getPieza(adelante) == nullptr)
        movs.push_back(adelante);

    if (primerMovimiento) {
        Coordenada doblePaso = { origen.fila + 2 * dir, origen.col };
        if (t.coordenadaValida(doblePaso) && t.getPieza(doblePaso) == nullptr && t.getPieza(adelante) == nullptr)
            movs.push_back(doblePaso);
    }

    for (int d = -1; d <= 1; d += 2) {
        Coordenada diag = { origen.fila + dir, origen.col + d };
        if (t.coordenadaValida(diag)) {
            Pieza* p = t.getPieza(diag);
            if (p)
                movs.push_back(diag);
        }
    }

    return movs;
}

