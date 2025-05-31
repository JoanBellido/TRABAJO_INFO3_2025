#include "TableroLogico.h"
#include <iostream>
#include <cctype> 
#include <cstdlib>
#include <ctime>
#include "Peon.h"
#include "Reina.h"
#include "Torre.h"
#include "Alfil.h"
#include "Caballo.h"
#include "Rey.h"

TableroLogico::TableroLogico() : turno(BLANCO) {
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

            Pieza* piezaOrigen = getPieza(origen);
            Pieza* piezaDestino = getPieza(destino);
            if (piezaDestino && piezaDestino->getID() == 'R') {
                return false;
            }

            cuadricula[destino.fila][destino.col] = piezaOrigen;
            cuadricula[origen.fila][origen.col] = nullptr;

            if (reyEnJaque(turno)) {
                cuadricula[origen.fila][origen.col] = piezaOrigen;
                cuadricula[destino.fila][destino.col] = piezaDestino;
                std::cout << "No puedes dejar tu rey en jaque.\n";
                return false;
            }

            delete piezaDestino;

            bool seraPromovido = dynamic_cast<Peon*>(piezaOrigen) && esCasillaFinalPromocionable(destino, piezaOrigen->getColor());
            if (auto peon = dynamic_cast<Peon*>(piezaOrigen); peon && !seraPromovido) {
                peon->desactivarPrimerMovimiento();
            }

            if (dynamic_cast<Peon*>(piezaOrigen) && seraPromovido) {
                char opcion;
                std::cout << "Promoción de peón. Elige pieza (Q: Reina, T: Torre, A: Alfil, C: Caballo): ";
                std::cin >> opcion;
                opcion = std::tolower(opcion);

                delete piezaOrigen;
                switch (opcion) {
                case 'q': piezaOrigen = new Reina(turno); break;
                case 't': piezaOrigen = new Torre(turno); break;
                case 'a': piezaOrigen = new Alfil(turno); break;
                case 'c': piezaOrigen = new Caballo(turno); break;
                default:  piezaOrigen = new Reina(turno); break;
                }

                cuadricula[destino.fila][destino.col] = piezaOrigen;
            }

            cambiarTurno();
            return true;
        }
    }

    return false;
}

