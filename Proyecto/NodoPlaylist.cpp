#include <iostream>
#include "Playlist.cpp"
using namespace std;

class NodoPlaylist{

private:
    Playlist *playlist;
    NodoPlaylist *izquierda;
    NodoPlaylist *derecha;
public:
    NodoPlaylist(Playlist *p){
        this->playlist = p;
        this->izquierda = 0;
        this->derecha = 0;
    }

    Playlist *getPlaylist(){ return this->playlist; }
    NodoPlaylist *getIzquierda(){ return this->izquierda; }
    NodoPlaylist  *getDerecha(){ return this->derecha; }

    void setPlaylist(Playlist *p){ this->playlist = p;}
    void setIzquierda(NodoPlaylist *n){ this->izquierda=n; }
    void setDerecha(NodoPlaylist *n){ this->derecha=n; }

};
