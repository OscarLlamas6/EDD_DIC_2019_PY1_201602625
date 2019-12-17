#include <iostream>
#include "NodoCircular.cpp"
#include <fstream>
using namespace std; 

class ListaCircular{

private:
    NodoCircular *primero;
    NodoCircular *ultimo;
    int size;

public:
    ListaCircular(){
        this->primero = 0;
        this->ultimo = 0;
        this->size = 0;
    }

    int getSize(){ return this->size; }
    bool estaVacia(){ return this->size==0; }
    NodoCircular *getPrimero(){ return this->primero; }
    NodoCircular *greater_equal(){ return this->ultimo; }

    void vinculo_Circular(){
        this->primero->setAnterior(this->ultimo);
        this->ultimo->setSiguiente(this->primero);
    }

    void insertar_inicio(Cancion_Circular *c){
        NodoCircular *n = new NodoCircular(c);
        if(this->estaVacia()){
            this->primero = n;
            this->ultimo = n;
            this->vinculo_Circular();
            this->size++;
        } else {
            n->setSiguiente(this->primero);
            this->primero->setAnterior(n);
            this->primero = n;
            this->vinculo_Circular();
            this->size++;
        }        
    }

    void insertar_final(Cancion_Circular *c){
        if(estaVacia()){
            this->insertar_inicio(c);
        }else {
            NodoCircular *n = new NodoCircular(c);
            this->ultimo->setSiguiente(n);
            n->setAnterior(this->ultimo);
            this->ultimo = n;
            this->vinculo_Circular();
            this->size++;
        }        
    }

};
