#ifndef LISTA_ENLAZADA_H_
#define LISTA_ENLAZADA_H_

#include "Nodo.h"
#ifndef NULL
#define NULL 0
#endif

template<class T>
class Lista{
private:
    Nodo<T>* ultimo;
    Nodo<T>* primero;
    unsigned int tamanio;
    Nodo<T>* cursor;
    unsigned int cursorPosicionActual;

    /*
     * pre: Posicion pertenece al intervalo: [1, contarElementos()]
     * post: Devuelve el Nodo en la posicion indicada.
     */
    Nodo<T>* getNodo(unsigned int posicion);

public:
    /*
     * post: Lista vacia.
     */
    Lista();

    /*
     * post: Lista identica a la Lista pasada por argumento.
     */
    Lista(Lista<T> &otraLista);

    /*
     * post: Indica si la Lista tiene algun elemento.
     */
    bool estaVacia();

    /*
     * post: Devuelve la cantidad de elementos que tiene la Lista.
     */
    unsigned int contarElementos();

    /*
     * post: Agrega elemento al final de la Lista, posicion contarElementos()+1
     */
    void agregar(T elemento);

    /*
     * pre: Posicion pertenece al intervalo: [1, contarElementos()+1]
     * post: Agrega el elemento en la posicion indicada.
     */
    void agregar(T elemento, unsigned int posicion);

    /*
     * post: Agrega todos los elementos de otra lista a partir de la
     * 		 posicion contarElementos()+1
     */
    void agregar(Lista<T> &otraLista);

    /*
     * pre: Posicion pertenece al intervalo: [1, contarElementos()]
     * post: Devuelve el elemento en la posicion indicada.
     */
    T getElemento(unsigned int posicion);

    /*
     * pre: Posicion pertenece al intervalo: [1, contarElementos()]
     * post: Cambia elemento de posicion indicada por elemento pasado.
     */
    void setElemento(T* elemento, unsigned int posicion);

    /*
     * pre: Posicion pertenece al intervalo: [1, contarElementos()]
     * post: Cambia elemento de posicion indicada por elemento pasado.
     */
    void remover(unsigned int posicion);

    /*
     * post: Deja cursor de Lista preparado para hacer nuevo recorrido.
     */
    void iniciarCursor();

    /*
     * El metodo avanzar cursor permite el movimiento de un nodo al
     * siguiente usando el cursor.
     * pre: Se ha iniciado un recorrido (invocando el metodo iniciarCursor().
     * post: Mueve el cursor, lo posiciona en el siguiente elemento del recorrido.
     * 		 El valor de retorno indica si el cursor quedo posicionado sobre un
     * 		 elemento o no (em caso de que la Lista este vacia o no existan mas
     * 		 elementos por recorrer.)
     */
    bool avanzarCursor();

    /*
     * pre: Se ha iniciado un recorrido (invocando el metodo iniciarCursor()
     * post: Mueve el cursor, lo posiciona en el anterior elemento del recorrido.
     * 		 El valor de retorno indica si el cursor quedo posicionado sobre un
     * 		 elemento o no (em caso de que la Lista este vacia o no existan mas
     * 		 elementos por recorrer.)
     */
    bool retrocederCursor();

    /*
     * post: Incia el cursor si es que no fue iniciado y lo posiciona
     *       en la posicion recibida, si la posicion no pertenece al
     *       intervalo: [1, contarElementos()] devuelve false y no
     *       se realiza ningun movimiento sobre el cursor.
     */
    bool posicionarCursor(unsigned int posicion);

    /*
     * pre: El cursor esta posicionado sobre un elemento de la Lista
     * 		(fue invocado el metodo avanzarCursor() y devolvio true).
     * post: Devuelve el elemento en la posicion del cursor.
     */
    T getCursor();


    /*
     * pre: El cursor esta posicionado sobre un elemento de la Lista
     * 		(fue invocado el metodo avanzarCursor() y devolvio true)y
     *      el nuevoDato es del mismo tipo que el anterior dato.
     * post: Se modifica el dato en la posicion del cursor con el nuevoDato.
     */
    void setCursor(T nuevoDato);

    /*
     * post: libera los recursos asociados a la Lista.
     */
    ~Lista();
};

template<class T>
Lista<T>::Lista(){
    this->primero = NULL;
    this->ultimo = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
    this->cursorPosicionActual = 0;
}

template<class T>
Lista<T>::Lista(Lista<T> &otraLista){
    this->ultimo = NULL;
    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
    this->cursorPosicionActual = 0;
    this->agregar(otraLista);
}

template<class T>
bool Lista<T>::estaVacia(){
    return (this->tamanio == 0);
}

template<class T>
unsigned int Lista<T>::contarElementos(){
    return this->tamanio;
}

template<class T>
void Lista<T>::agregar(T elemento){
    this->agregar(elemento, this->tamanio+1);
}

