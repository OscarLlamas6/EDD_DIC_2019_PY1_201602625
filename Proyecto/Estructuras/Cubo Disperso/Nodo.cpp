#include <iostream>
#include <fstream>
using namespace std; 

class Nodo{

private:
    Nodo *izquierda;
    Nodo *derecha;
    Nodo *arriba;
    Nodo *abajo;
    Nodo *adelante;
    Nodo *atras;
    int dato;
    int x;
    int y;

public:
    Nodo(int x, int y, int dato){
        this->dato = dato;
        this->x = x;
        this->y = y;
        this->izquierda = 0;
        this->derecha = 0;
        this->arriba = 0;
        this->abajo = 0;
        this->adelante = 0;
        this->atras = 0;
    }
    //////SETTERS
    void setIzquierda(Nodo *n){ this->izquierda = n;}
    void setDerecha(Nodo *n){ this->derecha = n;}
    void setArriba(Nodo *n){ this->arriba = n;}
    void setAbajo(Nodo *n){ this->abajo = n;}
    void setAdelante(Nodo *n){ this->adelante = n;}
    void setAtras(Nodo *n){ this->atras = n;}
    //////GETTERS
    int getDato(){ return this->dato; }
    int getX(){ return this->x; }
    int getY(){ return this->y; }
    Nodo *getIzquierda(){ return this->izquierda; }
    Nodo *getDerecha(){ return this->derecha; }
    Nodo *getArriba(){ return this->arriba; }
    Nodo *getAbajo(){ return this->abajo; }
    Nodo *getAdelante(){ return this->adelante; }
    Nodo *getAtras(){ return this->atras; }
};