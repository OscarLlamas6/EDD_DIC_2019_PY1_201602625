#include <iostream>
#include "ArtistaRating.cpp"
using namespace std; 

class NodoArtistaRating{

public:
    NodoArtistaRating(ArtistaRating *a){
        this->artist = a;
        this->siguiente = 0;
        this->anterior = 0;
    }
    ArtistaRating *getArtista(){return this->artist;}
    void setSiguiente(NodoArtistaRating *n){ this->siguiente = n;}
    void setAnterior(NodoArtistaRating *n){this->anterior = n;}
    NodoArtistaRating *getSiguiente(){return this->siguiente;}
    NodoArtistaRating *getAnterior(){return this->anterior;}

private:
    NodoArtistaRating *siguiente;
    NodoArtistaRating *anterior;
    ArtistaRating *artist;
};