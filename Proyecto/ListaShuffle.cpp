#include <iostream>
#include "NodoShuffle.cpp"
#include <fstream>
using namespace std; 

class ListaShuffle{

private:
    int size;
    NodoShuffle *primero;
    NodoShuffle *ultimo;
public:
    ListaShuffle(){
        this-> primero = 0;
        this-> ultimo = 0;
        this-> size = 0;
    }

int getSize(){ return this->size;}

bool estaVacia(){ return this->size==0;}

NodoShuffle *getPrimero(){ return this->primero;}

NodoShuffle *getUltimo(){ return this->ultimo; }

void insertar_inicio(Cancion_Shuffle *c){
    NodoShuffle *n = new NodoShuffle(c);
    if(this->estaVacia()){
        this->primero = n;
        this->ultimo = n;
        this->size++;
    } else {
        n->setSiguiente(this->primero);
        this->primero->setAnterior(n);
        this->primero = n;
        this->size++;
    }
}

void insertar_final(Cancion_Shuffle *c){
    if(this->estaVacia()){
        this->insertar_inicio(c);
    } else {
        NodoShuffle *n = new NodoShuffle(c);
        this->ultimo->setSiguiente(n);
        n->setAnterior(this->ultimo);
        this->ultimo = n;
        this->size++;
    }
}

void insertar_en(Cancion_Shuffle *c, int index){
    if(index >=0 && index <= this->size){
        if(index == 0){this->insertar_inicio(c); return;}
        if(index == this->size){this->insertar_final(c); return;}
        NodoShuffle *aux = this->primero;
        int x = 0;
        while (aux!=0)
        {
            if(x == index){break;}
            aux = aux->getSiguiente();
            x++;
        }
        NodoShuffle *n = new NodoShuffle(c);
        aux->getAnterior()->setSiguiente(n);
        n->setAnterior(aux->getAnterior());
        n->setSiguiente(aux);
        aux->setAnterior(n);
        this->size++;       
    }   
}


NodoShuffle *getCancion(string name){
    if(this->size==0){
        return 0;
    } else
    {
        NodoShuffle *aux = this->primero;
        while(aux!=0){
            if(aux->getCancion()->getName().compare(name)==0){ return aux;}
            aux = aux->getSiguiente();
        }
    return 0;
    }    
}

NodoShuffle *getCancion_Index(int index){
if(index>0 && index <=this->size){
        if(index == this->size){ return this->ultimo;}
         else {
            NodoShuffle *aux = this->primero;
            int x = 1;
            while(aux!=0){
                if(x == index){ break;}
                aux = aux->getSiguiente();
                x++;
            }
            return aux;
            }              
       } else {return 0;}
}

};


