#include <iostream>
#include "CancionCircular.cpp"
using namespace std; 

class NodoCircular{

public:
    NodoCircular(Cancion_Circular *c){
        this->song = c;
        this->siguiente = 0;
        this->anterior = 0;
    }
    Cancion_Circular *getCancion(){return this->song;}
    void setSiguiente(NodoCircular *n){ this->siguiente = n;}
    void setAnterior(NodoCircular *n){this->anterior = n;}
    NodoCircular *getSiguiente(){return this->siguiente;}
    NodoCircular *getAnterior(){return this->anterior;}

private:
    NodoCircular *siguiente;
    NodoCircular *anterior;
    Cancion_Circular *song;
};