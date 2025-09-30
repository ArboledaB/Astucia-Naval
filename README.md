# 🚢 Astucia Naval

Juego clásico de estrategia naval implementado en C++, con soporte para:
- Guardar y cargar partidas se guarda en `partida.dat`
- Historial de disparos
- Representación visual en consola con colores ANSI
- Sistema de turnos entre dos jugadores


## 📂 Estructura del proyecto
```
AstuciaNaval/
│── main.cpp              # Punto de entrada del programa
│── include/              # Archivos de cabecera (.h)
│   ├── Casilla.h
│   ├── Tablero.h
│   ├── Barco.h
│   ├── Jugador.h
│   ├── Partida.h
│   ├── Juego.h
│── src/                  # Implementaciones (.cpp)
│   ├── Casilla.cpp
│   ├── Tablero.cpp
│   ├── Barco.cpp
│   ├── Jugador.cpp
│   ├── Partida.cpp
│   ├── Juego.cpp
│── docs/                
│   └── Diagrama UML.png
│── build/                # Archivos generados (astucia_naval.exe, .obj)
│── compilar.bat          # Script de compilación + ejecución
│── clean.bat             # Script para limpiar build/
│── README.md             # Documentación
```

---

## Requisitos
- **Windows**
- **Visual Studio 2022** 
---

## Compilar y ejecutar
1. Abrir **Developer Command Prompt for VS 2022**.  
2. Navegar a la carpeta raíz del proyecto:
   cd C:\ruta\AstuciaNaval
3. Ejecutar:
   compilar.bat
   - Compilará todos los `.cpp`  
   - Guardará los `.obj` y el ejecutable dentro de `build/`  
   - Ejecutará automáticamente `build\astucia_naval.exe`

---

## Limpiar proyecto
Para borrar los archivos compilados (`.obj` y `astucia_naval.exe`):

clean.bat

Esto dejará la carpeta `build/` vacía o la eliminará si no contiene nada más.

---

## Cómo jugar
1. Cada jugador introduce su **nombre**.  
2. Cada jugador coloca **3 barcos de tamaño 4** 
   - Los barcos se muestran en verde en tu propio tablero.  
3. Los jugadores se turnan para disparar:  
   - **Impacto**: rojo  
   - **Agua**: azul  
   - **Barco hundido**: morado 
   - **Tus barcos**: verde  
   - **Áreas no disparadas**: gris  
4. Gana el primer jugador que hunda todos los barcos enemigos.  

---

## 💾 Guardado y carga
- Después de cada disparo, la partida se guarda en `partida.dat`.  
- Si ejecutas el programa y existe una partida guardada, se te preguntará si deseas reanudarla.  

---