#include <iostream>
#include <fstream>
#include "AlbumOrdenado.cpp"
using namespace std; 

class NodoAlbumOrdenado{

private:
    NodoAlbumOrdenado *siguiente;
    AlbumOrdenado *album;
public:
    NodoAlbumOrdenado( AlbumOrdenado *a ){
        this->album = a; 
        this->siguiente = 0;
    }

    AlbumOrdenado *getAlbum(){ return this->album; }
    void setSiguiente(NodoAlbumOrdenado *n){ this->siguiente = n; }
    NodoAlbumOrdenado *getSiguiente(){ return this->siguiente; }

};