template<class T>
void Lista<T>::agregar(T elemento, unsigned int posicion){
    if((posicion > 0)&&(posicion <= this->tamanio+1)){
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        if(posicion == 1){
            nuevo->setSiguiente(this->primero);
            if(this->primero != NULL){
                this->primero->setAnterior(nuevo);
            }else{
            	this->ultimo = nuevo;
            }
            this->primero = nuevo;
        }else if(posicion == this->tamanio + 1){
            this->ultimo->setSiguiente(nuevo);
            nuevo->setAnterior(this->ultimo);
            this->ultimo = nuevo;
        }else{
            Nodo<T>* anterior = this->getNodo(posicion-1);
            anterior->getSiguiente()->setAnterior(nuevo);
            nuevo->setSiguiente(anterior->getSiguiente());
            nuevo->setAnterior(anterior);
            anterior->setSiguiente(nuevo);
        }
        this->tamanio++;
        this->iniciarCursor();
        this->cursorPosicionActual = 0;
    }
}

template<class T>
void Lista<T>::agregar(Lista<T> &otraLista){
    otraLista.iniciarCursor();
    while(otraLista.avanzarCursor()){
        this->agregar(otraLista.getCursor());
    }
}

template<class T>
T Lista<T>::getElemento(unsigned int posicion){
    T elemento;
    if((posicion > 0)&&(posicion <= this->tamanio)){
       elemento = this->getNodo(posicion)->getDato();
       }
    return elemento;
}

template<class T>
void Lista<T>::setElemento(T* elemento, unsigned int posicion){
    if((posicion > 0)&&(posicion <= this->tamanio)){
        this->getNodo(posicion)->setDato(elemento);
    }
}

template<class T>
void Lista<T>::remover(unsigned int posicion){
    if((posicion > 0)&&(posicion <= this->tamanio)){
        Nodo<T>* removido;
        if(posicion == 1){
            removido = this->primero;
            if(this->primero->getSiguiente() == NULL){
                this->ultimo = this->primero;
            }else{
                removido->getSiguiente()->setAnterior(NULL);
            }
            this->primero = removido->getSiguiente();
        }else if(posicion == this->tamanio){
            removido = this->ultimo;
            this->ultimo = this->ultimo->getAnterior();
            this->ultimo->setSiguiente(NULL);
        }else{
            Nodo<T>* anterior = this->getNodo(posicion-1);
            removido = anterior->getSiguiente();
            removido->getSiguiente()->setAnterior(anterior);
            anterior->setSiguiente(removido->getSiguiente());
        }
        delete removido;
        this->tamanio--;
        this->iniciarCursor();
        this->cursorPosicionActual = 0;
    }
}

template<class T>
void Lista<T>::iniciarCursor(){
    this->cursor = NULL;
}

template<class T>
bool Lista<T>::avanzarCursor(){
    if(this->cursor == NULL){
        this->cursor = this->primero;
        if(this->cursor != NULL){
            this->cursorPosicionActual = 1;
        }else{
            this->cursorPosicionActual = 0;
        }
    }else{
        this->cursor = this->cursor->getSiguiente();
        if(this->cursor != NULL){
            this->cursorPosicionActual += 1;
        }else{
            this->cursorPosicionActual = 0;
        }
    }
    return (this->cursor != NULL);
}

template<class T>
bool Lista<T>::retrocederCursor(){
    if(this->cursor != NULL){
        this->cursor = this->cursor->getAnterior();
        if(cursor != NULL){
            cursorPosicionActual -= 1;
        }else{
            cursorPosicionActual = 0;
        }
    }
    return (this->cursor != NULL);
}

template<class T>
bool Lista<T>::posicionarCursor(unsigned int posicion){
    bool posicionValida = false;
    if(posicion <= this->tamanio && posicion > this->cursorPosicionActual){
        if( (this->tamanio - this->cursorPosicionActual) / 2 + this->cursorPosicionActual < posicion){
            this->cursor = this->ultimo;
            this->cursorPosicionActual = this->tamanio;
            for(unsigned int i = this->tamanio; i > posicion; i--){
                this->retrocederCursor();
            }
        }else{
            for(unsigned int i = this->cursorPosicionActual; i < posicion; i++){
                this->avanzarCursor();
            }
        }
        posicionValida = true;
    }
    else if(posicion > 0 && posicion < this->cursorPosicionActual){
        if( this->cursorPosicionActual / 2 >= posicion){
            this->iniciarCursor();
            this->cursorPosicionActual = 0;
            for(unsigned int i = 0; i < posicion; i++){
                this->avanzarCursor();
            }
        }else{
            for(unsigned int i = this->cursorPosicionActual; i > posicion; i--){
                this->retrocederCursor();
            }
        }
        posicionValida = true;
    }else if(this->cursorPosicionActual > 0 && this->cursorPosicionActual == posicion){
    	posicionValida = true;
    }
    return posicionValida;
}

template<class T>
T Lista<T>::getCursor(){
    T elemento;
    if(this->cursor != NULL){
        elemento = this->cursor->getDato();
    }
    return elemento;
}

template<class T>
void Lista<T>::setCursor(T nuevoDato){
    this->cursor->setDato(nuevoDato);
}

template<class T>
Nodo<T>* Lista<T>::getNodo(unsigned int posicion){
    Nodo<T>* actual = this->primero;
    for(unsigned int i = 1; i < posicion; i++){
        actual = actual->getSiguiente();
    }
    return actual;
}

template<class T>
Lista<T>::~Lista(){
    while(this->primero != NULL){
        Nodo<T>* aBorrar = this->primero;
        this->primero = this->primero->getSiguiente();
        delete aBorrar;
    }
}

#endif // LISTA_ENLAZADA_H_
