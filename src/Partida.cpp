#include "Partida.h"
using namespace std;

void Partida::Guardar(const Jugador &j1, const Jugador &j2, const string &turno,
                      const vector<string> &historial) {
    ofstream out("partida.dat", ios::binary);
    if (!out) {
        cerr << "ERROR - No se pudo abrir archivo para guardar.\n";
        return;
    }
    j1.Serializar(out);
    j2.Serializar(out);
    size_t len = turno.size();
    out.write((char*)&len, sizeof(len));
    out.write(turno.c_str(), len);
    size_t h = historial.size();
    out.write((char*)&h, sizeof(h));
    for (const string &s : historial) {
        size_t l = s.size();
        out.write((char*)&l, sizeof(l));
        out.write(s.c_str(), l);
    }
}

bool Partida::Cargar(Jugador &j1, Jugador &j2, string &turno, vector<string> &historial) {
    ifstream in("partida.dat", ios::binary);
    if (!in) return false;
    j1.Deserializar(in);
    j2.Deserializar(in);
    size_t len;
    in.read((char*)&len, sizeof(len));
    turno.resize(len);
    in.read(&turno[0], len);
    size_t h;
    in.read((char*)&h, sizeof(h));
    historial.resize(h);
    for (size_t i = 0; i < h; ++i) {
        size_t l;
        in.read((char*)&l, sizeof(l));
        historial[i].resize(l);
        in.read(&historial[i][0], l);
    }
    return true;
}
