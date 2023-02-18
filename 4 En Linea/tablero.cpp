#include "tablero.h"

Tablero::Tablero(unsigned int x, unsigned int y, unsigned int z){
    if(x < 1 || y < 1 || z < 1){
        throw std::string("X, Y, Z deben ser mayor a 0.");
    }
    this->dimensionX = x;
    this->dimensionY = y;
    this->dimensionZ = z;
    this->casillerosDisponibles = x*y*z;
    this->ejeZ = new tercerEje;
    this->crearTablero();
}

void Tablero::crearTablero(){
    segundoEje* ejeX;
    primerEje* ejeY;
    for(unsigned int k = 0; k < this->dimensionZ; k++){
        ejeX = new segundoEje;
        for(unsigned int i = 0; i < this->dimensionX; i++){
            ejeY = new primerEje;
            for(unsigned int j = 0; j < this->dimensionY; j++){
                ejeY->agregar(0);
            }
            ejeX->agregar(ejeY);
        }
        this->ejeZ->agregar(ejeX);
    }
}

unsigned int Tablero::obtenerDimensionEnX(){
    return this->dimensionX;
}

unsigned int Tablero::obtenerDimensionEnY(){
    return this->dimensionY;
}

unsigned int Tablero::obtenerDimensionEnZ(){
    return this->dimensionZ;
}

void Tablero::cambiarTablaDeColor(BMP& InputImage, Ficha* ficha){
    int BitDepth = InputImage.TellBitDepth();
    if( BitDepth != 1 && BitDepth != 4 && BitDepth != 8 ){
        return;
    }
    unsigned int NumberOfColors = IntPow(2,BitDepth);
    for(unsigned int i=0 ; i < NumberOfColors ; i++){
        RGBApixel Temp;
        Temp.Red = i * ficha->obtenerTempRed();
        Temp.Green = i * ficha->obtenerTempGreen();
        Temp.Blue = i * ficha->obtenerTempBlue();
        Temp.Alpha = 1;
        InputImage.SetColor(i,Temp);
    }
}

void Tablero::imprimirTablero(unsigned int x, unsigned int y, unsigned int z){
    int casillero = 100;
    bool posicionValidaEnX, ignorarCasilleroVacio;
    primerEje* ejeY;
    segundoEje* ejeX;
    BMP casilleroActual, tableroCentrado, fichaColoreada;
    tableroCentrado.ReadFromFile("4 en linea.bmp");
    tableroCentrado.SetBitDepth(8);
    if(validarPosicion(x, y, z)){
        this->ejeZ->posicionarCursor(z);
        ejeX = this->ejeZ->getCursor();
        for(int i = -3; i <= 3; i++){
            if(ejeX->posicionarCursor(x + i)){
            	posicionValidaEnX = true;
                ejeY = ejeX->getCursor();
            }else{
            	posicionValidaEnX = false;
            }
            for(int j = -3; j <= 3; j++){
            	ignorarCasilleroVacio = false;
                if(posicionValidaEnX && ejeY->posicionarCursor(y + j) ){
                	if(ejeY->getCursor()){
                        Ficha* fichaActual = ejeY->getCursor();
                        fichaColoreada.ReadFromFile("ficha.bmp");
                        this->cambiarTablaDeColor(fichaColoreada , fichaActual);
                        fichaColoreada.WriteToFile("ficha coloreada.bmp");
                        casilleroActual.ReadFromFile("ficha coloreada.bmp");
                	}else{
                    	ignorarCasilleroVacio = true;
                	}
                }else{
                    casilleroActual.ReadFromFile("posicion invalida.bmp");
                }
                if(i == 0 && j == 0){
                    RangedPixelToPixelCopy( casilleroActual, 0, casilleroActual.TellWidth()-1,
                                           casilleroActual.TellHeight()-1 , 0,
                                           tableroCentrado, 900, 400);
                }
                if(!ignorarCasilleroVacio){
                    RangedPixelToPixelCopy( casilleroActual, 0, casilleroActual.TellWidth()-1,
                    casilleroActual.TellHeight()-1 , 0,
                    tableroCentrado, casillero * (i+4), casillero * (-j+4) );
                }
            }
        }
        tableroCentrado.WriteToFile( "Ultima ficha colocada.bmp" );
    }
    this->ejeZ->iniciarCursor();
}

unsigned int Tablero::colocarFicha(unsigned int xElegido,unsigned int yElegido, Ficha* ficha){
    unsigned int zColocado = 0;
    if(this->validarPosicion(xElegido, yElegido, this->dimensionZ)){
        this->ejeZ->iniciarCursor();
        for(unsigned int k = 0; k < this->dimensionZ; k++){
            this->ejeZ->avanzarCursor();
            segundoEje* ejeX = ejeZ->getCursor();
            ejeX->iniciarCursor();
            for(unsigned int i = 0; i < xElegido; i++){
                ejeX->avanzarCursor();
            }
            primerEje* ejeY = ejeX->getCursor();
            ejeY->iniciarCursor();
            for(unsigned int j = 0; j < yElegido; j++){
                ejeY->avanzarCursor();
            }
            bool casilleroEstaDisponible = !( ejeY->getCursor() );
            if(casilleroEstaDisponible){ // porque el tablero vacio tiene ceros
                ejeY->setCursor(ficha);
                zColocado = k + 1;
                k = this->dimensionZ; // corta el ciclo
                casillerosDisponibles -= 1;
            }
        }
    }
    return zColocado;
}

bool Tablero::estaLleno(){
    return (casillerosDisponibles == 0);
}

void Tablero::modificarCasillero(unsigned int x, unsigned int y, unsigned int z, Ficha* ficha){
    if( this->validarPosicion(x, y, z) ){
        this->ejeZ->posicionarCursor(z);
        segundoEje* ejeX = ejeZ->getCursor();
        ejeX->posicionarCursor(x);
        primerEje* ejeY = ejeX->getCursor();
        ejeY->posicionarCursor(y);
        ejeY->setCursor(ficha);
    }
}

Ficha* Tablero::obtenerFicha(unsigned int x, unsigned int y, unsigned int z){
    Ficha* fichaBuscada = 0;
    if( this->validarPosicion(x, y, z) ){
        this->ejeZ->posicionarCursor(z);
        segundoEje* ejeX = this->ejeZ->getCursor();
        ejeX->posicionarCursor(x);
        primerEje* ejeY = ejeX->getCursor();
        ejeY->posicionarCursor(y);
        fichaBuscada = ejeY->getCursor();
    }
    return fichaBuscada;
}

bool Tablero::validarPosicion(unsigned int xValidar, unsigned int yValidar, unsigned int zValidar){
    bool validar = false;
    if(xValidar <= this->dimensionX && yValidar <= this->dimensionY && zValidar <= this->dimensionZ
        && xValidar > 0 && yValidar > 0 && zValidar > 0){
        validar = true;
    }
    return validar;
}

Tablero::~Tablero(){
    segundoEje* ejeX;
    primerEje* ejeY;
    ejeZ->iniciarCursor();
    while(ejeZ->avanzarCursor()){
        ejeX = ejeZ->getCursor();
        ejeX->iniciarCursor();
        while(ejeX->avanzarCursor()){
            ejeY = ejeX->getCursor();
            delete ejeY;
        }
        delete ejeX;
    }
    delete ejeZ;
}
