#include "Alfil.h"
#include "TableroLogico.h"

std::vector<Coordenada> Alfil::movimientos_validos(const Coordenada& origen, const TableroLogico& t) const {
    std::vector<Coordenada> movs;
    static const int dirs[4][2] = {
        {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
    };

    for (const auto& dir : dirs) {
        int f = origen.fila + dir[0];
        int c = origen.col + dir[1];

        while (t.coordenadaValida({ f, c })) {
            Pieza* p = t.getPieza({ f, c });
            if (p) {
                if (p->getColor() != color)
                    movs.push_back({ f, c });
                break;
            }
            movs.push_back({ f, c });
            f += dir[0];
            c += dir[1];
        }
    }

    return movs;
}
