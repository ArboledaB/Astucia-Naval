#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include "Tablero.h"
#include "Barco.h"

class Jugador {
public:
    std::string nombre;
    Tablero propio;
    Tablero oponente;
    std::vector<Barco> barcos;

    Jugador(std::string n = "");

    int LeerCoordenada(const std::string &msg);
    void ColocarBarcos();

    int BarcosRestantes() const;
    bool Disparar(Jugador &enemigo, std::vector<std::string> &historial);
    bool HaPerdido() const;

    void Serializar(std::ofstream &out) const;
    void Deserializar(std::ifstream &in);
};

#endif
