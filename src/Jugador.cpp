#include "Jugador.h"
using namespace std;

Jugador::Jugador(string n) : nombre(n) {}

int Jugador::LeerCoordenada(const string &msg) {
    int valor;
    while (true) {
        cout << msg;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR - Debe ingresar un numero.\n";
            continue;
        }
        if (valor < 0 || valor >= Tablero::GetTAM()) {
            cout << "ERROR - Valor fuera de rango. Ingrese un numero entre 0 y 19.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return valor;
    }
}

void Jugador::ColocarBarcos() {
    cout << "\n>>> Turno de " << nombre << " para colocar sus barcos.\n";
    for (int b = 0; b < 3; ++b) {
        cout << "\nBarco #" << (b + 1) << " de " << nombre << ":\n";
        while (true) {
            int x = LeerCoordenada("  x (0-19): ");
            int y = LeerCoordenada("  y (0-19): ");
            char orient;
            do {
                cout << "Orientacion (H=Horizontal, V=Vertical): ";
                cin >> orient;
                if (!(orient == 'H' || orient == 'h' || orient == 'V' || orient == 'v')) {
                    cout << "ERROR - Opcion no valida. Solo se acepta H o V.\n";
                }
            } while (!(orient == 'H' || orient == 'h' || orient == 'V' || orient == 'v'));

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            bool horizontal = (orient == 'H' || orient == 'h');
            int idBarco = static_cast<int>(barcos.size());
            Barco nuevo(idBarco, 4);

            if (propio.ColocarBarco(x, y, horizontal, idBarco)) {
                cout << "OK - Barco colocado con exito.\n";
                barcos.push_back(nuevo);
                propio.Mostrar(true);
                break;
            } else {
                cout << "ERROR - Posicion no valida. Elija otra.\n";
            }
        }
    }

    cout << "\n--- Fin del turno de " << nombre << " ---\n";
    cout << "Pase el control al siguiente jugador y presione ENTER...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int Jugador::BarcosRestantes() const {
    int vivos = 0;
    for (const Barco &b : barcos)
        if (!b.Hundido()) ++vivos;
    return vivos;
}

bool Jugador::Disparar(Jugador &enemigo, vector<string> &historial) {
    while (true) {
        cout << "\nGuia de disparos contra " << enemigo.nombre << ":\n";
        cout << oponente.ToStringGuia();

        int x = LeerCoordenada(" x (0-19): ");
        int y = LeerCoordenada(" y (0-19): ");

        int idImpactado = -1;
        bool yaDisparado = false;

        bool acierto = enemigo.propio.Disparar(x, y, idImpactado, yaDisparado);

        if (yaDisparado) {
            cout << "ERROR - Ya disparaste en (" << x << "," << y << "). Intente otra posicion.\n";
            continue;
        }

        int dummyId = -1; bool dummyBool = false;
        oponente.Disparar(x, y, dummyId, dummyBool);

        if (acierto) {
            oponente.SetBarcoID(x, y, idImpactado);
            cout << "IMPACTO - Disparo acertado!\n";
            enemigo.barcos[idImpactado].Impactar();
            if (enemigo.barcos[idImpactado].Hundido()) {
                cout << "HUNDIDO - Barco de " << enemigo.nombre << " destruido!\n";
                enemigo.propio.MarcarBarcoHundido(idImpactado);
                oponente.MarcarBarcoHundido(idImpactado);
            }
        } else {
            cout << "AGUA - No acertaste...\n";
        }

        cout << "> A " << enemigo.nombre << " le quedan "
             << enemigo.BarcosRestantes() << " barcos por destruir.\n";

        ostringstream ss;
        ss << "Disparo de " << nombre << " a (" << x << "," << y << ")\n\n";
        ss << "Guia de disparos de " << nombre << ":\n" << oponente.ToStringGuia() << "\n";
        historial.push_back(ss.str());

        return acierto;
    }
}

bool Jugador::HaPerdido() const {
    for (const Barco &b : barcos)
        if (!b.Hundido()) return false;
    return true;
}

void Jugador::Serializar(ofstream &out) const {
    size_t len = nombre.size();
    out.write((char*)&len, sizeof(len));
    out.write(nombre.c_str(), len);
    propio.Serializar(out);
    oponente.Serializar(out);
    size_t n = barcos.size();
    out.write((char*)&n, sizeof(n));
    for (const Barco &b : barcos) b.Serializar(out);
}

void Jugador::Deserializar(ifstream &in) {
    size_t len;
    in.read((char*)&len, sizeof(len));
    nombre.resize(len);
    in.read(&nombre[0], len);
    propio.Deserializar(in);
    oponente.Deserializar(in);
    size_t n;
    in.read((char*)&n, sizeof(n));
    barcos.resize(n);
    for (size_t i = 0; i < n; ++i) barcos[i].Deserializar(in);
}
