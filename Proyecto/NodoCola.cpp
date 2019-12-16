#include <iostream>
#include <fstream>
#include "CancionCola.cpp"
using namespace std; 

class NodoCola {

private:
    NodoCola *siguiente;
    Cancion_Cola *song;
public:
    NodoCola(Cancion_Cola *c){
        this->siguiente = 0;
        this->song = c;
    }

    void setSiguiente(NodoCola *n){ this->siguiente = n;}
    NodoCola *getSiguiente(){ return this->siguiente; }
    Cancion_Cola *getCancion(){ return this->song; }
};