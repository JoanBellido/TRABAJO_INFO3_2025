#include "Caballo.h"
#include "TableroLogico.h"

std::vector<Coordenada> Caballo::movimientos_validos(const Coordenada& origen, const TableroLogico& t) const {
    std::vector<Coordenada> movs;
    int dfilas[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
    int dcols[] = { 1,  2, 2, 1, -1, -2, -2, -1 };

    for (int i = 0; i < 8; ++i) {
        Coordenada destino{ origen.fila + dfilas[i], origen.col + dcols[i] };
        if (t.coordenadaValida(destino)) {
            Pieza* p = t.getPieza(destino);
            if (!p || p->getColor() != color)
                movs.push_back(destino);
        }
    }

    return movs;
}
