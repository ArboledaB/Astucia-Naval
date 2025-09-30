#include <iostream>
#include <fstream>
#include <limits>
#include "Juego.h"
#include "Partida.h"

using namespace std;

int main() {
    ifstream test("partida.dat", ios::binary);
    if (test) {
        char op;
        cout << "Se encontro una partida guardada. Desea cargarla? (S/N): ";
        cin >> op;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (op == 'S' || op == 's') {
            Jugador j1, j2;
            string turno;
            vector<string> historial;
            bool cargada = Partida::Cargar(j1, j2, turno, historial);
            if (!cargada) {
                cout << "ERROR - No se pudo cargar la partida.\n";
            } else {
                cout << "Partida cargada con exito.\n";

                char h;
                cout << "Desea ver el historial de jugadas anteriores? (S/N): ";
                cin >> h;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (h == 'S' || h == 's') {
                    Juego::MostrarHistorial(historial);
                }

                char r;
                cout << "Desea reanudar la partida cargada? (S/N): ";
                cin >> r;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (r == 'S' || r == 's') {
                    Juego juegoCargado(j1, j2, turno, historial);
                    juegoCargado.Iniciar();
                    return 0;
                } else {
                    cout << "La partida ha sido mostrada. Saliendo.\n";
                    return 0;
                }
            }
        }
    }

    string n1, n2;
    cout << "Nombre del Jugador 1: ";
    getline(cin, n1);
    if (n1.empty()) {
        cout << "Nombre del Jugador 1 (no vacio): ";
        getline(cin, n1);
    }
    cout << "Nombre del Jugador 2: ";
    getline(cin, n2);
    if (n2.empty()) {
        cout << "Nombre del Jugador 2 (no vacio): ";
        getline(cin, n2);
    }

    Juego juego(n1, n2);
    juego.Iniciar();

    return 0;
}
