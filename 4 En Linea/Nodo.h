#ifndef NODO_H_
#define NODO_H_

#ifndef NULL
#define NULL 0
#endif

template<class T>
class Nodo{
private:
    T dato;
    Nodo<T>* anterior;
    Nodo<T>* siguiente;

public:
    /*
     * post: Nodo inicializado con dato y siguiente NULL.
     */
    Nodo(T dato){
        this->dato = dato;
        this->anterior = NULL;
        this->siguiente = NULL;
    }

    /*
     * post: Nodo inicializado con dato y un puntero a un Nodo siguiente.
     */
    Nodo(T dato, Nodo* nodoSiguiente, Nodo* nodoAnterior){
        this->dato = dato;
        this->anterior = nodoAnterior;
        this->siguiente = nodoSiguiente;
    }

    /*
     * post: Devuelve el valor del dato.
     */
    T getDato(){
        return this->dato;
    }

    /*
     * post: Cambia el valor del dato.
     */
    void setDato(T nuevoDato){
        this->dato =  nuevoDato;
    }

    /*
     * post: Devuelve el siguiente Nodo.
     */
    Nodo<T>* getSiguiente(){
        return this->siguiente;
    }


    /*
     * post: Devuelve el Nodo anterior.
     */
    Nodo<T>* getAnterior(){
        return this->anterior;
    }

    /*
     * post: Cambia el siguiente Nodo por nuevoSiguiente.
     */
    void setSiguiente(Nodo<T>* nuevoSiguiente){
        this->siguiente = nuevoSiguiente;
    }

    /*
    * post: Cambia el anterior Nodo por nuevoAnterior.
    */
    void setAnterior(Nodo<T>* nuevoAnterior){
        this->anterior = nuevoAnterior;
    }
};

#endif // NODO_H_
