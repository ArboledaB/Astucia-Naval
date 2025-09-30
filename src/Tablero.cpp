#include "Tablero.h"
using namespace std;

int Tablero::GetTAM() { return TAM; }

bool Tablero::PuedeColocar(int x, int y) const {
    return x >= 0 && x < TAM && y >= 0 && y < TAM && !celdas[y][x].EstaOcupado();
}

bool Tablero::ColocarBarco(int x, int y, bool horizontal, int idBarco, int tam) {
    if (horizontal) {
        if (x + tam > TAM) return false;
        for (int i = 0; i < tam; ++i)
            if (!PuedeColocar(x + i, y)) return false;
        for (int i = 0; i < tam; ++i) celdas[y][x + i].ColocarBarco(idBarco);
    } else {
        if (y + tam > TAM) return false;
        for (int i = 0; i < tam; ++i)
            if (!PuedeColocar(x, y + i)) return false;
        for (int i = 0; i < tam; ++i) celdas[y + i][x].ColocarBarco(idBarco);
    }
    return true;
}

bool Tablero::Disparar(int x, int y, int &idImpactado, bool &yaDisparado) {
    if (x < 0 || x >= TAM || y < 0 || y >= TAM) return false;
    if (celdas[y][x].FueDisparado()) {
        yaDisparado = true;
        return false;
    }
    celdas[y][x].Disparar();
    if (celdas[y][x].EstaOcupado()) {
        idImpactado = celdas[y][x].GetBarcoID();
        return true;
    }
    return false;
}

void Tablero::MarcarBarcoHundido(int idBarco) {
    for (int y = 0; y < TAM; ++y)
        for (int x = 0; x < TAM; ++x)
            if (celdas[y][x].GetBarcoID() == idBarco)
                celdas[y][x].MarcarHundido();
}

void Tablero::SetBarcoID(int x, int y, int id) { celdas[y][x].SetBarcoID(id); }

void Tablero::Mostrar(bool propio) const { cout << ToString(propio); }
void Tablero::MostrarGuia() const { cout << ToStringGuia(); }

string Tablero::ToString(bool propio) const {
    ostringstream ss;
    ss << "    ";
    for (int i = 0; i < TAM; ++i) ss << setw(2) << i << " ";
    ss << "\n   +" << string(TAM * 3, '-') << "+\n";
    for (int y = 0; y < TAM; ++y) {
        ss << setw(2) << y << " |";
        for (int x = 0; x < TAM; ++x) {
            ss << celdas[y][x].ToString(propio) << "|";
        }
        ss << "\n   +" << string(TAM * 3, '-') << "+\n";
    }
    return ss.str();
}

string Tablero::ToStringGuia() const {
    ostringstream ss;
    ss << "    ";
    for (int i = 0; i < TAM; ++i) ss << setw(2) << i << " ";
    ss << "\n   +" << string(TAM * 3, '-') << "+\n";
    for (int y = 0; y < TAM; ++y) {
        ss << setw(2) << y << " |";
        for (int x = 0; x < TAM; ++x) {
            ss << celdas[y][x].ToStringGuia() << "|";
        }
        ss << "\n   +" << string(TAM * 3, '-') << "+\n";
    }
    return ss.str();
}

void Tablero::Serializar(ofstream &out) const {
    for (int y = 0; y < TAM; ++y)
        for (int x = 0; x < TAM; ++x)
            celdas[y][x].Serializar(out);
}

void Tablero::Deserializar(ifstream &in) {
    for (int y = 0; y < TAM; ++y)
        for (int x = 0; x < TAM; ++x)
            celdas[y][x].Deserializar(in);
}
