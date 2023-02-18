#include "mazo_de_cartas.h"
#include <iostream>

using namespace std;

MazoDeCartas::MazoDeCartas(unsigned int maximaCantidadCartas){
    this->cartasDePoderDisponible = new Lista<Carta *>;
    this->slotDeCartas = maximaCantidadCartas;
    this->cartasTotales = 0;
    this->cartasDisponibles = 0;
}

bool MazoDeCartas::usarCartaDePoder(int cartaElegida){
	bool seJugoLaCarta = false;
    if( this->cartasDisponibles > 0 && cartaElegida < 5 && cartaElegida > 0){
    	this->cartasDePoderDisponible->posicionarCursor(cartaElegida);
    	Carta* cartaActual = this->cartasDePoderDisponible->getCursor();
    	if( cartaActual->obtenerUsosRestantes() > 0 ){
    		cartaActual->usarCarta();
            this->cartasDisponibles -= 1;
            seJugoLaCarta = true;
    	}
    }
    return seJugoLaCarta;
}

void MazoDeCartas::mostrarDescripcion(){
    int cartaElegida;
    do{
        cout << "Ingrese un Tipo de Carta para ver una descripcion o '0' para continuar: ";
        cin >> cartaElegida;
        if(cartaElegida > 0 && cartaElegida < 5){
            this->cartasDePoderDisponible->posicionarCursor(cartaElegida);
            this->cartasDePoderDisponible->getCursor()->obtenerDescripcionTipoDeCarta();
        }
    }while(cartaElegida != 0);
}

bool MazoDeCartas::obtenerCartasDisponibles(){
    int i = 1;
    bool hayCartasParaMostrar = true;
    if(this->cartasDisponibles > 0){
        this->cartasDePoderDisponible->iniciarCursor();
        while( this->cartasDePoderDisponible->avanzarCursor()){
            Carta* cartaActual = this->cartasDePoderDisponible->getCursor();
            if(cartaActual->obtenerUsosRestantes() > 0){
                cout << "Cantidad de cartas de poder tipo '" << i << "' : " <<
                cartaActual->obtenerUsosRestantes() << endl;
            }
            i += 1;
        }
        this->mostrarDescripcion();
    }else{
        cout << "No hay cartas disponibles para jugar." << endl;
        hayCartasParaMostrar = false;
    }
    return hayCartasParaMostrar;
}

void MazoDeCartas::guardarCartaDePoder(Carta* carta){
    if( this->cartasTotales < this->slotDeCartas){
        this->cartasTotales += 1;
        this->cartasDePoderDisponible->agregar(carta);
    }
}

void MazoDeCartas::guardarCartaDePoder(int tipoDeCartaDePoder){
    this->cartasDePoderDisponible->posicionarCursor(tipoDeCartaDePoder);
    Carta* cartaActual = this->cartasDePoderDisponible->getCursor();
    if( this->cartasDisponibles < this->slotDeCartas) {
        this->cartasDisponibles += 1;
        cartaActual->sumarUsoRestante();
    }
}

MazoDeCartas::~MazoDeCartas(){
	this->cartasDePoderDisponible->iniciarCursor();
	while( this->cartasDePoderDisponible->avanzarCursor() ){
		Carta* cartaAborrar = this->cartasDePoderDisponible->getCursor();
		delete cartaAborrar;
	}
    delete cartasDePoderDisponible;
}
