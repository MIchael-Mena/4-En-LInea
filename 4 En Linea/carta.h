#ifndef CARTA_H_
#define CARTA_H_

#include "ficha.h"
#include "jugador.h"
#include "tablero.h"
#include "lista_enlazada.h"
#include <string>

typedef Lista< Ficha *> primerEje;
typedef Lista<primerEje *>  segundoEje;
typedef Lista<segundoEje *> tercerEje;

class Jugador;

class Carta{
private:
    unsigned int cantidadDeUsosRestantes;
    unsigned int x, y, z;
    unsigned int* turnoActual;
    Lista<Jugador *>* jugadores;
    unsigned int cambioDeColorAnterior;
    int tipoDeCartaDePoder;
    Tablero* tablero;

    /*
     * post: Elimina el movimiento del jugador anterior (la anterior Ficha jugada).
     */
    void ignorarJugadaPrevia();

    /*
     * post: Cambia una ficha con su vecina inmediata siempre que sea posible (existan las fichas
     * 		 en las posiciones recibidas), ambas deben ser seleccionadas por el jugador.
     */
    void intercambiarFichas();

    /*
     * post: Elimina una ficha del tablero siempre que sea posible (exista la ficha en la posicion
     * 		 recibida).
     */
    void eliminarUnaFichaDelTablero();

    /*
     * post: Cambia el color de una ficha 'efecto acumulable', el color resultante va de acuerdo a
     * 		 la cantidad de veces que se jugo la carta. La primera vez que se juega, toma el color
     * 		 del jugador 1, la segunda vez la del jugador 2 ...
     */
    void cambiarColorDeFicha();

    /*
     * pre: Pide por pantalla valores para (x, y, z) mientras los valores sean invalidos.
     * post: Asigna los valores a (x, y, z).
     */
    void verificarValoresDeEntrada();

public:
    /*
     * post: Se crea la carta, si el valor recibido es mayor a 4 o menor a 1
     *       se iniciara con una carta aleatoria.
     */
    Carta(int tipoCartaElegida, unsigned int* turnoActual, Tablero* tableroDeJuego,
             Lista<Jugador *>* listaDeJugadores);

    /*
     * post: Devuelve cuanto usos disponibles tiene la Carta.
     */
    unsigned int obtenerUsosRestantes();

    /*
     * post: Agrega una vida mas a la carta para poder ser jugada.
     */
    void sumarUsoRestante();

    /*
     * post: Devuelve la decripcion de la carta.
     */
    void obtenerDescripcionTipoDeCarta();

    /*
     * post: Juega la carta de acuerdo al tipo de carta, si la carta no puede
     *       ser jugada por no cumplir alguna condicion que requiera el tipo
     *       de carta elegida se ignora la jugada y se pierde la carta.
     */
    void usarCarta();

    ~Carta();
};

#endif // CARTA_H_
