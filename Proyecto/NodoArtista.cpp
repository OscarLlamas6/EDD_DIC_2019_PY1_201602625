#include <iostream>
#include "Artista.cpp"
using namespace std; 

class NodoArtista{

public:
    NodoArtista(Artista *a){
        this->artist = a;
        this->siguiente = 0;
        this->anterior = 0;
    }
    Artista *getArtista(){return this->artist;}
    void setSiguiente(NodoArtista *n){ this->siguiente = n;}
    void setAnterior(NodoArtista *n){this->anterior = n;}
    NodoArtista *getSiguiente(){return this->siguiente;}
    NodoArtista *getAnterior(){return this->anterior;}

private:
    NodoArtista *siguiente;
    NodoArtista *anterior;
    Artista *artist;
};