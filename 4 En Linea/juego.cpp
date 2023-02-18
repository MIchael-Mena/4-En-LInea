#include "juego.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define NONE 0

Juego::Juego(unsigned int x, unsigned int y, unsigned int z, unsigned int cantidadJugadores, int dificultadElegida){
    if(x < 5 && y < 5 && z < 5 && cantidadJugadores <= 0){
        throw std::string("Un valor introducido es menor a 0");
    }
    this->nivelDeDificultad = dificultadElegida;
    this->tablero = new Tablero(x, y, z);
    this->jugadores = new Lista<Jugador *>;
    this->dimensionEnX = x;
    this->dimensionEnY = y;
    this->dimensionEnZ = z;
    this->jugadorActual = NONE;
    this->turnoDeJugadorActual = 1;
    this->nJugadores = cantidadJugadores;
    this->turnosJugados = 0;
    this->ganador = NONE;
    this->turnoActivo = false;
}

Juego::Juego(){
    this->nivelDeDificultad = 1;
    this->tablero = new Tablero(7, 7, 7);
    this->jugadores = new Lista<Jugador *>;
    this->dimensionEnX = 7;
    this->dimensionEnY = 7;
    this->dimensionEnZ = 7;
    this->jugadorActual = NONE;
    this->turnoDeJugadorActual = 1;
    this->nJugadores = 2;
    this->turnosJugados = 0;
    this->ganador = NONE;
    this->turnoActivo = false;
}

unsigned int Juego::obtenerTurnosJugados(){
    return this->turnosJugados;
}

void Juego::agregarJugador(Jugador* jugador){
    if(this->jugadores->contarElementos() < this->nJugadores){
        MazoDeCartas* nuevoMazo = new MazoDeCartas(4);
        for(int i = 1; i <= 4; i++){
            Carta* cartaDePoder = new Carta(i, &this->turnoDeJugadorActual, this->tablero,
                                            this->jugadores);
            nuevoMazo->guardarCartaDePoder(cartaDePoder);
        }
        jugador->recibirMazoDeCartas(nuevoMazo);
        this->jugadores->agregar(jugador);
        jugador->asignarNumeroDeJugador(this->jugadores->contarElementos());
    }
    if(this->jugadores->contarElementos() == 1){
        this->jugadores->posicionarCursor(1);
        this->jugadorActual = this->jugadores->getCursor();
    }
}

bool Juego::jugarFicha(unsigned int xElegido, unsigned int yElegido){
    if( !this->turnoActivo ){
        throw std::string("No se devolvio el nombre del Jugador actual.");
    }
	bool seColocoFicha = false;
    unsigned int zElegido = this->tablero->colocarFicha(xElegido, yElegido,
        		this->jugadorActual->obtenerFicha() );
    if(zElegido != 0 || this->tablero->estaLleno() ){
        this->jugadorActual->asignarPosicionX(xElegido);
        this->jugadorActual->asignarPosicionY(yElegido);
        this->jugadorActual->asignarPosicionZ(zElegido);
        seColocoFicha = true;
    }
    return seColocoFicha;
}

bool Juego::comprobarDificultadElegida(){
    bool hayGanador = false;
    if( this->nivelDeDificultad == 2 && this->turnosJugados > 0 &&
       this->turnoDeJugadorActual == this->nJugadores ){
        this->jugadores->iniciarCursor();
        while( this->jugadores->avanzarCursor() && !hayGanador){
            hayGanador = this->verificarGanador( this->jugadores->getCursor() );
        }
    }
    else if(this->nivelDeDificultad == 1 && this->turnosJugados > 0){
        hayGanador = this->verificarGanador( this->jugadorActual );
    }
    if( !hayGanador ){
        this->avanzarJugador();
    }
    return hayGanador;
}

