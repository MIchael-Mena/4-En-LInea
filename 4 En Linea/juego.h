#ifndef JUEGO_H_
#define JUEGO_H_

#include "mazo_de_cartas.h"
#include "lista_enlazada.h"
#include "jugador.h"
#include "tablero.h"
#include "carta.h"
#include "ficha.h"

class Juego{
private:
    Jugador *ganador, *jugadorActual;
    Tablero* tablero;
    bool turnoActivo;
    int nivelDeDificultad;
    unsigned int dimensionEnX, dimensionEnY, dimensionEnZ;
    unsigned int nJugadores;
    Lista<Jugador *>* jugadores;
    unsigned int turnosJugados, turnoDeJugadorActual;

    void avanzarJugador();

    /*
     * pre: Todos los jugadores jugaron su turno en un ronda.
     * post: Devuelve true si hay un ganador o false en caso contrario.
     */
    bool verificarGanador(Jugador* posibleGanador);

    /*
     * post: Si el nivel de dificultad es 1 la verificacion del ganador se hara despues
     *       de cada turno.
     *       Si el nivel de dificultad es 2 la verificacion del ganador se realizara
     *       despues que todos lo jugadores hayan jugado su turno.
     */
    bool comprobarDificultadElegida();

    /*
     * pre: Opcion esta entre 1 y 5.
     * post: Cambia los planos formados x, y, z de acuerdo a la opcion elegida y verifica
     * 		 si la posicion pasada tiene una ficha igual a donde se empezo el recorrido
     *       para formar una linea de 4 (la posicion x, y, z Elegida del Jugador).
     */
    void reacomodarPlanos(int sEjeX, int sEjeY, int sEjeZ, unsigned int x,unsigned int y,
    		unsigned int z, Ficha* ficha, int opcion, int k, int i, int j, bool* hayGanador);

    /*
     * pre: Opcion esta entre 1 y 5.
     * post: Cambia los signos de sEjeX, sEjeY, sEjeZ dependiendo de la opcion elegida.
     * 		 ej. para opcion 1 en el plano z-y se empieza por el primer cuadrante, segundo
     * 		 cuadrante, cuarto cuadrante y por ultimo el tercer cuadrante.
     * 		   o    |    o
     * 		   	 o  |  o
     * 		 -------*-------
     * 		 	 o  |  o
     * 		   o    |    o
     */
    void cambiarSignoDiagonal(int* sEjex, int* sEjeY, int* sEjeZ, int opcion, bool* posibilidadGanar);

    /*
     * pre: Recibe una posicion de (x, y, z) valida dentro del tablero, posiciones del 1
     * 		a la dimension x, y, z del tablero
     * post: Verifica si en las diagonales alrededor de la posicion dada se puede formar
     * 		 una linea de 4 con la ficha recibida, devuelve true si se cumple.
     * 		 ej. para un plano z alrededor del punto *.
     * 		 x   -   -   o
     * 		 -   x   x   -
     * 		 -   x * x   -
     * 		 x   -   -   x
     */
    bool verificarDiagonales(unsigned int x,unsigned int y,unsigned int z, Ficha* ficha, int opcion);

    /*
     * pre: Recibe una posicion de (x, y, z) valida dentro del tablero, posiciones del 1
     * 		a la dimension x, y, z del tablero.
     * post: verifica si en las horizontales y verticales x, y, z se puede formar una
     * 		 linea de 4 con la ficha recibida, devuelve true si se cumple.
     * 		 ej. para un plano z
     * 		 -   -   o   -
     * 		 -   -   o   -
     * 		 o   x   o   o
     * 		 -   -   o   -
     */
    bool verificarHorizontales(unsigned int x, unsigned int y, unsigned int z, Ficha* ficha);

public:
    /*
     * pre: Los ejex, ejey, ejez y candidadJugadores deben ser mayor o igual 4 (tablero mas
     *      chico posible para jugar una partida)
     * post: Simula un juego de 4 linea en 3D.
     */
    Juego(unsigned int ejeX, unsigned int ejeY, unsigned int ejeZ, unsigned int cantidadJugadores,
          int dificultadElegida);

    /*
     * post: Crea un tablero con x = 7, y = 7, z = 7 para 2 jugadores.
     */
    Juego();

    /*
     * post: Devuelve la cantidad de turnos jugados hasta el momento.
     */
    unsigned int obtenerTurnosJugados();

    /*
     * post: Agrega como maximo 'n' CantidadJugadores.
     */
    void agregarJugador(Jugador* jugador);

    /*
     * pre: Se llamo a obtenerTurnoDeJugadorActual.
     * post: Devuelve true si la posicion elegida era valida si no lo es (por que esta fuera
     *       del tablero o porque la posicion elegida ya contenia otra ficha) devuelve false.
     *       Se actualiza el tablero on la ficha si paso la verificacion. En caso de que el
     *       tablero este lleno siempre se devuelve true por imposibilidad de que pueda
     *       haber un ganador.
     */
    bool jugarFicha(unsigned int xElegido, unsigned int yElegido);


    /*
     * pre: Se debe haber jugado al menos una ficha;
     * post: Muestra una representacion de la ultima ficha jugada. Se debe llamar
     *       previo a finalizar el turno, de lo contrario se mostraria la ficha de
     *       la anterior jugada del siguiente Jugador.
     */
    void imprimirEstadoActualDelJuego();

    /*
     * post: Si el nivel de dificultad es 1 se devuelve true si hubo un ganador, en caso
     *       contrario se avanza el turno al siguiente jugador y devuelve false .
     *       Si el nivel de dificultad es 2 y hay un ganador, solo se devuelve true cuando
     *       todos lo jugadores hayan jugado su turno.
     *       Adicionalmente hay %50 probabilidad de que el jugador reciba una carta de poder.
     */
    bool terminarTurno();

    /*
     * pre: Se llamo a terminar turno y devolvio false, en caso contrario devuelve '0'
     * post: Devuelve el nombre del ganador o empate si el tablero esta lleno.
     */
    std::string obtenerGanador();

    /*
     * post: Devuelve el Jugador para el turno actual.
     */
    Jugador* obtenerTurnoDeJugadorActual();

    ~Juego();
};


#endif // JUEGO_H_
