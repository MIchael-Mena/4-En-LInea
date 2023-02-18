#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "mazo_de_cartas.h"
#include "ficha.h"
#include "tablero.h"
#include <string>

#define NONE 0

class MazoDeCartas;

class Jugador{
private:
    unsigned int cantidadDeFichasDisponibles;
    std::string nombre;
    Ficha* ficha;
    unsigned int xElegido, yElegido, zElegido;
    MazoDeCartas* mazo;
    unsigned int numeroDeJugador;

public:
    Jugador(std::string nombreJugador);

    /*
     * post: Asigna un numero mayor a cero al Jugador.
     */
    void asignarNumeroDeJugador(unsigned int nJugador);

    /*
     * post: Asigna un mazo al Jugador.
     */
    void recibirMazoDeCartas(MazoDeCartas* mazoNuevo);

    /*
     * post: Devuelve el numero asignado, si no se asigno un numero devuelve '0'.
     */
    unsigned int obtenerNumeroDeJugador();

    /*
     * post: Recibi la carta de poder y la guarda en el mazo si este tiene espcio disponible.
     */
    void recibirCartaDePoder(int tipo);

    /*
     * post: Devuelve true si la carta esta disponible y la juega.
     */
    bool jugarCartaDePoder(int cartaElegida);

    /*
     * post: Devuelve true si hay cartas disponibles para mostrar y las muestra por pantalla.
     */
    bool mostrarCartasDePoderDisponible();

    /*
     * post: Devuelve la ficha que se asigno al jugador (un numero).
     */
    Ficha* obtenerFicha();

    /*
     * post: Devuelve el nombre del jugador.
     */
    std::string obtenerNombre();

    /*
     * pre: Se asigno un valor a xElegido si no devuelve 0.
     * post: Devuelve el 'x' elegido por el jugador.
     */
    unsigned int obtenerPosicionX();

    /*
     * pre: se asigno un valor a yElegido si no devuelve 0.
     * post: devuelve el 'y' elegido por el jugador.
     */
    unsigned int obtenerPosicionY();

    /*
     * pre: Se asigno un valor a zElegido si no devuelve 0.
     * post: Devuelve el 'z' elegido por el jugador.
     */
    unsigned int obtenerPosicionZ();

    /*
     * post: Asigna un valor x.
     */
    void asignarPosicionX(unsigned int x);

    /*
     * post: Asigna un valor y.
     */
    void asignarPosicionY(unsigned int y);

    /*
     * post: Asigna un valor z.
     */
    void asignarPosicionZ(unsigned int z);

    ~Jugador();
};

#endif // JUGADOR_H_