void Juego::avanzarJugador(){
	if( this->jugadores->posicionarCursor(this->turnoDeJugadorActual + 1) ){
		this->turnoDeJugadorActual += 1;
        this->jugadorActual = this->jugadores->getCursor();
	}else{
        this->turnoDeJugadorActual = 1;
        this->jugadores->posicionarCursor(1);
        this->jugadorActual = this->jugadores->getCursor();
	}
}

bool Juego::verificarGanador(Jugador* posibleGanador){
    bool hayGanador = false;
    unsigned int x = posibleGanador->obtenerPosicionX();
    unsigned int y = posibleGanador->obtenerPosicionY();
    unsigned int z = posibleGanador->obtenerPosicionZ();
    Ficha* fichaActual = posibleGanador->obtenerFicha();
    for(int i = 1; i < 6; i++){
        if(!hayGanador){
            hayGanador = this->verificarDiagonales(x, y, z, fichaActual, i);
        }
    }
    if(!hayGanador){
        hayGanador = this->verificarHorizontales(x, y, z, fichaActual);
    }
    if(hayGanador){
        this->ganador = posibleGanador;
    }
    return hayGanador;
}

void Juego::imprimirEstadoActualDelJuego(){
    if( !this->tablero->estaLleno() ){
        cout << "Ficha colocada en el plano 'Z' igual a " << this->jugadorActual->obtenerPosicionZ() << endl
        << "Creando imagen..." << endl;
        this->tablero->imprimirTablero( this->jugadorActual->obtenerPosicionX(),
                                       this->jugadorActual->obtenerPosicionY(),
                                       this->jugadorActual->obtenerPosicionZ() );
    }else{
        cout << "El tablero esta lleno." << endl;
    }
}

bool Juego::terminarTurno(){
    bool hayGanador = false;
    int tipoDeCartaDePoder;
    if(this->tablero->estaLleno()){
        hayGanador = true;
    }else{
        srand(time(NULL));
        int probabilidadDeEntregarCarta = rand() % 10;
        if(probabilidadDeEntregarCarta > 4){
            tipoDeCartaDePoder = 1 + (rand() % 4);
            this->jugadorActual->recibirCartaDePoder(tipoDeCartaDePoder);
        }
        hayGanador = this->comprobarDificultadElegida();
    }
    this->turnosJugados += 1;
    this->turnoActivo = false;
    return hayGanador;
}

Jugador* Juego::obtenerTurnoDeJugadorActual(){
    this->turnoActivo = true;
    return this->jugadorActual;
}

std::string Juego::obtenerGanador(){
    if(this->tablero->estaLleno()){
        return "EMPATE";
    }
    else{
        return this->ganador->obtenerNombre();
    }
}

void Juego::reacomodarPlanos(int sEjeX, int sEjeY, int sEjeZ, unsigned int x, unsigned int y,
		unsigned int z, Ficha* ficha, int opcion, int k, int i, int j, bool* hayGanador){
    if(opcion > 3 && *hayGanador && (i * sEjeX) == (k * sEjeZ) && (i * sEjeX) == (j * sEjeY) ){
        *hayGanador = (ficha == this->tablero->obtenerFicha(x + i, y + j,  z + k) );
    }
    else if(opcion <= 3 && *hayGanador && (i * sEjeX) == (j * sEjeY) ){
        if(opcion == 1){
            *hayGanador = (ficha == this->tablero->obtenerFicha(x, y + j, z + i) );
        }
        else if(opcion == 2){
            *hayGanador = (ficha == this->tablero->obtenerFicha(x + j, y, z + i) );
        }
        else if(opcion == 3){
            *hayGanador = (ficha == this->tablero->obtenerFicha(x + i, y  + j, z) );
        }
    }
}

