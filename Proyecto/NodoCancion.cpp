
#include <iostream>
#include <fstream>
#include "Cancion.cpp"
using namespace std; 

class NodoCancion{

private:
    NodoCancion *siguiente;
    Song *song;
public:
    NodoCancion( Song *c ){
        this->song = c; 
        this->siguiente = 0;
    }

    Song *getCancion(){ return this->song; }
    void setSiguiente(NodoCancion *n){ this->siguiente = n; }
    NodoCancion *getSiguiente(){ return this->siguiente; }

};