#include "carta.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

Carta::Carta(int tipoCartaElegida, unsigned int* turnoActual, Tablero* tableroDeJuego,
             Lista<Jugador *>* listaDeJugadores){
    this->cantidadDeUsosRestantes = 0;
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->cambioDeColorAnterior = 0;
    this->tablero = tableroDeJuego;
    this->jugadores = listaDeJugadores;
    this->turnoActual = turnoActual;
    if(tipoCartaElegida < 5 && tipoCartaElegida > 0){
        this->tipoDeCartaDePoder = tipoCartaElegida;
    }else{
        srand(time(NULL));
        this->tipoDeCartaDePoder = rand() % 5;
    }
}

unsigned int Carta::obtenerUsosRestantes(){
    return this->cantidadDeUsosRestantes;
}

void Carta::sumarUsoRestante(){
    this->cantidadDeUsosRestantes += 1;
}

void Carta::obtenerDescripcionTipoDeCarta(){
    switch(this->tipoDeCartaDePoder){
        case 1:{
            cout << "Cambio de color 'Efecto Acumulable': Cambia el color de una ficha, el color resultante va de acuerdo \n" <<
            		"a la cantidad de  veces que se jugo la carta. La primera vez que se juega, toma el color del \n" <<
					"jugador 1, la segunda vez  la del jugador 2 ...\n" << endl;
            break;
        }
        case 2:{
            cout << "Destruir: Elimina una ficha del tablero elegida por el jugador.\n" << endl;
            break;
        }
        case 3:{
            cout << "Intercambio: Cambia una ficha con su vecina inmediata, ambas deben ser seleccionadas por el jugador.\n" << endl;
            break;
        }
        case 4:{
            cout << "Ignorar: Elimina el movimiento del jugador anterior.\n";
            break;
        }
    }
}

void Carta::usarCarta(){
    this->cantidadDeUsosRestantes -= 1;
    if(this->tipoDeCartaDePoder == 1){
        this->cambiarColorDeFicha();
    }
    else if(this->tipoDeCartaDePoder == 2){
        this->eliminarUnaFichaDelTablero();
    }
    else if(this->tipoDeCartaDePoder == 3){
        this->intercambiarFichas();
    }
    else if(this->tipoDeCartaDePoder == 4){
        this->ignorarJugadaPrevia();
    }
}


void Carta::ignorarJugadaPrevia(){
    this->jugadores->posicionarCursor(*this->turnoActual - 1);
    Jugador* jugadorAnterior = this->jugadores->getCursor();
    this->tablero->modificarCasillero(jugadorAnterior->obtenerPosicionX(),
                                      jugadorAnterior->obtenerPosicionY(),
                                      jugadorAnterior->obtenerPosicionZ(),
                                      jugadorAnterior->obtenerFicha() );
    cout << "Se elimino la jugada del anterior Jugador." << endl;
}

void Carta::intercambiarFichas(){
	bool intercambioCompletado;
    unsigned int xInicial, yInicial, zInicial;
    cout << "Elija una posicion para la primera Ficha." << endl;
    this->verificarValoresDeEntrada();
    xInicial = this->x, yInicial = this->y, zInicial = this->z;
    cout << "Elija una posicion alrededor de la anterior Ficha para la segunda Ficha." << endl;
    this->verificarValoresDeEntrada(); // x, y, z debe ser una ficha alrededor de la anterior
    if(this->tablero->obtenerFicha(this->x, this->y, this->z) == 0 ||
       this->tablero->obtenerFicha(xInicial, yInicial, zInicial) == 0){
     	intercambioCompletado = false;
     }else{
    	 for(int k = -1; k <= 1; k++){
    		 for(int i = -1; i <= 1; i++){
    			 for(int j = 1; j <= 1; j++){
    				 if(i != 0 && j != 0 && k != 0
    	                && this->x == xInicial + i
    					&& this->y == yInicial + j
    					&& this->z == zInicial + k){
    					 Ficha* fichaIntercambio = this->tablero->obtenerFicha(this->x, this->y, this->z);
    					 this->tablero->modificarCasillero(this->x, this->y, this->z,
    	                                                   this->tablero->obtenerFicha(xInicial, yInicial, zInicial));
    					 this->tablero->modificarCasillero(xInicial, yInicial, zInicial, fichaIntercambio);
    					 intercambioCompletado = true;
    				 }
    			 }
    		 }
    	 }
     }
    if(intercambioCompletado){
    	cout << "Se intercambio con exito las posicion de las fichas recibidas." << endl;
    }else{
    	cout << "No se pudo realizar el intercambio" << endl;
    }
}

void Carta::eliminarUnaFichaDelTablero(){
    this->verificarValoresDeEntrada();
    if(this->tablero->obtenerFicha(this->x, this->y, this->z) != 0){
        this->tablero->modificarCasillero(this->x, this->y, this->z, 0);
        cout << "Se elimino la ficha de la poscion elegida." << endl;
    }else{
        cout << "No habia ninguna ficha para eliminar." << endl;
    }
}

void Carta::cambiarColorDeFicha(){
    this->verificarValoresDeEntrada();
    if( this->jugadores->posicionarCursor(cambioDeColorAnterior + 1) ){
        cambioDeColorAnterior += 1;
    }else{
        cambioDeColorAnterior = 1;
        this->jugadores->posicionarCursor(1);
    }
    if(this->tablero->obtenerFicha(this->x, this->y, this->y)  != 0){
        Jugador* anteriorCambioDeColor = this->jugadores->getCursor();
        this->tablero->modificarCasillero(this->x, this->y, this->z, anteriorCambioDeColor->obtenerFicha() );
        cout << "\nSe cambio el color de la ficha  de " << this->tablero->obtenerFicha(x, y, z)->obtenerPropietarioActual();
        cout << " por la ficha de " << this->jugadores->getCursor()->obtenerNombre() << ".\n" << endl;
    }
}

void Carta::verificarValoresDeEntrada(){
    do{
        cout << "ingrese un 'x': ";
        cin >> this->x;
        cout << "ingrese un 'y': ";
        cin >> this->y;
        cout << "ingrese un 'z': ";
        cin >> this->z;
        if(this->tablero->validarPosicion(this->x, this->y, this->z)){
            cout << "POSICION INVALIDA" << endl;
        }
    }while( !this->tablero->validarPosicion(this->x, this->y, this->z) );
}

Carta::~Carta(){
}
