#include <iostream>
#include <fstream>
#include "CancionPila.cpp"
using namespace std;

class NodoPila {

private:
    NodoPila *siguiente;
    Cancion_Pila *song;
public:
    NodoPila(Cancion_Pila *c){
        this->siguiente = 0;
        this->song = c;
    }

    void setSiguiente(NodoPila *n){ this->siguiente = n; }
    NodoPila *getSiguiente(){ return this->siguiente; }
    Cancion_Pila *getCancion(){ return this->song; }

};
