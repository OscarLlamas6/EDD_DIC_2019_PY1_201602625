#include <iostream>
#include "NodoPila.cpp"
using namespace std;

class PilaCanciones{

private:
    NodoPila *cima;
    int size;

public:
    PilaCanciones(){
        this->cima = 0;
        this->size = 0;
    }

    bool estaVacia(){ return this->size==0; }
    int getSize(){ return this->size; }
    NodoPila *getCima(){ return this->cima; }

    void push(Cancion_Pila *c){
        NodoPila *n = new NodoPila(c);
        if(estaVacia()){
            this->cima = n;
            this->size++;
        } else {
            n->setSiguiente(this->cima);
            this->cima = n;
            this->size++;
        }
    }

    void pop(){
        NodoPila *aux = this->cima;
        this->cima = this->cima->getSiguiente();
        delete aux;
        this->size--;
        
    }

};