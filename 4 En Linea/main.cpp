#include <iostream>
#include <cctype>
#include <string>
#include "juego.h"

using namespace std;


int main(){
    char centinela;
    do{
    	int dificultadElegida, cartaElegida = 0;
    	Juego* juegoActual;
    	bool seJugoLaCarta;
    	char opcionElegida;
        unsigned int x, y, z, nJugadores;
        string ganador = "NONE";
        cout << "BIENBENIDO A 4 EN LIENA EN 3D\n" << endl;
        cout << "Para ganar debe formar una linea de 4 en cualquier direccion.\n" <<
        		"Al final de carta turno el jugador tiene una posibilidad de recibir uno de los 4 tipos de \n"
        		"carta de poder: 1 - Cambio de color, 2 - Destruir, 3 - Intercambio, 4 - Ignorar " << endl;
        cout << "Existen 2 iveles de dificultad: " << endl;
        cout << "Nivel 1) Se comprabara si hay un ganador al termino de cada turno.\n" <<
                "Nivel 2) La comprabacion del ganador se realiza despues de que todos los jugadores hallan \n"
                "completado su turno." << endl;
        cout << "Las dimensiones minimas para un tablero son 4x4x4 y la cantidad de jugadores debe ser al menos 2.\n";
        cout << "Para crear un tablero predefinido de 7x7x7 para 2 jugadores y nivel de dificultad 1 ingrese 's': ";
        cin >> opcionElegida;
        opcionElegida = tolower(opcionElegida);
        if(opcionElegida == 's'){
            juegoActual = new Juego;
            cout << "Se creara un tablero de 7x7x7 para 2 jugadores con un nivel de dificultad 1." << endl;
            nJugadores = 2;
        }else{

        	cout << "Elija un nivel de difultadad: " << endl;
        	cin >> dificultadElegida;
            cout << "Ingrese cantidad jugadores: " << endl;
            cin >> nJugadores;
            cout << "Ingrese las dimensiones del tablero 3D." << endl;
            cout << "Ancho (x): " << endl;
            cin >> x;
            cout << "Largo (y): " << endl;
            cin >> y;
            cout << "Alto (z): " << endl;
            cin >> z;
            if(x < 5 || y < 5 || z < 5 || nJugadores < 2 || dificultadElegida < 1 || dificultadElegida > 2){
                juegoActual = new Juego;
                cout << "Algun valor igresado no es valido.\n" <<
                		"Se creara un tablero de 7x7x7 para 2 jugadores con un nivel de dificultad 1." << endl;
            }else{
                juegoActual = new Juego(x, y, z, nJugadores, dificultadElegida);
            }
        }
        cout << endl;
        for ( unsigned int i = 0; i < nJugadores; i++){
            string nombreJugador;
            cout << "Ingrese un nombre: ";
            cin >> nombreJugador;
            Jugador* jugadorActual = new Jugador(nombreJugador);
            juegoActual->agregarJugador(jugadorActual);
            cout << "Numero de jugador: " << jugadorActual->obtenerNumeroDeJugador() << "\n" << endl;
        }
        cout << "-------------------------------------------------------------------------------------------" << endl;
        do{
            bool seJugoElTurno = true;
            long xElegido, yElegido;
            Jugador* jugadorActual = juegoActual->obtenerTurnoDeJugadorActual();
            cout << "\n" << jugadorActual->obtenerNombre() << " - Jugador: "
                    << jugadorActual->obtenerNumeroDeJugador() << endl;
            if(juegoActual->obtenerTurnosJugados() >= nJugadores  && jugadorActual->mostrarCartasDePoderDisponible() ){
            	do{
            		seJugoLaCarta = true;
					cout << "Ingrese un tipo de Carta para jugar o '0' para continuar: ";
					cin >> cartaElegida;
					if(cartaElegida != 0 && !jugadorActual->jugarCartaDePoder(cartaElegida) ){
							cout << "No se pudo jugar la Carta." << endl;
							seJugoLaCarta = false;
					}
            	}while (cartaElegida != 0 && !seJugoLaCarta);
             }
            do{
                if (!seJugoElTurno){
                    cout << "\nPoscion invalida." << endl;
                }
                cout << "Ingrese x: ";
                cin >> xElegido;
                cout << "Ingrese y: ";
                cin >> yElegido;
                seJugoElTurno = juegoActual->jugarFicha(xElegido, yElegido);
            }while (!seJugoElTurno);
            juegoActual->imprimirEstadoActualDelJuego();
        }while (!juegoActual->terminarTurno());
        if(juegoActual->obtenerGanador() != "EMPATE"){
            cout << juegoActual->obtenerGanador() << " es el GANADOR.\n" << endl;
        }
        else{
            cout << juegoActual->obtenerGanador();
        }
        delete juegoActual;
        cout << "Para volver a jugar ingrese 's' o cualquier tecla para terminar: ";
        cin >> centinela;
        centinela = tolower(centinela);
        cout << "\n\n\n" << endl;
    }while(centinela == 's');
    return 0;
}
