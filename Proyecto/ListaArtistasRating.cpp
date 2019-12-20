#include <iostream>
#include <iostream>
#include <fstream>
#include "NodoArtistaRating.cpp"
using namespace std; 

class ListaArtistasRating{

private:
    int size;
    NodoArtistaRating *primero;
    NodoArtistaRating *ultimo;
public:
    ListaArtistasRating(){
        this->primero = 0;
        this->ultimo = 0;
        this->size = 0;
    }
    
    NodoArtistaRating *getPrimero(){ return this->primero; }
    NodoArtistaRating *getUltimo(){ return this->ultimo; }
    int getSize(){ return this->size;}
    bool estaVacia(){ return this->size==0;}


    void insertar_alinicio(string name, double rating){
        ArtistaRating *a = new ArtistaRating(name, rating);
        NodoArtistaRating *n = new NodoArtistaRating(a);
        if(this->estaVacia()){
            this->primero = n;
            this->ultimo = n;
            this->size++;
        }else {
            n->setSiguiente(this->primero);
            this->primero = n;
            this->size++;
        }

    }


    void insertar_alfinal(string name, double rating){       
        if(this->estaVacia()){
            this->insertar_alinicio(name,rating);
        } else {
            ArtistaRating *a = new ArtistaRating(name,  rating);
            NodoArtistaRating *n = new NodoArtistaRating(a);
            this->ultimo->setSiguiente(n);
            this->ultimo = n;
            size++;
        }
    }

    void insertar_en(string name, double rating, int index){
        if(index>=0 && index<=this->size){
            if(index == 0){this->insertar_alinicio(name, rating);return;}
            if(index == this->size){this->insertar_alfinal(name, rating); return;}
            NodoArtistaRating *aux = this->primero;
            int x = 0;
            while(aux!=0){
                if(x == index-1){ break;}
                aux = aux->getSiguiente();
                x++;
            }
            ArtistaRating *a = new ArtistaRating(name, rating);
            NodoArtistaRating *n = new NodoArtistaRating(a);
            n->setSiguiente(aux->getSiguiente());
            aux->setSiguiente(n);
            this->size++;
        }
    }

    void insertar_ordenado(string name, double rating){
        if(this->estaVacia()){
            insertar_alinicio(name, rating); return;
        }
        int index = 0;
        NodoArtistaRating *aux = this->primero;
        while(aux!=0){
            if(rating>this->getPrimero()->getArtista()->getRating()){ index=0; break;} //Ingresa al inicio
            if(rating<this->getUltimo()->getArtista()->getRating()){index=size; break;} //Ingresa al final
            if(rating<=aux->getArtista()->getRating()){ index++;} //Busca la posición correcta
            if(rating>aux->getSiguiente()->getArtista()->getRating()){ break;} //valida si ya encontro la posición correcta
            aux = aux->getSiguiente();  
        }
        this->insertar_en(name, rating, index); //llama al metodo para insertar en el index indicado
    }


};