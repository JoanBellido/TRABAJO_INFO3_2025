#include "TableroLogico.h"
#include <iostream>

TableroLogico::TableroLogico() : turno(Color::BLANCO) {
    int tamanios[] = { 3, 5, 7, 9, 11, 11, 9, 7, 5, 3 };
    for (int i = 0; i < 10; ++i)
        cuadricula.push_back(std::vector<Pieza*>(tamanios[i], nullptr));
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

    std::cout << "Movimientos válidos: ";
    for (auto& m : movimientos)
        std::cout << "[" << m.fila << "," << m.col << "] ";
    std::cout << "\n";

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
    return c.fila >= 0 && c.fila < filas() &&
        c.col >= 0 && c.col < columnas(c.fila);
}

void TableroLogico::inicializar() {
    for (auto& fila : cuadricula)
        for (auto& casilla : fila)
            delete casilla, casilla = nullptr;

    turno = Color::BLANCO;

    // --- BLANCAS ---
    asignar({ 0, 0 }, new Reina(Color::BLANCO));
    asignar({ 0, 1 }, new Alfil(Color::BLANCO));
    asignar({ 0, 2 }, new Rey(Color::BLANCO));

    asignar({ 1, 0 }, new Torre(Color::BLANCO));
    asignar({ 1, 1 }, new Caballo(Color::BLANCO));
    asignar({ 1, 2 }, new Alfil(Color::BLANCO));
    asignar({ 1, 3 }, new Caballo(Color::BLANCO));
    asignar({ 1, 4 }, new Torre(Color::BLANCO));

    for (int j = 0; j < static_cast<int>(cuadricula[2].size()); ++j)
        asignar({ 2, j }, new Peon(Color::BLANCO));

    // --- NEGRAS ---
    for (int j = 0; j < static_cast<int>(cuadricula[7].size()); ++j)
        asignar({ 7, j }, new Peon(Color::NEGRO));

    asignar({ 8, 0 }, new Torre(Color::NEGRO));
    asignar({ 8, 1 }, new Caballo(Color::NEGRO));
    asignar({ 8, 2 }, new Alfil(Color::NEGRO));
    asignar({ 8, 3 }, new Caballo(Color::NEGRO));
    asignar({ 8, 4 }, new Torre(Color::NEGRO));

    asignar({ 9, 0 }, new Reina(Color::NEGRO));
    asignar({ 9, 1 }, new Alfil(Color::NEGRO));
    asignar({ 9, 2 }, new Rey(Color::NEGRO));

    imprimir(); // ✅ Mostrar el tablero al arrancar
}

void TableroLogico::imprimir() const {
    std::cout << "\nTABLERO:\n";
    for (int i = 0; i < filas(); ++i) {
        std::cout << "Fila " << i << ": ";
        for (int j = 0; j < columnas(i); ++j) {
            Pieza* p = cuadricula[i][j];
            if (p)
                std::cout << (p->getColor() == Color::BLANCO ? 'B' : 'N') << p->getID() << ' ';
            else
                std::cout << "-- ";
        }
        std::cout << '\n';
    }
}



