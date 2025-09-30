#include "Juego.h"
using namespace std;

Juego::Juego() {}
Juego::Juego(const string &n1, const string &n2) : j1(n1), j2(n2), turno(n1) {}
Juego::Juego(const Jugador &p1, const Jugador &p2, const string &turn,
             const vector<string> &hist)
    : j1(p1), j2(p2), turno(turn), historial(hist) {}

void Juego::Iniciar() {
    cout << "=== ASTUCIA NAVAL ===\n";

    if (j1.barcos.empty()) j1.ColocarBarcos();
    if (j2.barcos.empty()) j2.ColocarBarcos();

    Jugador *turnoPtr = (turno == j1.nombre) ? &j1 : &j2;
    Jugador *enemigoPtr = (turnoPtr == &j1) ? &j2 : &j1;

    while (true) {
        cout << "\nTurno de " << turnoPtr->nombre << "\n";

        bool acierto;
        do {
            acierto = turnoPtr->Disparar(*enemigoPtr, historial);

            Partida::Guardar(j1, j2, turnoPtr->nombre, historial);

            if (enemigoPtr->HaPerdido()) {
                cout << "\nTABLERO FINAL - Estado del tablero de " << enemigoPtr->nombre << ":\n";
                enemigoPtr->propio.Mostrar(true);

                cout << "\nTABLERO FINAL - Estado del tablero de " << turnoPtr->nombre << ":\n";
                turnoPtr->propio.Mostrar(true);

                cout << "\nVICTORIA - " << turnoPtr->nombre << " ha ganado la partida!\n";

                cout << "\nPresione ENTER para salir...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                return;
            }

            if (acierto) {
                cout << "REPITE - " << turnoPtr->nombre << " acerto y repite disparo.\n";
            }

        } while (acierto);

        if (turnoPtr == &j1) {
            turnoPtr = &j2;
            enemigoPtr = &j1;
        } else {
            turnoPtr = &j1;
            enemigoPtr = &j2;
        }
        turno = turnoPtr->nombre;
    }
}

void Juego::MostrarHistorial(const vector<string> &h) {
    cout << "\n=== HISTORIAL DE PARTIDA ===\n";
    for (size_t i = 0; i < h.size(); ++i) {
        cout << "---- Jugada " << (i + 1) << " ----\n";
        cout << h[i] << "\n";
    }
}
