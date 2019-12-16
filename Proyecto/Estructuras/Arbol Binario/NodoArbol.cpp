#include <iostream>
using namespace std;

class Nodo{

private:
    int dato;
    Nodo *izquierda;
    Nodo *derecha;
public:
    Nodo(int dato){
        this->dato = dato;
        this->izquierda = 0;
        this->derecha = 0;
    }

    int getDato(){ return this->dato; }
    Nodo *getIzquierda(){ return this->izquierda; }
    Nodo  *getDerecha(){ return this->derecha; }

    void setDAto(int dato){ this->dato = dato;}
    void setIzquierda(Nodo *n){ this->izquierda=n; }
    void setDerecha(Nodo *n){ this->derecha=n; }

};
