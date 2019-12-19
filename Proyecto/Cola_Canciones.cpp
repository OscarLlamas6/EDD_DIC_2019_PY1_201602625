#include <iostream>
#include "NodoCola.cpp"
using namespace std;

class ColaCanciones{

private:
    NodoCola *frente;
    NodoCola *fin;
    int size;

public:
    ColaCanciones(){
        this->frente = 0;
        this->fin = 0;
        this->size = 0;
    }

    bool estaVacia(){ return this->size==0;}
    NodoCola *getFrente(){ return this->frente; }
    NodoCola *getFin(){ return this->fin; }
    int getSize(){ return this->size; }

    void enqueue(Cancion_Cola *c){
        NodoCola *n = new NodoCola(c);
        if(estaVacia()){
            this->frente = n;
        } else {
            this->fin->setSiguiente(n);
        }
        this->fin = n;
        this->size++;
    }

    void dequeue(){
        if(!estaVacia()){
            NodoCola *aux = frente;
            this->frente = frente->getSiguiente();
            delete aux;
            this->size--;
        }
    }





};