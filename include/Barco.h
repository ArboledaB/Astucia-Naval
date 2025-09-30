#ifndef BARCO_H
#define BARCO_H

#include <fstream>

class Barco {
public:
    int id;
    int tam;
    int impactos;

    Barco(int i = 0, int t = 4);

    void Impactar();
    bool Hundido() const;

    void Serializar(std::ofstream &out) const;
    void Deserializar(std::ifstream &in);
};

#endif
