#include "TableroLogico.h"
#include <iostream>

TableroLogico::TableroLogico() : turno(Color::BLANCO) {
    for (int i = 0; i < 10; ++i)
        cuadricula.push_back(std::vector<Pieza*>(11, nullptr));
}

TableroLogico::~TableroLogico() {
    for (auto& fila : cuadricula)
        for (auto pieza : fila)
            delete pieza;
}

void TableroLogico::asignar(const Coordenada& pos, Pieza* pieza) {
    if (coordenadaValida(pos)) {
        delete cuadricula[pos.fila][pos.col];
        cuadricula[pos.fila][pos.col] = pieza;
    }
}

Pieza* TableroLogico::getPieza(const Coordenada& pos) const {
    if (coordenadaValida(pos))
        return cuadricula[pos.fila][pos.col];
    return nullptr;
}

bool TableroLogico::mover(const Coordenada& origen, const Coordenada& destino) {
    if (!coordenadaValida(origen) || !coordenadaValida(destino))
        return false;
    
    Pieza* p = getPieza(origen);
    if (!p || p->getColor() != turno)
        return false;

    auto movimientos = p->movimientos_validos(origen, *this);

    for (const auto& m : movimientos) {
        if (m.fila == destino.fila && m.col == destino.col) {
            delete cuadricula[destino.fila][destino.col];
            cuadricula[destino.fila][destino.col] = p;
            cuadricula[origen.fila][origen.col] = nullptr;
            cambiarTurno();
            return true;
        }
    }

    return false;
}

void TableroLogico::cambiarTurno() {
    turno = (turno == Color::BLANCO) ? Color::NEGRO : Color::BLANCO;
}

int TableroLogico::filas() const {
    return static_cast<int>(cuadricula.size());
}

int TableroLogico::columnas(int fila) const {
    return static_cast<int>(cuadricula[fila].size());
}

bool TableroLogico::coordenadaValida(const Coordenada& c) const {
    static int activos[] = { 3,5,7,9,11,11,9,7,5,3 };
    int min = (11 - activos[c.fila]) / 2;
    int max = min + activos[c.fila];
    return c.fila >= 0 && c.fila < 10 && c.col >= min && c.col < max;
}

void TableroLogico::inicializar() {
    for (auto& fila : cuadricula)
        for (auto& casilla : fila)
            delete casilla, casilla = nullptr;

    turno = Color::BLANCO;

    // Blancas
    asignar({ 0, 4 }, new Reina(Color::BLANCO));
    asignar({ 0, 5 }, new Alfil(Color::BLANCO));
    asignar({ 0, 6 }, new Rey(Color::BLANCO));

    asignar({ 1, 3 }, new Torre(Color::BLANCO));
    asignar({ 1, 4 }, new Caballo(Color::BLANCO));
    asignar({ 1, 5 }, new Alfil(Color::BLANCO));
    asignar({ 1, 6 }, new Caballo(Color::BLANCO));
    asignar({ 1, 7 }, new Torre(Color::BLANCO));

    for (int j = 2; j <= 8; ++j)
        asignar({ 2, j }, new Peon(Color::BLANCO));

    // Negras
    for (int j = 2; j <= 8; ++j)
        asignar({ 7, j }, new Peon(Color::NEGRO));

    asignar({ 8, 3 }, new Torre(Color::NEGRO));
    asignar({ 8, 4 }, new Caballo(Color::NEGRO));
    asignar({ 8, 5 }, new Alfil(Color::NEGRO));
    asignar({ 8, 6 }, new Caballo(Color::NEGRO));
    asignar({ 8, 7 }, new Torre(Color::NEGRO));

    asignar({ 9, 4 }, new Reina(Color::NEGRO));
    asignar({ 9, 5 }, new Alfil(Color::NEGRO));
    asignar({ 9, 6 }, new Rey(Color::NEGRO));

    imprimir();
}

void TableroLogico::imprimir() const {
    for (int i = 0; i < filas(); ++i) {
        std::cout << "Fila " << i << ": ";
        for (int j = 0; j < columnas(i); ++j) {
            if (coordenadaValida({ i, j })) {
                Pieza* p = cuadricula[i][j];
                if (p)
                    std::cout << (p->getColor() == Color::BLANCO ? 'B' : 'N') << p->getID() << " ";
                else
                    std::cout << "-- ";
            }
            else {
                std::cout << "   ";
            }
        }
        std::cout << std::endl;
    }
}



