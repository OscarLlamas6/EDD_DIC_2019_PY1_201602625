#include <iostream>
#include <fstream>
#include "CancionOrdenada.cpp"
using namespace std; 

class NodoCancionOrdenado{

private:
    NodoCancionOrdenado *siguiente;
    SongOrdenada *song;
public:
    NodoCancionOrdenado( SongOrdenada *c ){
        this->song = c; 
        this->siguiente = 0;
    }

    SongOrdenada *getCancion(){ return this->song; }
    void setSiguiente(NodoCancionOrdenado *n){ this->siguiente = n; }
    NodoCancionOrdenado *getSiguiente(){ return this->siguiente; }

};