#include "Barco.h"
using namespace std;

Barco::Barco(int i, int t) : id(i), tam(t), impactos(0) {}

void Barco::Impactar() { impactos++; }
bool Barco::Hundido() const { return impactos >= tam; }

void Barco::Serializar(ofstream &out) const {
    out.write((char*)&id, sizeof(id));
    out.write((char*)&tam, sizeof(tam));
    out.write((char*)&impactos, sizeof(impactos));
}

void Barco::Deserializar(ifstream &in) {
    in.read((char*)&id, sizeof(id));
    in.read((char*)&tam, sizeof(tam));
    in.read((char*)&impactos, sizeof(impactos));
}
