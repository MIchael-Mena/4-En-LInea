#include "jugador.h"
#include <string>

using namespace std;

Jugador::Jugador(string nombreJugador){
	this->cantidadDeFichasDisponibles = -1;
    this->mazo = NONE;
    this->nombre = nombreJugador;
    this->ficha = new Ficha(nombreJugador);
    this->xElegido = NONE;
    this->yElegido = NONE;
    this->zElegido = NONE;
    this->numeroDeJugador = NONE;
}

void Jugador::asignarNumeroDeJugador(unsigned int nJugador){
	this->numeroDeJugador = nJugador;
}

void Jugador::recibirMazoDeCartas(MazoDeCartas* mazoNuevo){
    this->mazo = mazoNuevo;
}

bool Jugador::jugarCartaDePoder(int cartaElegida){
    return this->mazo->usarCartaDePoder(cartaElegida);
}

bool Jugador::mostrarCartasDePoderDisponible(){
    return this->mazo->obtenerCartasDisponibles();
}

unsigned int Jugador::obtenerNumeroDeJugador(){
    return this->numeroDeJugador;
}

void Jugador::recibirCartaDePoder(int tipoDeCarta){
    this->mazo->guardarCartaDePoder(tipoDeCarta);
}

Ficha* Jugador::obtenerFicha(){
    return this->ficha;
}

string Jugador::obtenerNombre(){
    return this->nombre;
}

unsigned int Jugador::obtenerPosicionX(){
    return this->xElegido;
}

unsigned int Jugador::obtenerPosicionY(){
    return this->yElegido;
}

unsigned int Jugador::obtenerPosicionZ(){
    return this->zElegido;
}

void Jugador::asignarPosicionX(unsigned int x){
    this->xElegido = x;
}

void Jugador::asignarPosicionY(unsigned int y){
    this->yElegido = y;
}

void Jugador::asignarPosicionZ(unsigned int z){
    this->zElegido = z;
}

Jugador::~Jugador(){
	delete this->ficha;
    delete this->mazo;
}
