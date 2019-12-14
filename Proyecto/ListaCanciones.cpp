#include <iostream>
#include <iostream>
#include <fstream>
#include "NodoCancion.cpp"
using namespace std; 

class ListaCanciones{

private:
    int size;
    NodoCancion *primero;
    NodoCancion *ultimo;
public:
    ListaCanciones(){
        this->primero = 0;
        this->ultimo = 0;
        this->size = 0;
    }
    
    NodoCancion *getPrimero(){ return this->primero; }
    NodoCancion *getUltimo(){ return this->ultimo; }
    int getSize(){ return this->size;}
    bool estaVacia(){ return this->size==0;}

    void insertar(string name, string album, string artista, double rating){
        Song *c = new Song(name, album, artista, rating);
        NodoCancion *n = new NodoCancion(c);
        if(this->estaVacia()){
            this->primero = n;
            this->ultimo = n;
            this->size++;
        } else {
            this->ultimo->setSiguiente(n);
            this->ultimo = n;
            size++;
        }
    }

    double CalculateRating(){
        double result = 0;
        NodoCancion *aux = this->primero;
        while(aux!=0){
        result+=aux->getCancion()->getRating();
        aux = aux->getSiguiente();
        }
        double d = (double)this->size;
        result = result / d;
        return result;
    }

};