void TableroLogico::cambiarTurno() {
    turno = (turno == BLANCO) ? NEGRO : BLANCO;
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
    if (color == BLANCO) {
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

    turno = BLANCO;

    asignar({ 0, 4 }, new Reina(BLANCO));
    asignar({ 0, 5 }, new Alfil(BLANCO));
    asignar({ 0, 6 }, new Rey(BLANCO));

    asignar({ 1, 3 }, new Torre(BLANCO));
    asignar({ 1, 4 }, new Caballo(BLANCO));
    asignar({ 1, 5 }, new Alfil(BLANCO));
    asignar({ 1, 6 }, new Caballo(BLANCO));
    asignar({ 1, 7 }, new Torre(BLANCO));

    for (int j = 2; j <= 8; ++j)
        asignar({ 2, j }, new Peon(BLANCO));

    for (int j = 2; j <= 8; ++j)
        asignar({ 7, j }, new Peon(NEGRO));

    asignar({ 8, 3 }, new Torre(NEGRO));
    asignar({ 8, 4 }, new Caballo(NEGRO));
    asignar({ 8, 5 }, new Alfil(NEGRO));
    asignar({ 8, 6 }, new Caballo(NEGRO));
    asignar({ 8, 7 }, new Torre(NEGRO));

    asignar({ 9, 4 }, new Reina(NEGRO));
    asignar({ 9, 5 }, new Alfil(NEGRO));
    asignar({ 9, 6 }, new Rey(NEGRO));
}

void TableroLogico::imprimir() const {
    for (int i = 0; i < filas(); ++i) {
        std::cout << "Fila " << i << ": ";
        for (int j = 0; j < columnas(i); ++j) {
            if (coordenadaValida({ i, j })) {
                Pieza* p = cuadricula[i][j];
                if (p)
                    std::cout << (p->getColor() == BLANCO ? 'B' : 'N') << p->getID() << " ";
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

bool TableroLogico::reyEnJaque(Color colorRey) const {
    Coordenada posRey = { -1, -1 };

    for (int i = 0; i < filas(); ++i) {
        for (int j = 0; j < columnas(i); ++j) {
            Coordenada c = { i, j };
            if (!coordenadaValida(c)) continue;

            Pieza* p = getPieza(c);
            if (p && p->getColor() == colorRey && p->getID() == 'R') {
                posRey = c;
                break;
            }
        }
    }

    if (posRey.fila == -1) return false;

    for (int i = 0; i < filas(); ++i) {
        for (int j = 0; j < columnas(i); ++j) {
            Coordenada c = { i, j };
            if (!coordenadaValida(c)) continue;

            Pieza* p = getPieza(c);
            if (p && p->getColor() != colorRey) {
                auto movs = p->movimientos_validos(c, *this);
                for (const auto& m : movs) {
                    if (m.fila == posRey.fila && m.col == posRey.col)
                        return true;
                }
            }
        }
    }

    return false;
}

bool TableroLogico::esJaqueMate(Color color) {
    if (!reyEnJaque(color))
        return false;

    for (int i = 0; i < filas(); ++i) {
        for (int j = 0; j < columnas(i); ++j) {
            Coordenada origen = { i, j };
            Pieza* p = getPieza(origen);
            if (p && p->getColor() == color) {
                auto posibles = p->movimientos_validos(origen, *this);
                for (const Coordenada& destino : posibles) {
                    Pieza* capturada = getPieza(destino);
                    cuadricula[destino.fila][destino.col] = p;
                    cuadricula[origen.fila][origen.col] = nullptr;

                    bool sigueEnJaque = reyEnJaque(color);

                    cuadricula[origen.fila][origen.col] = p;
                    cuadricula[destino.fila][destino.col] = capturada;

                    if (!sigueEnJaque)
                        return false;
                }
            }
        }
    }

    return true;
}


bool TableroLogico::movimientoIA() {
    struct Movimiento {
        Coordenada origen;
        Coordenada destino;
        int valorCaptura;
    };

    std::vector<Movimiento> posibles;

    for (int i = 0; i < filas(); ++i) {
        for (int j = 0; j < columnas(i); ++j) {
            Coordenada origen{ i, j };
            Pieza* p = getPieza(origen);
            if (p && p->getColor() == turno) {
                auto destinos = p->movimientos_validos(origen, *this);
                for (const auto& destino : destinos) {
                    Pieza* piezaOrigen = cuadricula[origen.fila][origen.col];
                    Pieza* piezaDestino = cuadricula[destino.fila][destino.col];

                    cuadricula[destino.fila][destino.col] = piezaOrigen;
                    cuadricula[origen.fila][origen.col] = nullptr;

                    bool enJaque = reyEnJaque(turno);

                    cuadricula[origen.fila][origen.col] = piezaOrigen;
                    cuadricula[destino.fila][destino.col] = piezaDestino;

                    if (enJaque) continue;

                    int valor = 0;
                    if (piezaDestino) {
                        if (piezaDestino->getColor() == turno) {
                            valor = -1000;
                        }
                        else {
                            switch (piezaDestino->getID()) {
                            case 'P': valor = 1; break;
                            case 'C': case 'A': valor = 3; break;
                            case 'T': valor = 5; break;
                            case 'Q': valor = 9; break;
                            case 'R': valor = 100; break;
                            default: valor = 0; break;
                            }
                        }
                    }


                    posibles.push_back({ origen, destino, valor });
                }
            }
        }
    }

    if (posibles.empty()) return false;

    int mejorValor = -1;
    std::vector<Movimiento> mejores;

    for (const auto& m : posibles) {
        if (m.valorCaptura > mejorValor) {
            mejorValor = m.valorCaptura;
            mejores.clear();
            mejores.push_back(m);
        }
        else if (m.valorCaptura == mejorValor) {
            mejores.push_back(m);
        }
    }

    srand(static_cast<unsigned int>(time(nullptr)));
    Movimiento elegido = mejores[rand() % mejores.size()];

    return mover(elegido.origen, elegido.destino);
}

bool TableroLogico::esTabla() const {
    int cantidadPiezas = 0;
    int cantidadReyes = 0;

    for (int i = 0; i < filas(); ++i) {
        for (int j = 0; j < columnas(i); ++j) {
            Coordenada c = { i, j };
            if (!coordenadaValida(c)) continue;

            Pieza* p = getPieza(c);
            if (p) {
                cantidadPiezas++;
                if (p->getID() == 'R') cantidadReyes++;
            }
        }
    }

    return cantidadPiezas == 2 && cantidadReyes == 2;
}





