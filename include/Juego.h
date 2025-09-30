#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <vector>
#include <string>
#include "Jugador.h"
#include "Partida.h"

class Juego {
public:
    Jugador j1, j2;
    std::string turno;
    std::vector<std::string> historial;

    Juego();
    Juego(const std::string &n1, const std::string &n2);
    Juego(const Jugador &p1, const Jugador &p2, const std::string &turn,
          const std::vector<std::string> &hist);

    void Iniciar();
    static void MostrarHistorial(const std::vector<std::string> &h);
};

#endif
