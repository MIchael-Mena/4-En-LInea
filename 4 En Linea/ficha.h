#ifndef FICHA_H_
#define FICHA_H_

#include <string>

class Ficha{
private:
    int red;
    int green;
    int blue;
    std::string propietarioActual;

public:
    /*
     * post: Crea la ficha con un color en RGB.
     */
    Ficha(std::string nombreDeJugador);

    /*
     * pre: El valor debe estar entre 0 y 255.
     * post: Asgina un valor a RED.
     */
    void cambiarTempRed(int redAsignado);

    /*
     * pre: El valor debe estar entre 0 y 255.
     * post: Asgina un valor a BLUE.
     */
    void cambiarTempBlue(int blueAsignado);

    /*
     * pre: El valor debe estar entre 0 y 255.
     * post: Asgina un valor a GREEN.
     */
    void cambiarTempGreen(int greenAsignado);


    /*
     * post: Devuelve el valor en RED.
     */
    int obtenerTempRed();

    /*
     * post: Devuelve el valor en GREEN.
     */
    int obtenerTempGreen();

    /*
     * post: Devuelve el valor en BLUE.
     */
    int obtenerTempBlue();

    /*
     * post: Devuelve el nombre del Jugador asociado a esta Ficha.
     */
    std::string obtenerPropietarioActual();

    /*
     * post: Cambia el nombre del propietario de esta Ficha por el nuevo nombre.
     */
    void cambiarPropietarioDeFicha(std::string nombreNuevo);

    ~Ficha();
};

#endif // ficha_H_