bool Juego::verificarDiagonales(unsigned int x,unsigned int y,unsigned int z, Ficha* ficha, int opcion){
    int sEjeX = 1, sEjeY = 1, sEjeZ = 1;
    int ciclosEnZ;
    if(opcion <= 3){
    	ciclosEnZ = 1;
    }
    else if(opcion == 4 || opcion == 5){
    	ciclosEnZ = 3;
    	if(opcion == 4){
    		sEjeY = -1;
    	}
    }
    bool posibilidadGanar = true, hayGanador = true;
    while(hayGanador && posibilidadGanar){
        for(int k = ciclosEnZ * sEjeZ; k > 0 || k < 0; k = k - sEjeZ){
            for(int i = 3 * sEjeX; i > 0 || i < 0; i = i - sEjeX){
                for(int j =  3 * sEjeY; j > 0 || j < 0; j = j - sEjeY){
                    this->reacomodarPlanos(sEjeX, sEjeY, sEjeZ, x, y, z, ficha,
                    		opcion, k, i, j, &hayGanador);
                }
            }
        }
        hayGanador = !hayGanador;
        this->cambiarSignoDiagonal(&sEjeX, &sEjeY, &sEjeZ, opcion, &posibilidadGanar);
    }
    return !hayGanador;
}

void Juego::cambiarSignoDiagonal(int* sEjeX, int* sEjeY, int* sEjeZ, int opcion, bool* posibilidadGanar){
    if(opcion <= 3 && *sEjeX > 0){
    	*sEjeX = (-1) * (*sEjeX);
    }
    else if(opcion <= 3){
        *posibilidadGanar = !(*sEjeX < 0 && *sEjeY < 0);
        *sEjeX = (-1) * (*sEjeX);
        *sEjeY = (-1) * (*sEjeY);
    }
    if(opcion == 4 && *sEjeZ > 0){
    	*sEjeZ = (-1) * (*sEjeZ);
    }
    else if(opcion == 4){
        if(*sEjeY < 0 && *sEjeZ < 0){
        	*sEjeY = (-1) * (*sEjeY);
        }
        *posibilidadGanar = !(*sEjeZ < 0 && *sEjeX < 0);
        *sEjeZ = (-1) * (*sEjeZ);
        *sEjeX = (-1) * (*sEjeX);
    }
    if(opcion == 5 && *sEjeZ > 0){
    	*sEjeZ = (-1) * (*sEjeZ);
    }
    else if(opcion == 5){
        *posibilidadGanar = !(*sEjeZ < 0 && *sEjeY < 0);
        *sEjeZ = (-1) * (*sEjeZ);
        *sEjeY = (-1) * (*sEjeY);
        *sEjeX = (-1) * (*sEjeX);
    }
}

bool Juego::verificarHorizontales(unsigned int x, unsigned int y, unsigned int z, Ficha* ficha){
    int opcion = 1, par = 1, signoEje = -1;
    bool posibilidadGanar = true, hayGanador;
    while(posibilidadGanar){
        hayGanador = true;
        int xConst = 1, yConst = 1, zConst = 1;
        if(opcion == 1){
        	yConst = zConst = 0;
        }
        else if(opcion == 2){
        	xConst = zConst = 0;
        }
        else if(opcion == 3){
        	xConst = yConst = 0;
        }
        for(int ejeActual = 3*signoEje; ejeActual > 0 || ejeActual < 0; ejeActual = ejeActual - signoEje){
            if(hayGanador && this->tablero->obtenerFicha(x + ejeActual*xConst, y + ejeActual*yConst,
                                                         z + ejeActual*zConst) != ficha){
                hayGanador = false;
            }
        }
        posibilidadGanar = !hayGanador;
        signoEje = (-1)*signoEje;
        par += 1;
        opcion = (1 + par)/ 2;
        if(opcion == 4 && posibilidadGanar){
            posibilidadGanar = false;
        }
    }
    return hayGanador;
}

Juego::~Juego(){
    delete this->tablero;
    this->jugadores->iniciarCursor();
    while( this->jugadores->avanzarCursor() ){
    	Jugador* jugadorAborrar = this->jugadores->getCursor();
    	delete jugadorAborrar;
    }
    delete this->jugadores;
}
