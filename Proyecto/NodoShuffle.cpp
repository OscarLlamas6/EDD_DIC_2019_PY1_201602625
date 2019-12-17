#include <iostream>
#include "CancionShuffle.cpp"
using namespace std; 

class NodoShuffle{

public:
    NodoShuffle(Cancion_Shuffle *c){
        this->song = c;
        this->siguiente = 0;
        this->anterior = 0;
    }
    Cancion_Shuffle *getCancion(){return this->song;}
    void setSiguiente(NodoShuffle *n){ this->siguiente = n;}
    void setAnterior(NodoShuffle *n){this->anterior = n;}
    NodoShuffle *getSiguiente(){return this->siguiente;}
    NodoShuffle *getAnterior(){return this->anterior;}

private:
    NodoShuffle *siguiente;
    NodoShuffle *anterior;
    Cancion_Shuffle *song;
};