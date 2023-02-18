#ifndef MAZO_DE_CARTAS_
#define MAZO_DE_CARTAS_

#include "carta.h"
#include "lista_enlazada.h"

class Carta;

class MazoDeCartas{
private:
    unsigned int slotDeCartas, cartasTotales, cartasDisponibles;
    Lista<Carta *>* cartasDePoderDisponible;

    /*
     * post: Muestra por pantalla la descripcion de la carta elegida.
     */
    void mostrarDescripcion();

public:
    MazoDeCartas(unsigned int maximaCantidadCartas);

    /*
     * post: Devuelve true si hay una carta disponible del tipo elegido, se usa la Carta
     *       y se la elimina de las cartas de poder disponibles.
     */
    bool usarCartaDePoder(int cartaElegida);

    /*
     * pre: La Cartas recibida tendran el siguiente orden primero la carta tipo 1,
     *      segundo la carta tipo 2 ... hasta la 4 carta.
     *      El tipo de carta de poder debe ser entre 1 y 4.
     * post: Guarda la carta mientras no se tenga mas que 4.
     */
    void guardarCartaDePoder(Carta* cartaDePoder);


    /*
     * pre: El tipo de carta de poder esta entre 1 y 4.
     * post: Guarda el tipo de carta de poder recibido, si ya se tenia otra del mismo
     *       tipo se suma a la anterior.
     */
    void guardarCartaDePoder(int tipoDeCartaDePoder);

    /*
     * post: Devuelve true si hay cartas disponibles y Imprime por pantalla la cantidad
     *       de cada cartas disponiblie, adicionalmente permite ver la descripcion.
     */
    bool obtenerCartasDisponibles();

    ~MazoDeCartas();
};

#endif // MAZO_DE_CARTAS_
