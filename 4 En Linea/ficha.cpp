#include "ficha.h"

#include <stdlib.h>
#include <time.h>

using namespace std;

Ficha::Ficha(string nombreDeJugador){
    this->propietarioActual = nombreDeJugador;
    srand(time(NULL));
    this->red = rand() % 256;
    this->green = rand() % 256;
    this->blue = rand() % 256;
}

void Ficha::cambiarTempRed(int redAsignado){
    if( redAsignado > 255){
        throw std::string("Valor invalido.");
    }
	this->red = redAsignado;
}

void Ficha::cambiarTempBlue(int blueAsignado){
    if( blueAsignado > 255){
        throw std::string("Valor invalido.");
    }
	this->blue = blueAsignado;
}

void Ficha::cambiarTempGreen(int greenAsignado){
    if( greenAsignado > 255){
        throw std::string("Valor invalido.");
    }
	this->green = greenAsignado;
}

int Ficha::obtenerTempRed(){
    return this->red;
}

int Ficha::obtenerTempGreen(){
    return this->green;
}

int Ficha::obtenerTempBlue(){
    return this->blue;
}

string Ficha::obtenerPropietarioActual(){
    return this->propietarioActual;
}

void Ficha::cambiarPropietarioDeFicha(string nombreNuevo){
    this->propietarioActual = nombreNuevo;
}

Ficha::~Ficha(){
}
