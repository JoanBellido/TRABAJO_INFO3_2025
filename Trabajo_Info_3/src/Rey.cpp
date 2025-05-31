#include "Rey.h"
#include "TableroLogico.h"

std::vector<Coordenada> Rey::movimientos_validos(const Coordenada& origen, const TableroLogico& t) const {
    std::vector<Coordenada> movs;

    for (int df = -1; df <= 1; ++df) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (df == 0 && dc == 0) continue;

            Coordenada destino{ origen.fila + df, origen.col + dc };
            if (t.coordenadaValida(destino)) {
                movs.push_back(destino);
            }
        }
    }

    return movs;
}

