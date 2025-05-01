#include "TableroLogico.h"
#include <iostream>
#include <cctype> // para std::tolower

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

            // --- Desactivar doble paso si es peón no promovido ---
            bool seraPromovido = dynamic_cast<Peon*>(p) && esCasillaFinalPromocionable(destino, p->getColor());
            if (auto peon = dynamic_cast<Peon*>(p); peon && !seraPromovido) {
                peon->desactivarPrimerMovimiento();
            }

            delete cuadricula[destino.fila][destino.col];
            cuadricula[destino.fila][destino.col] = p;
            cuadricula[origen.fila][origen.col] = nullptr;

            // --- PROMOCIÓN DE PEÓN ---
            if (dynamic_cast<Peon*>(p) && seraPromovido) {
                char opcion;
                std::cout << "Promoción de peón. Elige pieza (Q: Reina, T: Torre, A: Alfil, C: Caballo): ";
                std::cin >> opcion;
                opcion = std::tolower(opcion);

                delete p;
                switch (opcion) {
                case 'q': p = new Reina(turno); break;
                case 't': p = new Torre(turno); break;
                case 'a': p = new Alfil(turno); break;
                case 'c': p = new Caballo(turno); break;
                default:  p = new Reina(turno); break;
                }

                cuadricula[destino.fila][destino.col] = p;
            }

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
    if (c.fila < 0 || c.fila >= 10 || c.col < 0 || c.col >= 11) return false;
    int min = (11 - activos[c.fila]) / 2;
    int max = min + activos[c.fila];
    return c.col >= min && c.col < max;
}

bool TableroLogico::esCasillaFinalPromocionable(const Coordenada& c, Color color) const {
    if (!coordenadaValida(c)) return false;
    if (color == Color::BLANCO) {
        return (c.fila == 9) || (c.fila == 8 && (c.col == 3 || c.col == 7));
    }
    else {
        return (c.fila == 0) || (c.fila == 1 && (c.col == 3 || c.col == 7));
    }
}

void TableroLogico::inicializar() {
    for (auto& fila : cuadricula)
        for (auto& casilla : fila)
            delete casilla, casilla = nullptr;

    turno = Color::BLANCO;

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






