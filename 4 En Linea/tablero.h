#ifndef TABLERO_H_
#define TABLERO_H_

#include "lista_enlazada.h"
#include "ficha.h"
#include "EasyBMP.h"

typedef Lista< Ficha *> primerEje;
typedef Lista<primerEje *> segundoEje;
typedef Lista<segundoEje *> tercerEje;

class Tablero{
private:
    tercerEje* ejeZ;
    unsigned long casillerosDisponibles;
    unsigned int dimensionX, dimensionY, dimensionZ;

    /*
     * post: crea un tablero que que es una Lista < Lista < Lista < T *> > que
     *       contiene punteros al tipo 'T', donde la primer Lista representa
     *       el eje 'Z', la segunda el eje 'X' y la tercera el eje 'Y'.
     */
    void crearTablero();

    /*
     * pre: La profundidad de bits esta entre 1, 4 o 8.
     * post: Cambia la tabla de color con de la imagen pasada con
     *       el color RGB que contenga la ficha.
     */
    void cambiarTablaDeColor(BMP& InputImage, Ficha* ficha);

public:
    /*
     * pre: x, y, z deben se mayor a 0.
     * post: Crea el tablero con las dimensiones de x, y, z .
     */
    Tablero(unsigned int x, unsigned int y, unsigned int z);

    /*
     * post: Muestra una representacion del estado actual con una imagen bmp,
     *       en x e y del plano pasado 'z'.
     *       ej: (4, 3, 1) donde '.' representa un espacio que no esta en el tablero.
     *
     *                 y
     *         6 - - - - - - -
     *         5 - - - - - - -
     *         4 - - - - - - -
     *         3 - - - 0 - - -  x
     *         2 - - - - - - -
     *         1 - - - - - - -
     *           . . . . . . .
     *           1 2 3 4 5 6 7
     *
     */
    void imprimirTablero(unsigned int x, unsigned int y, unsigned int z);

    /*
     * pre: La posicion recibida debe estar
     *      para x de 1 hasta dimensionX,
     *      para y de 1 hasta dimensionY,
     *      Si la posicion no es valida devuelve '0'
     * post: Deja caer la fica hasta una posicion libre en 'z' y devuelve el valor de z
     * 		 o '0' si el casillero ya estaba lleno (usar tableroEstaLleno para saber si
     * 		 quedan casilleros disponibles). .
     */
    unsigned int colocarFicha(unsigned int xElegido,unsigned int yElegido, Ficha* ficha);

    /*
     * post: Devuelve la dimension en 'x' del tablero.
     */
    unsigned int obtenerDimensionEnX();

    /*
     * post: Devuelve la dimension en 'y' del tablero.
     */
    unsigned int obtenerDimensionEnY();

    /*
     * post: Devuelve la dimension en 'z' del tablero.
     */
    unsigned int obtenerDimensionEnZ();

    /*
     * post: Devuelve false si quedan casilleros disponibles o true
     *       en caso contrario.
     */
    bool estaLleno();

    /*
     * pre: Recibe posiciones en x, y, z.
     *      para x de 1 hasta dimensionX,
     *      para y de 1 hasta dimensionY,
     *      para z de 1 hasta dimensionZ.
     * post: Modifica la posicion (x, y, z) recibida con la ficha si la posicion,
     *       es valida.
     */
    void modificarCasillero(unsigned int x, unsigned int y, unsigned int z, Ficha* ficha);

    /*
     * post: Devuelve '0' si la posicion es invalida o si no hay ninguna ficha
     *       en esa posicion, si no devuelve un puntero al elemento.
     */
    Ficha* obtenerFicha(unsigned int x, unsigned int y, unsigned int z);

    /*
     * pre: Recibe posiciones en x, y, z.
     *      para x de 1 hasta dimensionX,
     *      para y de 1 hasta dimensionY,
     *      para z de 1 hasta dimensionZ.
     * post: Devuelve true si las posiciones estan dentro del tablero, false
     * 		 en caso contrario.
     */
    bool validarPosicion(unsigned int xValidar, unsigned int yValidar, unsigned int zValidar);

    ~Tablero();
};

#endif // TABLERO_H_
