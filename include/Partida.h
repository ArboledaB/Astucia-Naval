#ifndef PARTIDA_H
#define PARTIDA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Jugador.h"

class Partida {
public:
    static void Guardar(const Jugador &j1, const Jugador &j2, const std::string &turno,
                        const std::vector<std::string> &historial);

    static bool Cargar(Jugador &j1, Jugador &j2, std::string &turno,
                       std::vector<std::string> &historial);
};

#endif
