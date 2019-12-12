#include <iostream>
#include "Cancion.cpp"
using namespace std; 

class NodoCancion{

private:
    NodoCancion *siguiente;
    Cancion *song;
public:
    NodoCancion(Cancion *c){
        this->song = c;
        this->siguiente = 0;
    }

    Cancion *getCancion(){ return this->song; }
    void setSiguiente(NodoCancion *n){ this->siguiente = n; }
    NodoCancion *getSiguiente(){ return this->siguiente; }

};