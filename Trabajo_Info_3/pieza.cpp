#include "pieza.h"
#include "TableroLogico.h"

bool valida_y_añade(std::vector<Coordenada>& lista, const Coordenada& c, const TableroLogico& t, Color propio) {
    if (!t.coordenadaValida(c)) return false;
    Pieza* destino = t.getPieza(c);
    if (!destino || destino->getColor() != propio) {
        lista.push_back(c);
        return destino == nullptr; // true si la casilla está vacía
    }
    return false;
}

std::vector<Coordenada> Peon::movimientos_validos(const Coordenada& o, const TableroLogico& t) const {
    std::vector<Coordenada> movs;
    
    int dir = (color == Color::BLANCO) ? 1 : -1;

    // Movimiento de 1 casilla hacia adelante
    Coordenada adelante = { o.fila + dir, o.col };
    if (t.coordenadaValida(adelante) && t.getPieza(adelante) == nullptr) {
        movs.push_back(adelante);

    }
    // Movimiento de 2 casillas desde la fila inicial
    Coordenada dobleAdelante = { o.fila + 2 * dir, o.col };
    if (t.coordenadaValida(adelante) && t.getPieza(dobleAdelante) == nullptr) {
        movs.push_back(dobleAdelante);
    }
   
    // Capturas diagonales
    for (int dx : {-1, 1}) {
        Coordenada diag = { o.fila + dir, o.col + dx };
        if (t.coordenadaValida(diag)) {
            Pieza* objetivo = t.getPieza(diag);
            if (objetivo && objetivo->getColor() != color) {
                movs.push_back(diag);
            }
        }
    }

    return movs;
}

std::vector<Coordenada> Torre::movimientos_validos(const Coordenada& o, const TableroLogico& t) const {
    std::vector<Coordenada> movs;
    std::vector<Coordenada> dirs = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    for (auto& d : dirs) {
        for (int i = 1;; ++i) {
            Coordenada c = { o.fila + i * d.fila, o.col + i * d.col };
            if (!valida_y_añade(movs, c, t, color)) break;
        }
    }
    return movs;
}

std::vector<Coordenada> Alfil::movimientos_validos(const Coordenada& o, const TableroLogico& t) const {
    std::vector<Coordenada> movs;
    std::vector<Coordenada> dirs = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
    for (auto& d : dirs) {
        for (int i = 1;; ++i) {
            Coordenada c = { o.fila + i * d.fila, o.col + i * d.col };
            if (!valida_y_añade(movs, c, t, color)) break;
        }
    }
    return movs;
}

std::vector<Coordenada> Reina::movimientos_validos(const Coordenada& o, const TableroLogico& t) const {
    std::vector<Coordenada> movs;
    std::vector<Coordenada> dirs = {
        {1,0},{-1,0},{0,1},{0,-1},
        {1,1},{1,-1},{-1,1},{-1,-1}
    };
    for (auto& d : dirs) {
        for (int i = 1;; ++i) {
            Coordenada c = { o.fila + i * d.fila, o.col + i * d.col };
            if (!valida_y_añade(movs, c, t, color)) break;
        }
    }
    return movs;
}

std::vector<Coordenada> Rey::movimientos_validos(const Coordenada& o, const TableroLogico& t) const {
    std::vector<Coordenada> movs;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            Coordenada c = { o.fila + dr, o.col + dc };
            valida_y_añade(movs, c, t, color);
        }
    }
    return movs;
}

std::vector<Coordenada> Caballo::movimientos_validos(const Coordenada& o, const TableroLogico& t) const {
    std::vector<Coordenada> movs;
    std::vector<Coordenada> offs = {
        {2,1},{2,-1},{-2,1},{-2,-1},
        {1,2},{1,-2},{-1,2},{-1,-2}
    };
    for (auto& d : offs) {
        Coordenada c = { o.fila + d.fila, o.col + d.col };
        valida_y_añade(movs, c, t, color);
    }
    return movs;
}


