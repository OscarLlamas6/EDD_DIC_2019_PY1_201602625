#include <iostream>
#include "NodoArtista.cpp"
#include <fstream>
using namespace std; 

class ListaArtistas{

private:
    int size;
    NodoArtista *primero;
    NodoArtista *ultimo;
public:
    ListaArtistas(){
        this-> primero = 0;
        this-> ultimo = 0;
        this-> size = 0;
    }

int getSize(){ return this->size;}

bool estaVacia(){ return this->size==0;}

NodoArtista *getPrimero(){ return this->primero;}

NodoArtista *getUltimo(){ return this->ultimo; }

void insertar_inicio(string name, double rating){
    Artista *a = new Artista(name, rating);
    NodoArtista *n = new NodoArtista(a);
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

void insertar_final(string name, double rating){
    if(this->estaVacia()){
        this->insertar_inicio(name, rating);
    } else {
        Artista *a = new Artista(name, rating);
        NodoArtista *n = new NodoArtista(a);
        this->ultimo->setSiguiente(n);
        n->setAnterior(this->ultimo);
        this->ultimo = n;
        this->size++;
    }
}

void insertar_en(string name, double rating, int index){
    if(index >=0 && index <= this->size){
        if(index == 0){this->insertar_inicio(name, rating); return;}
        if(index == this->size){this->insertar_final(name, rating); return;}
        NodoArtista *aux = this->primero;
        int x = 0;
        while (aux!=0)
        {
            if(x == index){break;}
            aux = aux->getSiguiente();
            x++;
        }
        Artista *a = new Artista(name, rating);
        NodoArtista *n = new NodoArtista(a);
        aux->getAnterior()->setSiguiente(n);
        n->setAnterior(aux->getAnterior());
        n->setSiguiente(aux);
        aux->setAnterior(n);
        this->size++;       
    }   
}

void insertar_ordenado(string name, double rating){       
        if(this->estaVacia()){
            this->insertar_inicio(name, rating); return;
        }
        int index = 0;
        NodoArtista *aux = this->primero;
        while(aux!=0){
            if(name.compare(this->getPrimero()->getArtista()->getName()) == -1){ index=0; break;} //Ingresa al inicio
            if(name.compare(this->getUltimo()->getArtista()->getName()) == 1 || name.compare(this->getUltimo()->getArtista()->getName()) == 0){index=size; break;} //Ingresa al final
            if(name.compare(aux->getArtista()->getName()) == 1 || name.compare(this->getUltimo()->getArtista()->getName()) == 0){ index++;} //Busca la posición correcta
            if(name.compare(aux->getSiguiente()->getArtista()->getName()) == -1){ break;}                 
            aux = aux->getSiguiente();           
        }
        this->insertar_en(name, rating, index);        
}

NodoArtista *getArtista(string name){
    if(this->size==0){
        return 0;
    } else
    {
        NodoArtista *aux = this->primero;
        while(aux!=0){
            if(aux->getArtista()->getName().compare(name)==0){ return aux;}
            aux = aux->getSiguiente();
        }
    return 0;
    }    
}

NodoArtista *getArtista_Index(int index){
if(index>0 && index <=this->size){
        if(index == this->size){ return this->ultimo;}
         else {
            NodoArtista *aux = this->primero;
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


